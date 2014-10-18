/*
 * @document : open.h
 * @date     : 23 4 2003
 * @author   : Naveen
 * @comment  : Open File table
 */
#ifndef __FS_OPEN_H
#define __FS_OPEN_H

#include "type_blk.h"
/**
    Open file table entry . It is a memory array of fnodes.
    Permission , size are all stored in fnode , so need not
    be stored explicitly
 **/
 struct open{
	u8 used;                /* says whether it is being used 
                               or not ,so in open file table we can just
                               contain pointer to this location */
	union type_in_block
            block;          /* contains a hard copy of fnode block */
	u8 f_status ;           /* status is CLEAN or DIRTY */
	u8 mode ;               /* this is to say how the file is opened R or W
                               or RW , APPEND , TRUNC possibly CREAT mode*/
	u32 file_pos;           /* for seeking  */
	u32 lba;                /* this will help in writing it back to 
                               disk after change , if any*/
	u8 dev;
        u8 pid ;    /*process id of the process opening the file*/
}; 

#endif
