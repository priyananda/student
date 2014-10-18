#include <io/floppy.h>

int printf(const char *,...);

int biosdisk(u8 fnno,u8 dev,u8 head,u8 track,u8 sector,u8 count,u8 * address){
	int ret = 0,i;
	u16 ax = (u16)((((u16)fnno ) << 8) | count);
	u16 cx = (u16)((((u16)track) << 8) | sector);
	u16 dx = (u16)((((u16)head ) << 8) | dev);
	char * src = (char *)(0xa000);
	if(fnno == 3){
		for(i = 0;i < 512 * count;i++)
			*src++ = *address++;
	}
	__asm__ __volatile__ ( "cli" );
	InitPIC(0x8,0x70);
	__asm__ __volatile__ (
		"call _int13h"
		: "=a"(ret)
		: "a"(ax),
		  "d"(dx),
		  "c"(cx)
		: "esi","edi","ebx"
	);
	InitPIC(0x20,0x28);
	outb(0x21,0x1);
	__asm__ __volatile__ ( "sti" );
	if(ret & 0xff00 || fnno == 3)return (ret >> 8);
    if(fnno == 2){
    	for(i = 0;i < 512 * count;i++)
    		*address++ = *src++;
    }
	return (ret >> 8);
}
