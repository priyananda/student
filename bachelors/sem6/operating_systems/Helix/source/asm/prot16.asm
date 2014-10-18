%define REAL_CODE_SEL 0x38
%define REAL_DATA_SEL 0x40
[BITS 16]
	mov di,REAL_DATA_SEL
	mov ds,di
	mov ss,di
	mov esi,eax
	mov eax,cr0
	and al,0xFE
	mov cr0,eax
	mov eax,esi
	jmp far [ebx]
