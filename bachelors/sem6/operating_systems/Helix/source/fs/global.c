/*
 * @file : global.c
 * @date : 23 4 2003
 * @author : naveen
 * @comments : global variables definition
 * @exports : -
 */
/**
 *  This file contain all global variables declared for operation other
 *  than those which are declared along with the definition of their type
 *  itself , like in case of structure definitions along with variable
 **/
#include "global.h"

u8 BUF_START ;       /* start of buffer */
u8 BUF_END ;  		 /* last node of buffer at any instant */
u8 CUR_ROOT ;
u8 USER_ID;
u8 CUR_MAX_SUPER;    /* current maximum value of super, ex if fdd
						alone then zero. if hdd mounted then 1 and
						so on atmost 3*/
u8 ERROR_NO;

union type_in_block block[CT_DUMMY_BLOCKS];
struct open  open[CT_OPEN_FILE];
struct super_block super[CT_SUPER];
struct buffer buf[CT_BUFS];
union  bit_map  bit_map[45]  ;
/* only for FLOPPY DISK because it is only 45 bytes and
 * can be held in memory  */
u8 dot1[2]={'.' , '\0'};
u8 dot2[3]={'.' , '.', '\0'};
u8 flpchange;
