/*
 * @document : type_blk.h
 * @date     : 23 4 2003
 * @author   : Naveen
 * @comment  : lots of structures
 */
#ifndef __FS_TYPE_BLK_H
#define __FS_TYPE_BLK_H

#ifdef __cplusplus 
    extern "C" {
#endif

#include "types.h"
#include "const.h"
#include "fnode.h"
#include "dir_str.h"
#include "super.h"
#include "bit.h"
/**
 * Changes  : 5/15/03 changed union data to union only_data
 **/

/**
    This file contains definition of all structures that may fill exactly
    one block on secondary storage, so some of them are combinations of 
    few earlier declared structures this can be used in say declaration 
    of buffers which may contain any of following structures, so later
    we define buffer as array of union type_in_block
 **/

/* this represents a combination of fnode and data in a block */
struct fnode_and_data {   
	   struct fnode hc_fnode;
	   u8 data[BLOCK_SIZE-FNODE_SIZE] ;
};

/* this represents a combination of fnode and directory entries in a block*/
 struct fnode_and_dir {  
	struct fnode hc_fnode;
	struct dir_str dir[(BLOCK_SIZE-FNODE_SIZE)/DIR_ENTRY_SIZE];
	u8 unused[(BLOCK_SIZE-FNODE_SIZE)%DIR_ENTRY_SIZE]; /*padding*/
};

/* this represents mere data in a block */
union only_data {         
	u8 data[BLOCK_SIZE];
	struct dir_str 
        dir[BLOCK_SIZE/DIR_ENTRY_SIZE]; /* data may be directory entries  */
};

/* this represents a collection of first level indexes in a block */
struct first_idx_block{ 
	u32 lba[BLOCK_SIZE/LBA_SIZE];
	#ifdef C99SUPPORT
		u8 unused[BLOCK_SIZE%LBA_SIZE];
	#endif
};

 /* this represents a collection of second level indexes in a block */
struct second_idx_block{ 
	u32 first_idx_idx[BLOCK_SIZE/LBA_SIZE];
	#ifdef C99SUPPORT
		u8 unused[BLOCK_SIZE % LBA_SIZE];
	#endif
};


struct initial_floppy{
	u8 boot_sector[512];
	u8 boot_loader[6*512];
	struct super_block sb;
	union bit_map bit_map[45];
	u8 unused[BLOCK_SIZE - 7*512 - SUPER_SIZE - 45 * sizeof(union bit_map )] ;  
/* the remaining bytes in last sector to make this structure worth 512 bytes*/
};

/* 
    This union represents any of the following data types,it can be 
    used in buffer or any other place which has exactly one block data */
union type_in_block {
	struct fnode_and_data   fadt;
	struct fnode_and_dir    fadr;
	union  only_data        data;
	struct first_idx_block  fib;
	struct second_idx_block sib;
	struct initial_floppy  ini;
};       
/* declared for the purpose of packing */


#ifdef __cplusplus 
    }
#endif

#endif
