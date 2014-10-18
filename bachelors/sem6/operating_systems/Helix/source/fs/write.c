/*
 * @document : write.c
 * @date : 23 4 2003
 * @author : Naveen
 * @exports : 
	u8 write(fd , u8 * src, u32 count );
 */	

#include "proto.h"
#include "global.h"
#include "read.h"

u8 go_write(u8 fd , u8 * src , u32 count){
    struct rw val;
    u32 fn,dr,fi,fidr,si,sifi,sifidr,pos ;
    u8 bufr,bufr2,buf3;
    u32 j,k=0;
    u8 sem_dr=0, sem_fidr=0 , sem_sifidr=0 ; 
    /*semaphores to indicate whether it is the entry point*/ 
    fn = dr = fi = fidr = si = sifidr = pos =0;
    if ( !IS_ORD_FILE(open[fd].block.fadt.hc_fnode.mode)){
        ERROR_NO=NOT_A_FILE;
        handle_error();
        return 0;
    }
        if (! (open[fd].mode & O_WRITE)) {
                ERROR_NO= NOT_WRITE;
                handle_error();
                return 0;
        }

   if ( open[fd].file_pos  > open[fd].block.fadt.hc_fnode.size+1){
        ERROR_NO=READ_FRENZY;
        handle_error();
        return 0;
    }
    if(  ! read_map( &val , open[fd].file_pos) ){
        ERROR_NO=INVALID;
        handle_error();
        return 0;
    }
    fn = val.fn  ; dr=val.dr;      fi = val.fi;/*setting values as returned by structure*/
    fidr = val.fidr ;  si = val.si ; sifi = val.sifi ;
    sifidr = val.sifidr ;  pos = val.pos  ;
    if (! fn){
        /*when read starts from fnode block itself , fn is 1 if does not*/
        j=0;
        while ( k < count && pos+j < (BLOCK_SIZE -  FNODE_SIZE)){
            open[fd].block.fadt.data[pos+j++] = src[k++];
            open[fd].f_status=DIRTY;
        }
        if ( k == count ){
            open[fd].block.fadt.hc_fnode.size = open[fd].file_pos+count ;
            open[fd].file_pos+=count;
            return 1;
        }
        sem_dr=1;       /*semaphore saying to set for dirsct index pos to 0, 
                          sinco original pos  has already been handled*/
    }
    for (; dr < CT_DIRECT_IDX; dr++){
        /*reading when starts from direct indexes*/
        if (sem_dr){
                pos=0;
        }
        j=0;
        if (open[fd].block.fadt.hc_fnode.index[dr]  == NO_LBA){
             open[fd].block.fadt.hc_fnode.index[dr] = alloc_node(FDD);
             open[fd].f_status=DIRTY;
        }
        bufr = get_block (FDD,open[fd].block.fadt.hc_fnode.index[dr],NOT_ONLY_SEARCH) ;
        if (bufr == NO_BUF){
             return 0;
        }
        while ( k < count   &&  pos+j < BLOCK_SIZE ){
             buf[bufr].data.data.data[pos + j++] = src[k++];
             buf[bufr].status=DIRTY;
        }
        if ( k == count ){
             put_block(bufr , NOT_FRONT) ;
             open[fd].block.fadt.hc_fnode.size=open[fd].file_pos+count ;
             open[fd].file_pos+=count;
             return 1;
        }
        sem_dr=1;
        sem_fidr=1;
        put_block(bufr , NOT_FRONT) ;
    }

    for (;fi < CT_FIRST_IDX ; fi++ ){   /*when pos comes in first indirect index*/
        if (open[fd].block.fadt.hc_fnode.index[CT_DIRECT_IDX+fi] == NO_LBA){
                open[fd].block.fadt.hc_fnode.index[CT_DIRECT_IDX+fi] = alloc_node(FDD);
                open[fd].f_status=DIRTY;
        }
        bufr2 = get_block (FDD , open[fd].block.fadt.hc_fnode.index[CT_DIRECT_IDX+fi] , NOT_ONLY_SEARCH) ;
        if (bufr2 == NO_BUF){
                return 0;
        }
        for (; fidr < (BLOCK_SIZE/LBA_SIZE); fidr++){  /*direct indexes within first indirect indexes*/
            if (sem_fidr){
               pos=0;
            }
            j=0;
            if ( buf[bufr2].data.fib.lba[fidr] == NO_LBA){
                buf[bufr2].data.fib.lba[fidr]=alloc_node(FDD);
                buf[bufr2].status=DIRTY;
            }
            bufr = get_block (FDD , buf[bufr2].data.fib.lba[fidr] , NOT_ONLY_SEARCH) ;
            if (bufr == NO_BUF){
                put_block(bufr2 , NOT_FRONT);
                return 0;
            }
            while ( k < count   &&  pos+j < BLOCK_SIZE ){
                buf[bufr].data.data.data[pos + j++] = src[k++];
                buf[bufr].status=DIRTY;
            }
            if ( k == count ){
                put_block(bufr , NOT_FRONT) ;
                put_block(bufr2 , NOT_FRONT) ;
                open[fd].block.fadt.hc_fnode.size=open[fd].file_pos+count ;
                open[fd].file_pos+=count;
                return 1;
            }
            sem_fidr=1;
            put_block(bufr , NOT_FRONT) ;
        }
        put_block(bufr2 , NOT_FRONT);
        sem_sifidr=1;
    }

    for (;si < CT_SECOND_IDX ;si++ ){
        if (open[fd].block.fadt.hc_fnode.index[CT_DIRECT_IDX + CT_FIRST_IDX + si]  == NO_LBA){
            open[fd].block.fadt.hc_fnode.index[CT_DIRECT_IDX + CT_FIRST_IDX + si] =alloc_node(FDD);
            open[fd].f_status=DIRTY;
        }
        buf3 = get_block(FDD , open[fd].block.fadt.hc_fnode.index[CT_DIRECT_IDX + CT_FIRST_IDX + si] , NOT_ONLY_SEARCH);
        for (;sifi < (BLOCK_SIZE / LBA_SIZE ) ; sifi++ ){   /*when pos comes in first indirect index*/
           if (buf[buf3].data.fib.lba[sifi]  == NO_LBA){
               buf[buf3].data.fib.lba[sifi] =alloc_node(FDD);
               buf[buf3].status=DIRTY;
           }
           bufr2 = get_block (FDD , buf[buf3].data.fib.lba[sifi] , NOT_ONLY_SEARCH) ;
           if (bufr2 == NO_BUF){
               put_block(buf3 , NOT_FRONT);
               return 0;
           }
        
           for (; sifidr < (BLOCK_SIZE/LBA_SIZE); sifidr++){  /*direct indexes within first indirect indexes*/
              if (sem_sifidr){
                  pos=0;
              }
              j=0;
              if ( buf[bufr2].data.fib.lba[fidr] == NO_LBA){
                  buf[bufr2].data.fib.lba[fidr]=alloc_node(FDD);
                  buf[bufr2].status=DIRTY;
              }
              bufr = get_block (FDD , buf[bufr2].data.fib.lba[fidr] , NOT_ONLY_SEARCH) ;
              if (bufr == NO_BUF){
                  put_block(buf3 , NOT_FRONT) ;
                  put_block(bufr2 , NOT_FRONT);
                  return 0;
              }
              while ( k < count   &&  pos+j < BLOCK_SIZE ){
                  buf[bufr].data.data.data[pos + j++] =src[k++];
                  buf[bufr].status=DIRTY;
              }
              if ( k == count ){
                  put_block(bufr , NOT_FRONT) ;
                  put_block(bufr2 , NOT_FRONT) ;
                  put_block(buf3 , NOT_FRONT) ;
                  open[fd].block.fadt.hc_fnode.size=open[fd].file_pos+count ;
                  open[fd].file_pos+=count;
                  return 1;
              }      
              sem_sifidr=1;
              put_block(bufr , NOT_FRONT) ;
           }
           put_block(bufr2 , NOT_FRONT);
        }
        put_block(bufr2, NOT_FRONT);
    }
    return 0;
}
/*************************************************************************/
/*************************************************************************/


