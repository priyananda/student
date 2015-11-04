;_____________________________________________________________________________
; boot12.asm  FAT12 bootstrap for real mode image or loader
; Version 1.0, Jul 5, 1999
; Sample code
; by John S. Fine  johnfine@erols.com
; I do not place any restrictions on your use of this source code
; I do not provide any warranty of the correctness of this source code
;_____________________________________________________________________________
%define ROOT_SEG	0x60
%define FAT_SEG		0x800
%define IMAGE_SEG	0xA00

%if ROOT_SEG & 31
	%error "ROOT_SEG must be divisible by 0x20"
%endif
%if ROOT_SEG > 0xC00
	%error "Root directory must fit within first 64Kb"
%endif
%if FAT_SEG & 31
	%error "FAT_SEG must be divisible by 0x20"
%endif
%if FAT_SEG > 0xE80
	%error "FAT must fit within first 64Kb"
%endif
%if IMAGE_SEG & 31
	%error "IMAGE_SEG must be divisible by 0x20"
%endif

; The following %define directives declare the parts of the FAT12 "DOS BOOT
; RECORD" that are used by this code, based on BP being set to 7C00.
;
%define	sc_p_clu	bp+0Dh		;byte  Sectors per cluster
%define	sc_b4_fat	bp+0Eh		;word  Sectors (in partition) before FAT
%define	fats		bp+10h		;byte  Number of FATs
%define dir_ent		bp+11h		;word  Number of root directory entries
%define	sc_p_fat	bp+16h		;word  Sectors per FAT
%define sc_p_trk	bp+18h		;word  Sectors per track
%define heads		bp+1Ah		;word  Number of heads
%define sc_b4_prt	bp+1Ch		;dword Sectors before partition
%define drive		bp+24h		;byte  Drive number

	org	0x7C00

entry:
	jmp	short begin
	nop

; Skip over the data portion of the "DOS BOOT RECORD".  The install method
; must merge the code from this ASM with the data put in the boot record
; by the FAT12 formatter.
;
	times 0x3B db 0

begin:
	xor	ax, ax
	mov	ds, ax
	mov	ss, ax
	mov	sp, 0x7C00
	mov	bp, sp
	mov	[drive], dl		;Drive number

	mov	al, [fats]		;Number of FATs
	mul	word [sc_p_fat]	; * Sectors per FAT
	add	ax, [sc_b4_fat]	; + Sectors before FAT
						;AX = Sector of Root directory

	mov	si, [dir_ent]	;Max root directory entries
	mov	cl, 4
	dec	si
	shr	si, cl
	inc	si				;SI = Length of root in sectors

	mov	di, ROOT_SEG/32	;Buffer (paragraph / 32)
	call	read_16		;Read root directory
	mov si, smsg1
	call    showmsg
	push	ax			;Sector of cluster two
%define sc_clu2 bp-2	;Later access to the word just pushed is via bp

	mov	dx, [dir_ent]	;Number of directory entries
	push ds
	pop	es
	mov	di, ROOT_SEG*16

search:
	dec	dx				;Any more directory entries?
	js	error1			;No
	mov	si, filename	;Name we are searching for
	mov	cx, 11			;11 characters long
	lea	ax, [di+0x20]	;Precompute next entry address
	push	ax
	repe cmpsb			;Compare
	pop	di
	jnz	search			;Repeat until match

	push word [di-6]	;Starting cluster number

	mov	ax, [sc_b4_fat]	;Sector number of FAT
	mov	si, [sc_p_fat]	;Length of FAT
	mov	di, FAT_SEG/32	;Buffer (paragraph / 32)
	call	read_16		;Read FAT

	mov si, smsg2
	call showmsg

next:
	pop	bx			;Cluster number
	mov	si, bx		;First cluster in this sequence
	mov	ax, bx		;Last cluster in this sequence

.0:
	cmp	bx, 0xFF8	;End of file?
	jae	.2			;Yes
	inc	ax			;Last cluster plus one in sequence

	;Look in FAT for next cluster
	mov	di, bx		;Cluster number
	rcr	bx, 1		;1.5 byte entry per cluster
					;bx = 0x8000 + cluster/2
					;c-bit set for odd clusters

	mov	bx, [bx+di+FAT_SEG*16-0x8000]
	jnc	.1
	shr	bx, 1
	shr	bx, 1
	shr	bx, 1
	shr	bx, 1
.1:	and	bh, 0xF

	cmp	ax, bx		;Is the next one contiguous?
	je	.0			;Yes: look further ahead
