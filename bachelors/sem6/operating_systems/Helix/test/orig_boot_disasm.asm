00000000  8CC8              mov ax,cs
00000002  8ED8              mov ds,ax
00000004  8EC0              mov es,ax
00000006  FA                cli
00000007  31C0              xor ax,ax
00000009  8ED0              mov ss,ax
0000000B  BC0000            mov sp,0x0
0000000E  FB                sti
0000000F  E8C300            call word 0xd5
00000012  CD19              int 0x19
00000014  BB0000            mov bx,0x0
00000017  B40E              mov ah,0xe
00000019  8A04              mov al,[si]
0000001B  46                inc si
0000001C  08C0              or al,al
0000001E  7405              jz 0x25
00000020  CD10              int 0x10
00000022  E9F4FF            jmp word 0x19
00000025  C3                ret
00000026  31C0              xor ax,ax
00000028  8EC0              mov es,ax
0000002A  FC                cld
0000002B  BE7D00            mov si,0x7d
0000002E  BF007C            mov di,0x7c00
00000031  B94800            mov cx,0x48
00000034  F3A4              rep movsb
00000036  BF0080            mov di,0x8000
00000039  B80001            mov ax,0x100
0000003C  BECB00            mov si,0xcb
0000003F  B90800            mov cx,0x8
00000042  F3A4              rep movsb
00000044  48                dec ax
00000045  75F5              jnz 0x3c
00000047  BF0090            mov di,0x9000
0000004A  B91800            mov cx,0x18
0000004D  30C0              xor al,al
0000004F  F3AA              rep stosb
00000051  C3                ret
00000052  FA                cli
00000053  0F0116C500        lgdt [0xc5]
00000058  0F20C0            mov eax,cr0
0000005B  0C01              or al,0x1
0000005D  0F22C0            mov cr0,eax
00000060  66EA000001001800  jmp dword 0x18:0x10000
00000068  FA                cli
00000069  66B80800668E      mov eax,0x8e660008
0000006F  E865C6            call word 0xc6d7
00000072  059E80            add ax,0x809e
00000075  0B00              or ax,[bx+si]
00000077  21E9              and cx,bp
00000079  FB                sti
0000007A  FF                db 0xff
0000007B  FF                db 0xff
0000007C  FF00              inc word [bx+si]
0000007E  0000              add [bx+si],al
00000080  0000              add [bx+si],al
00000082  0000              add [bx+si],al
00000084  00FF              add bh,bh
00000086  FF00              inc word [bx+si]
00000088  0000              add [bx+si],al
0000008A  92                xchg ax,dx
0000008B  CF                iretw
0000008C  00FF              add bh,bh
0000008E  0F00800B92        sldt [bx+si-0x6df5]
00000093  0000              add [bx+si],al
00000095  FF                db 0xff
00000096  FF00              inc word [bx+si]
00000098  0000              add [bx+si],al
0000009A  9ACF00FFFF        call word 0xffff:0xcf
0000009F  0000              add [bx+si],al
000000A1  0092CF00          add [bp+si+0xcf],dl
000000A5  FF                db 0xff
000000A6  FF00              inc word [bx+si]
000000A8  0000              add [bx+si],al
000000AA  92                xchg ax,dx
000000AB  CF                iretw
000000AC  0017              add [bx],dl
000000AE  0000              add [bx+si],al
000000B0  90                nop
000000B1  00825000          add [bp+si+0x50],al
000000B5  FF                db 0xff
000000B6  FF00              inc word [bx+si]
000000B8  0001              add [bx+di],al
000000BA  9A1000FFFF        call word 0xffff:0x10
000000BF  0000              add [bx+si],al
000000C1  01921000          add [bp+si+0x10],dx
000000C5  47                inc di
000000C6  0000              add [bx+si],al
000000C8  7C00              jl 0xca
000000CA  0068A0            add [bx+si-0x60],ch
000000CD  1800              sbb [bx+si],al
000000CF  008E0000          add [bp+0x0],cl
000000D3  3000              xor [bx+si],al
000000D5  55                push bp
000000D6  8BEC              mov bp,sp
000000D8  E81207            call word 0x7ed
000000DB  B84209            mov ax,0x942
000000DE  50                push ax
000000DF  E8AD06            call word 0x78f
000000E2  59                pop cx
000000E3  E840FF            call word 0x26
000000E6  B86209            mov ax,0x962
000000E9  50                push ax
000000EA  E8A206            call word 0x78f
000000ED  59                pop cx
000000EE  E861FF            call word 0x52
000000F1  CD19              int 0x19
000000F3  33C0              xor ax,ax
000000F5  EB00              jmp short 0xf7
000000F7  5D                pop bp
000000F8  C3                ret
000000F9  55                push bp
000000FA  8BEC              mov bp,sp
000000FC  31C0              xor ax,ax
000000FE  30D2              xor dl,dl
00000100  CD13              int 0x13
00000102  A32621            mov [0x2126],ax
00000105  B108              mov cl,0x8
00000107  D32E2621          shr word [0x2126],cl
0000010B  A12621            mov ax,[0x2126]
0000010E  EB00              jmp short 0x110
00000110  5D                pop bp
00000111  C3                ret
00000112  55                push bp
00000113  8BEC              mov bp,sp
00000115  83EC04            sub sp,byte +0x4
00000118  833E262100        cmp word [0x2126],byte +0x0
0000011D  7403              jz 0x122
0000011F  E8D7FF            call word 0xf9
00000122  EB03              jmp short 0x127
00000124  E8D2FF            call word 0xf9
00000127  833E262106        cmp word [0x2126],byte +0x6
0000012C  74F6              jz 0x124
0000012E  833E262100        cmp word [0x2126],byte +0x0
00000133  7405              jz 0x13a
00000135  A12621            mov ax,[0x2126]
00000138  EB50              jmp short 0x18a
0000013A  8B4604            mov ax,[bp+0x4]
0000013D  BB1200            mov bx,0x12
00000140  33D2              xor dx,dx
00000142  F7F3              div bx
00000144  FEC2              inc dl
00000146  8856FD            mov [bp-0x3],dl
00000149  8B4604            mov ax,[bp+0x4]
0000014C  BB1200            mov bx,0x12
0000014F  33D2              xor dx,dx
00000151  F7F3              div bx
00000153  2401              and al,0x1
00000155  8846FF            mov [bp-0x1],al
00000158  8B4604            mov ax,[bp+0x4]
0000015B  BB2400            mov bx,0x24
0000015E  33D2              xor dx,dx
00000160  F7F3              div bx
00000162  8846FE            mov [bp-0x2],al
00000165  A12421            mov ax,[0x2124]
00000168  8EC0              mov es,ax
0000016A  B402              mov ah,0x2
0000016C  B001              mov al,0x1
0000016E  8B1E2221          mov bx,[0x2122]
00000172  8A76FF            mov dh,[bp-0x1]
00000175  B200              mov dl,0x0
00000177  8A6EFE            mov ch,[bp-0x2]
0000017A  8A4EFD            mov cl,[bp-0x3]
0000017D  CD13              int 0x13
0000017F  A32621            mov [0x2126],ax
00000182  B108              mov cl,0x8
00000184  D32E2621          shr word [0x2126],cl
00000188  EBAB              jmp short 0x135
0000018A  8BE5              mov sp,bp
0000018C  5D                pop bp
0000018D  C3                ret
0000018E  55                push bp
0000018F  8BEC              mov bp,sp
00000191  83EC0C            sub sp,byte +0xc
00000194  C746FE1300        mov word [bp-0x2],0x13
00000199  C746F67C09        mov word [bp-0xa],0x97c
0000019E  C7062421000A      mov word [0x2124],0xa00
000001A4  C7062221220D      mov word [0x2122],0xd22
000001AA  C746FC0000        mov word [bp-0x4],0x0
000001AF  E9C100            jmp word 0x273
000001B2  8B46FE            mov ax,[bp-0x2]
000001B5  FF46FE            inc word [bp-0x2]
000001B8  50                push ax
000001B9  E856FF            call word 0x112
000001BC  59                pop cx
000001BD  0BC0              or ax,ax
000001BF  740D              jz 0x1ce
000001C1  B88809            mov ax,0x988
000001C4  50                push ax
000001C5  E8EC06            call word 0x8b4
000001C8  59                pop cx
000001C9  33C0              xor ax,ax
000001CB  E9B100            jmp word 0x27f
000001CE  C746F4220D        mov word [bp-0xc],0xd22
000001D3  C746FA0000        mov word [bp-0x6],0x0
000001D8  E98C00            jmp word 0x267
000001DB  8B46FA            mov ax,[bp-0x6]
000001DE  B105              mov cl,0x5
000001E0  D3E0              shl ax,cl
000001E2  8B5EF4            mov bx,[bp-0xc]
000001E5  03D8              add bx,ax
000001E7  803F00            cmp byte [bx],0x0
000001EA  7478              jz 0x264
000001EC  8B46FA            mov ax,[bp-0x6]
000001EF  B105              mov cl,0x5
000001F1  D3E0              shl ax,cl
000001F3  8B5EF4            mov bx,[bp-0xc]
000001F6  03D8              add bx,ax
000001F8  803FE5            cmp byte [bx],0xe5
000001FB  7467              jz 0x264
000001FD  8B46FA            mov ax,[bp-0x6]
00000200  B105              mov cl,0x5
00000202  D3E0              shl ax,cl
00000204  8B5EF4            mov bx,[bp-0xc]
00000207  03D8              add bx,ax
00000209  F6470B08          test byte [bx+0xb],0x8
0000020D  7555              jnz 0x264
0000020F  8B46FA            mov ax,[bp-0x6]
00000212  B105              mov cl,0x5
00000214  D3E0              shl ax,cl
00000216  8B5EF4            mov bx,[bp-0xc]
00000219  03D8              add bx,ax
0000021B  F6470B10          test byte [bx+0xb],0x10
0000021F  7543              jnz 0x264
00000221  C746F80000        mov word [bp-0x8],0x0
00000226  EB03              jmp short 0x22b
00000228  FF46F8            inc word [bp-0x8]
0000022B  837EF80B          cmp word [bp-0x8],byte +0xb
0000022F  7D1B              jnl 0x24c
00000231  8B46FA            mov ax,[bp-0x6]
00000234  B105              mov cl,0x5
00000236  D3E0              shl ax,cl
00000238  8B5EF4            mov bx,[bp-0xc]
0000023B  03D8              add bx,ax
0000023D  035EF8            add bx,[bp-0x8]
00000240  8A07              mov al,[bx]
00000242  8B5EF6            mov bx,[bp-0xa]
00000245  035EF8            add bx,[bp-0x8]
00000248  3A07              cmp al,[bx]
0000024A  74DC              jz 0x228
0000024C  837EF80B          cmp word [bp-0x8],byte +0xb
00000250  7512              jnz 0x264
00000252  8B46FA            mov ax,[bp-0x6]
00000255  B105              mov cl,0x5
00000257  D3E0              shl ax,cl
00000259  8B5EF4            mov bx,[bp-0xc]
0000025C  03D8              add bx,ax
0000025E  8B471A            mov ax,[bx+0x1a]
00000261  E967FF            jmp word 0x1cb
00000264  FF46FA            inc word [bp-0x6]
00000267  837EFA10          cmp word [bp-0x6],byte +0x10
0000026B  7D03              jnl 0x270
0000026D  E96BFF            jmp word 0x1db
00000270  FF46FC            inc word [bp-0x4]
00000273  837EFC0E          cmp word [bp-0x4],byte +0xe
00000277  7D03              jnl 0x27c
00000279  E936FF            jmp word 0x1b2
0000027C  E94AFF            jmp word 0x1c9
0000027F  8BE5              mov sp,bp
00000281  5D                pop bp
00000282  C3                ret
00000283  55                push bp
00000284  8BEC              mov bp,sp
00000286  83EC04            sub sp,byte +0x4
00000289  C746FE0000        mov word [bp-0x2],0x0
0000028E  8B4604            mov ax,[bp+0x4]
00000291  BA0300            mov dx,0x3
00000294  F7EA              imul dx
00000296  BB0200            mov bx,0x2
00000299  99                cwd
0000029A  F7FB              idiv bx
0000029C  8946FC            mov [bp-0x4],ax
0000029F  8B4604            mov ax,[bp+0x4]
000002A2  BB0200            mov bx,0x2
000002A5  99                cwd
000002A6  F7FB              idiv bx
000002A8  0BD2              or dx,dx
000002AA  7524              jnz 0x2d0
000002AC  8B5EFC            mov bx,[bp-0x4]
000002AF  8A87230F          mov al,[bx+0xf23]
000002B3  B400              mov ah,0x0
000002B5  250F00            and ax,0xf
000002B8  8946FE            mov [bp-0x2],ax
000002BB  8B46FE            mov ax,[bp-0x2]
000002BE  B108              mov cl,0x8
000002C0  D3E0              shl ax,cl
000002C2  8946FE            mov [bp-0x2],ax
000002C5  8B5EFC            mov bx,[bp-0x4]
000002C8  8A87220F          mov al,[bx+0xf22]
000002CC  B400              mov ah,0x0
000002CE  EB26              jmp short 0x2f6
000002D0  8B5EFC            mov bx,[bp-0x4]
000002D3  8A87230F          mov al,[bx+0xf23]
000002D7  B400              mov ah,0x0
000002D9  8946FE            mov [bp-0x2],ax
000002DC  8B46FE            mov ax,[bp-0x2]
000002DF  B104              mov cl,0x4
000002E1  D3E0              shl ax,cl
000002E3  8946FE            mov [bp-0x2],ax
000002E6  8B5EFC            mov bx,[bp-0x4]
000002E9  8A87220F          mov al,[bx+0xf22]
000002ED  B400              mov ah,0x0
000002EF  25F000            and ax,0xf0
000002F2  B104              mov cl,0x4
000002F4  D3F8              sar ax,cl
000002F6  8B56FE            mov dx,[bp-0x2]
000002F9  0BD0              or dx,ax
000002FB  8956FE            mov [bp-0x2],dx
000002FE  8B46FE            mov ax,[bp-0x2]
00000301  EB00              jmp short 0x303
00000303  8BE5              mov sp,bp
00000305  5D                pop bp
00000306  C3                ret
00000307  55                push bp
00000308  8BEC              mov bp,sp
0000030A  83EC02            sub sp,byte +0x2
0000030D  C7062421000A      mov word [0x2124],0xa00
00000313  C7062221220F      mov word [0x2122],0xf22
00000319  C746FE0000        mov word [bp-0x2],0x0
0000031E  EB20              jmp short 0x340
00000320  8B46FE            mov ax,[bp-0x2]
00000323  40                inc ax
00000324  50                push ax
00000325  E8EAFD            call word 0x112
00000328  59                pop cx
00000329  0BC0              or ax,ax
0000032B  740A              jz 0x337
0000032D  B89C09            mov ax,0x99c
00000330  50                push ax
00000331  E88005            call word 0x8b4
00000334  59                pop cx
00000335  EB06              jmp short 0x33d
00000337  810622210002      add word [0x2122],0x200
0000033D  FF46FE            inc word [bp-0x2]
00000340  837EFE09          cmp word [bp-0x2],byte +0x9
00000344  7CDA              jl 0x320
00000346  8BE5              mov sp,bp
00000348  5D                pop bp
00000349  C3                ret
0000034A  55                push bp
0000034B  8BEC              mov bp,sp
0000034D  83EC02            sub sp,byte +0x2
00000350  E83BFE            call word 0x18e
00000353  8946FE            mov [bp-0x2],ax
00000356  837EFE00          cmp word [bp-0x2],byte +0x0
0000035A  750C              jnz 0x368
0000035C  B8AB09            mov ax,0x9ab
0000035F  50                push ax
00000360  E85105            call word 0x8b4
00000363  59                pop cx
00000364  33C0              xor ax,ax
00000366  EB14              jmp short 0x37c
00000368  E89CFF            call word 0x307
0000036B  C70624210010      mov word [0x2124],0x1000
00000371  C70622210000      mov word [0x2122],0x0
00000377  8B46FE            mov ax,[bp-0x2]
0000037A  EBEA              jmp short 0x366
0000037C  8BE5              mov sp,bp
0000037E  5D                pop bp
0000037F  C3                ret
00000380  55                push bp
00000381  8BEC              mov bp,sp
00000383  83EC02            sub sp,byte +0x2
00000386  837E0400          cmp word [bp+0x4],byte +0x0
0000038A  7426              jz 0x3b2
0000038C  817E04F00F        cmp word [bp+0x4],0xff0
00000391  7D1F              jnl 0x3b2
00000393  8B4604            mov ax,[bp+0x4]
00000396  051F00            add ax,0x1f
00000399  8946FE            mov [bp-0x2],ax
0000039C  FF76FE            push word [bp-0x2]
0000039F  E870FD            call word 0x112
000003A2  59                pop cx
000003A3  FF7604            push word [bp+0x4]
000003A6  E8DAFE            call word 0x283
000003A9  59                pop cx
000003AA  894604            mov [bp+0x4],ax
000003AD  8306242120        add word [0x2124],byte +0x20
000003B2  817E04F00F        cmp word [bp+0x4],0xff0
000003B7  7C05              jl 0x3be
000003B9  C746040000        mov word [bp+0x4],0x0
000003BE  8B4604            mov ax,[bp+0x4]
000003C1  EB00              jmp short 0x3c3
000003C3  8BE5              mov sp,bp
000003C5  5D                pop bp
000003C6  C3                ret
000003C7  55                push bp
000003C8  8BEC              mov bp,sp
000003CA  83EC04            sub sp,byte +0x4
000003CD  C70626210100      mov word [0x2126],0x1
000003D3  E8B8FD            call word 0x18e
000003D6  8946FE            mov [bp-0x2],ax
000003D9  837EFE00          cmp word [bp-0x2],byte +0x0
000003DD  750A              jnz 0x3e9
000003DF  B8C009            mov ax,0x9c0
000003E2  50                push ax
000003E3  E8CE04            call word 0x8b4
000003E6  59                pop cx
000003E7  EB3D              jmp short 0x426
000003E9  E81BFF            call word 0x307
000003EC  C70624210010      mov word [0x2124],0x1000
000003F2  C70622210000      mov word [0x2122],0x0
000003F8  EB1F              jmp short 0x419
000003FA  8B46FE            mov ax,[bp-0x2]
000003FD  051F00            add ax,0x1f
00000400  8946FC            mov [bp-0x4],ax
00000403  FF76FC            push word [bp-0x4]
00000406  E809FD            call word 0x112
00000409  59                pop cx
0000040A  FF76FE            push word [bp-0x2]
0000040D  E873FE            call word 0x283
00000410  59                pop cx
00000411  8946FE            mov [bp-0x2],ax
00000414  8306242120        add word [0x2124],byte +0x20
00000419  837EFE00          cmp word [bp-0x2],byte +0x0
0000041D  7407              jz 0x426
0000041F  817EFEF00F        cmp word [bp-0x2],0xff0
00000424  7CD4              jl 0x3fa
00000426  8BE5              mov sp,bp
00000428  5D                pop bp
00000429  C3                ret
0000042A  E82200            call word 0x44f
0000042D  E89E00            call word 0x4ce
00000430  E8AB01            call word 0x5de
00000433  06                push es
00000434  E813FF            call word 0x34a
00000437  07                pop es
00000438  A38007            mov [0x780],ax
0000043B  E81001            call word 0x54e
0000043E  813E80070000      cmp word [0x780],0x0
00000444  75F5              jnz 0x43b
00000446  B400              mov ah,0x0
00000448  B002              mov al,0x2
0000044A  B720              mov bh,0x20
0000044C  CD10              int 0x10
0000044E  C3                ret
0000044F  E81500            call word 0x467
00000452  BB0100            mov bx,0x1
00000455  81FB1700          cmp bx,0x17
00000459  7D0B              jnl 0x466
0000045B  E81A00            call word 0x478
0000045E  43                inc bx
0000045F  43                inc bx
00000460  E85A00            call word 0x4bd
00000463  E9EFFF            jmp word 0x455
00000466  C3                ret
00000467  B9A00F            mov cx,0xfa0
0000046A  B800B8            mov ax,0xb800
0000046D  8EC0              mov es,ax
0000046F  B80000            mov ax,0x0
00000472  FC                cld
00000473  31FF              xor di,di
00000475  F3AB              rep stosw
00000477  C3                ret
00000478  B91900            mov cx,0x19
0000047B  29D9              sub cx,bx
0000047D  D1E9              shr cx,1
0000047F  89C8              mov ax,cx
00000481  BA5000            mov dx,0x50
00000484  F7E2              mul dx
00000486  89C1              mov cx,ax
00000488  31FF              xor di,di
0000048A  FC                cld
0000048B  BA00B8            mov dx,0xb800
0000048E  8EC2              mov es,dx
00000490  B410              mov ah,0x10
00000492  B020              mov al,0x20
00000494  F3AB              rep stosw
00000496  89D9              mov cx,bx
00000498  89C8              mov ax,cx
0000049A  BA5000            mov dx,0x50
0000049D  F7E2              mul dx
0000049F  89C1              mov cx,ax
000004A1  A16A06            mov ax,[0x66a]
000004A4  F3AB              rep stosw
000004A6  B91900            mov cx,0x19
000004A9  29D9              sub cx,bx
000004AB  D1E1              shl cx,1
000004AD  89C8              mov ax,cx
000004AF  BA5000            mov dx,0x50
000004B2  F7E2              mul dx
000004B4  89C1              mov cx,ax
000004B6  B410              mov ah,0x10
000004B8  B020              mov al,0x20
000004BA  F3AB              rep stosw
000004BC  C3                ret
000004BD  50                push ax
000004BE  52                push dx
000004BF  51                push cx
000004C0  B90200            mov cx,0x2
000004C3  BAFF00            mov dx,0xff
000004C6  B486              mov ah,0x86
000004C8  CD15              int 0x15
000004CA  59                pop cx
000004CB  5A                pop dx
000004CC  58                pop ax
000004CD  C3                ret
000004CE  BF6004            mov di,0x460
000004D1  B95000            mov cx,0x50
000004D4  B48F              mov ah,0x8f
000004D6  B00F              mov al,0xf
000004D8  F3AB              rep stosw
000004DA  BF2008            mov di,0x820
000004DD  B95000            mov cx,0x50
000004E0  B48F              mov ah,0x8f
000004E2  B00E              mov al,0xe
000004E4  F3AB              rep stosw
000004E6  BB0000            mov bx,0x0
000004E9  81FB3C00          cmp bx,0x3c
000004ED  7D0B              jnl 0x4fa
000004EF  E80900            call word 0x4fb
000004F2  43                inc bx
000004F3  43                inc bx
000004F4  E8C6FF            call word 0x4bd
000004F7  E9EFFF            jmp word 0x4e9
000004FA  C3                ret
000004FB  BF0005            mov di,0x500
000004FE  B99001            mov cx,0x190
00000501  B428              mov ah,0x28
00000503  B020              mov al,0x20
00000505  F3AB              rep stosw
00000507  BF0005            mov di,0x500
0000050A  01DF              add di,bx
0000050C  BE7906            mov si,0x679
0000050F  8B0EA506          mov cx,[0x6a5]
00000513  F3A4              rep movsb
00000515  BFA005            mov di,0x5a0
00000518  01DF              add di,bx
0000051A  BEA706            mov si,0x6a7
0000051D  8B0EA506          mov cx,[0x6a5]
00000521  F3A4              rep movsb
00000523  BF4006            mov di,0x640
00000526  01DF              add di,bx
00000528  BED306            mov si,0x6d3
0000052B  8B0EA506          mov cx,[0x6a5]
0000052F  F3A4              rep movsb
00000531  BFE006            mov di,0x6e0
00000534  01DF              add di,bx
00000536  BEFF06            mov si,0x6ff
00000539  8B0EA506          mov cx,[0x6a5]
0000053D  F3A4              rep movsb
0000053F  BF8007            mov di,0x780
00000542  01DF              add di,bx
00000544  BE2B07            mov si,0x72b
00000547  8B0EA506          mov cx,[0x6a5]
0000054B  F3A4              rep movsb
0000054D  C3                ret
0000054E  51                push cx
0000054F  BF6009            mov di,0x960
00000552  81C72600          add di,0x26
00000556  B92000            mov cx,0x20
00000559  B430              mov ah,0x30
0000055B  B020              mov al,0x20
0000055D  F3AB              rep stosw
0000055F  BFA00A            mov di,0xaa0
00000562  81C72600          add di,0x26
00000566  B92000            mov cx,0x20
00000569  B430              mov ah,0x30
0000056B  B020              mov al,0x20
0000056D  F3AB              rep stosw
0000056F  BF120A            mov di,0xa12
00000572  AB                stosw
00000573  BF640A            mov di,0xa64
00000576  AB                stosw
00000577  BB1400            mov bx,0x14
0000057A  81FB3200          cmp bx,0x32
0000057E  7D21              jnl 0x5a1
00000580  E82000            call word 0x5a3
00000583  43                inc bx
00000584  43                inc bx
00000585  43                inc bx
00000586  53                push bx
00000587  57                push di
00000588  06                push es
00000589  52                push dx
0000058A  51                push cx
0000058B  FF368007          push word [0x780]
0000058F  E8EEFD            call word 0x380
00000592  8F068007          pop word [0x780]
00000596  A38007            mov [0x780],ax
00000599  59                pop cx
0000059A  5A                pop dx
0000059B  07                pop es
0000059C  5F                pop di
0000059D  5B                pop bx
0000059E  E9D9FF            jmp word 0x57a
000005A1  59                pop cx
000005A2  C3                ret
000005A3  BF000A            mov di,0xa00
000005A6  B95000            mov cx,0x50
000005A9  B400              mov ah,0x0
000005AB  B020              mov al,0x20
000005AD  F3AB              rep stosw
000005AF  B430              mov ah,0x30
000005B1  BF260A            mov di,0xa26
000005B4  AB                stosw
000005B5  BF640A            mov di,0xa64
000005B8  AB                stosw
000005B9  BF000A            mov di,0xa00
000005BC  01DF              add di,bx
000005BE  01DF              add di,bx
000005C0  B410              mov ah,0x10
000005C2  B020              mov al,0x20
000005C4  B90300            mov cx,0x3
000005C7  F3AB              rep stosw
000005C9  C3                ret
000005CA  BE7307            mov si,0x773
000005CD  6631C0            xor eax,eax
000005D0  0FA2              cpuid
000005D2  66891C            mov [si],ebx
000005D5  66895404          mov [si+0x4],edx
000005D9  66894C08          mov [si+0x8],ecx
000005DD  C3                ret
000005DE  FC                cld
000005DF  BFEE08            mov di,0x8ee
000005E2  BE5707            mov si,0x757
000005E5  8B0E7107          mov cx,[0x771]
000005E9  F3A4              rep movsb
000005EB  C3                ret
000005EC  F9                stc
000005ED  66B801E80000      mov eax,0xe801
000005F3  6631C9            xor ecx,ecx
000005F6  6631D2            xor edx,edx
000005F9  6631DB            xor ebx,ebx
000005FC  CD15              int 0x15
000005FE  89D0              mov ax,dx
00000600  BB4000            mov bx,0x40
00000603  F7E3              mul bx
00000605  01C8              add ax,cx
00000607  81D20000          adc dx,0x0
0000060B  92                xchg ax,dx
0000060C  C3                ret
0000060D  BB0000            mov bx,0x0
00000610  B40E              mov ah,0xe
00000612  8A04              mov al,[si]
00000614  46                inc si
00000615  08C0              or al,al
00000617  7405              jz 0x61e
00000619  CD10              int 0x10
0000061B  E9F4FF            jmp word 0x612
0000061E  C3                ret
0000061F  55                push bp
00000620  B40E              mov ah,0xe
00000622  BB2E06            mov bx,0x62e
00000625  0E                push cs
00000626  5D                pop bp
00000627  BB6400            mov bx,0x64
0000062A  CD10              int 0x10
0000062C  5D                pop bp
0000062D  C3                ret
0000062E  3031              xor [bx+di],dh
00000630  3233              xor dh,[bp+di]
00000632  3435              xor al,0x35
00000634  3637              ss aaa
00000636  3839              cmp [bx+di],bh
00000638  41                inc cx
00000639  42                inc dx
0000063A  43                inc bx
0000063B  44                inc sp
0000063C  45                inc bp
0000063D  46                inc si
0000063E  89C7              mov di,ax
00000640  C1E80C            shr ax,byte 0xc
00000643  E8D9FF            call word 0x61f
00000646  89F8              mov ax,di
00000648  C1E808            shr ax,byte 0x8
0000064B  250F00            and ax,0xf
0000064E  E8CEFF            call word 0x61f
00000651  89F8              mov ax,di
00000653  C1E804            shr ax,byte 0x4
00000656  250F00            and ax,0xf
00000659  E8C3FF            call word 0x61f
0000065C  89F8              mov ax,di
0000065E  250F00            and ax,0xf
00000661  E8BBFF            call word 0x61f
00000664  C3                ret
00000665  EA007C0000        jmp word 0x0:0x7c00
0000066A  2000              and [bx+si],al
0000066C  2010              and [bx+si],dl
0000066E  48                dec ax
0000066F  204520            and [di+0x20],al
00000672  4C                dec sp
00000673  204920            and [bx+di+0x20],cl
00000676  58                pop ax
00000677  0900              or [bx+si],ax
00000679  7C20              jl 0x69b
0000067B  2020              and [bx+si],ah
0000067D  2020              and [bx+si],ah
0000067F  2020              and [bx+si],ah
00000681  7C20              jl 0x6a3
00000683  2020              and [bx+si],ah
00000685  2B20              sub sp,[bx+si]
00000687  2D202D            sub ax,0x2d20
0000068A  2020              and [bx+si],ah
0000068C  207C20            and [si+0x20],bh
0000068F  2020              and [bx+si],ah
00000691  2020              and [bx+si],ah
00000693  2020              and [bx+si],ah
00000695  2020              and [bx+si],ah
00000697  7C20              jl 0x6b9
00000699  2020              and [bx+si],ah
0000069B  7C20              jl 0x6bd
0000069D  2020              and [bx+si],ah
0000069F  2020              and [bx+si],ah
000006A1  2020              and [bx+si],ah
000006A3  7C20              jl 0x6c5
000006A5  2C00              sub al,0x0
000006A7  7C20              jl 0x6c9
000006A9  2020              and [bx+si],ah
000006AB  2020              and [bx+si],ah
000006AD  2020              and [bx+si],ah
000006AF  7C20              jl 0x6d1
000006B1  2020              and [bx+si],ah
000006B3  7C20              jl 0x6d5
000006B5  2020              and [bx+si],ah
000006B7  2020              and [bx+si],ah
000006B9  2020              and [bx+si],ah
000006BB  7C20              jl 0x6dd
000006BD  2020              and [bx+si],ah
000006BF  2020              and [bx+si],ah
000006C1  2020              and [bx+si],ah
000006C3  2020              and [bx+si],ah
000006C5  7C20              jl 0x6e7
000006C7  2020              and [bx+si],ah
000006C9  2020              and [bx+si],ah
000006CB  7C20              jl 0x6ed
000006CD  2020              and [bx+si],ah
000006CF  7C20              jl 0x6f1
000006D1  2020              and [bx+si],ah
000006D3  2B20              sub sp,[bx+si]
000006D5  2D202D            sub ax,0x2d20
000006D8  202D              and [di],ch
000006DA  202B              and [bp+di],ch
000006DC  2020              and [bx+si],ah
000006DE  202B              and [bp+di],ch
000006E0  202D              and [di],ch
000006E2  202D              and [di],ch
000006E4  2020              and [bx+si],ah
000006E6  207C20            and [si+0x20],bh
000006E9  2020              and [bx+si],ah
000006EB  2020              and [bx+si],ah
000006ED  2020              and [bx+si],ah
000006EF  2020              and [bx+si],ah
000006F1  7C20              jl 0x713
000006F3  2020              and [bx+si],ah
000006F5  2020              and [bx+si],ah
000006F7  2020              and [bx+si],ah
000006F9  7C20              jl 0x71b
000006FB  2020              and [bx+si],ah
000006FD  2020              and [bx+si],ah
000006FF  7C20              jl 0x721
00000701  2020              and [bx+si],ah
00000703  2020              and [bx+si],ah
00000705  2020              and [bx+si],ah
00000707  7C20              jl 0x729
00000709  2020              and [bx+si],ah
0000070B  7C20              jl 0x72d
0000070D  2020              and [bx+si],ah
0000070F  2020              and [bx+si],ah
00000711  2020              and [bx+si],ah
00000713  7C20              jl 0x735
00000715  2020              and [bx+si],ah
00000717  2020              and [bx+si],ah
00000719  2020              and [bx+si],ah
0000071B  2020              and [bx+si],ah
0000071D  7C20              jl 0x73f
0000071F  2020              and [bx+si],ah
00000721  2020              and [bx+si],ah
00000723  7C20              jl 0x745
00000725  2020              and [bx+si],ah
00000727  7C20              jl 0x749
00000729  2020              and [bx+si],ah
0000072B  7C20              jl 0x74d
0000072D  2020              and [bx+si],ah
0000072F  2020              and [bx+si],ah
00000731  2020              and [bx+si],ah
00000733  7C20              jl 0x755
00000735  2020              and [bx+si],ah
00000737  2B20              sub sp,[bx+si]
00000739  5F                pop di
0000073A  205F20            and [bx+0x20],bl
0000073D  2020              and [bx+si],ah
0000073F  7C20              jl 0x761
00000741  5F                pop di
00000742  205F20            and [bx+0x20],bl
00000745  5F                pop di
00000746  2020              and [bx+si],ah
00000748  207C20            and [si+0x20],bh
0000074B  2020              and [bx+si],ah
0000074D  7C20              jl 0x76f
0000074F  2020              and [bx+si],ah
00000751  2020              and [bx+si],ah
00000753  2020              and [bx+si],ah
00000755  7C20              jl 0x777
00000757  4C                dec sp
00000758  07                pop es
00000759  6F                outsw
0000075A  07                pop es
0000075B  61                popaw
0000075C  07                pop es
0000075D  6407              fs pop es
0000075F  69076E07          imul ax,[bx],word 0x76e
00000763  6707              pop es
00000765  2007              and [bx],al
00000767  2E07              cs pop es
00000769  2E07              cs pop es
0000076B  2E07              cs pop es
0000076D  2E07              cs pop es
0000076F  2E07              cs pop es
00000771  1A00              sbb al,[bx+si]
00000773  0000              add [bx+si],al
00000775  0000              add [bx+si],al
00000777  0000              add [bx+si],al
00000779  0000              add [bx+si],al
0000077B  0000              add [bx+si],al
0000077D  0000              add [bx+si],al
0000077F  0000              add [bx+si],al
00000781  00558B            add [di-0x75],dl
00000784  EC                in al,dx
00000785  56                push si
00000786  8B7604            mov si,[bp+0x4]
00000789  E888F8            call word 0x14
0000078C  5E                pop si
0000078D  5D                pop bp
0000078E  C3                ret
0000078F  55                push bp
00000790  8BEC              mov bp,sp
00000792  FF7604            push word [bp+0x4]
00000795  E8EAFF            call word 0x782
00000798  59                pop cx
00000799  B8D609            mov ax,0x9d6
0000079C  50                push ax
0000079D  E8E2FF            call word 0x782
000007A0  59                pop cx
000007A1  5D                pop bp
000007A2  C3                ret
000007A3  55                push bp
000007A4  8BEC              mov bp,sp
000007A6  B40E              mov ah,0xe
000007A8  31DB              xor bx,bx
000007AA  8A4604            mov al,[bp+0x4]
000007AD  CD10              int 0x10
000007AF  5D                pop bp
000007B0  C3                ret
000007B1  55                push bp
000007B2  8BEC              mov bp,sp
000007B4  8066040F          and byte [bp+0x4],0xf
000007B8  807E0409          cmp byte [bp+0x4],0x9
000007BC  7704              ja 0x7c2
000007BE  B030              mov al,0x30
000007C0  EB02              jmp short 0x7c4
000007C2  B037              mov al,0x37
000007C4  8A5604            mov dl,[bp+0x4]
000007C7  02D0              add dl,al
000007C9  885604            mov [bp+0x4],dl
000007CC  8A4604            mov al,[bp+0x4]
000007CF  50                push ax
000007D0  E8D0FF            call word 0x7a3
000007D3  59                pop cx
000007D4  5D                pop bp
000007D5  C3                ret
000007D6  55                push bp
000007D7  8BEC              mov bp,sp
000007D9  83EC02            sub sp,byte +0x2
000007DC  30E4              xor ah,ah
000007DE  CD16              int 0x16
000007E0  8846FF            mov [bp-0x1],al
000007E3  8A46FF            mov al,[bp-0x1]
000007E6  98                cbw
000007E7  EB00              jmp short 0x7e9
000007E9  8BE5              mov sp,bp
000007EB  5D                pop bp
000007EC  C3                ret
000007ED  55                push bp
000007EE  8BEC              mov bp,sp
000007F0  83EC04            sub sp,byte +0x4
000007F3  E8DF00            call word 0x8d5
000007F6  E831FC            call word 0x42a
000007F9  E8F0FD            call word 0x5ec
000007FC  8946FC            mov [bp-0x4],ax
000007FF  8956FE            mov [bp-0x2],dx
00000802  B8D909            mov ax,0x9d9
00000805  50                push ax
00000806  E886FF            call word 0x78f
00000809  59                pop cx
0000080A  B8210A            mov ax,0xa21
0000080D  50                push ax
0000080E  E87EFF            call word 0x78f
00000811  59                pop cx
00000812  B8690A            mov ax,0xa69
00000815  50                push ax
00000816  E876FF            call word 0x78f
00000819  59                pop cx
0000081A  B8B10A            mov ax,0xab1
0000081D  50                push ax
0000081E  E86EFF            call word 0x78f
00000821  59                pop cx
00000822  B8F90A            mov ax,0xaf9
00000825  50                push ax
00000826  E859FF            call word 0x782
00000829  59                pop cx
0000082A  8B46FC            mov ax,[bp-0x4]
0000082D  B10C              mov cl,0xc
0000082F  D3F8              sar ax,cl
00000831  50                push ax
00000832  E87CFF            call word 0x7b1
00000835  59                pop cx
00000836  8B46FC            mov ax,[bp-0x4]
00000839  B108              mov cl,0x8
0000083B  D3F8              sar ax,cl
0000083D  50                push ax
0000083E  E870FF            call word 0x7b1
00000841  59                pop cx
00000842  8B46FC            mov ax,[bp-0x4]
00000845  B104              mov cl,0x4
00000847  D3F8              sar ax,cl
00000849  50                push ax
0000084A  E864FF            call word 0x7b1
0000084D  59                pop cx
0000084E  8A46FC            mov al,[bp-0x4]
00000851  50                push ax
00000852  E85CFF            call word 0x7b1
00000855  59                pop cx
00000856  8B46FE            mov ax,[bp-0x2]
00000859  B10C              mov cl,0xc
0000085B  D3F8              sar ax,cl
0000085D  50                push ax
0000085E  E850FF            call word 0x7b1
00000861  59                pop cx
00000862  8B46FE            mov ax,[bp-0x2]
00000865  B108              mov cl,0x8
00000867  D3F8              sar ax,cl
00000869  50                push ax
0000086A  E844FF            call word 0x7b1
0000086D  59                pop cx
0000086E  8B46FE            mov ax,[bp-0x2]
00000871  B104              mov cl,0x4
00000873  D3F8              sar ax,cl
00000875  50                push ax
00000876  E838FF            call word 0x7b1
00000879  59                pop cx
0000087A  8A46FE            mov al,[bp-0x2]
0000087D  50                push ax
0000087E  E830FF            call word 0x7b1
00000881  59                pop cx
00000882  B82F0B            mov ax,0xb2f
00000885  50                push ax
00000886  E806FF            call word 0x78f
00000889  59                pop cx
0000088A  B8320B            mov ax,0xb32
0000088D  50                push ax
0000088E  E8FEFE            call word 0x78f
00000891  59                pop cx
00000892  B87B0B            mov ax,0xb7b
00000895  50                push ax
00000896  E8E9FE            call word 0x782
00000899  59                pop cx
0000089A  E82DFD            call word 0x5ca
0000089D  B87307            mov ax,0x773
000008A0  50                push ax
000008A1  E8EBFE            call word 0x78f
000008A4  59                pop cx
000008A5  B8AB0B            mov ax,0xbab
000008A8  50                push ax
000008A9  E8E3FE            call word 0x78f
000008AC  59                pop cx
000008AD  E826FF            call word 0x7d6
000008B0  8BE5              mov sp,bp
000008B2  5D                pop bp
000008B3  C3                ret
000008B4  55                push bp
000008B5  8BEC              mov bp,sp
000008B7  B400              mov ah,0x0
000008B9  B002              mov al,0x2
000008BB  B720              mov bh,0x20
000008BD  CD10              int 0x10
000008BF  FF7604            push word [bp+0x4]
000008C2  E8CAFE            call word 0x78f
000008C5  59                pop cx
000008C6  B8D70B            mov ax,0xbd7
000008C9  50                push ax
000008CA  E8C2FE            call word 0x78f
000008CD  59                pop cx
000008CE  E805FF            call word 0x7d6
000008D1  CD19              int 0x19
000008D3  5D                pop bp
000008D4  C3                ret
000008D5  55                push bp
000008D6  8BEC              mov bp,sp
000008D8  83EC02            sub sp,byte +0x2
000008DB  C646FF00          mov byte [bp-0x1],0x0
000008DF  B400              mov ah,0x0
000008E1  B002              mov al,0x2
000008E3  B720              mov bh,0x20
000008E5  CD10              int 0x10
000008E7  B8EF0B            mov ax,0xbef
000008EA  50                push ax
000008EB  E8A1FE            call word 0x78f
000008EE  59                pop cx
000008EF  B83D0C            mov ax,0xc3d
000008F2  50                push ax
000008F3  E899FE            call word 0x78f
000008F6  59                pop cx
000008F7  B88B0C            mov ax,0xc8b
000008FA  50                push ax
000008FB  E891FE            call word 0x78f
000008FE  59                pop cx
000008FF  B8D90C            mov ax,0xcd9
00000902  50                push ax
00000903  E889FE            call word 0x78f
00000906  59                pop cx
00000907  B8E00C            mov ax,0xce0
0000090A  50                push ax
0000090B  E881FE            call word 0x78f
0000090E  59                pop cx
0000090F  B8F90C            mov ax,0xcf9
00000912  50                push ax
00000913  E879FE            call word 0x78f
00000916  59                pop cx
00000917  E8BCFE            call word 0x7d6
0000091A  8846FF            mov [bp-0x1],al
0000091D  807EFF31          cmp byte [bp-0x1],0x31
00000921  7502              jnz 0x925
00000923  EB18              jmp short 0x93d
00000925  B8C007            mov ax,0x7c0
00000928  8EC0              mov es,ax
0000092A  B402              mov ah,0x2
0000092C  B001              mov al,0x1
0000092E  31DB              xor bx,bx
00000930  B600              mov dh,0x0
00000932  B280              mov dl,0x80
00000934  B500              mov ch,0x0
00000936  B101              mov cl,0x1
00000938  CD13              int 0x13
0000093A  E828FD            call word 0x665
0000093D  8BE5              mov sp,bp
0000093F  5D                pop bp
00000940  C3                ret
00000941  000A              add [bp+si],cl
00000943  0D5365            or ax,0x6553
00000946  7474              jz 0x9bc
00000948  696E672075        imul bp,[bp+0x67],word 0x7520
0000094D  7020              jo 0x96f
0000094F  3332              xor si,[bp+si]
00000951  206269            and [bp+si+0x69],ah
00000954  7420              jz 0x976
00000956  45                inc bp
00000957  6E                outsb
00000958  7669              jna 0x9c3
0000095A  726F              jc 0x9cb
0000095C  6E                outsb
0000095D  6D                insw
0000095E  656E              gs outsb
00000960  7400              jz 0x962
00000962  53                push bx
00000963  7769              ja 0x9ce
00000965  7463              jz 0x9ca
00000967  68696E            push word 0x6e69
0000096A  6720746F20        and [dword edi+ebp*2+0x20],dh
0000096F  3332              xor si,[bp+si]
00000971  206269            and [bp+si+0x69],ah
00000974  7420              jz 0x996
00000976  6D                insw
00000977  6F                outsw
00000978  64650000          add [gs:bx+si],al
0000097C  4B                dec bx
0000097D  45                inc bp
0000097E  52                push dx
0000097F  4E                dec si
00000980  45                inc bp
00000981  4C                dec sp
00000982  2020              and [bx+si],ah
00000984  42                inc dx
00000985  49                dec cx
00000986  4E                dec si
00000987  00726F            add [bp+si+0x6f],dh
0000098A  6F                outsw
0000098B  7420              jz 0x9ad
0000098D  646972207265      imul si,[fs:bp+si+0x20],word 0x6572
00000993  61                popaw
00000994  64206572          and [fs:di+0x72],ah
00000998  726F              jc 0xa09
0000099A  7200              jc 0x99c
0000099C  6661              popad
0000099E  7420              jz 0x9c0
000009A0  6C                insb
000009A1  6F                outsw
000009A2  61                popaw
000009A3  64206572          and [fs:di+0x72],ah
000009A7  726F              jc 0xa18
000009A9  7200              jc 0x9ab
000009AB  6B65726E          imul sp,[di+0x72],byte +0x6e
000009AF  656C              gs insb
000009B1  2E62696E          bound bp,[cs:bx+di+0x6e]
000009B5  206E6F            and [bp+0x6f],ch
000009B8  7420              jz 0x9da
000009BA  666F              outsd
000009BC  756E              jnz 0xa2c
000009BE  64006B65          add [fs:bp+di+0x65],ch
000009C2  726E              jc 0xa32
000009C4  656C              gs insb
000009C6  2E62696E          bound bp,[cs:bx+di+0x6e]
000009CA  206E6F            and [bp+0x6f],ch
000009CD  7420              jz 0x9ef
000009CF  666F              outsd
000009D1  756E              jnz 0xa41
000009D3  640000            add [fs:bx+si],al
000009D6  0A0D              or cl,[di]
000009D8  002B              add [bp+di],ch
000009DA  2D2D2D            sub ax,0x2d2d
000009DD  2D2D2D            sub ax,0x2d2d
000009E0  2D2D2D            sub ax,0x2d2d
000009E3  2D2D2D            sub ax,0x2d2d
000009E6  2D2D2D            sub ax,0x2d2d
000009E9  2D2D2D            sub ax,0x2d2d
000009EC  2D2D2D            sub ax,0x2d2d
000009EF  2D2D2D            sub ax,0x2d2d
000009F2  2D2D2D            sub ax,0x2d2d
000009F5  2D2D2D            sub ax,0x2d2d
000009F8  2D2D2D            sub ax,0x2d2d
000009FB  2D2D2D            sub ax,0x2d2d
000009FE  2D2D2D            sub ax,0x2d2d
00000A01  2D2D2D            sub ax,0x2d2d
00000A04  2D2D2D            sub ax,0x2d2d
00000A07  2D2D2D            sub ax,0x2d2d
00000A0A  2D2D2D            sub ax,0x2d2d
00000A0D  2D2D2D            sub ax,0x2d2d
00000A10  2D2D2D            sub ax,0x2d2d
00000A13  2D2D2D            sub ax,0x2d2d
00000A16  2D2D2D            sub ax,0x2d2d
00000A19  2D2D2D            sub ax,0x2d2d
00000A1C  2D2D2D            sub ax,0x2d2d
00000A1F  2B00              sub ax,[bx+si]
00000A21  7C20              jl 0xa43
00000A23  2020              and [bx+si],ah
00000A25  2020              and [bx+si],ah
00000A27  2020              and [bx+si],ah
00000A29  2020              and [bx+si],ah
00000A2B  2020              and [bx+si],ah
00000A2D  2020              and [bx+si],ah
00000A2F  20456E            and [di+0x6e],al
00000A32  7465              jz 0xa99
00000A34  7269              jc 0xa9f
00000A36  6E                outsb
00000A37  672031            and [ecx],dh
00000A3A  36204269          and [ss:bp+si+0x69],al
00000A3E  7420              jz 0xa60
00000A40  49                dec cx
00000A41  6E                outsb
00000A42  697469616C        imul si,[si+0x69],word 0x6c61
00000A47  697A617469        imul di,[bp+si+0x61],word 0x6974
00000A4C  6F                outsw
00000A4D  6E                outsb
00000A4E  20526F            and [bp+si+0x6f],dl
00000A51  7574              jnz 0xac7
00000A53  696E652020        imul bp,[bp+0x65],word 0x2020
00000A58  2020              and [bx+si],ah
00000A5A  2020              and [bx+si],ah
00000A5C  2020              and [bx+si],ah
00000A5E  2020              and [bx+si],ah
00000A60  2020              and [bx+si],ah
00000A62  2020              and [bx+si],ah
00000A64  2020              and [bx+si],ah
00000A66  207C00            and [si+0x0],bh
00000A69  2B2D              sub bp,[di]
00000A6B  2D2D2D            sub ax,0x2d2d
00000A6E  2D2D2D            sub ax,0x2d2d
00000A71  2D2D2D            sub ax,0x2d2d
00000A74  2D2D2D            sub ax,0x2d2d
00000A77  2D2D2D            sub ax,0x2d2d
00000A7A  2D2D2D            sub ax,0x2d2d
00000A7D  2D2D2D            sub ax,0x2d2d
00000A80  2D2D2D            sub ax,0x2d2d
00000A83  2D2D2D            sub ax,0x2d2d
00000A86  2D2D2D            sub ax,0x2d2d
00000A89  2D2D2D            sub ax,0x2d2d
00000A8C  2D2D2D            sub ax,0x2d2d
00000A8F  2D2D2D            sub ax,0x2d2d
00000A92  2D2D2D            sub ax,0x2d2d
00000A95  2D2D2D            sub ax,0x2d2d
00000A98  2D2D2D            sub ax,0x2d2d
00000A9B  2D2D2D            sub ax,0x2d2d
00000A9E  2D2D2D            sub ax,0x2d2d
00000AA1  2D2D2D            sub ax,0x2d2d
00000AA4  2D2D2D            sub ax,0x2d2d
00000AA7  2D2D2D            sub ax,0x2d2d
00000AAA  2D2D2D            sub ax,0x2d2d
00000AAD  2D2D2B            sub ax,0x2b2d
00000AB0  0020              add [bx+si],ah
00000AB2  2020              and [bx+si],ah
00000AB4  205072            and [bx+si+0x72],dl
00000AB7  6F                outsw
00000AB8  62696E            bound bp,[bx+di+0x6e]
00000ABB  67204D65          and [ebp+0x65],cl
00000ABF  6D                insw
00000AC0  6F                outsw
00000AC1  7279              jc 0xb3c
00000AC3  202E2E2E          and [0x2e2e],ch
00000AC7  2E2E2E2E2E2E2E2E  and [cs:bx+si],al
         -2E2E2E2E2E2E2E2E
         -2E2E2E2E2E2E2E2E
         -2E2E2E2E2E2E2E2E
         -2E2E2E2E2E2E2E2E
         -2E2E2E2E2E2E2E2E
         -2000
