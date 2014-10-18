#ifndef __FSIO_H
#define __FSIO_H

#include "types.h"
#include "type_blk.h"

extern u8 Read( union type_in_block * buff,
		 		u32 lba,
		 		u8 dev );
extern u8 Write(union type_in_block * buff,
                u32 lba,
				u8 dev );
u8 read_sector(int head , int track , int sector, u8 * buff);
u8 write_sector(int head , int track , int sector, u8 * buff);

#endif
