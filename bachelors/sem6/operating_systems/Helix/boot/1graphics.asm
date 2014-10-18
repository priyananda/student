%define VIDEO_SEG 0xb800
[BITS 16]
segment	_TEXT class=CODE

;;;;;;;;;;;;;;;;;;;;;
; void show_gfx();
;;;;;;;;;;;;;;;;;;;;;
[GLOBAL  _show_gfx]
_show_gfx:
	call _draw_screen_message
	call _show_funky_message
	call _show_loading
	mov cx,3
.start:
	call _play_with_progress
	loop .start
    mov ah,0
	mov al,02
	mov bh,0x20
	int 10h
	ret

;;;;;;;;;;;;;;;;;;;;;
;	void draw_screen_message(void);
;;;;;;;;;;;;;;;;;;;;;
[GLOBAL  _draw_screen_message]
_draw_screen_message:
	call _fill_screen
	mov bx,01
.start:
	cmp bx,23
	jge	.end
	call _fill_partial
	inc bx
	inc bx
	call _delay
	jmp .start
.end
	ret  
;;;;;;;;;;;;;;;;;;;;;
;   void fill_screen(void);
;;;;;;;;;;;;;;;;;;;;;
[GLOBAL _fill_screen]
_fill_screen:
	mov cx,80*50
	mov ax,VIDEO_SEG
	mov es,ax
	mov ax,0
	cld
	xor di,di
	rep stosw
	ret
;;;;;;;;;;;;;;;;;;;;;
; void _fill_partial(void)
;;;;;;;;;;;;;;;;;;;;;
; bx = number of free rows ( must be odd )
[GLOBAL _fill_partial]
_fill_partial:
	mov cx,25
	sub cx,bx
	shr cx,1
	mov ax,cx
	mov dx,80
	mul dx
	mov cx,ax
	xor di,di
	cld
	mov dx,VIDEO_SEG
	mov es,dx
	mov ah,4
	mov al,16
	rep stosw
	mov cx,bx
	mov ax,cx
	mov dx,80
	mul dx
	mov cx,ax
	mov ax,[blank_data]
	rep stosw
	mov cx,25
	sub cx,bx
	shl cx,1
	mov ax,cx
	mov dx,80
	mul dx
	mov cx,ax
	mov ah,1
	mov al,16
	rep stosw
	ret
;;;;;;;;;;;;;;;;;;;;;
;void delay(void);
;;;;;;;;;;;;;;;;;;;;;
_delay:
    push ax
    push dx
    push cx
    mov cx , 2
    mov dx , 0ffh
    mov ah , 86h
    int 15h
    pop cx
    pop dx
    pop ax
    ret


_show_funky_message:
	mov di,18*80
	mov cx,80
	mov ah,32 | 1
	mov al,21
	rep stosw
	mov di,22*80
	mov cx,80
	mov ah,32 | 1
	mov al,21
	rep stosw
	mov bx,0
.start:
	cmp bx,60
	jge .end
	call _show_message
	inc bx
	inc bx
	call _delay
	jmp .start
.end:
	ret

; bx = left offset
_show_message:
	mov di,20*80
	mov cx,80
	mov ah,32
	mov al,' '
	rep stosw
	mov di,20*80
	add di,bx
	mov si,message_data
	mov cx,[size]
	rep movsb
	ret

_play_with_progress:
	push cx
	mov di,30*80
	add di,38
	mov cx,32
	mov ah,48
	mov al,' '
	rep stosw
	mov di,34*80
	add di,38
	mov cx,32
	mov ah,48
	mov al,' '
	rep stosw
	mov di,32*80 + 18
	stosw 
	mov di,32*80 + 100
	stosw
	mov bx,20
.start:
	cmp bx,50
	jge .end
	call _draw_progress
	inc bx
	inc bx
	inc bx
	call _delay
	jmp .start
.end:
	pop cx
	ret

; bx = left offset
_draw_progress:
	mov di,32*80
	mov cx,80
	mov ah,0
	mov al,' '
	rep stosw
	mov ah,48
	mov di,32*80 + 38
	stosw 
	mov di,32*80 + 100
	stosw
	mov di,32*80
	add di,bx
	add di,bx
	mov ah,16
	mov al,' '
	mov cx,3
	rep stosw
	ret

; void get_cpu();
[GLOBAL _get_cpu]
_get_cpu:
	xor eax,eax
	cpuid
	add edx,'AAAA'
	mov [cpu_str],edx
	add ebx,'AAAA'
	mov [cpu_str + 4],edx
	add ecx,'AAAA'
	mov [cpu_str + 8],edx
	ret

_show_loading:
	cld
	mov di,28*80 + 46
	mov si,loading_msg
	mov cx,[l_size]
	rep movsb
	ret		


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; out : AX-DX contains mem size
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
[GLOBAL _get_mem_size]
_get_mem_size:
	stc             ; I don't know why
    mov eax,0e801h  ; 'e' is just for fun
    xor ecx,ecx
    xor edx,edx
    xor ebx,ebx
	int 15h
	; CX = size of RAM upto 16M ( in k )
	; DX = size of RAM after 16M ( in 64k blocks)
	; so total_memory ( in Kb )  = DX * 40 + CX
	; I spent hours figuring this out!!!!!!!!
	mov ax,dx
	mov bx,40h
	mul bx
	add ax,cx
	adc dx,0
	; the Result is in DX-AX . invert it for convenience
	xchg ax,dx
	; memory size now in AX-DX
    ret
	

_proc_dispch:
	push bp
    mov ah,0eh
    mov bx,_data_tab
    push cs
    pop bp
    xlat
    mov bx,64h
    int 10h
	pop bp
    ret
_data_tab: db '0123456789ABCDEF'
	     
;; end of procedure disp char


;;Start of procedure dispint - display s an integer in ax
; hardcoded , but much faster .... loop unrolling !!!!!!!
[GLOBAL _dispint]
_dispint:
	mov di,ax
	shr ax,12
	call _proc_dispch
	mov ax,di
	shr ax,8
	and ax,0fh
	call _proc_dispch
	mov ax,di
	shr ax,4
	and ax,0fh
	call _proc_dispch
	mov ax,di
	and ax,0fh
	call _proc_dispch
	ret



blank_data: db ' ',0; 
door_data:	db ' ',16;
message_data:  db 'H',0x20,'E',0x20,'L',0x20,'I',0x20,'X',0x20
size  dw $ - message_data
loading_msg: db 'L' , 7 , 'o', 7 ,'a', 7 ,'d', 7 ,'i', 7 ,'n', 7 ,'g', 7 
			 db  ' ', 7 , '.', 7 ,'.', 7 ,'.', 7 ,'.', 7 ,'.', 7 
l_size  dw $ - loading_msg
cpu_str: times 13 db 0