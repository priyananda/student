#include <io/pic.h>

void InitPIC(u8 c1,u8 c2){
	/* Reprogram the master 8259. */
	outb(I8259_A0, 0x11);

	outb(I8259_A1, c1);
	outb(I8259_A1, 0x04);
	outb(I8259_A1, 0x01);
	outb(I8259_A1, 0x00);

	/* Reprogram the slave 8259. */
	outb(I8259_B0, 0x11);

	outb(I8259_B1, c2);
	outb(I8259_B1, 0x02);
	outb(I8259_B1, 0x01);
	outb(I8259_B1, 0x00);

}
