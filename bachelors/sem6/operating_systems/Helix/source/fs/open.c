/*
 * @document : init.c
 * @date : 23 4 2003
 * @author : Naveen
 * @exports :
	go_mkdir() go_creat() go_open() go_close() go_lseek() new_node()
	truncate(fd) is an entry point to be used by unlink

	latest change go_creat
 */
#include "proto.h"
#include "global.h"

u32 new_node( u8  *  path){
	/* This is a support routine, this creates a file in this path,
	 * adds entry to directory file, update it's ct_links.mkdir and
	 * creat calls can first use this and then write the fnode structure
	 * the way they want */
	u32 lba,dlba,slba;
    u8 string[MAX_NAME];
    dlba = last_dir(path,string);
    if(dlba ==  NO_LBA)
          return dlba;
    search_dir(dlba , string , &slba , LOOK_UP );
    if(slba  !=  NO_LBA){
         ERROR_NO=ALREADY_PRESENT;
         handle_error();
         return NO_LBA;
    }
    lba=alloc_bit(FDD);
    if(lba == NO_LBA)
		return lba;
    if  (  search_dir(dlba , string , &lba ,  ENTER  ) )
	    return lba;
    else
		return NO_LBA;
}

u32  go_creat( u8 * path, u8 mode){
        u32 lba;
        u8 bufr,i;
        lba=new_node(path);
        if(lba  ==  NO_LBA)
                return NO_LBA;
        bufr = get_block(FDD  ,  lba ,  ONLY_SEARCH);
        if(bufr  ==  NO_BUF)
                return NO_LBA;
        buf[bufr].data.fadt.hc_fnode.uid=get_user();
        buf[bufr].data.fadt.hc_fnode.c_time=get_time();
        buf[bufr].data.fadt.hc_fnode.size=0;
        buf[bufr].data.fadt.hc_fnode.m_time=get_time();
        buf[bufr].data.fadt.hc_fnode.ct_links=1;
        buf[bufr].data.fadt.hc_fnode.mode = (ORD_FILE | (mode & 63));
        /*63 is lower 6 bits 1 , so mode passed on copied*/
        for(i=0; i < CT_TOTAL_IDX; i++)
                buf[bufr].data.fadt.hc_fnode.index[i] = NO_LBA;
	buf[bufr].status=DIRTY;
        put_block(bufr, FRONT);
        return lba;
}


u32 go_mkdir(u8 * path , u8 mode){
        u32 lba,plba;
        u8 bufr,i;
        u8 string[MAX_NAME] ;
        lba=new_node(path);
        if(lba  ==  NO_LBA)
                return NO_LBA;
        plba=last_dir(path, string);
        bufr = get_block(FDD  ,  lba ,  ONLY_SEARCH);
        if(bufr  ==  NO_BUF)
                return NO_LBA;
        buf[bufr].data.fadr.hc_fnode.uid=get_user();
        buf[bufr].data.fadr.hc_fnode.c_time=get_time();
        buf[bufr].data.fadr.hc_fnode.size=0;
        buf[bufr].data.fadr.hc_fnode.m_time=get_time();
        buf[bufr].data.fadr.hc_fnode.ct_links=0;
        buf[bufr].data.fadr.hc_fnode.mode = (DIRECTORY | (mode & 63)) ;
        /*63 is lower 6 bits 1 , so mode passed on copied*/
        for(i=0; i < CT_TOTAL_IDX; i++)
                buf[bufr].data.fadr.hc_fnode.index[i] = NO_LBA;

        strcpy( (char *)buf[bufr].data.fadr.dir[0].name ,(char *) dot1 );  /*handling the . directory*/
        buf[bufr].data.fadr.dir[0].hash = hash(dot1);      /*hard coded for .  and .. as 0*/
        buf[bufr].data.fadr.dir[0].lba=lba;

        strcpy((char *) buf[bufr].data.fadr.dir[1].name ,(char *)dot2 );  /*handling the .. directory*/
        buf[bufr].data.fadr.dir[1].hash = hash(dot2);      /*hard coded for .  and .. as 0*/
        buf[bufr].data.fadr.dir[1].lba=plba;
 	buf[bufr].status = DIRTY;
        put_block(bufr, NOT_FRONT);
        return lba;
}


