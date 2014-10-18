/*
 * @document : global.h
 * @date     : 23 4 2003
 * @author   : Naveen
 * @comment  : Global  variables
 */
#ifndef __FS_GLOBAL_H
#define __FS_GLOBAL_H

#include "types.h"
#include "const.h"
#include  "type_blk.h"
#include  "open.h"
#include  "super.h"
#include  "buf.h"
#include  "bit.h"

/**
    This file contain all global variables declared for operation other
    than those which are declared along with the definition of their type
    itself , like in case of structure definitions along with variable
**/

extern u8 BUF_START ;           /* start of buffer */
extern u8 BUF_END ;             /* last node of buffer at any instant */
extern u8 CUR_ROOT ;
extern u8 USER_ID;
extern u8 CUR_MAX_SUPER;        /* current maximum value of super, ex if fdd
                                   alone then zero. if hdd mounted then 1 and
                                   so on atmost 3*/
extern u8 ERROR_NO;

extern union type_in_block
       block[CT_DUMMY_BLOCKS];
extern struct open
        open[CT_OPEN_FILE];
extern struct super_block
        super[CT_SUPER];
extern struct buffer
        buf[CT_BUFS];

extern union  bit_map
        bit_map[45]  ;          /* only for FLOPPY DISK  because it is only 45
                                   bytes and can be held in memory  */
extern u8 dot1[2];
extern u8 dot2[3];
extern u8 flpchange ;


#endif