
/*
 * @document : perm.c
 * @date : 23 4 2003
 * @author : Naveen
 * @exports :
 *	go_finfo(fd , struct fnode *)
 *	go_chmod();  go_chown();
 */
#include "proto.h"
#include "global.h"
#include "passwd.h"

u8 go_finfo (u8 fd , struct fnode * fn ){
        *fn = open[fd].block.fadt.hc_fnode;
        return 1;
}

 u8 go_info (u8 * path , struct fnode * fn ){
        u32 lba;
        u8 fd;
        lba = eat_path(path);
        if (lba == NO_LBA){
                return 0;
        }
        fd = get_fnode(lba , FDD);
        if (fd == NO_OPEN){
                return 0;
        }
        if (go_finfo (fd , fn)){
                put_fnode(fd);
                return 1;
        }
        put_fnode(fd);
        return 0;
 }

 u8 go_chown(u8 * path ,u8 * newowner){
        u32 lba ;
        u8 bufr,fd ,i,ret;
        u8 olduser,newownerid;
        struct logininfo l[MAX_USER] ;
        lba = eat_path(path);
        if (lba == NO_LBA){
                return 0;
        }
        bufr=get_block(FDD,lba,NOT_ONLY_SEARCH);
        if (bufr == NO_BUF){
                return 0;
        }
        if (buf[bufr].data.fadt.hc_fnode.uid  != get_user() ){
                ERROR_NO=NOT_ENOUGH_PRIVILEGE ;
                handle_error();
                return 0;
        }
        olduser=USER_ID;
        USER_ID=0;
         fd=go_open((u8 *)"|passwd",O_RW);
    if (fd == NO_OPEN){
        put_block(bufr,NOT_FRONT);
        return 0;
    }
    ret=go_read(fd,(u8 *)l, MAX_USER * sizeof(struct logininfo));
    if (!ret){
        go_close(fd);
        put_block(bufr,NOT_FRONT);
        return 0;
    }
    for(i=0; i < MAX_USER && l[i].name[0]!=0 && strcmp(l[i].name,newowner) ; i++);
    if (i == MAX_USER  ||  l[i].name[0]== 0) {
        ERROR_NO=INVALID_USER;
        handle_error();
        go_close(fd);
        return 0;
    }
    newownerid= l[i].uid;
    USER_ID=olduser;
    go_close(fd);
        buf[bufr].data.fadt.hc_fnode.uid = newownerid;
        buf[bufr].status=DIRTY ;
        put_block(bufr,NOT_FRONT);
        return 1;
 }

u8 go_chperm(u8 * path ,u8 newperm){
        u32 lba ;
        u8 bufr ;
        lba = eat_path(path);
        if (lba == NO_LBA){
                return 0;
        }
        bufr=get_block(FDD,lba,NOT_ONLY_SEARCH);
        if (bufr == NO_BUF){
                return 0;
        }
        if (buf[bufr].data.fadt.hc_fnode.uid  != get_user() ){
                ERROR_NO=NOT_ENOUGH_PRIVILEGE ;
                handle_error();
                return 0;
        }
        buf[bufr].data.fadt.hc_fnode.mode =( u8 )( (buf[bufr].data.fadt.hc_fnode.mode & (3<<6) ) | (newperm & 63 ) );
        buf[bufr].status=DIRTY ;
        put_block(bufr,NOT_FRONT);
        return 1;
 }

 void go_fl_clean(){
    u8 i;
    for(i=0; i < CT_OPEN_FILE ; i++){
        open[i].used=NOT_IN_USE ;
    }
 }
 