u8 go_open( u8 * path , u8 mode){
    /*opens the file , puts in file table with basic open modes
      if trunc or creat or append is given acts suatably*/
    u32 lba;
	u8 fd;
    if((mode &  O_CREAT) && (mode & O_WRITE)) /*if creat used then write should be enbled*/
        lba=go_creat(path , 064);
    else
        lba=eat_path(path);
    if (lba == NO_LBA){
        return NO_OPEN;
    }
    fd = get_fnode(lba , FDD);
    if (fd == NO_OPEN)
            return NO_OPEN;
    open[fd].mode = mode  &  O_ACCMODE ;
    if (! IS_ORD_FILE(open[fd].block.fadt.hc_fnode.mode) ) {
       put_fnode(fd);
       if(!ERROR_NO){
       		ERROR_NO=NOT_A_FILE;
	       handle_error();
	   }
       return NO_OPEN;
    }
   if (open[fd].mode & O_WRITE) {

        if ( open[fd].block.fadt.hc_fnode.uid == get_user()){
                         if (! (OWNER_WRITE & open[fd].block.fadt.hc_fnode.mode)){
                                ERROR_NO=NOT_ENOUGH_PRIVILEGE;
                                handle_error();
                                put_fnode(fd);
                                return NO_OPEN;
                        }
        }else{
                        if (! (OTHER_WRITE & open[fd].block.fadt.hc_fnode.mode)){
                                ERROR_NO=NOT_ENOUGH_PRIVILEGE ;
                                handle_error();
                                put_fnode(fd);
                                return NO_OPEN;
                        }
        }
   }

   if (open[fd].mode & O_READ) {

        if ( open[fd].block.fadt.hc_fnode.uid == get_user()){
                         if (! (OWNER_READ & open[fd].block.fadt.hc_fnode.mode)){
                                ERROR_NO=NOT_ENOUGH_PRIVILEGE;
                                handle_error();
                                put_fnode(fd);
                                return NO_OPEN;
                        }
        }else{
                        if (! (OTHER_READ & open[fd].block.fadt.hc_fnode.mode)){
                                ERROR_NO=NOT_ENOUGH_PRIVILEGE ;
                                handle_error();
                                put_fnode(fd);
                                return NO_OPEN;
                        }
        }
   }

    open[fd].file_pos=0;
    if ( (mode  &  O_TRUNC) && (mode & O_WRITE))
        truncate (fd);
    if ( (mode  &  O_APPEND) && (mode & O_WRITE)){
        open[fd].file_pos= open[fd].block.fadt.hc_fnode.size;
    }
    /*put_fnode (fd);   not done here , but in close function*/
    return fd;
}

/* prototypes given here because thay are not in proto.h as they
 * are not entry points to this file*/
void clear_first_indirect(u32 count ,  u32 array[]);
void clear_second_indirect(u32 count , u32 array[]);
void clear_direct ( u32 count , u32 array[]);


