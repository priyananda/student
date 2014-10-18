#ifndef __PROCESS_H
#define __PROCESS_H

#include <types.h>

extern u32 spawn(u8 * filename);
extern u32 _exit();
extern u32 exit();

extern phys_addr free_mem_base;

#endif