.2:	sub	ax, si		;How many contiguous in this sequence?
	jz	eof			;None, must be done.

	push	bx		;Save next (eof or discontiguous) cluster

	mov	bl, [sc_p_clu]	;Sectors per cluster
	mov	bh, 0			;  as a word
	mul	bx				;Length of sequence in sectors
.3:	mov	di, IMAGE_SEG/32 ;Destination (paragraph / 32)
	add	[.3+1], ax		;Precompute next destination
	xchg	ax, si		;AX = starting cluster ;SI = length in sectors
	dec	ax
	dec	ax		;Starting cluster minus two
	mul	bx		; * sectors per cluster
	add	ax, [sc_clu2]	; + sector number of cluster two
	adc	dl, dh		;Allow 24-bit result

	call	read_32		;Read it
	jmp	short next	;Look for more

eof:
	mov si, smsg3
	call showmsg
	jmp	IMAGE_SEG:0x0000

error1:	mov	si, errmsg1
	jmp j2

error2:	mov	si, errmsg2
j2:
	mov	ax, 0xE0D	;Start message with CR
	mov	bx, 7
.1:	int	10h
	lodsb
	test	al, al
	jnz	.1
	xor	ah, ah
	int	16h		;Wait for a key
	int	19h		;Try to reboot

read_16:
	xor	dx, dx

read_32:
;
; Input:
;    dx:ax = sector within partition
;    si    = sector count
;    di    = destination segment / 32
;
; The sector number is converted from a partition-relative to a whole-disk
; (LBN) value, and then converted to CHS form, and then the sectors are read
; into (di*32):0.
;
; Output:
;    dx:ax  updated (sector count added)
;    di     updated (sector count added)
;    si = 0
;    bp, ds preserved
;    bx, cx, es modified

.1:	push	dx			;(high) relative sector
	push	ax			;(low) relative sector

	add	ax, [sc_b4_prt]		;Convert to LBN
	adc	dx, [sc_b4_prt+2]

	mov	bx, [sc_p_trk]		;Sectors per track
	div	bx			;AX = track ;DX = sector-1
	sub	bx, dx			;Sectors remaining, this track
	cmp	bx, si			;More than we want?
	jbe	.2			;No
	mov	bx, si			;Yes: Transfer just what we want
.2:	inc	dx			;Sector number
	mov	cx, dx			;CL = sector ;CH = 0
	cwd				;(This supports up to 32767 tracks
	div	word [heads]		;Track number / Number of heads
	mov	dh, dl			;DH = head

	xchg	ch, al			;CH = (low) cylinder  ;AL=0
	ror	ah, 1			;rotate (high) cylinder
	ror	ah, 1
	add	cl, ah			;CL = combine: sector, (high) cylinder

	sub	ax, di
	and	ax, byte 0x7F		;AX = sectors to next 64Kb boundary
	jz	.3			;On a 64Kb boundary already
	cmp	ax, bx			;More than we want?
	jbe	.4			;No
.3:	xchg	ax, bx			;Yes: Transfer just what we want
.4:	push	ax			;Save length
	mov	bx, di			;Compute destination seg
	push	cx
	mov	cl, 5
	shl	bx, cl
	pop	cx
	mov	es, bx
	xor	bx, bx			;ES:BX = address
	mov	dl, [drive]		;DL = Drive number
	mov	ah, 2			;AH = Read command
	int	13h			;Do it
	jc	error2
	pop	bx			;Length
	pop	ax			;(low) relative sector
	pop	dx			;(high) relative sector
	add	ax, bx			;Update relative sector
	adc	dl, dh
	add	di, bx			;Update destination
	sub	si, bx			;Update count
	jnz	.1			;Read some more
	ret

showmsg:
	push ax
	push bx
	mov	ax, 0xE0D	;Start message with CR
	mov	bx, 7
.1:	int	10h
	lodsb
	test al, al
	jnz .1
	xor	ah, ah
	int	16h		;Wait for a key
	pop bx
	pop ax
	ret

errmsg1 db 10, "E1", 10, 0
errmsg2 db 10, "E2", 10, 0
smsg1 db 10, "S1", 10, 0
smsg2 db 10, "Fat Read", 10, 0
smsg3 db 10, "Boot1 jmp", 10, 0
errmsg	db	10,"Error Executing FAT12 bootsector",13
	db	10,"Press any key to reboot",13,10,0
size	equ	$ - entry
%if size+11+2 > 512
  %error "code is too large for boot sector"
%endif
	times	(512 - size - 11 - 2) db 0

filename db	"BOOT1   BIN"		;11 byte name
	db	0x55, 0xAA		;2  byte boot signature
