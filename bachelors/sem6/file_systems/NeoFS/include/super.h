/*
 * @document : super.h
 * @date     : 23 4 2003
 * @author   : Naveen
 * @comment  : Superblock entry
 */
#ifndef __FS_SUPER_H
#define __FS_SUPER_H

#include "types.h"
#include "bit.h"
/*
    This is floppy disk super block.It needs some changes like count of lba.
    .size of super block is 27 bytes  
 */
struct super_block {
	u8 magic;           /* id for fs */
	u8 ver;             /* version of file system  */ 
	u32 ct_lba;         /* total number of lba present */
	u8 dev;       
	u32 empty_lba;      /* number of empty lba  */
	u32 ff_lba;         /* first free lba at any instant  */
	u32 bit_map_bytes;  /* number of bytes to store the bit map of the lba */
	u32 bit_map_blocks; /* number of blocks required to store bit_maps-- not 
                           very usefull because we store some bit maps in 
                           super block  */
	u32 root_dir_lba;
} ;	
	
struct super_sect{
    struct super_block block;
    union bit_map bit_mapa[45];
    u8 padd[512 - sizeof(struct super_block) - 45 * sizeof(union bit_map)] ;
};

#endif
