#ifndef __PIC_H__
#define __PIC_H__

#include <types.h>

#define I8259_A0	0x020			// 8259 #1, port #1
#define I8259_A1	0x021			// 8259 #1, port #2
#define I8259_B0	0x0a0			// 8259 #2, port #1
#define I8259_B1	0x0a1			// 8259 #2, port #2

void InitPIC(u8 masterPort,u8 slavePort);

#endif