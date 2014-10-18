[BITS 16]
%define GDT_ADDRESS 0x7c00	; 31K
%define IDT_ADDRESS 0x8000	; 32K
%define LDT_ADDRESS 0x9000	; 36K
%define KERNEL_ADDR 0x10000	; 64K
%define LDT_LEN		256 * 3 * 8

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;Loads gdt & idt table at GDT_ADDRESS
;
[GLOBAL _copy_gdt]
_copy_gdt:
copy_gdt:
	;Set es to 0
	xor ax,ax
	mov es,ax
	cld

	mov si,NULL_GDT
	mov di,GDT_ADDRESS
	mov cx,gdt_end-NULL_GDT
	rep movsb

;Initializing with a default IDT
	mov di,IDT_ADDRESS
	mov ax,256
.loop_idt:
	mov si,idt
	mov cx,idt_end - idt
	rep movsb
	dec ax
	jnz .loop_idt

;Loading the ldt segment with all zeros
	mov di,LDT_ADDRESS
	mov cx,3 * 8
	xor al,al
	rep stosb

	ret
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;	Switch To protected mode and jump to kernel
;
[GLOBAL _switch_prot]
_switch_prot:
	cli
	lgdt [gdtr]
	mov eax,cr0
	or   al,1
	mov cr0,eax
	db 0x66,0xEA	;jmp KERNEL_CODE_SEL:KERNEL_ADDR
	dd KERNEL_ADDR
	dw KERNEL_CODE_SEL
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

[BITS 32]
unhand:	cli
	mov ax,LINEAR_SEL
	mov gs,ax
	mov byte [gs:0xB809E],'!'
	jmp $
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;The first entry of the gdtr is a null descriptor;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
NULL_GDT:
	dw 0
	dw 0
	db 0
	db 0
	db 0
	db 0
LINEAR_SEL equ $-NULL_GDT
lin_sel:
	dw 0xffff
	dw 0
	db 0
	db 0x92	;It is data segment which can be accessed when rpl = 0 and it is a not a system	segment
	db 0xcf
	db 0
VIDE0_SEL equ $-NULL_GDT
video_sel:
	dw 0xfff
	dw 0x8000
	db 0xb
	db 0x92
	db 0
	db 0
KERNEL_CODE_SEL	equ $-NULL_GDT
kernel_code_sel:
	dw 0xffff
	dw 0x0000
	db 0x00
	db 0x9a;[present] [dpl 00 :2][non-system:1][exec-read:4]
	db 0xcf;[granular][32 bit Register/operands][0][present][limit higher:4]
	db 0
KERNEL_DATA_SEL	equ $-NULL_GDT
kernel_data_sel:
	dw 0xffff
	dw 0
	db 0
	db 0x92
	db 0xcf
	db 0
KERNEL_STACK_SEL equ $-NULL_GDT
kernel_stack_sel:
	dw 0xffff
	dw 0
	db 0
	db 0x92
	db 0xcf
	db 0
LDT_SEL equ $-NULL_GDT
ldt_sel:
	dw 8 * 3 - 1 ;Length of the LDT
	dw LDT_ADDRESS ;default ldt that has to be replaced when a process is created
	db 0	; Higher bits of offset
	db 0x82 ; [present][ring 0 :2][system][ldt :4]
	db 0x50	; [not granular][32 bit Register/operands][0][present][limit higher:4]
	db 0
REAL_CODE_SEL equ $-NULL_GDT
real_code_sel:
	dw 0xffff
	dw 0
	db 1
	db 0x9a
	db 0x10
	db 0
REAL_DATA_SEL equ $-NULL_GDT
real_data_sel:
	dw 0xffff
	dw 0
	db 1
	db 0x92
	db 0x10
	db 0

gdt_end:
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;	End of GDT
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

gdtr:
	dw gdt_end - NULL_GDT -	1
	dd GDT_ADDRESS

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;	IDT Template
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
idt:
	dw unhand + 0xA000
	dw KERNEL_CODE_SEL
	db 0
	db 0x8E
	dw 0
idt_end:

ldtr:
	dw LDT_SEL