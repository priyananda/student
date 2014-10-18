#ifndef _IODRV_H
#define _IODRV_H

#include <types.h>

u8   inb  ( port_no port );
void outb ( port_no port , u8 value);

u16  inw  ( port_no port );
void outw ( port_no port , u16 value);

u32  inl  ( port_no port );
void outl ( port_no port , u32 value);

#endif