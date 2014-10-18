
/*
 * @document : link.c
 * @date : 23 4 2003
 * @author : Naveen
 * @exports : go_link(); go_unlink(); go_rename();
 */
#include "proto.h"
#include "global.h"

u8 go_link(u8 * original_fl  ,  u8  *  link_fl , u8 dev ){
        u32 oflba , lfplba;
        u8 string[MAX_NAME];
        u8 bufr,ret;
        oflba=eat_path(original_fl);
        if ( oflba == NO_LBA){
        	if (!ERROR_NO){
            	ERROR_NO = NOT_A_FILE;
            	handle_error();
            }
            return 0;
        }
        lfplba = last_dir( link_fl , string);
        if ( lfplba == NO_LBA){
            ERROR_NO = NO_DIR_FILE;
            handle_error();
            return 0;
        }
        bufr = get_block (dev , oflba , NOT_ONLY_SEARCH ) ;
       if ( buf[bufr].data.fadt.hc_fnode.ct_links >= 255){
            put_block(bufr,NOT_FRONT);
            ERROR_NO = LINK_OVERFLOW;
            handle_error();
            return 0;
       }else{
                 ret =search_dir(lfplba , string , &oflba , ENTER);
                if (ret) {
                        buf[bufr].data.fadt.hc_fnode.ct_links++;
                        buf[bufr].status=DIRTY;
                        put_block (bufr , NOT_FRONT);
                        return 1;
                 }
       }
        put_block (bufr , NOT_FRONT);
        return 0;
}

u8 go_unlink (u8 * path){
        u32 pdlba,lba;
        u8 string [MAX_NAME];
        u8 fd,ret;

        lba = eat_path(path);
        fd = get_fnode (lba ,FDD);
        if ( ! IS_ORD_FILE(open[fd].block.fadt.hc_fnode.mode) ){
            put_fnode(fd);
            ERROR_NO = NOT_A_FILE;
            handle_error();
            return 0;
        }
       /* if (open[fd].block.fadt.hc_fnode.uid != get_user()){
            put_fnode(fd);
            ERROR_NO = NOT_ENOUGH_PRIVILEGE;
            handle_error();
            return 0;
        }*/
        pdlba = last_dir (path, string ) ;
        ret = search_dir ( pdlba , string , & lba , DELETE);
        if (!ret){
                put_fnode(fd);
                return 0;
        }
        open[fd].block.fadt.hc_fnode.ct_links--;
        open[fd].f_status=DIRTY;
        if (open[fd].block.fadt.hc_fnode.ct_links == 0){
            truncate(fd);
            free_node(lba,FDD) ;
            clean_fnode(lba);
            clean_buffer(lba);
            return 1;
        }
        put_fnode(fd);
        return 1;
}

u8 go_rename (u8 * orgi  , u8  ren[MAX_NAME] ){
    /*the first name is given with complete path, while the second
	 * one is just replacement*/
    u32 plba,lba;
    u8 string[MAX_NAME];
    u8 bufr,rec_no;
    plba = last_dir (orgi,string);
    if (plba == NO_LBA){
        return 0;
    }
    rec_no = search_dir(plba , string , &lba , LOOK_UP ) ;
    if ( lba == NO_LBA){
    	if(!ERROR_NO){
        	ERROR_NO = NO_DIR_FILE;
        	handle_error();
        }
        return 0;
    }
    search_dir(plba , ren, &lba , LOOK_UP ) ;
    if (  lba  !=  NO_LBA){
        ERROR_NO = ALREADY_PRESENT;
        handle_error();
        return 0;
    }

    bufr = get_block(FDD , plba , NOT_ONLY_SEARCH);
    if (bufr == NO_BUF)
        return 0;
    if (buf[bufr].data.fadr.hc_fnode.uid == get_user()){
        if (! (buf[bufr].data.fadr.hc_fnode.mode & OWNER_WRITE) ) {
                ERROR_NO=NOT_ENOUGH_PRIVILEGE;
                handle_error();
                put_block(bufr,NOT_FRONT);
                return 0;
        }
    }else{
        if (! (buf[bufr].data.fadr.hc_fnode.mode & OTHER_WRITE) ) {
                ERROR_NO=NOT_ENOUGH_PRIVILEGE;
                handle_error();
                put_block(bufr,NOT_FRONT);
                return 0;
        }

    }
    if ( rec_no < CT_DIR_FNODE){
        strcpy ((char *) buf[bufr].data.fadr.dir[rec_no].name ,(char*) ren );
        buf[bufr].data.fadr.dir[rec_no].hash = hash(ren);
        buf[bufr].status=DIRTY;
        put_block(bufr , NOT_FRONT);
        return 1;
    }else if ( rec_no < (CT_DIR_FNODE+ CT_DIR_NO_FNODE)){
        lba = buf[bufr].data.fadr.hc_fnode.index[0];
        put_block(bufr,NOT_FRONT);
        bufr=get_block( FDD , lba , NOT_ONLY_SEARCH);
        if (bufr == NO_BUF)
            return 0;
        strcpy ((char *)buf[bufr].data.fadr.dir[rec_no - CT_DIR_FNODE].name , (char *)ren );
        buf[bufr].data.fadr.dir[rec_no - CT_DIR_FNODE].hash = hash(ren);
        buf[bufr].status=DIRTY;
        put_block(bufr,FRONT);
        return 1;
    }else {
        lba = buf[bufr].data.fadr.hc_fnode.index[1];
        put_block(bufr,NOT_FRONT);
        bufr=get_block( FDD , lba , NOT_ONLY_SEARCH);
        if (bufr == NO_BUF)
            return 0;
        strcpy(
	       (char * )buf[bufr].data.fadr.dir[rec_no-CT_DIR_FNODE-CT_DIR_NO_FNODE].name,
		   (char * )ren
		);
        buf[bufr].data.fadr.dir[rec_no - CT_DIR_FNODE - CT_DIR_NO_FNODE].hash
			= hash(ren);
        buf[bufr].status=DIRTY;
        put_block(bufr, NOT_FRONT);
        return 1;
    }
}
