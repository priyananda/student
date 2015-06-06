[BITS 16]

; group DGROUP .text .data .bss .stack

extern main
; ****************************CODE-Segment*********************************
segment	.text
[GLOBAL start]
start:	;Actual Entry Point
pmain:
	mov ax, cs
	mov ds, ax
	mov es, ax
	cli
	xor ax,ax
	mov ss, ax		; Stack segment  0x0000
	mov sp, main	; Stack start is 0xA000
	sti

	call main		; C code main

;Control never comes here
	int 19h


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;	Prints a null terminated string in DS:SI
;
[GLOBAL	put_string]
put_string:
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
segment	.data

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;Bss-Segment;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
segment	.bss

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;Stack-Segment;;;;;;;;;;;;;;;;;;;;;;;;;;;
segment	.stack
