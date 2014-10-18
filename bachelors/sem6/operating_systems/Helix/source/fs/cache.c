/*
 * @document : cache.c
 * @date : 23 4 2003
 * @author : Naveen
 * @exports : get_block  , put_block , all_out , alloc_bit , free_bit

 change on 22 -5 in line 116
 */

#include "proto.h"
#include "fsio.h"
#include "global.h"

/**
    get_block() function first searches the buffer for required device
    and lba if found  return the buffer pointer. if not found then it searches
    for a free buffer ie NOT_IN_USE buffer. higher priority is given to the
    clean one else the dirty one at front of LRU queue is selected
    In any case the buffer element is added to end of LRU queue .
    now if free buffer is given then it is filled by reading the requested
    lba from device unless only_search is specified
    if  no usable block is obtained an error function is called
 **/

u8 get_block(u8  _dev, u32  _lba , u8  _only_search){
    u8 cur,prev;
    u8 first_dirty =NO_BUF;         /* to mark first free dirty page to be
                                       used if no clean page available  */
    u8 first_dirty_prev=NO_BUF;     /* buffer previous to first dirty buffer*/
    if (_lba  ==  NO_LBA){
    	if(!ERROR_NO){
        	ERROR_NO=NO_DIR_FILE;
        	handle_error();
        }
        return NO_BUF;
    }
    prev = cur= BUF_START;
    while( cur  != NO_BUF){         /* search for match in device and lba */
        if ( buf[cur].dev ==  _dev  &&  buf[cur].lba ==   _lba)
            break ;
        prev = cur;
        cur = buf[cur].next;
    }
    if(cur !=  NO_BUF){
        /* found so implementing LRU by placing it at the end of LRU queue  */
        if (cur == BUF_START)
            BUF_START=buf[cur].next;
        else if (cur == BUF_END)
            BUF_END=prev;
        else
            buf[prev].next = buf[cur].next;

        buf[BUF_END].next=cur;
        buf[cur].next = NO_BUF;
        BUF_END = cur;
        buf[cur].used=IN_USE;/* we are not calling it clean because
                                it may not be so */
        return cur;
    }
    prev = cur=BUF_START;  /* match has not occured ,so searching
                             for a NOT_IN_USE page  */
    while( cur != NO_BUF){
        if( buf[cur].used ==  NOT_IN_USE  && buf[cur].status == CLEAN)
            break;
        if( buf[cur].used ==  NOT_IN_USE  && buf[cur].status == DIRTY){
            if(first_dirty == NO_BUF){
                first_dirty = cur;
                first_dirty_prev=prev;
            }
        }
        prev = cur;
        cur= buf[cur].next;
    }
    if(cur !=  NO_BUF   ||  first_dirty != NO_BUF){  /* free page found  */
        if(cur == NO_BUF){  /* it is dirty so need to be written  */
            u8 ret;
            ret=Write(& buf[first_dirty].data,  buf[first_dirty].lba,
                buf[first_dirty].dev);
            cur=first_dirty;
            prev=first_dirty_prev;
            if(!ret )
                return NO_BUF;
        }
        if (cur == BUF_START)
            BUF_START=buf[cur].next;
        else if (cur == BUF_END)
            BUF_END=prev;
        else
            buf[prev].next = buf[cur].next;

        buf[BUF_END].next=cur;
        buf[cur].next = NO_BUF;
        BUF_END = cur;
        buf[cur].used=IN_USE;
        buf[cur].status=CLEAN;   /* here we can call it clean because it will
                                    now be read  */
        buf[cur].lba = _lba;
        buf[cur].dev = _dev;
        if (  _only_search  != ONLY_SEARCH){
            u8 ret;
            ret = Read( & buf[cur].data,  _lba,   _dev) ;
                                /* watch out & and so program the Read function*/
            if (!ret)
                return NO_BUF;
        }
        return cur;
    }else{ /* no free page found  */
        ERROR_NO =  NO_EMPTY_BUFS;
        handle_error();
        return NO_BUF;
    }
}
/**
    This function returns the buffer to LRU queue and has no contribution
    to LRU feature , but when _front is set to FRONT , it puts the buffer
    at the front of queue  so that it is written as early as possible,
    required for some file system blocks
 **/
