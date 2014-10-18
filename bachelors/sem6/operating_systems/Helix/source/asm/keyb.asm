

[SECTION .text text]
[BITS 32]
[EXTERN _kb_int_handler]

[GLOBAL _intr33]
_intr33:
	cli
	call _kb_int_handler
	sti
	iret