00000AF9  2020              and [bx+si],ah
00000AFB  2020              and [bx+si],ah
00000AFD  2020              and [bx+si],ah
00000AFF  2020              and [bx+si],ah
00000B01  53                push bx
00000B02  697A65206F        imul di,[bp+si+0x65],word 0x6f20
00000B07  66206D61          o32 and [di+0x61],ch
00000B0B  696E206D65        imul bp,[bp+0x20],word 0x656d
00000B10  6D                insw
00000B11  6F                outsw
00000B12  7279              jc 0xb8d
00000B14  206973            and [bx+di+0x73],ch
00000B17  2020              and [bx+si],ah
00000B19  2020              and [bx+si],ah
00000B1B  2020              and [bx+si],ah
00000B1D  2020              and [bx+si],ah
00000B1F  2020              and [bx+si],ah
00000B21  2020              and [bx+si],ah
00000B23  2020              and [bx+si],ah
00000B25  2020              and [bx+si],ah
00000B27  2020              and [bx+si],ah
00000B29  205B20            and [bp+di+0x20],bl
00000B2C  307800            xor [bx+si+0x0],bh
00000B2F  205D00            and [di+0x0],bl
00000B32  2020              and [bx+si],ah
00000B34  205072            and [bx+si+0x72],dl
00000B37  6F                outsw
00000B38  62696E            bound bp,[bx+di+0x6e]
00000B3B  67205072          and [eax+0x72],dl
00000B3F  6F                outsw
00000B40  636573            arpl [di+0x73],sp
00000B43  736F              jnc 0xbb4
00000B45  7220              jc 0xb67
00000B47  2E2E2E2E2E2E2E2E  and [cs:bx+si],al
         -2E2E2E2E2E2E2E2E
         -2E2E2E2E2E2E2E2E
         -2E2E2E2E2E2E2E2E
         -2E2E2E2E2E2E2E2E
         -2E2E2E2E2E2E2E2E
         -2E2E2000
