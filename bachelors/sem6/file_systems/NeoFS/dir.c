/*
 * @document : dir.c
 * @date : 23 4 2003
 * @author : Naveen
 * @exports :   go_opendir() go_closedir() go_readdir()
 *              go_seekdir() go_rewinddir()
 */
#include "proto.h"
#include "open.h"
#include "global.h"
/**
    Opens a directory file  provided enough privilege is present
**/
u8 go_opendir(u8 * path){
    u32 lba;
    u8 fd;
    lba = eat_path(path);
    if (lba == NO_LBA){
            return NO_OPEN;
    }
    fd = get_fnode(lba , FDD);
    if (fd == NO_OPEN){
            return NO_OPEN;
    }
    if ( !( open[fd].block.fadr.hc_fnode.mode & DIRECTORY) ){
            ERROR_NO=NOT_DIR;
            put_fnode(fd);
            handle_error();
            return NO_OPEN;
    }
        if ( open[fd].block.fadt.hc_fnode.uid == get_user()){
                if (! (OWNER_READ & open[fd].block.fadt.hc_fnode.mode)){
                        put_fnode(fd);
                        ERROR_NO=NOT_ENOUGH_PRIVILEGE;
                        handle_error();
                        return NO_OPEN;
                }
        }else{
                if (! (OTHER_READ & open[fd].block.fadt.hc_fnode.mode)){
                        put_fnode(fd);
                        ERROR_NO=NOT_ENOUGH_PRIVILEGE ;
                        handle_error();
                        return NO_OPEN;
                }
        }

    return fd;
}

u8 go_closedir(u8 fd){
        if (fd >= NO_OPEN){
                ERROR_NO=NOT_DIR;
                handle_error();
                return 0;
        }
        put_fnode(fd);
		return 1;
}

u8 go_seekdir(u8 fd , u8 whence , u8 offset){
    u8 pos ;
    if ( !( open[fd].block.fadr.hc_fnode.mode & DIRECTORY) ){
        ERROR_NO=NOT_DIR;
        handle_error();
        return 0;
    }
    switch (whence) {
        case 0 : pos=0;
                        break;
        case 1:  pos =open[fd].file_pos;
                        break;
        case 2:  pos=open[fd].block.fadr.hc_fnode.ct_links+1;
                    /* point to the last element because, beyond first
                       element makes no sense in read*/
                        break;
        default : ERROR_NO = INVALID;
                  handle_error();
                   return 0;
    }
    if ( pos+offset < pos){    /*overflow can cause this*/
            ERROR_NO=INVALID;
            handle_error();
            return 0;
    }
    pos = pos + offset;
    if ( pos > open[fd].block.fadr.hc_fnode.ct_links+1 ){ 
            /*ct_links does not keep count of . and .. directory*/
            ERROR_NO=SEEK_WACKY;
            handle_error();
            return 0;
    }
    open[fd].file_pos = pos;
    return 1;
}


u8 go_rewinddir ( u8 fd){
    if ( !( open[fd].block.fadr.hc_fnode.mode & DIRECTORY) ){
         ERROR_NO=NOT_DIR;
         handle_error();
         return 0;
     }
     open[fd].file_pos = 0;
         return 1;
 }

/**
     from the directory fd , reads the count number of directory entries 
     into the dir_str structure dir array, out of bound is memory management
     problem-- watch out shenoy
**/
 u8 go_readdir (u8 fd , u8 count , struct dir_str dir[] ){
    u8 k=0,bufr,p=0,pos,j;
    if ( !( open[fd].block.fadr.hc_fnode.mode & DIRECTORY) ){
        ERROR_NO=NOT_DIR;
        handle_error();
        return 0;
    }
    if ( count + open[fd].file_pos  > 
            open[fd].block.fadr.hc_fnode.ct_links + (u32)2){ 
        /*because ct_links do not consider the . and .. directories*/
        ERROR_NO = READ_FRENZY;
        handle_error();
        return 0;
    }
    if (open[fd].file_pos < CT_DIR_FNODE){ /*starts in fnode block itself*/
        j=0;
        pos=open[fd].file_pos ;
        while (pos + j <  CT_DIR_FNODE && k < count){
            dir[k++] = open[fd].block.fadr.dir[pos + j++];
        }
        if (k == count)
            return 1;
        while ( p <= 1 ){  
            /*k != count, then as long as index goes read and copy*/
            bufr=get_block( FDD ,  open[fd].block.fadr.hc_fnode.index[p++],
                            NOT_ONLY_SEARCH);
            if (bufr == NO_BUF)
                return 0;
            j=0;
            while (j <  CT_DIR_NO_FNODE && k < count){
                dir[k++] = open[fd].block.fadr.dir[j++];
            }
            if (k == count)
                return 0;
            put_block(bufr,NOT_FRONT);
        }
        return 0;
    }
    pos = open[fd].file_pos ;
    if ( pos < CT_DIR_FNODE + CT_DIR_NO_FNODE){
        p=0;
        pos=count - CT_DIR_FNODE;
    }else{
        p=1;
        pos = count - CT_DIR_FNODE - CT_DIR_NO_FNODE;
    }
    while ( p <= 1 ){ 
        /*k != count, then as long as index goes read and copy*/
        bufr=get_block( FDD ,  open[fd].block.fadr.hc_fnode.index[p++] ,
                        NOT_ONLY_SEARCH);
        if (bufr == NO_BUF)
            return 0;
        j=0;
        while (pos + j <  CT_DIR_NO_FNODE && k < count){
            dir[k++] = open[fd].block.fadr.dir[pos + j++];
        }
        if (k == count)
            return 0;
        put_block(bufr,NOT_FRONT);
        pos=0;
    }
        return 1;
 }

 
u8 go_removedir(u8* path){
    u32 pdlba,lba;
    u8 string [MAX_NAME],bufr;
    lba = eat_path(path);
    if (lba == NO_LBA){
        return 0;
    }
    bufr = get_block(FDD , lba , NOT_ONLY_SEARCH);
    if (bufr == NO_BUF){
        return 0;
    }
    if( ! (buf[bufr].data.fadr.hc_fnode.mode & DIRECTORY) ){
        ERROR_NO=NOT_DIR;
        put_block(bufr, NOT_FRONT);
        handle_error();
        return 0;
    }
    if (buf[bufr].data.fadr.hc_fnode.ct_links){
        ERROR_NO=DIR_GRAVID;
        put_block(bufr, NOT_FRONT);
        handle_error();
        return 0;
    }
    put_block(bufr , NOT_FRONT);
    pdlba = last_dir(path , string);
    if (search_dir ( pdlba , string , &lba ,DELETE) ){
        free_node (lba ,FDD);
        return 1;
    }
    return 0;
}        
