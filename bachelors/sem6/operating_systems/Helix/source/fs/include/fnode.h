/*
 * @document : fnode.h
 * @date     : 23 4 2003
 * @author   : Naveen
 * @comment  : File node structure
 */
#ifndef  __FS_FNODE_H
#define __FS_FNODE_H

#include "types.h"
#include "const.h"

/**
    hard copy of inode structure on secondary storage . size is 27 octets
**/
struct fnode {
	u8 uid;                 /* gid is currently not used */
	u64 c_time;             /* fnode change time */
	u32 index[CT_TOTAL_IDX];
	u32 size;               /* size of file , for directories 
                               no of entries under it*/
	u64 m_time;             /* modification time */
	u8 mode;                /* rwx permissions for user and others | 
                               (bit wise OR) typeof file dire or ordinary*/
	u8 ct_links;            /* number of hard links to the file*/ 
};

#endif
