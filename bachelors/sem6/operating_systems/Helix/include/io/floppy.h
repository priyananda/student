#ifndef __FLOPPY_H__
#define __FLOPPY_H__

#include <types.h>

int biosdisk(u8 fnno,u8 dev,u8 head,u8 track,u8 sector,u8 count,u8 * address);

#endif