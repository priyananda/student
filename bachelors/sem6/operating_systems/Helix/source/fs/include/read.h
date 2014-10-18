/*
 * @document : read.h
 * @date     : 23 4 2003
 * @author   : Naveen
 * @comment  : Structures for Read syscall
 */
#ifndef __FS_READ_H
#define __FS_READ_H

#include "types.h"

struct rw{
        u32 fn;     /* whether file_pos  is in fnode block, 0 if present*/
        u32 dr;     /* whether given by direct block, < CT_DIRECT_IDX if 
                       present , else not present*/
        u32 fi;     /* first index */
        u32 fidr;   /* direct index of first index*/
        u32 si;     /* second index*/
        u32 sifi;   /* first of second*/
        u32 sifidr; /* direct of first of second*/
        u32 pos;    /* irrespective of top things , the array index pos */
};

#endif