00000B7B  2020              and [bx+si],ah
00000B7D  2020              and [bx+si],ah
00000B7F  2020              and [bx+si],ah
00000B81  205072            and [bx+si+0x72],dl
00000B84  6F                outsw
00000B85  636573            arpl [di+0x73],sp
00000B88  736F              jnc 0xbf9
00000B8A  7220              jc 0xbac
00000B8C  53                push bx
00000B8D  7472              jz 0xc01
00000B8F  696E672069        imul bp,[bp+0x67],word 0x6920
00000B94  7320              jnc 0xbb6
00000B96  2020              and [bx+si],ah
00000B98  2020              and [bx+si],ah
00000B9A  2020              and [bx+si],ah
00000B9C  2020              and [bx+si],ah
00000B9E  2020              and [bx+si],ah
00000BA0  2020              and [bx+si],ah
00000BA2  2020              and [bx+si],ah
00000BA4  2020              and [bx+si],ah
00000BA6  2020              and [bx+si],ah
00000BA8  2020              and [bx+si],ah
00000BAA  005072            add [bx+si+0x72],dl
00000BAD  657373            gs jnc 0xc23
00000BB0  20616E            and [bx+di+0x6e],ah
00000BB3  7920              jns 0xbd5
00000BB5  6B657920          imul sp,[di+0x79],byte +0x20
00000BB9  746F              jz 0xc2a
00000BBB  207377            and [bp+di+0x77],dh
00000BBE  6974636820        imul si,[si+0x63],word 0x2068
00000BC3  746F              jz 0xc34
00000BC5  2033              and [bp+di],dh
00000BC7  3220              xor ah,[bx+si]
00000BC9  626974            bound bp,[bx+di+0x74]
00000BCC  206D6F            and [di+0x6f],ch
00000BCF  6465202E2E2E      and [gs:0x2e2e],ch
00000BD5  2000              and [bx+si],al
00000BD7  50                push ax
00000BD8  7265              jc 0xc3f
00000BDA  7373              jnc 0xc4f
00000BDC  20616E            and [bx+di+0x6e],ah
00000BDF  7920              jns 0xc01
00000BE1  6B657920          imul sp,[di+0x79],byte +0x20
00000BE5  746F              jz 0xc56
00000BE7  207265            and [bp+si+0x65],dh
00000BEA  626F6F            bound bp,[bx+0x6f]
00000BED  7400              jz 0xbef
00000BEF  2D2D2D            sub ax,0x2d2d
00000BF2  2D2D2D            sub ax,0x2d2d
00000BF5  2D2D2D            sub ax,0x2d2d
00000BF8  2D2D2D            sub ax,0x2d2d
00000BFB  2D2D2D            sub ax,0x2d2d
00000BFE  2D2D2D            sub ax,0x2d2d
00000C01  2D2D2D            sub ax,0x2d2d
00000C04  2D2D2D            sub ax,0x2d2d
00000C07  2D2D2D            sub ax,0x2d2d
00000C0A  2D2D2D            sub ax,0x2d2d
00000C0D  2D2D2D            sub ax,0x2d2d
00000C10  2D2D2D            sub ax,0x2d2d
00000C13  2D2D2D            sub ax,0x2d2d
00000C16  2D2D2D            sub ax,0x2d2d
00000C19  2D2D2D            sub ax,0x2d2d
00000C1C  2D2D2D            sub ax,0x2d2d
00000C1F  2D2D2D            sub ax,0x2d2d
00000C22  2D2D2D            sub ax,0x2d2d
00000C25  2D2D2D            sub ax,0x2d2d
00000C28  2D2D2D            sub ax,0x2d2d
00000C2B  2D2D2D            sub ax,0x2d2d
00000C2E  2D2D2D            sub ax,0x2d2d
00000C31  2D2D2D            sub ax,0x2d2d
00000C34  2D2D2D            sub ax,0x2d2d
00000C37  2D2D2D            sub ax,0x2d2d
00000C3A  2D2D00            sub ax,0x2d
00000C3D  2020              and [bx+si],ah
00000C3F  2020              and [bx+si],ah
00000C41  2020              and [bx+si],ah
00000C43  2020              and [bx+si],ah
00000C45  2020              and [bx+si],ah
00000C47  2020              and [bx+si],ah
00000C49  2020              and [bx+si],ah
00000C4B  2020              and [bx+si],ah
00000C4D  2020              and [bx+si],ah
00000C4F  2020              and [bx+si],ah
00000C51  2020              and [bx+si],ah
00000C53  2020              and [bx+si],ah
00000C55  2020              and [bx+si],ah
00000C57  2020              and [bx+si],ah
00000C59  204849            and [bx+si+0x49],cl
00000C5C  4C                dec sp
00000C5D  4F                dec di
00000C5E  57                push di
00000C5F  204865            and [bx+si+0x65],cl
00000C62  6C                insb
00000C63  6978204C6F        imul di,[bx+si+0x20],word 0x6f4c
00000C68  61                popaw
00000C69  64657220          gs jc 0xc8d
00000C6D  2020              and [bx+si],ah
00000C6F  2020              and [bx+si],ah
00000C71  2020              and [bx+si],ah
00000C73  2020              and [bx+si],ah
00000C75  2020              and [bx+si],ah
00000C77  2020              and [bx+si],ah
00000C79  2020              and [bx+si],ah
00000C7B  2020              and [bx+si],ah
00000C7D  2020              and [bx+si],ah
00000C7F  2020              and [bx+si],ah
00000C81  2020              and [bx+si],ah
00000C83  2020              and [bx+si],ah
00000C85  2020              and [bx+si],ah
00000C87  2020              and [bx+si],ah
00000C89  2000              and [bx+si],al
00000C8B  2D2D2D            sub ax,0x2d2d
00000C8E  2D2D2D            sub ax,0x2d2d
00000C91  2D2D2D            sub ax,0x2d2d
00000C94  2D2D2D            sub ax,0x2d2d
00000C97  2D2D2D            sub ax,0x2d2d
00000C9A  2D2D2D            sub ax,0x2d2d
00000C9D  2D2D2D            sub ax,0x2d2d
00000CA0  2D2D2D            sub ax,0x2d2d
00000CA3  2D2D2D            sub ax,0x2d2d
00000CA6  2D2D2D            sub ax,0x2d2d
00000CA9  2D2D2D            sub ax,0x2d2d
00000CAC  2D2D2D            sub ax,0x2d2d
00000CAF  2D2D2D            sub ax,0x2d2d
00000CB2  2D2D2D            sub ax,0x2d2d
00000CB5  2D2D2D            sub ax,0x2d2d
00000CB8  2D2D2D            sub ax,0x2d2d
00000CBB  2D2D2D            sub ax,0x2d2d
00000CBE  2D2D2D            sub ax,0x2d2d
00000CC1  2D2D2D            sub ax,0x2d2d
00000CC4  2D2D2D            sub ax,0x2d2d
00000CC7  2D2D2D            sub ax,0x2d2d
00000CCA  2D2D2D            sub ax,0x2d2d
00000CCD  2D2D2D            sub ax,0x2d2d
00000CD0  2D2D2D            sub ax,0x2d2d
00000CD3  2D2D2D            sub ax,0x2d2d
00000CD6  2D2D00            sub ax,0x2d
00000CD9  50                push ax
00000CDA  7265              jc 0xd41
00000CDC  7373              jnc 0xd51
00000CDE  3A00              cmp al,[bx+si]
00000CE0  2020              and [bx+si],ah
00000CE2  2020              and [bx+si],ah
00000CE4  2020              and [bx+si],ah
00000CE6  3120              xor [bx+si],sp
00000CE8  42                inc dx
00000CE9  6F                outsw
00000CEA  6F                outsw
00000CEB  7420              jz 0xd0d
00000CED  696E746F20        imul bp,[bp+0x74],word 0x206f
00000CF2  48                dec ax
00000CF3  656C              gs insb
00000CF5  6978200020        imul di,[bx+si+0x20],word 0x2000
00000CFA  2020              and [bx+si],ah
00000CFC  2020              and [bx+si],ah
00000CFE  2032              and [bp+si],dh
00000D00  20426F            and [bp+si+0x6f],al
00000D03  6F                outsw
00000D04  7420              jz 0xd26
00000D06  696E746F20        imul bp,[bp+0x74],word 0x206f
00000D0B  4F                dec di
00000D0C  7468              jz 0xd76
00000D0E  657220            gs jc 0xd31
00000D11  4F                dec di
00000D12  7065              jo 0xd79
00000D14  7261              jc 0xd77
00000D16  7469              jz 0xd81
00000D18  6E                outsb
00000D19  67207379          and [ebx+0x79],dh
00000D1D  7374              jnc 0xd93
00000D1F  656D              gs insw
00000D21  00                db 0x00
