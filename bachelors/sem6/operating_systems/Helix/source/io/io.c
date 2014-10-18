#include <types.h>
#include <io/iodrv.h>

void outb (port_no port, u8 data){
	__asm__ __volatile__ ("outb %1, %0"
		:
		: "d" (port), "a" (data)
	);
}

u8 inb(port_no port){
	u8 data;
	__asm__ __volatile__ (
		"inb %1, %0"
		: "=a" (data)
		: "d" (port)
	);
	return data;
}

void outw (port_no port, u16 data){
	__asm__ __volatile__ ("outw %1, %0"
		:
		: "d" (port), "a" (data)
	);
}

u16 inw(port_no port){
	u16 data;
	__asm__ __volatile__ (
		"inw %1, %0"
		: "=a" (data)
		: "d" (port)
	);
	return data;
}

void outl (port_no port, u32 data){
	__asm__ __volatile__ ("outb %1, %0"
		:
		: "d" (port), "a" (data)
	);
}

u32 inl(port_no port){
	u32 data;
	__asm__ __volatile__ (
		"inl %1, %0"
		: "=a" (data)
		: "d" (port)
	);
	return data;
}
