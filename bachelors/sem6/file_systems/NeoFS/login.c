#include "string.h"
#include "proto.h"
#include "passwd.h"
#include "global.h"


/**
before calling this file system it is necessary that the file system is loaded
else the call is expected to give an error
**/
u8 go_login(u8 * username, u8 * password){
    u8 fd;
    u8 i,ret;
    struct logininfo l[MAX_USER] ;
    USER_ID=0;
    fd=go_open((u8 *)"|passwd",O_READ);
    if (fd == NO_OPEN)
        return 0;
    ret=go_read(fd,(u8 *)l, MAX_USER * sizeof(struct logininfo));
    if (!ret){
        go_close(fd);
        return 0;
    }
    for(i=0; i < MAX_USER && l[i].name[0]!=0 && strcmp(l[i].name,username) ; i++);
    if(i == MAX_USER  ||  l[i].name[0]==0){
        ERROR_NO = BAD_USER_OR_PASSWORD;
        handle_error();
        go_close(fd);
        return 0;
    }
    if ( strcmp(l[i].password,password) ){
        ERROR_NO = BAD_USER_OR_PASSWORD;
        handle_error();
        go_close(fd);
        return 0;
    }
    USER_ID=l[i].uid;
    go_close(fd);
    return 1;
}



u8 go_adduser(u8 * username, u8 * password){
    u8 fd,fd1;
    u8 i;
    u32 ret;
    u8 dirname[MAX_NAME+1]; /*for creating the user home directory*/
    struct logininfo l[MAX_USER] ;
    if (USER_ID != 0){
        ERROR_NO=NOT_ENOUGH_PRIVILEGE;
        handle_error();
        return 0;
    }
    fd=go_open((u8 *)"|passwd",O_RW);
    if (fd == NO_OPEN)
        return 0;
    ret=go_read(fd,(u8 *)l, MAX_USER * sizeof(struct logininfo));
    if (!ret){
        go_close(fd);
        return 0;
    }
    for(i=1; i < MAX_USER && l[i].name[0]!=0 && strcmp(l[i].name,username) ; i++);
    if (i == MAX_USER) {
        ERROR_NO=USER_OVERFLOW ;
        handle_error();
        go_close(fd);
        return 0;
    }
    if (!strcmp(l[i].name , username)){
        ERROR_NO=DUPLICATE_USER;
        handle_error();
        go_close(fd);
        return 0;
    }
    if(l[i].name[0]== 0){
            strcpy(l[i].name, username);
            strcpy(l[i].password,password);
            l[i].uid=i;
            

            dirname[0]=(u8 )'|' ;
            dirname[1]=0;
            strcat(dirname,username);
            ret = go_mkdir(dirname,064);
            if (ret ==  NO_LBA){
                go_close(fd);
                return 0;
            }
            fd1 = go_opendir(dirname);
            open[fd1].block.fadr.hc_fnode.uid=i;
            open[fd1].f_status=DIRTY;

            go_lseek(fd,0,SEEK_BEG);
            ret = go_write(fd,(u8 *)l ,MAX_USER * sizeof(struct logininfo));
            open[fd].f_status=DIRTY ;
            if (!ret) {
                go_close(fd);
                go_close(fd1);
                go_unlink(dirname);
                return 0;
            }
            go_closedir(fd1);
            go_close(fd);
            return 1;
    }
    go_close(fd1);
    go_close(fd);
    return 0;
}


u8 go_geterror(){
        return ERROR_NO;
}