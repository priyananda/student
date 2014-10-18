#include <int/intrinit.h>
#include <io/video.h>
/* Initializes the idtr with the appropriate interrupt base and limit */


u32 set_idtr(){
	struct {
		u16 length __attribute__ ((packed));
		u32 base __attribute__ ((packed));
	} idtr = { IDT_LEN, IDT_ADDRESS };

	__asm__ __volatile__(
		"lidt (%%eax)"
		:
		: "a"(&idtr)
	);
}

/* Initailizes a particular interrupt handlers offset w.r.t to kernel code segement */

u32 init_kernel(u32 intNo,u32 (*fn)()){
	SetIDTGate(intNo, IDTGATE_INT, KERNEL_CODE_SEL, (u32)fn);
	return 0;
}

u32 init_user(u32 intNo,u32 (*fn)()){
	SetIDTGate(intNo, IDTGATE_INT, KERNEL_CODE_SEL, (u32)fn);
	return 0;
}

void SetIDTGate(u16 IntNo, u16 Type, u16 Selector, u32 Offset)
{
	IDT_GATE * Idt = (IDT_GATE *)(IDT_ADDRESS);
	IDT_GATE *	pGate = &Idt[IntNo];
	pGate->Offset   = (u16) (Offset & 0xffff);
	pGate->Offset2  = (u16) (Offset >> 16);
	pGate->Selector = Selector;
	pGate->Type     = Type;
}
