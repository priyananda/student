%define LINEAR_SEL 0x8
%define KERNEL_CODE_SEL 0x18
%define KERNEL_DATA_SEL 0x20
%define KERNEL_STACK_SEL 0x28
%define REAL_CODE_SEL 0x38
%define REAL_DATA_SEL 0x40
%define KERNEL_STACK_START 0x9A000	; 64K + 500K


[SECTION .text text]
[BITS 32]
[EXTERN _main]
[EXTERN _set_idtr]
[GLOBAL _start]
_start:
	cli
	cld
	xor eax,eax
	mov ax, KERNEL_DATA_SEL
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ax, KERNEL_STACK_SEL
	mov ss, ax
	mov esp,KERNEL_STACK_START
	call _main
	cli
	clc
lbl1:
	jnc lbl1


[GLOBAL _int13h]
_int13h:
	lidt [ridtr]
	mov ebx,[rjmp]
	mov [real_jmp],bx
	mov ebx,real_jmp - 0x10000
	jmp REAL_CODE_SEL:prot16 - 0x10000
prot16:
	%include "prot16.bin"
real_jmp:
	dw 0
	dw 0x1000
real_code:
	%include "real.bin"
	dd fin_i13h
	dw KERNEL_CODE_SEL
fin_i13h:
	mov bx,KERNEL_STACK_SEL
	mov ss,bx
	mov bx,KERNEL_DATA_SEL
	mov ds,bx
	mov es,bx
	mov gs,bx
	mov fs,bx
	push eax
	call _set_idtr
	pop eax
	ret

[SECTION .data data]
ridtr:
	dw 0x3ff
	dd 0x0
rjmp:
	dd real_code - 0x10000