u8 put_block(u8   _buf_no , u8  _front){
    u8 prev,cur;
    prev = cur=BUF_START;
    buf[_buf_no].used=NOT_IN_USE;   /* come what may this has to be done to
                                       enable its usage  */
    //_front=FRONT ;
    if( _front  !=  FRONT )         /* leave at its place or it is already
                                       at front */
        return 1;
    if (_buf_no != BUF_START){
        while(cur !=  _buf_no && cur != NO_BUF){
                                    /*  search for prev element, done so
                                        because it is a linked list*/
            prev=cur;
            cur = buf[cur].next;
        }
        if(cur == NO_BUF){
                return 0;
        }
        buf[prev].next= buf[cur].next;
        if(cur  == BUF_END)
            BUF_END=prev;
        buf[cur].next = BUF_START;
        BUF_START = cur;            /*added at the front of queue*/
    }
    if (buf[BUF_START].status == DIRTY){
        u8 ret;
        ret = Write(& buf[BUF_START].data,  buf[BUF_START].lba,
                buf[BUF_START].dev);
        buf[BUF_START].status = CLEAN;
        if(! ret )
            return 0;
    }
    return 1;
}
/**
    This function writes all the dirty buffers to the disk irrespective
    of whether it is in use or not but does not clean the buffers so that
    data still remain in buffers
 **/
u8 all_out(u8 dev){
        u8 trav=BUF_START;
        while (trav  !=  NO_BUF){
            if ( buf[trav].status == DIRTY &&  buf[trav].dev ==  dev){
                u8 ret;
                ret = Write(& buf[trav].data, buf[trav].lba,buf[trav].dev);
                buf[trav].status=CLEAN;
                /*  watch this flush all does not mean i no more use it,
                    it can even be in use. noe a unmount function should set
                    dev to NO_DEV , so that a newly mounted same device say
                    FDD does not use this on get_block*/
                if(!ret)
                    return 0;
            }
            trav=buf[trav].next;
        }
        return 1;
}
/**
   Here i am not concerned whether something is written or not , this is used
   in deleting files, where i want  to remove all remenences of that lba
 **/
