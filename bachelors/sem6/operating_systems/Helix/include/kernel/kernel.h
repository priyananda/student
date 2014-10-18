#ifndef __KERNEL_H
#define __KERNEL_H

/* 
	each process including the kernel has 4 segments : CS ,  DS  , SS 
	Along with this the Extra Segment is used exclusively by kernel for 
	File and related buffers etc . 
*/
#define LINEAR_SEL      0x8
#define	KERNEL_CODE_SEL	0x18
#define	KERNEL_DATA_SEL	0x20
#define	KERNEL_STACK_SEL 0x28
#define VIDEO_SEL       0x18
#define IDT_ADDRESS 0x8000
#define LDT_ADDRESS 0x9000
#define GDT_ADDRESS 0x7C00

#define	USER_STACK_SIZE	4096
#define	KRNL_STACK_SIZE	4096
#define IDT_LEN (256 * 8 - 1)

#endif