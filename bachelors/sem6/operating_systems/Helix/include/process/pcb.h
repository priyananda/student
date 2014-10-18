#ifndef __PCB_H__
#define __PCB_H__
	
#include <types.h>
#define PACKED __attribute__ ((packed))

struct pcb	 
{
    /* physical addresses */
	u32 code_base  PACKED;
	u32 data_base  PACKED;
	u32 stack_base  PACKED;
    /* registers */
	u32 eax  PACKED;
	u32 ebx  PACKED;
	u32 ecx PACKED;
	u32 edx PACKED;
	u32 esi PACKED;
	u32 edi PACKED;
	u32 esp PACKED;
	u32 ebp PACKED;
    /* selectors */
	u16 cs PACKED;
	u16 ds PACKED;
	u16 ss PACKED;
	u16 es PACKED;
	u16 gs PACKED;
	u16 fs PACKED;
    /* execution context */
    u32 eip PACKED;
};

extern struct pcb pcb_stack[256];
extern u32 current_process;


#endif