void clean_buffer(u32 lba){
    u8 i;
    for(i=0 ; i < CT_BUFS ; i++)
           if( i == lba) {
               buf[i].used=NOT_IN_USE ;
               buf[i].lba = NO_LBA;
               buf[i].status = CLEAN;
           }
}
/**
    This function allocates a bit that represents a block on secondary storage
    IMP - this is clearly based on fact that the super[CUR_ROOT].ff_lba is
    pointing to a free lba  , so once a bit has been allocated, this field
    is updated to represent  next free bit.  now when _empty_lba is 0, ie no
    free lba , then FF_LBA CANNOT BE LOGICAL, THIS IS HANDELED IN FREE_BIT
    FUNCTION  . If there is a free block , them super.empty_lba is positive ,
    and super.ff_lba always point to it
*/
u32 alloc_bit(u8 dev){
    u64 temp1,i;
    u64 temp2;
    u8 ret;
    u8 cur_root=get_super(dev);
    while(1){
            if  (super[cur_root].empty_lba == 0){  /* NO FREE BIT AVAILABLE  */
                    ERROR_NO = NO_BLOCKS;
                    handle_error();
                    return NO_LBA;
            }
            temp1 = super[cur_root].ff_lba;
            temp2 = (temp1)/8;              /* WHICH BYTE DOES IT BELONG TO*/
            temp1 = temp1 - temp2 * 8;      /* temp 1th bit of temp2 byte ,
                                                both bit and byte start from 0 */
            switch (temp1)    {
                    case 0:bit_map[temp2].pat.b0=0; /* CORRESPONDING BIT SET TO used*/
                                            break;
                    case 1:bit_map[temp2].pat.b1=0;
                                            break;
                    case 2:bit_map[temp2].pat.b2=0;
                                            break;
                    case 3:bit_map[temp2].pat.b3=0;
                                            break;
                    case 4:bit_map[temp2].pat.b4=0;
                                            break;
                    case 5:bit_map[temp2].pat.b5=0;
                                            break;
                    case 6:bit_map[temp2].pat.b6=0;
                                            break;
                    case 7:bit_map[temp2].pat.b7=0;
                                            break;
            }
            super[cur_root].empty_lba -= 1;
            temp1 = super[cur_root].ff_lba;  /* this is to return the value to the
                                        calling program returning the
                                        allocated bit lba NUMBER */


            ret = Read(&block[0],(u32)temp1 ,FDD);
            if (ret) {
                break;
            }
             if (ERROR_NO == BAD_BLOCK){
                continue;
             }
             return NO_LBA;

    }
    if (super[cur_root].empty_lba <1) {
                /* NO FREE BIT ,SO FF_LBA CANNOT BE SET TO LOGICALY CORRECT VALUE,
                   but next invocation of this function, first empty check fails*/
        return temp1;
    }
    for(i=temp2; i <  super[cur_root].bit_map_bytes ; i++)
            /*SEARCH FOR THE NEXT NEAREST FF_LBA VALUE*/
            if  (bit_map[i].octet   !=  0)
                    break;
    if (i != super[cur_root].bit_map_bytes){  /*some free bit available*/
            if (bit_map[i].pat.b0 == 1)
                        super[cur_root].ff_lba = i*8 + 0;
            else if (bit_map[i].pat.b1 == 1)
                        super[cur_root].ff_lba = i*8 + 1;
            else if (bit_map[i].pat.b2 == 1)
                        super[cur_root].ff_lba = i*8 + 2;
            else if (bit_map[i].pat.b3 == 1)
                        super[cur_root].ff_lba = i*8 + 3;
            else if (bit_map[i].pat.b4 == 1)
                        super[cur_root].ff_lba = i*8 + 4;
            else if (bit_map[i].pat.b5 == 1)
                        super[cur_root].ff_lba = i*8 + 5;
            else if (bit_map[i].pat.b6 == 1)
                        super[cur_root].ff_lba = i*8 + 6;
            else if (bit_map[i].pat.b7 == 1)
                        super[cur_root].ff_lba = i*8 + 7;

            return temp1;
    }

    for(i=0; i <  temp2 ; i++)
            /* WHEN PREVIOUS TEST FAILS THEN WE GO BACK FROM BLOCK 0
               ,AND SEARCH FOR A FREE BIT*/
            if (bit_map[i].octet   !=  0)
                break;

    if (i == temp2){          /* EMPTY_LBA IS NOT 0, BUT NO FREE BIT WAS
                              AVAILABLE , REPRESENTING SOME FLAW IN CODE */
        ERROR_NO = SCRAP_CODE;
        handle_error();
        return temp1;
    }

    if (bit_map[i].pat.b0 == 1)
                super[cur_root].ff_lba = i*8 + 0;
    else if (bit_map[i].pat.b1 == 1)
                super[cur_root].ff_lba = i*8 + 1;
    else if (bit_map[i].pat.b2 == 1)
                super[cur_root].ff_lba = i*8 + 2;
    else if (bit_map[i].pat.b3 == 1)
                super[cur_root].ff_lba = i*8 + 3;
    else if (bit_map[i].pat.b4 == 1)
                super[cur_root].ff_lba = i*8 + 4;
    else if (bit_map[i].pat.b5 == 1)
                super[cur_root].ff_lba = i*8 + 5;
    else if (bit_map[i].pat.b6 == 1)
                super[cur_root].ff_lba = i*8 + 6;
    else if (bit_map[i].pat.b7 == 1)
                super[cur_root].ff_lba = i*8 + 7;
    return temp1;

}

/**
   This fuction frees a bit, not if there where no free bits before ,
   this also sets super.ff_lba to this value so that it is correct on
   call of alloc_bit which blindly believes ff_lba to be correct
 **/
u8 free_bit(u32  _lba,u8 dev){
        u8 cur_root=get_super(dev);
        u64 temp1,temp2;
                if (_lba  ==  NO_LBA){
                        ERROR_NO=NO_DIR_FILE;
                        handle_error();
                        return 0;   /*failure*/
                }

        if (super[cur_root].empty_lba == 0 ) {
                super[cur_root].ff_lba  =  _lba;
        }
        super[cur_root].empty_lba += 1;
        temp2 = (_lba)/8;            /* WHICH BYTE DOES IT BELONG TO*/
        temp1 = _lba  -  temp2* 8;   /* temp 1th bit of temp2 byte , both bit
                                        and byte start from 0 */

        switch (temp1)    {
            case 0:bit_map[temp2].pat.b0=1;/*CORRESPONDING BIT SET to notused*/
                                    break;
            case 1:bit_map[temp2].pat.b1=1;
                                    break;
            case 2:bit_map[temp2].pat.b2=1;
                                    break;
            case 3:bit_map[temp2].pat.b3=1;
                                    break;
            case 4:bit_map[temp2].pat.b4=1;
                                    break;
            case 5:bit_map[temp2].pat.b5=1;
                                    break;
            case 6:bit_map[temp2].pat.b6=1;
                                    break;
            case 7:bit_map[temp2].pat.b7=1;
                                    break;
    }
    return 1;  /*success */
}

