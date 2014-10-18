#ifndef __INTRINIT_H_
#define __INTRINIT_H_

#include <types.h>
#include <kernel/kernel.h>

/* Restores	the	value of the kernel	data segment */
#define	SET_KERNEL_DS()	__asm__	__volatile__ (\
	"movw %0,%%ax\n"\
	"\tmov %%ax,%%ds\n"\
	:\
	:"i"(KERNEL_DATA_SEL)\
)

/* Macro that all stores the registers on to the pcb of	current	process	*/
#define	STORE_ALLREG()	__asm__	__volatile__(""\
		:"=a"(scallno)\
		:\
	);\
	__asm__	__volatile__(""\
		:"=c"(pcb_stack[current_process].ecx)\
		:\
	);\
	__asm__	__volatile__("mov %%esp,%%ecx"\
		:"=c"(pcb_stack[current_process].esp)\
		:\
	);\
	__asm__	__volatile__("mov %%ebp,%%ecx"\
		:"=c"(pcb_stack[current_process].ebp)\
		:\
	);\
	__asm__	__volatile__(""\
		:"=a"(pcb_stack[current_process].eax)\
		:\
	);\
	__asm__	__volatile__(""\
		:"=b"(pcb_stack[current_process].ebx)\
		:\
	);\
	__asm__	__volatile__(""\
		:"=d"(pcb_stack[current_process].edx)\
		:\
	);\
	__asm__	__volatile__(""\
		:"=S"(pcb_stack[current_process].esi)\
		:\
	);\
	__asm__	__volatile__(""\
		:"=D"(pcb_stack[current_process].edi)\
		:\
	)

/* Resets all the registers	to context before interrupt	*/
#define	RESET_ALLREG()	__asm__	__volatile__("movw %%cx,%%sp"\
		:\
		:"c"(pcb_stack[current_process].esp)\
	);\
	__asm__	__volatile__("movw %%cx,%%bp"\
		:\
		:"c"(pcb_stack[current_process].ebp)\
	);\
	__asm__	__volatile__(""\
		:\
		:"S"(pcb_stack[current_process].esi)\
	);\
	__asm__	__volatile__(""\
		:\
		:"D"(pcb_stack[current_process].edi)\
	);\
	__asm__	__volatile__("movw %%cx,%%ss"\
		:\
		:"c"(pcb_stack[current_process].ss)\
	);\
	__asm__	__volatile__("movw %%cx,%%ds"\
		:\
		:"c"(pcb_stack[current_process].ds)\
	);\
	__asm__	__volatile__("movw %%cx,%%es"\
		:\
		:"c"(pcb_stack[current_process].es)\
	);\
	__asm__	__volatile__(""\
		:\
		:"b"(pcb_stack[current_process].ebx)\
	);\
	__asm__	__volatile__(""\
		:\
		:"d"(pcb_stack[current_process].edx)\
	);\
	__asm__	__volatile__(""\
		:\
		:"c"(pcb_stack[current_process].edx)\
	)


u32 set_idtr(); /* Calls assembly funtion to load the idtr register */
u32 init_intr(u8 intr,u32 lin_add); /* Calls */
void SetIDTGate(u16 IntNo, u16 Type, u16 Selector, u32 Offset);

typedef struct _idt_gate
{
	u16	Offset __attribute__ ((packed));
	u16	Selector __attribute__ ((packed));
	u16	Type __attribute__ ((packed));
	u16	Offset2 __attribute__ ((packed));
} IDT_GATE;

#define IDTGATE_TRAP	0x8f00
#define IDTGATE_INT		0x8e00
#define IDTGATE_TASK	0x8500

void intr33();

#endif