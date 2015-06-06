#include <types.h>
#include <int/intrinit.h>
#include <io/video.h>

u32	intr0(){
	SET_KERNEL_DS();
	vd_puts("\n DivideByZero exception	: Process Killed");
	__asm__	__volatile__(
		"mov %ebp, %esp\n"
		"\tpopl %ebp\n"
		"iret"
	);
}

u32	intr1(){
	SET_KERNEL_DS();
	vd_puts("\n Single	step not allowed : Process Killed");
	__asm__	__volatile__(
		"mov %ebp, %esp\n"
		"\tpopl %ebp\n"
		"iret"
	);
}

u32	intr2(){
	SET_KERNEL_DS();
	vd_puts("\n Sorry restarting system : Process Killed");
	__asm__	__volatile__(
		"mov %ebp, %esp\n"
		"\tpopl %ebp\n"
		"iret"
	);
}


u32	intr3(){
	SET_KERNEL_DS();
	vd_puts("\n Software break	point  : Process Killed");
	__asm__	__volatile__(
		"mov %ebp, %esp\n"
		"\tpopl %ebp\n"
		"iret"
	);
}


u32	intr4(){
	SET_KERNEL_DS();
	vd_puts("\n Aritematic	overflow exception : Process Killed");
	__asm__	__volatile__(
		"mov %ebp, %esp\n"
		"\tpopl %ebp\n"
		"iret"
	);
}

u32	intr5(){
	SET_KERNEL_DS();
	vd_puts("\n Printscreen bounds	exceed exception : Process life	not	 spared");
	__asm__	__volatile__(
		"mov %ebp, %esp\n"
		"\tpopl %ebp\n"
		"iret"
	);
}

u32	intr6(){
	SET_KERNEL_DS();
	vd_puts("\n InvalidOpcode :	Process	Killed");
	__asm__	__volatile__(
		"mov %ebp, %esp\n"
		"\tpopl %ebp\n"
		"iret"
	);
}

u32	intr7(){
	SET_KERNEL_DS();
	vd_puts("\n CoprocessorAbsent : Process Killed");
	__asm__	__volatile__(
		"mov %ebp, %esp\n"
		"\tpopl %ebp\n"
		"iret"
	);
}


u32	intr8(){
	SET_KERNEL_DS();
	vd_puts("\n DoubleFault exception : Process Killed");
	__asm__	__volatile__(
		"mov %ebp, %esp\n"
		"\tpopl %ebp\n"
		"iret"
	);
}

u32	intr9(){
	SET_KERNEL_DS();
	vd_puts("\n CoprocessorSegmentOverrun exception : Process Killed");
	__asm__	__volatile__(
		"mov %ebp, %esp\n"
		"\tpopl %ebp\n"
		"iret"
	);
}


u32	intr10(){
	SET_KERNEL_DS();
	vd_puts("\n InvalidTSS	exception :	Process	Killed");
	__asm__	__volatile__(
		"mov %ebp, %esp\n"
		"\tpopl %ebp\n"
		"iret"
	);
}

u32	intr11(){
	SET_KERNEL_DS();
	vd_puts("\n Segment exception : Process Killed");
	__asm__	__volatile__(
		"mov %ebp, %esp\n"
		"\tpopl %ebp\n"
		"iret"
	);
}


u32	intr12(){
	SET_KERNEL_DS();
	vd_puts("\n StackSegmentOverflow exception	: Process Killed");
	__asm__	__volatile__(
		"mov %ebp, %esp\n"
		"\tpopl %ebp\n"
		"iret"
	);
}

u32	intr13(){
	SET_KERNEL_DS();
	vd_puts("\n GeneralProtectionFault	exception :	Process	Killed");
	__asm__	__volatile__(
		"mov %ebp, %esp\n"
		"\tpopl %ebp\n"
		"iret"
	);
}

u32	intr14(){
	SET_KERNEL_DS();
	vd_puts("\n Page Fault : Process killed ");
	__asm__	__volatile__(
		"mov %ebp, %esp\n"
		"\tpopl %ebp\n"
		"iret"
	);
}

u32	intr15(){
	SET_KERNEL_DS();
	vd_puts("\nIntel has reserved this stupid interrupt");
	__asm__	__volatile__(
		"mov %ebp, %esp\n"
		"\tpopl %ebp\n"
		"iret"
	);
}

u32	intr16(){
	SET_KERNEL_DS();
	vd_puts("\nFloating Point error ");
	__asm__	__volatile__(
		"mov %ebp, %esp\n"
		"\tpopl %ebp\n"
		"iret"
	);
}

u32	intr17(){
	SET_KERNEL_DS();
	vd_puts("\nAlignment Check error");
	__asm__	__volatile__(
		"mov %ebp, %esp\n"
		"\tpopl %ebp\n"
		"iret"
	);
}

u32 intr32(){
	__asm__ __volatile__("cli");
	outb(0x20,0x20);
	vd_puts("\nService timer");
	__asm__	__volatile__(
		"sti\n"
		"\tmov %ebp, %esp\n"
		"\tpopl %ebp\n"
		"iret"
	);
}

u32	populateIVT(){
	set_idtr();
	init_kernel(0,intr0);
	init_kernel(1,intr1);
	init_kernel(2,intr2);
	init_kernel(4,intr4);
	init_kernel(5,intr5);
	init_kernel(6,intr6);
	init_kernel(7,intr7);
	init_kernel(8,intr8);
	init_kernel(9,intr9);
	init_kernel(10,intr10);
	init_kernel(11,intr11);
	init_kernel(12,intr12);
	init_kernel(13,intr13);
	init_kernel(14,intr14);
	init_kernel(15,intr15);
	init_kernel(16,intr16);
	init_kernel(17,intr17);
	init_kernel(32,intr32);
	init_kernel(33,intr33);
	outb(0x21,0x01);	//Disable timer interrupt
	return 0;
}
