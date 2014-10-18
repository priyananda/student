
/*
 * @document : init.c
 * @date : 23 4 2003
 * @author : Naveen
 * @exports :
        read_map();
        go_read();
*/
#include "proto.h"
#include "global.h"
#include "read.h"

/**   takes file_pos , and rw structure pointer, then fills
	 * rw structure based on pos **/
u8 read_map (struct rw * rw , u32 file_pos ) {
	    u32 pos = file_pos ;
    u32 quotient ,  rem ;
    (*rw).fn = rw->dr = rw->fi = rw->fidr = 0;
    rw->si = rw->sifi = rw->sifidr = rw->pos =0;
    if (pos < (BLOCK_SIZE - FNODE_SIZE)){
				/* it is < not <= because it varies from 0 to (B-F-1)*/
                rw->pos = pos;
                return 1;      /*in fnode block*/
    }
    (*rw).fn=1;
	/*saying that pos is beyond fnode block and should be bypassed
	 * in read or write*/
    pos  -= (BLOCK_SIZE - FNODE_SIZE);
    quotient = pos / BLOCK_SIZE ; /*determining direct block*/
    if (quotient <  CT_DIRECT_IDX  ){
         (*rw).dr = quotient;
         (*rw).pos = pos - quotient*BLOCK_SIZE ;
         return 1;
    }
    (*rw).dr=CT_DIRECT_IDX;      /*not in direct block*/
    pos = pos - CT_DIRECT_IDX * BLOCK_SIZE;

        quotient = pos / ((BLOCK_SIZE/LBA_SIZE)* BLOCK_SIZE);
		/*first indirect*/
        if (quotient < CT_FIRST_IDX){
                (*rw).fi=quotient;
                rem=pos%((BLOCK_SIZE/LBA_SIZE)* BLOCK_SIZE);
                {
                        u32 q1 = rem / BLOCK_SIZE;
                        (*rw).fidr=q1;
                        (*rw).pos= rem - q1*BLOCK_SIZE ;
                        return 1;
                }
        }

        (*rw).fi=CT_FIRST_IDX;  /*not here*/
        (*rw).fidr=(BLOCK_SIZE/LBA_SIZE);
        pos -= ( CT_FIRST_IDX * (BLOCK_SIZE / LBA_SIZE) * BLOCK_SIZE );
        quotient = (u32)( (u64)pos / (u64)( (u32) BLOCK_SIZE * (BLOCK_SIZE / LBA_SIZE) * (BLOCK_SIZE / LBA_SIZE)  ) );

        if (quotient >= CT_SECOND_IDX){   /*this has to fail because , before calling this function, the file_pos is checked against size*/
                ERROR_NO=SCRAP_CODE;
                handle_error();
                return 0;
        }

        (*rw).si = quotient;
		rem = (u32)( (u64)pos% (u64)( (u32) BLOCK_SIZE * (BLOCK_SIZE / LBA_SIZE) * (BLOCK_SIZE / LBA_SIZE)  ) );
//        rem = (pos % ( (BLOCK_SIZE / LBA_SIZE) * (BLOCK_SIZE / LBA_SIZE) * BLOCK_SIZE )  ;
        {
                u32 quotient1, pos1=rem,rem1;
                quotient1 = pos1 / ((BLOCK_SIZE/LBA_SIZE)* BLOCK_SIZE);
                if (quotient1 < CT_FIRST_IDX){
                        (*rw).sifi=quotient1;
                        rem1=pos1%((BLOCK_SIZE/LBA_SIZE)* BLOCK_SIZE);
                        {
                                u32 q1 = rem1 / BLOCK_SIZE;
                                (*rw).sifidr=q1;
                                (*rw).pos= rem1 - q1*BLOCK_SIZE ;
                                return 1;
                        }
                }else{
                        ERROR_NO=SCRAP_CODE;
                        handle_error();
                        return 0;
                }

        }
        return 0;
}

/*************************************************************************/
/*************************************************************************/

