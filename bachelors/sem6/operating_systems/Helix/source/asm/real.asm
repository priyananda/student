
;	Code to call int 13h and switch back to protected mode
[BITS 16]
	xor bx,bx
	mov ss,bx
	mov ds,bx
	mov bx,sp
	mov sp,0xffff
	push bx
	mov bx,0xa00
	mov es,bx
	xor bx,bx

	int 13h
	cli
	mov ebx,eax
	mov eax,cr0
	or al,1
	mov cr0,eax
	mov eax,ebx
	pop sp
	db 0x66, 0xea