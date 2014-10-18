/*
 * @document : buf.h
 * @date     : 23 4 2003
 * @author   : Naveen
 * @comment  : Buffer file
 */

#ifndef __FS_BUF__H
#define __FS_BUF__H

union type_in_block;

struct buffer{
    union type_in_block 
       data;        /* data portion of buffer  . all possible 
                       block structures are there in this union */
    /* header portion of buffer */
    u8 next;        /* for buffer management */
    u32 lba;        /* lba is lba to which  block refers to */
    u8 dev;         /* dev says from which device is it read from*/
    u8 status;      /* status is dirty or clean ie modified */
    u8  used ;      /* says whether it is currently being used so that we do not
                        remove some buffer if usage by some file  */
};
#endif