u8 go_read(u8 fd , u8 * dest , u32 count){
        struct rw val;
        u32 fn,dr,fi,fidr,si,sifi,sifidr,pos ;
        u8 bufr,bufr2,buf3;
        u32 j,k=0;
        u8 sem_dr=0, sem_fidr=0 , sem_sifidr=0 ; /*semaphores to indicate whether it is the entry point*/
        fn = dr = fi = fidr = si = sifidr = pos =0;
        if ( !IS_ORD_FILE (open[fd].block.fadt.hc_fnode.mode)){ /*check for ordinary file*/
                ERROR_NO=NOT_A_FILE;
                handle_error();
                return 0;
        }
        if (! (open[fd].mode & O_READ)) {
                ERROR_NO= NOT_READ;
                handle_error();
                return 0;
        }
/*        if ( open[fd].block.fadt.hc_fnode.uid == get_user()){
                if (! (OWNER_READ & open[fd].block.fadt.hc_fnode.mode)){
                        ERROR_NO=NOT_ENOUGH_PRIVILEGE;
                        handle_error();
                        return 0;
                }
        }else{
                if (! (OTHER_READ & open[fd].block.fadt.hc_fnode.mode)){
                        ERROR_NO=NOT_ENOUGH_PRIVILEGE ;
                        handle_error();
                        return 0;
                }
        } */
        if ( open[fd].file_pos + count > open[fd].block.fadt.hc_fnode.size ){
                ERROR_NO=READ_FRENZY;
                handle_error();
                return 0;
        }
        if(  ! read_map( &val , open[fd].file_pos) ){
                ERROR_NO=INVALID;
                handle_error();
                return 0;
        }
        fn = val.fn  ; dr=val.dr;      fi = val.fi;           /*setting values as returned by structure*/
        fidr = val.fidr ;  si = val.si ; sifi = val.sifi ;
        sifidr = val.sifidr ;  pos = val.pos  ;

        if (! fn){    /*when read starts from fnode block itself , fn is 1 if does not*/
                j=0;
                while ( k < count && pos+j < (BLOCK_SIZE -  FNODE_SIZE)){
                        dest[k++] = open[fd].block.fadt.data[pos+j++] ;
                }
                if ( k == count ){
                        open[fd].file_pos+=count;
                        return 1;
                }
                sem_dr=1;       /*semaphore saying to set for dirsct index pos to 0, sinco original pos  has already been handled*/
        }

        for (; dr < CT_DIRECT_IDX; dr++){   /*reading when starts from direct indexes*/
                if (sem_dr){
                        pos=0;
                }
                j=0;
                bufr = get_block (FDD,open[fd].block.fadt.hc_fnode.index[dr],NOT_ONLY_SEARCH) ;
                if (bufr == NO_BUF){
                        return 0;
                }
                while ( k < count   &&  pos+j < BLOCK_SIZE ){
                        dest[k++] = buf[bufr].data.data.data[pos + j++] ;
                }
                if ( k == count ){
                        put_block(bufr , NOT_FRONT) ;
                        open[fd].file_pos+=count;
                        return 1;
                }
                sem_dr=1;
                sem_fidr=1;
                put_block(bufr , NOT_FRONT) ;
        }

        for (;fi < CT_FIRST_IDX ; fi++ ){   /*when pos comes in first indirect index*/
                bufr2 = get_block (FDD , open[fd].block.fadt.hc_fnode.index[CT_DIRECT_IDX+fi] , NOT_ONLY_SEARCH) ;
                if (bufr2 == NO_BUF){
                        return 0;
                }

                for (; fidr < (BLOCK_SIZE/LBA_SIZE); fidr++){  /*direct indexes within first indirect indexes*/
                        if (sem_fidr){
                                pos=0;
                        }
                        j=0;
                        bufr = get_block (FDD , buf[bufr2].data.fib.lba[fidr] , NOT_ONLY_SEARCH) ;
                        if (bufr == NO_BUF){
                                put_block(bufr2 , NOT_FRONT);
                                return 0;
                        }
                        while ( k < count   &&  pos+j < BLOCK_SIZE ){
                                dest[k++] = buf[bufr].data.data.data[pos + j++] ;
                        }
                        if ( k == count ){
                                put_block(bufr , NOT_FRONT) ;
                                put_block(bufr2 , NOT_FRONT) ;
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
                buf3 = get_block(FDD , open[fd].block.fadt.hc_fnode.index[CT_DIRECT_IDX + CT_FIRST_IDX + si] , NOT_ONLY_SEARCH);

                for (;sifi < (BLOCK_SIZE / LBA_SIZE ) ; sifi++ ){   /*when pos comes in first indirect index*/
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
                                bufr = get_block (FDD , buf[bufr2].data.fib.lba[fidr] , NOT_ONLY_SEARCH) ;
                                if (bufr == NO_BUF){
                                        put_block(buf3 , NOT_FRONT) ;
                                        put_block(bufr2 , NOT_FRONT);
                                        return 0;
                                }
                                while ( k < count   &&  pos+j < BLOCK_SIZE ){
                                        dest[k++] = buf[bufr].data.data.data[pos + j++] ;
                                }
                                if ( k == count ){
                                        put_block(bufr , NOT_FRONT) ;
                                        put_block(bufr2 , NOT_FRONT) ;
                                        put_block(buf3 , NOT_FRONT) ;
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