u8 truncate (u8 fd){
    u32 size;
    if(!IS_ORD_FILE(open[fd].block.fadt.hc_fnode.mode)){
        ERROR_NO = NOT_A_FILE;
        handle_error();
        return 0;
    }
    size = open[fd].block.fadt.hc_fnode.size;
    if ( size > (BLOCK_SIZE - FNODE_SIZE )){
        clear_direct( CT_DIRECT_IDX , & open[fd].block.fadt.hc_fnode.index[0] );
        size -= (BLOCK_SIZE - FNODE_SIZE ) ;
        if ( size   >= CT_DIRECT_IDX  *  BLOCK_SIZE   ){
            clear_first_indirect( CT_FIRST_IDX , &open[fd].block.fadt.hc_fnode.index[CT_DIRECT_IDX]); /*if file extends beyond fnode block and direct indexes, this is called*/
            size   -=  ( CT_DIRECT_IDX  *  BLOCK_SIZE  );
            if (size   >   CT_FIRST_IDX * (BLOCK_SIZE / LBA_SIZE) * BLOCK_SIZE )
                   clear_second_indirect( CT_SECOND_IDX , &open[fd].block.fadt.hc_fnode.index[CT_DIRECT_IDX]); /* direct index effect is removed, now if size is greater that */
        }
    }
    open[fd].block.fadt.hc_fnode.size=0;
    open[fd].f_status = DIRTY;
    open[fd].file_pos  = 0;
    return 1;
}


void clear_first_indirect(u32 count ,  u32 array[]){
    u32 i,j;
    u8 bufr;
    for (i=0;i < count ;i++ ){
        /*clear all first level indexes, and thigs pointed to by them*/
        if ( array[ i ]   !=  NO_LBA){
            bufr = get_block( FDD , array[i ] ,  NOT_ONLY_SEARCH);
            if ( bufr ==  NO_BUF){
                return ;
            }
            for ( j=0 ; j < (BLOCK_SIZE /  LBA_SIZE) ; j++ ){
                if ( buf[bufr].data.fib.lba[j] !=  NO_LBA )
                    free_node(buf[bufr].data.fib.lba[j],FDD);
                 buf[bufr].data.fib.lba[j] = NO_LBA;
                 buf[bufr].status=DIRTY;
            }
            put_block(bufr , FRONT);
            free_node(array[i],FDD) ;
            array[i] = NO_LBA;
        }
    }
}

void clear_second_indirect(u32 count , u32 array[]){
    u32 i ;
    u8 bufr ;
    for (i=0;i < count ; i++ ){
        if ( array[i] !=  NO_LBA ){
            bufr = get_block( FDD , array[i] , NOT_ONLY_SEARCH) ;
            if ( bufr ==  NO_BUF){
                 return ;
            }
            clear_first_indirect(  (BLOCK_SIZE/ LBA_SIZE)  ,  buf[bufr].data.fib.lba ) ;
            put_block ( bufr , FRONT);
            free_node (array [i],FDD);
            array[i] = NO_LBA;
        }
    }
}

void clear_direct ( u32 count , u32 array[]) {
    u32 j;
    for ( j=0 ; j < count ; j++ ){
        if ( array[j] !=  NO_LBA )
            free_node(array[j],FDD) ;
        array[j] = NO_LBA;
    }
}


u8 go_close (u8 fd){
    put_fnode(fd);
    knock_out(FDD);
    all_out (FDD);
    return 1;
}


u8 go_lseek(u8 fd,  u32 offset ,u8 whence ){
    u32 pos;
    if ( ! IS_ORD_FILE(open[fd].block.fadt.hc_fnode.mode) ){
        ERROR_NO=NOT_A_FILE;
        handle_error();
        return 0;
    }
    switch (whence) {
        case 0 : pos=0;
                        break;
        case 1:  pos =open[fd].file_pos;
                        break;
        case 2:  pos=open[fd].block.fadt.hc_fnode.size;
                        break;
        default : ERROR_NO = INVALID;
                        handle_error();
                        return 0;
    }
    if ( offset > 0   &&  pos+offset < pos){    /*overflow can cause this*/
        ERROR_NO=INVALID;
        handle_error();
        return 0;
    }
    pos = pos + offset;
    if ( pos > open[fd].block.fadt.hc_fnode.size ){
        ERROR_NO=SEEK_WACKY;
        handle_error();
        return 0;
    }
    open[fd].file_pos = pos;
    return 1;
}

