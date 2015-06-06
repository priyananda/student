

[SECTION .text text]
[BITS 32]
[EXTERN kb_int_handler]

[GLOBAL intr33]
intr33:
	cli
	call kb_int_handler
	sti
	iret
