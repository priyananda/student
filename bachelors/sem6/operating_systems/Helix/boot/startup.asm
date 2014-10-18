[BITS 16]
group DGROUP _TEXT _DATA _BSS _STACK

extern _main
; ****************************CODE-Segment*********************************
segment	_TEXT class=CODE
..start:	;Actual Entry Point
main:
	mov ax, cs
	mov ds, ax
	mov es, ax
	cli
	xor ax,ax
	mov ss, ax		; Stack segment  0x0000
	mov sp, main	; Stack start is 0xA000
	sti

	call _main		; C code main

;Control never comes here
	int 19h


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;	Prints a null terminated string in DS:SI
;
[GLOBAL	_put_string]
_put_string:
	mov	bx,00
	mov	ah,0eh
.do:
	mov	al,[si]
	inc	si
	or al,al
	jz .done
	int	10h
	jmp	.do
.done:
	ret
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


%include "gdt.asm"	; The Tables and other stuff related to GDT

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;Data-Segment;;;;;;;;;;;;;;;;;;;;;;;;;;;;
segment	_DATA class=DATA

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;Bss-Segment;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
segment	_BSS class=BSS

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;Stack-Segment;;;;;;;;;;;;;;;;;;;;;;;;;;;
segment	_STACK class=STACK
