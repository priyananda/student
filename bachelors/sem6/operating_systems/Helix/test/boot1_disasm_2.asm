00000000  8CC8              mov ax,cs
00000002  8ED8              mov ds,ax
00000004  8EC0              mov es,ax
00000006  BE2B00            mov si,0x2b
00000009  E80C00            call word 0x18
0000000C  FA                cli
0000000D  31C0              xor ax,ax
0000000F  8ED0              mov ss,ax
00000011  BCE100            mov sp,0xe1
00000014  FB                sti
00000015  E8C900            call word 0xe1
00000018  BB0700            mov bx,0x7
0000001B  B40E              mov ah,0xe
0000001D  8A04              mov al,[si]
0000001F  46                inc si
00000020  08C0              or al,al
00000022  7404              jz 0x28
00000024  CD10              int 0x10
00000026  EBF5              jmp short 0x1d
00000028  C3                ret
00000029  CD19              int 0x19
0000002B  0A4E69            or cl,[bp+0x69]
0000002E  6D                insw
0000002F  6D                insw
00000030  61                popaw
00000031  6A6A              push byte +0x6a
00000033  690A0031          imul cx,[bp+si],word 0x3100
00000037  C08EC0FCBE        ror byte [bp-0x340],byte 0xbe
0000003C  8900              mov [bx+si],ax
0000003E  BF007C            mov di,0x7c00
00000041  B94800            mov cx,0x48
00000044  F3A4              rep movsb
00000046  BF0080            mov di,0x8000
00000049  B80001            mov ax,0x100
0000004C  BED700            mov si,0xd7
0000004F  B90800            mov cx,0x8
00000052  F3A4              rep movsb
00000054  48                dec ax
00000055  75F5              jnz 0x4c
00000057  BF0090            mov di,0x9000
0000005A  B91800            mov cx,0x18
0000005D  30C0              xor al,al
0000005F  F3AA              rep stosb
00000061  C3                ret
00000062  FA                cli
00000063  0F0116D100        lgdt [0xd1]
00000068  0F20C0            mov eax,cr0
0000006B  0C01              or al,0x1
0000006D  0F22C0            mov cr0,eax
00000070  66EA000001001800  jmp dword 0x18:0x10000
00000078  FA                cli
00000079  66B808008EE8      mov eax,0xe88e0008
0000007F  65C6059E          mov byte [gs:di],0x9e
00000083  800B00            or byte [bp+di],0x0
00000086  21EB              and bx,bp
00000088  FE00              inc byte [bx+si]
0000008A  0000              add [bx+si],al
0000008C  0000              add [bx+si],al
0000008E  0000              add [bx+si],al
00000090  00FF              add bh,bh
00000092  FF00              inc word [bx+si]
00000094  0000              add [bx+si],al
00000096  92                xchg ax,dx
00000097  CF                iretw
00000098  00FF              add bh,bh
0000009A  0F00800B92        sldt [bx+si-0x6df5]
0000009F  0000              add [bx+si],al
000000A1  FF                db 0xff
000000A2  FF00              inc word [bx+si]
000000A4  0000              add [bx+si],al
000000A6  9ACF00FFFF        call word 0xffff:0xcf
000000AB  0000              add [bx+si],al
000000AD  0092CF00          add [bp+si+0xcf],dl
000000B1  FF                db 0xff
000000B2  FF00              inc word [bx+si]
000000B4  0000              add [bx+si],al
000000B6  92                xchg ax,dx
000000B7  CF                iretw
000000B8  0017              add [bx],dl
000000BA  0000              add [bx+si],al
000000BC  90                nop
000000BD  00825000          add [bp+si+0x50],al
000000C1  FF                db 0xff
000000C2  FF00              inc word [bx+si]
000000C4  0001              add [bx+di],al
000000C6  9A1000FFFF        call word 0xffff:0x10
000000CB  0000              add [bx+si],al
000000CD  01921000          add [bp+si+0x10],dx
000000D1  47                inc di
000000D2  0000              add [bx+si],al
000000D4  7C00              jl 0xd6
000000D6  0078A0            add [bx+si-0x60],bh
000000D9  1800              sbb [bx+si],al
000000DB  008E0000          add [bp+0x0],cl
000000DF  3000              xor [bx+si],al
000000E1  67668D4C2404      lea ecx,[dword esp+0x4]
000000E7  6683E4F0          and esp,byte -0x10
000000EB  6766FF71FC        push dword [ecx-0x4]
000000F0  6655              push ebp
000000F2  6689E5            mov ebp,esp
000000F5  6651              push ecx
000000F7  6683EC04          sub esp,byte +0x4
000000FB  E86E06            call word 0x76c
000000FE  6683EC0C          sub esp,byte +0xc
00000102  6668E8090000      push dword 0x9e8
00000108  E8B305            call word 0x6be
0000010B  6683C410          add esp,byte +0x10
0000010F  E824FF            call word 0x36
00000112  6683EC0C          sub esp,byte +0xc
00000116  6668080A0000      push dword 0xa08
0000011C  E89F05            call word 0x6be
0000011F  6683C410          add esp,byte +0x10
00000123  E83CFF            call word 0x62
00000126  CD19              int 0x19
00000128  66B800000000      mov eax,0x0
0000012E  67668B4DFC        mov ecx,[ebp-0x4]
00000133  C9                leave
00000134  67668D61FC        lea esp,[ecx-0x4]
00000139  C3                ret
0000013A  6655              push ebp
0000013C  6689E5            mov ebp,esp
0000013F  31C0              xor ax,ax
00000141  30D2              xor dl,dl
00000143  CD13              int 0x13
00000145  89C0              mov ax,ax
00000147  A30013            mov [0x1300],ax
0000014A  660FB7060013      movzx eax,word [0x1300]
00000150  C1E808            shr ax,byte 0x8
00000153  A30013            mov [0x1300],ax
00000156  660FB7060013      movzx eax,word [0x1300]
0000015C  660FB7C0          movzx eax,ax
00000160  665D              pop ebp
00000162  C3                ret
00000163  6655              push ebp
00000165  6689E5            mov ebp,esp
00000168  6657              push edi
0000016A  6656              push esi
0000016C  6653              push ebx
0000016E  6683EC10          sub esp,byte +0x10
00000172  660FB7060013      movzx eax,word [0x1300]
00000178  85C0              test ax,ax
0000017A  7403              jz 0x17f
0000017C  E8BBFF            call word 0x13a
0000017F  EB03              jmp short 0x184
00000181  E8B6FF            call word 0x13a
00000184  660FB7060013      movzx eax,word [0x1300]
0000018A  83F806            cmp ax,byte +0x6
0000018D  74F2              jz 0x181
0000018F  660FB7060013      movzx eax,word [0x1300]
00000195  85C0              test ax,ax
00000197  740D              jz 0x1a6
00000199  660FB7060013      movzx eax,word [0x1300]
0000019F  660FB7C0          movzx eax,ax
000001A3  E9B900            jmp word 0x25f
000001A6  67668B4D08        mov ecx,[ebp+0x8]
000001AB  66BA398EE338      mov edx,0x38e38e39
000001B1  6689C8            mov eax,ecx
000001B4  66F7E2            mul edx
000001B7  66C1EA02          shr edx,byte 0x2
000001BB  6689D0            mov eax,edx
000001BE  66C1E003          shl eax,byte 0x3
000001C2  6601D0            add eax,edx
000001C5  6601C0            add eax,eax
000001C8  6629C1            sub ecx,eax
000001CB  6689CA            mov edx,ecx
000001CE  6689D0            mov eax,edx
000001D1  6683C001          add eax,byte +0x1
000001D5  678845F3          mov [ebp-0xd],al
000001D9  67668B4508        mov eax,[ebp+0x8]
000001DE  66BA398EE338      mov edx,0x38e38e39
000001E4  66F7E2            mul edx
000001E7  6689D0            mov eax,edx
000001EA  66C1E802          shr eax,byte 0x2
000001EE  6683E001          and eax,byte +0x1
000001F2  678845F2          mov [ebp-0xe],al
000001F6  67668B4508        mov eax,[ebp+0x8]
000001FB  66BA398EE338      mov edx,0x38e38e39
00000201  66F7E2            mul edx
00000204  6689D0            mov eax,edx
00000207  66C1E803          shr eax,byte 0x3
0000020B  678845F1          mov [ebp-0xf],al
0000020F  660FB73E0213      movzx edi,word [0x1302]
00000215  660FB7160413      movzx edx,word [0x1304]
0000021B  67660FB64DF2      movzx ecx,byte [ebp-0xe]
00000221  67660FB65DF1      movzx ebx,byte [ebp-0xf]
00000227  67660FB675F3      movzx esi,byte [ebp-0xd]
0000022D  6689F0            mov eax,esi
00000230  89F8              mov ax,di
00000232  8EC0              mov es,ax
00000234  B402              mov ah,0x2
00000236  B001              mov al,0x1
00000238  89D3              mov bx,dx
0000023A  88CE              mov dh,cl
0000023C  B200              mov dl,0x0
0000023E  88DD              mov ch,bl
00000240  88C1              mov cl,al
00000242  CD13              int 0x13
00000244  89C0              mov ax,ax
00000246  A30013            mov [0x1300],ax
00000249  660FB7060013      movzx eax,word [0x1300]
0000024F  C1E808            shr ax,byte 0x8
00000252  A30013            mov [0x1300],ax
00000255  660FB7060013      movzx eax,word [0x1300]
0000025B  660FB7C0          movzx eax,ax
0000025F  6683C410          add esp,byte +0x10
00000263  665B              pop ebx
00000265  665E              pop esi
00000267  665F              pop edi
00000269  665D              pop ebp
0000026B  C3                ret
0000026C  6655              push ebp
0000026E  6689E5            mov ebp,esp
00000271  6683EC28          sub esp,byte +0x28
00000275  6766C745F4130000  mov dword [ebp-0xc],0x13
         -00
0000027E  6766C745E4210A00  mov dword [ebp-0x1c],0xa21
         -00
00000287  C7060213000A      mov word [0x1302],0xa00
0000028D  66B840250000      mov eax,0x2540
00000293  A30413            mov [0x1304],ax
00000296  6766C745F0000000  mov dword [ebp-0x10],0x0
         -00
0000029F  E97601            jmp word 0x418
000002A2  67668B45F4        mov eax,[ebp-0xc]
000002A7  67668D5001        lea edx,[eax+0x1]
000002AC  67668955F4        mov [ebp-0xc],edx
000002B1  6650              push eax
000002B3  E8ADFE            call word 0x163
000002B6  6683C404          add esp,byte +0x4
000002BA  6685C0            test eax,eax
000002BD  741A              jz 0x2d9
000002BF  6683EC0C          sub esp,byte +0xc
000002C3  66682D0A0000      push dword 0xa2d
000002C9  E83A06            call word 0x906
000002CC  6683C410          add esp,byte +0x10
000002D0  66B800000000      mov eax,0x0
000002D6  E94F01            jmp word 0x428
000002D9  6766C745E0402500  mov dword [ebp-0x20],0x2540
         -00
000002E2  6766C745EC000000  mov dword [ebp-0x14],0x0
         -00
000002EB  E91701            jmp word 0x405
000002EE  67668B45EC        mov eax,[ebp-0x14]
000002F3  66C1E005          shl eax,byte 0x5
000002F7  6689C2            mov edx,eax
000002FA  67668B45E0        mov eax,[ebp-0x20]
000002FF  6601D0            add eax,edx
00000302  67660FB600        movzx eax,byte [eax]
00000307  84C0              test al,al
00000309  0F84F200          jz word 0x3ff
0000030D  67668B45EC        mov eax,[ebp-0x14]
00000312  66C1E005          shl eax,byte 0x5
00000316  6689C2            mov edx,eax
00000319  67668B45E0        mov eax,[ebp-0x20]
0000031E  6601D0            add eax,edx
00000321  67660FB600        movzx eax,byte [eax]
00000326  3CE5              cmp al,0xe5
00000328  0F84D300          jz word 0x3ff
0000032C  67668B45EC        mov eax,[ebp-0x14]
00000331  66C1E005          shl eax,byte 0x5
00000335  6689C2            mov edx,eax
00000338  67668B45E0        mov eax,[ebp-0x20]
0000033D  6601D0            add eax,edx
00000340  67660FB6400B      movzx eax,byte [eax+0xb]
00000346  660FB6C0          movzx eax,al
0000034A  6683E008          and eax,byte +0x8
0000034E  6685C0            test eax,eax
00000351  0F85AA00          jnz word 0x3ff
00000355  67668B45EC        mov eax,[ebp-0x14]
0000035A  66C1E005          shl eax,byte 0x5
0000035E  6689C2            mov edx,eax
00000361  67668B45E0        mov eax,[ebp-0x20]
00000366  6601D0            add eax,edx
00000369  67660FB6400B      movzx eax,byte [eax+0xb]
0000036F  660FB6C0          movzx eax,al
00000373  6683E010          and eax,byte +0x10
00000377  6685C0            test eax,eax
0000037A  0F858100          jnz word 0x3ff
0000037E  6766C745E8000000  mov dword [ebp-0x18],0x0
         -00
00000387  EB06              jmp short 0x38f
00000389  67668345E801      add dword [ebp-0x18],byte +0x1
0000038F  6766837DE80A      cmp dword [ebp-0x18],byte +0xa
00000395  7F40              jg 0x3d7
00000397  67668B55E8        mov edx,[ebp-0x18]
0000039C  67668B45E4        mov eax,[ebp-0x1c]
000003A1  6601D0            add eax,edx
000003A4  67660FB600        movzx eax,byte [eax]
000003A9  660FBED0          movsx edx,al
000003AD  67668B45EC        mov eax,[ebp-0x14]
000003B2  66C1E005          shl eax,byte 0x5
000003B6  6689C1            mov ecx,eax
000003B9  67668B45E0        mov eax,[ebp-0x20]
000003BE  6601C1            add ecx,eax
000003C1  67668B45E8        mov eax,[ebp-0x18]
000003C6  6601C8            add eax,ecx
000003C9  67660FB600        movzx eax,byte [eax]
000003CE  660FB6C0          movzx eax,al
000003D2  6639C2            cmp edx,eax
000003D5  74B2              jz 0x389
000003D7  6766837DE80B      cmp dword [ebp-0x18],byte +0xb
000003DD  7520              jnz 0x3ff
000003DF  67668B45EC        mov eax,[ebp-0x14]
000003E4  66C1E005          shl eax,byte 0x5
000003E8  6689C2            mov edx,eax
000003EB  67668B45E0        mov eax,[ebp-0x20]
000003F0  6601D0            add eax,edx
000003F3  67660FB7401A      movzx eax,word [eax+0x1a]
000003F9  660FB7C0          movzx eax,ax
000003FD  EB29              jmp short 0x428
000003FF  67668345EC01      add dword [ebp-0x14],byte +0x1
00000405  67668B45EC        mov eax,[ebp-0x14]
0000040A  6683F80F          cmp eax,byte +0xf
0000040E  0F86DCFE          jna word 0x2ee
00000412  67668345F001      add dword [ebp-0x10],byte +0x1
00000418  6766837DF00D      cmp dword [ebp-0x10],byte +0xd
0000041E  0F8E80FE          jng word 0x2a2
00000422  66B800000000      mov eax,0x0
00000428  C9                leave
00000429  C3                ret
0000042A  6655              push ebp
0000042C  6689E5            mov ebp,esp
0000042F  6683EC10          sub esp,byte +0x10
00000433  6766C745FC000000  mov dword [ebp-0x4],0x0
         -00
0000043C  67668B5508        mov edx,[ebp+0x8]
00000441  6689D0            mov eax,edx
00000444  6601C0            add eax,eax
00000447  6601D0            add eax,edx
0000044A  6689C2            mov edx,eax
0000044D  66C1EA1F          shr edx,byte 0x1f
00000451  6601D0            add eax,edx
00000454  66D1F8            sar eax,1
00000457  67668945F8        mov [ebp-0x8],eax
0000045C  67668B4508        mov eax,[ebp+0x8]
00000461  6683E001          and eax,byte +0x1
00000465  6685C0            test eax,eax
00000468  7540              jnz 0x4aa
0000046A  67668B45F8        mov eax,[ebp-0x8]
0000046F  6683C001          add eax,byte +0x1
00000473  67660FB680401300  movzx eax,byte [eax+0x1340]
         -00
0000047C  660FB6C0          movzx eax,al
00000480  6683E00F          and eax,byte +0xf
00000484  67668945FC        mov [ebp-0x4],eax
00000489  6766C165FC08      shl dword [ebp-0x4],byte 0x8
0000048F  67668B45F8        mov eax,[ebp-0x8]
00000494  660540130000      add eax,0x1340
0000049A  67660FB600        movzx eax,byte [eax]
0000049F  660FB6C0          movzx eax,al
000004A3  67660945FC        or [ebp-0x4],eax
000004A8  EB3D              jmp short 0x4e7
000004AA  67668B45F8        mov eax,[ebp-0x8]
000004AF  6683C001          add eax,byte +0x1
000004B3  67660FB680401300  movzx eax,byte [eax+0x1340]
         -00
000004BC  660FB6C0          movzx eax,al
000004C0  67668945FC        mov [ebp-0x4],eax
000004C5  6766C165FC04      shl dword [ebp-0x4],byte 0x4
000004CB  67668B45F8        mov eax,[ebp-0x8]
000004D0  660540130000      add eax,0x1340
000004D6  67660FB600        movzx eax,byte [eax]
000004DB  C0E804            shr al,byte 0x4
000004DE  660FB6C0          movzx eax,al
000004E2  67660945FC        or [ebp-0x4],eax
000004E7  67668B45FC        mov eax,[ebp-0x4]
000004EC  C9                leave
000004ED  C3                ret
000004EE  6655              push ebp
000004F0  6689E5            mov ebp,esp
000004F3  6683EC18          sub esp,byte +0x18
000004F7  C7060213000A      mov word [0x1302],0xa00
000004FD  66B840130000      mov eax,0x1340
00000503  A30413            mov [0x1304],ax
00000506  6766C745F4000000  mov dword [ebp-0xc],0x0
         -00
0000050F  EB3C              jmp short 0x54d
00000511  67668B45F4        mov eax,[ebp-0xc]
00000516  6683C001          add eax,byte +0x1
0000051A  6650              push eax
0000051C  E844FC            call word 0x163
0000051F  6683C404          add esp,byte +0x4
00000523  6685C0            test eax,eax
00000526  7413              jz 0x53b
00000528  6683EC0C          sub esp,byte +0xc
0000052C  6668410A0000      push dword 0xa41
00000532  E8D103            call word 0x906
00000535  6683C410          add esp,byte +0x10
00000539  EB0C              jmp short 0x547
0000053B  660FB7060413      movzx eax,word [0x1304]
00000541  050002            add ax,0x200
00000544  A30413            mov [0x1304],ax
00000547  67668345F401      add dword [ebp-0xc],byte +0x1
0000054D  6766837DF408      cmp dword [ebp-0xc],byte +0x8
00000553  7EBC              jng 0x511
00000555  C9                leave
00000556  C3                ret
00000557  6655              push ebp
00000559  6689E5            mov ebp,esp
0000055C  6683EC18          sub esp,byte +0x18
00000560  E809FD            call word 0x26c
00000563  67668945F4        mov [ebp-0xc],eax
00000568  6766837DF400      cmp dword [ebp-0xc],byte +0x0
0000056E  7519              jnz 0x589
00000570  6683EC0C          sub esp,byte +0xc
00000574  6668500A0000      push dword 0xa50
0000057A  E88903            call word 0x906
0000057D  6683C410          add esp,byte +0x10
00000581  66B800000000      mov eax,0x0
00000587  EB14              jmp short 0x59d
00000589  E862FF            call word 0x4ee
0000058C  C70602130010      mov word [0x1302],0x1000
00000592  C70604130000      mov word [0x1304],0x0
00000598  67668B45F4        mov eax,[ebp-0xc]
0000059D  C9                leave
0000059E  C3                ret
0000059F  6655              push ebp
000005A1  6689E5            mov ebp,esp
000005A4  6683EC10          sub esp,byte +0x10
000005A8  6766837D0800      cmp dword [ebp+0x8],byte +0x0
000005AE  7445              jz 0x5f5
000005B0  6766817D08EF0F00  cmp dword [ebp+0x8],0xfef
         -00
000005B9  7F3A              jg 0x5f5
000005BB  67668B4508        mov eax,[ebp+0x8]
000005C0  6683C01F          add eax,byte +0x1f
000005C4  67668945FC        mov [ebp-0x4],eax
000005C9  67668B45FC        mov eax,[ebp-0x4]
000005CE  6650              push eax
000005D0  E890FB            call word 0x163
000005D3  6683C404          add esp,byte +0x4
000005D7  6766FF7508        push dword [ebp+0x8]
000005DC  E84BFE            call word 0x42a
000005DF  6683C404          add esp,byte +0x4
000005E3  6766894508        mov [ebp+0x8],eax
000005E8  660FB7060213      movzx eax,word [0x1302]
000005EE  6683C020          add eax,byte +0x20
000005F2  A30213            mov [0x1302],ax
000005F5  6766817D08EF0F00  cmp dword [ebp+0x8],0xfef
         -00
000005FE  7E09              jng 0x609
00000600  6766C74508000000  mov dword [ebp+0x8],0x0
         -00
00000609  67668B4508        mov eax,[ebp+0x8]
0000060E  C9                leave
0000060F  C3                ret
00000610  6655              push ebp
00000612  6689E5            mov ebp,esp
00000615  6683EC18          sub esp,byte +0x18
00000619  C70600130100      mov word [0x1300],0x1
0000061F  E84AFC            call word 0x26c
00000622  67668945F4        mov [ebp-0xc],eax
00000627  6766837DF400      cmp dword [ebp-0xc],byte +0x0
0000062D  7513              jnz 0x642
0000062F  6683EC0C          sub esp,byte +0xc
00000633  6668500A0000      push dword 0xa50
00000639  E8CA02            call word 0x906
0000063C  6683C410          add esp,byte +0x10
00000640  EB66              jmp short 0x6a8
00000642  E8A9FE            call word 0x4ee
00000645  C70602130010      mov word [0x1302],0x1000
0000064B  C70604130000      mov word [0x1304],0x0
00000651  EB42              jmp short 0x695
00000653  67668B45F4        mov eax,[ebp-0xc]
00000658  6683C01F          add eax,byte +0x1f
0000065C  67668945F0        mov [ebp-0x10],eax
00000661  67668B45F0        mov eax,[ebp-0x10]
00000666  6683EC0C          sub esp,byte +0xc
0000066A  6650              push eax
0000066C  E8F4FA            call word 0x163
0000066F  6683C410          add esp,byte +0x10
00000673  6683EC0C          sub esp,byte +0xc
00000677  6766FF75F4        push dword [ebp-0xc]
0000067C  E8ABFD            call word 0x42a
0000067F  6683C410          add esp,byte +0x10
00000683  67668945F4        mov [ebp-0xc],eax
00000688  660FB7060213      movzx eax,word [0x1302]
0000068E  6683C020          add eax,byte +0x20
00000692  A30213            mov [0x1302],ax
00000695  6766837DF400      cmp dword [ebp-0xc],byte +0x0
0000069B  740B              jz 0x6a8
0000069D  6766817DF4EF0F00  cmp dword [ebp-0xc],0xfef
         -00
000006A6  7EAB              jng 0x653
000006A8  C9                leave
000006A9  C3                ret
000006AA  6655              push ebp
000006AC  6689E5            mov ebp,esp
000006AF  6683EC08          sub esp,byte +0x8
000006B3  678B4508          mov ax,[ebp+0x8]
000006B7  89C6              mov si,ax
000006B9  E85CF9            call word 0x18
000006BC  C9                leave
000006BD  C3                ret
000006BE  6655              push ebp
000006C0  6689E5            mov ebp,esp
000006C3  6683EC08          sub esp,byte +0x8
000006C7  6683EC0C          sub esp,byte +0xc
000006CB  6766FF7508        push dword [ebp+0x8]
000006D0  E8D7FF            call word 0x6aa
000006D3  6683C410          add esp,byte +0x10
000006D7  6683EC0C          sub esp,byte +0xc
000006DB  6668680A0000      push dword 0xa68
000006E1  E8C6FF            call word 0x6aa
000006E4  6683C410          add esp,byte +0x10
000006E8  C9                leave
000006E9  C3                ret
000006EA  6655              push ebp
000006EC  6689E5            mov ebp,esp
000006EF  6683EC04          sub esp,byte +0x4
000006F3  67668B4508        mov eax,[ebp+0x8]
000006F8  678845FC          mov [ebp-0x4],al
000006FC  67660FB645FC      movzx eax,byte [ebp-0x4]
00000702  B40E              mov ah,0xe
00000704  31DB              xor bx,bx
00000706  88C0              mov al,al
00000708  CD10              int 0x10
0000070A  C9                leave
0000070B  C3                ret
0000070C  6655              push ebp
0000070E  6689E5            mov ebp,esp
00000711  6683EC04          sub esp,byte +0x4
00000715  67668B4508        mov eax,[ebp+0x8]
0000071A  678845FC          mov [ebp-0x4],al
0000071E  678065FC0F        and byte [ebp-0x4],0xf
00000723  67807DFC09        cmp byte [ebp-0x4],0x9
00000728  7708              ja 0x732
0000072A  66B830000000      mov eax,0x30
00000730  EB06              jmp short 0x738
00000732  66B837000000      mov eax,0x37
00000738  670045FC          add [ebp-0x4],al
0000073C  67660FB645FC      movzx eax,byte [ebp-0x4]
00000742  660FBEC0          movsx eax,al
00000746  6650              push eax
00000748  E89FFF            call word 0x6ea
0000074B  6683C404          add esp,byte +0x4
0000074F  C9                leave
00000750  C3                ret
00000751  6655              push ebp
00000753  6689E5            mov ebp,esp
00000756  6683EC10          sub esp,byte +0x10
0000075A  30E4              xor ah,ah
0000075C  CD16              int 0x16
0000075E  88C0              mov al,al
00000760  678845FF          mov [ebp-0x1],al
00000764  67660FBE45FF      movsx eax,byte [ebp-0x1]
0000076A  C9                leave
0000076B  C3                ret
0000076C  6655              push ebp
0000076E  6689E5            mov ebp,esp
00000771  6683EC18          sub esp,byte +0x18
00000775  E8C701            call word 0x93f
00000778  E83108            call word 0xfac
0000077B  E8E709            call word 0x1165
0000077E  89C2              mov dx,ax
00000780  89D0              mov ax,dx
00000782  678955F6          mov [ebp-0xa],dx
00000786  678945F4          mov [ebp-0xc],ax
0000078A  6683EC0C          sub esp,byte +0xc
0000078E  66686C0A0000      push dword 0xa6c
00000794  E827FF            call word 0x6be
00000797  6683C410          add esp,byte +0x10
0000079B  6683EC0C          sub esp,byte +0xc
0000079F  6668B40A0000      push dword 0xab4
000007A5  E816FF            call word 0x6be
000007A8  6683C410          add esp,byte +0x10
000007AC  6683EC0C          sub esp,byte +0xc
000007B0  66686C0A0000      push dword 0xa6c
000007B6  E805FF            call word 0x6be
000007B9  6683C410          add esp,byte +0x10
000007BD  6683EC0C          sub esp,byte +0xc
000007C1  6668FC0A0000      push dword 0xafc
000007C7  E8F4FE            call word 0x6be
000007CA  6683C410          add esp,byte +0x10
000007CE  6683EC0C          sub esp,byte +0xc
000007D2  6668440B0000      push dword 0xb44
000007D8  E8CFFE            call word 0x6aa
000007DB  6683C410          add esp,byte +0x10
000007DF  67660FB745F6      movzx eax,word [ebp-0xa]
000007E5  C1F80C            sar ax,byte 0xc
000007E8  660FB6C0          movzx eax,al
000007EC  6683EC0C          sub esp,byte +0xc
000007F0  6650              push eax
000007F2  E817FF            call word 0x70c
000007F5  6683C410          add esp,byte +0x10
000007F9  67660FB745F6      movzx eax,word [ebp-0xa]
000007FF  C1F808            sar ax,byte 0x8
00000802  660FB6C0          movzx eax,al
00000806  6683EC0C          sub esp,byte +0xc
0000080A  6650              push eax
0000080C  E8FDFE            call word 0x70c
0000080F  6683C410          add esp,byte +0x10
00000813  67660FB745F6      movzx eax,word [ebp-0xa]
00000819  C1F804            sar ax,byte 0x4
0000081C  660FB6C0          movzx eax,al
00000820  6683EC0C          sub esp,byte +0xc
00000824  6650              push eax
00000826  E8E3FE            call word 0x70c
00000829  6683C410          add esp,byte +0x10
0000082D  67660FB745F6      movzx eax,word [ebp-0xa]
00000833  660FB6C0          movzx eax,al
00000837  6683EC0C          sub esp,byte +0xc
0000083B  6650              push eax
0000083D  E8CCFE            call word 0x70c
00000840  6683C410          add esp,byte +0x10
00000844  67660FB745F4      movzx eax,word [ebp-0xc]
0000084A  C1F80C            sar ax,byte 0xc
0000084D  660FB6C0          movzx eax,al
00000851  6683EC0C          sub esp,byte +0xc
00000855  6650              push eax
00000857  E8B2FE            call word 0x70c
0000085A  6683C410          add esp,byte +0x10
0000085E  67660FB745F4      movzx eax,word [ebp-0xc]
00000864  C1F808            sar ax,byte 0x8
00000867  660FB6C0          movzx eax,al
0000086B  6683EC0C          sub esp,byte +0xc
0000086F  6650              push eax
00000871  E898FE            call word 0x70c
00000874  6683C410          add esp,byte +0x10
00000878  67660FB745F4      movzx eax,word [ebp-0xc]
0000087E  C1F804            sar ax,byte 0x4
00000881  660FB6C0          movzx eax,al
00000885  6683EC0C          sub esp,byte +0xc
00000889  6650              push eax
0000088B  E87EFE            call word 0x70c
0000088E  6683C410          add esp,byte +0x10
00000892  67660FB745F4      movzx eax,word [ebp-0xc]
00000898  660FB6C0          movzx eax,al
0000089C  6683EC0C          sub esp,byte +0xc
000008A0  6650              push eax
000008A2  E867FE            call word 0x70c
000008A5  6683C410          add esp,byte +0x10
000008A9  6683EC0C          sub esp,byte +0xc
000008AD  66687A0B0000      push dword 0xb7a
000008B3  E808FE            call word 0x6be
000008B6  6683C410          add esp,byte +0x10
000008BA  6683EC0C          sub esp,byte +0xc
000008BE  6668800B0000      push dword 0xb80
000008C4  E8F7FD            call word 0x6be
000008C7  6683C410          add esp,byte +0x10
000008CB  6683EC0C          sub esp,byte +0xc
000008CF  6668CC0B0000      push dword 0xbcc
000008D5  E8D2FD            call word 0x6aa
000008D8  6683C410          add esp,byte +0x10
000008DC  E86408            call word 0x1143
000008DF  6683EC0C          sub esp,byte +0xc
000008E3  6668EB120000      push dword 0x12eb
000008E9  E8D2FD            call word 0x6be
000008EC  6683C410          add esp,byte +0x10
000008F0  6683EC0C          sub esp,byte +0xc
000008F4  6668FC0B0000      push dword 0xbfc
000008FA  E8ADFD            call word 0x6aa
000008FD  6683C410          add esp,byte +0x10
00000901  E84DFE            call word 0x751
00000904  C9                leave
00000905  C3                ret
00000906  6655              push ebp
00000908  6689E5            mov ebp,esp
0000090B  6683EC08          sub esp,byte +0x8
0000090F  30E4              xor ah,ah
00000911  B002              mov al,0x2
00000913  B720              mov bh,0x20
00000915  CD10              int 0x10
00000917  6683EC0C          sub esp,byte +0xc
0000091B  6766FF7508        push dword [ebp+0x8]
00000920  E89BFD            call word 0x6be
00000923  6683C410          add esp,byte +0x10
00000927  6683EC0C          sub esp,byte +0xc
0000092B  6668280C0000      push dword 0xc28
00000931  E88AFD            call word 0x6be
00000934  6683C410          add esp,byte +0x10
00000938  E816FE            call word 0x751
0000093B  CD19              int 0x19
0000093D  C9                leave
0000093E  C3                ret
0000093F  6655              push ebp
00000941  6689E5            mov ebp,esp
00000944  6683EC18          sub esp,byte +0x18
00000948  67C645F700        mov byte [ebp-0x9],0x0
0000094D  30E4              xor ah,ah
0000094F  B002              mov al,0x2
00000951  B720              mov bh,0x20
00000953  CD10              int 0x10
00000955  6683EC0C          sub esp,byte +0xc
00000959  6668400C0000      push dword 0xc40
0000095F  E85CFD            call word 0x6be
00000962  6683C410          add esp,byte +0x10
00000966  6683EC0C          sub esp,byte +0xc
0000096A  6668900C0000      push dword 0xc90
00000970  E84BFD            call word 0x6be
00000973  6683C410          add esp,byte +0x10
00000977  6683EC0C          sub esp,byte +0xc
0000097B  6668400C0000      push dword 0xc40
00000981  E83AFD            call word 0x6be
00000984  6683C410          add esp,byte +0x10
00000988  6683EC0C          sub esp,byte +0xc
0000098C  6668DE0C0000      push dword 0xcde
00000992  E829FD            call word 0x6be
00000995  6683C410          add esp,byte +0x10
00000999  6683EC0C          sub esp,byte +0xc
0000099D  6668E50C0000      push dword 0xce5
000009A3  E818FD            call word 0x6be
000009A6  6683C410          add esp,byte +0x10
000009AA  6683EC0C          sub esp,byte +0xc
000009AE  6668000D0000      push dword 0xd00
000009B4  E807FD            call word 0x6be
000009B7  6683C410          add esp,byte +0x10
000009BB  E893FD            call word 0x751
000009BE  678845F7          mov [ebp-0x9],al
000009C2  67807DF731        cmp byte [ebp-0x9],0x31
000009C7  7502              jnz 0x9cb
000009C9  EB18              jmp short 0x9e3
000009CB  B8C007            mov ax,0x7c0
000009CE  8EC0              mov es,ax
000009D0  B402              mov ah,0x2
000009D2  B001              mov al,0x1
000009D4  31DB              xor bx,bx
000009D6  30F6              xor dh,dh
000009D8  B280              mov dl,0x80
000009DA  30ED              xor ch,ch
000009DC  B101              mov cl,0x1
000009DE  CD13              int 0x13
000009E0  E8FA07            call word 0x11dd
000009E3  C9                leave
000009E4  C3                ret
000009E5  0000              add [bx+si],al
000009E7  000A              add [bp+si],cl
000009E9  0D5365            or ax,0x6553
000009EC  7474              jz 0xa62
000009EE  696E672075        imul bp,[bp+0x67],word 0x7520
000009F3  7020              jo 0xa15
000009F5  3332              xor si,[bp+si]
000009F7  206269            and [bp+si+0x69],ah
000009FA  7420              jz 0xa1c
000009FC  45                inc bp
000009FD  6E                outsb
000009FE  7669              jna 0xa69
00000A00  726F              jc 0xa71
00000A02  6E                outsb
00000A03  6D                insw
00000A04  656E              gs outsb
00000A06  7400              jz 0xa08
00000A08  53                push bx
00000A09  7769              ja 0xa74
00000A0B  7463              jz 0xa70
00000A0D  68696E            push word 0x6e69
00000A10  6720746F20        and [dword edi+ebp*2+0x20],dh
00000A15  3332              xor si,[bp+si]
00000A17  206269            and [bp+si+0x69],ah
00000A1A  7420              jz 0xa3c
00000A1C  6D                insw
00000A1D  6F                outsw
00000A1E  6465004B45        add [gs:bp+di+0x45],cl
00000A23  52                push dx
00000A24  4E                dec si
00000A25  45                inc bp
00000A26  4C                dec sp
00000A27  2020              and [bx+si],ah
00000A29  42                inc dx
00000A2A  49                dec cx
00000A2B  4E                dec si
00000A2C  00726F            add [bp+si+0x6f],dh
00000A2F  6F                outsw
00000A30  7420              jz 0xa52
00000A32  646972207265      imul si,[fs:bp+si+0x20],word 0x6572
00000A38  61                popaw
00000A39  64206572          and [fs:di+0x72],ah
00000A3D  726F              jc 0xaae
00000A3F  7200              jc 0xa41
00000A41  6661              popad
00000A43  7420              jz 0xa65
00000A45  6C                insb
00000A46  6F                outsw
00000A47  61                popaw
00000A48  64206572          and [fs:di+0x72],ah
00000A4C  726F              jc 0xabd
00000A4E  7200              jc 0xa50
00000A50  6B65726E          imul sp,[di+0x72],byte +0x6e
00000A54  656C              gs insb
00000A56  2E62696E          bound bp,[cs:bx+di+0x6e]
00000A5A  206E6F            and [bp+0x6f],ch
00000A5D  7420              jz 0xa7f
00000A5F  666F              outsd
00000A61  756E              jnz 0xad1
00000A63  640000            add [fs:bx+si],al
00000A66  0000              add [bx+si],al
00000A68  0A0D              or cl,[di]
00000A6A  0000              add [bx+si],al
00000A6C  2B2D              sub bp,[di]
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
00000AAD  2D2D2D            sub ax,0x2d2d
00000AB0  2D2D2B            sub ax,0x2b2d
00000AB3  007C20            add [si+0x20],bh
00000AB6  2020              and [bx+si],ah
00000AB8  2020              and [bx+si],ah
00000ABA  2020              and [bx+si],ah
00000ABC  2020              and [bx+si],ah
00000ABE  2020              and [bx+si],ah
00000AC0  2020              and [bx+si],ah
00000AC2  20456E            and [di+0x6e],al
00000AC5  7465              jz 0xb2c
00000AC7  7269              jc 0xb32
00000AC9  6E                outsb
00000ACA  672031            and [ecx],dh
00000ACD  36204269          and [ss:bp+si+0x69],al
00000AD1  7420              jz 0xaf3
00000AD3  49                dec cx
00000AD4  6E                outsb
00000AD5  697469616C        imul si,[si+0x69],word 0x6c61
00000ADA  697A617469        imul di,[bp+si+0x61],word 0x6974
00000ADF  6F                outsw
00000AE0  6E                outsb
00000AE1  20526F            and [bp+si+0x6f],dl
00000AE4  7574              jnz 0xb5a
00000AE6  696E652020        imul bp,[bp+0x65],word 0x2020
00000AEB  2020              and [bx+si],ah
00000AED  2020              and [bx+si],ah
00000AEF  2020              and [bx+si],ah
00000AF1  2020              and [bx+si],ah
00000AF3  2020              and [bx+si],ah
00000AF5  2020              and [bx+si],ah
00000AF7  2020              and [bx+si],ah
00000AF9  207C00            and [si+0x0],bh
00000AFC  2020              and [bx+si],ah
00000AFE  2020              and [bx+si],ah
00000B00  50                push ax
00000B01  726F              jc 0xb72
00000B03  62696E            bound bp,[bx+di+0x6e]
00000B06  67204D65          and [ebp+0x65],cl
00000B0A  6D                insw
00000B0B  6F                outsw
00000B0C  7279              jc 0xb87
00000B0E  202E2E2E          and [0x2e2e],ch
00000B12  2E2E2E2E2E2E2E2E  and [cs:bx+si],al
         -2E2E2E2E2E2E2E2E
         -2E2E2E2E2E2E2E2E
         -2E2E2E2E2E2E2E2E
         -2E2E2E2E2E2E2E2E
         -2E2E2E2E2E2E2E2E
         -2000
00000B44  2020              and [bx+si],ah
00000B46  2020              and [bx+si],ah
00000B48  2020              and [bx+si],ah
00000B4A  2020              and [bx+si],ah
00000B4C  53                push bx
00000B4D  697A65206F        imul di,[bp+si+0x65],word 0x6f20
00000B52  66206D61          o32 and [di+0x61],ch
00000B56  696E206D65        imul bp,[bp+0x20],word 0x656d
00000B5B  6D                insw
00000B5C  6F                outsw
00000B5D  7279              jc 0xbd8
00000B5F  206973            and [bx+di+0x73],ch
00000B62  2020              and [bx+si],ah
00000B64  2020              and [bx+si],ah
00000B66  2020              and [bx+si],ah
00000B68  2020              and [bx+si],ah
00000B6A  2020              and [bx+si],ah
00000B6C  2020              and [bx+si],ah
00000B6E  2020              and [bx+si],ah
00000B70  2020              and [bx+si],ah
00000B72  2020              and [bx+si],ah
00000B74  205B20            and [bp+di+0x20],bl
00000B77  307800            xor [bx+si+0x0],bh
00000B7A  205D00            and [di+0x0],bl
00000B7D  0000              add [bx+si],al
00000B7F  0020              add [bx+si],ah
00000B81  2020              and [bx+si],ah
00000B83  50                push ax
00000B84  726F              jc 0xbf5
00000B86  62696E            bound bp,[bx+di+0x6e]
00000B89  67205072          and [eax+0x72],dl
00000B8D  6F                outsw
00000B8E  636573            arpl [di+0x73],sp
00000B91  736F              jnc 0xc02
00000B93  7220              jc 0xbb5
00000B95  2E2E2E2E2E2E2E2E  and [cs:bx+si],al
         -2E2E2E2E2E2E2E2E
         -2E2E2E2E2E2E2E2E
         -2E2E2E2E2E2E2E2E
         -2E2E2E2E2E2E2E2E
         -2E2E2E2E2E2E2E2E
         -2E2E2000
00000BC9  0000              add [bx+si],al
00000BCB  0020              add [bx+si],ah
00000BCD  2020              and [bx+si],ah
00000BCF  2020              and [bx+si],ah
00000BD1  2020              and [bx+si],ah
00000BD3  50                push ax
00000BD4  726F              jc 0xc45
00000BD6  636573            arpl [di+0x73],sp
00000BD9  736F              jnc 0xc4a
00000BDB  7220              jc 0xbfd
00000BDD  53                push bx
00000BDE  7472              jz 0xc52
00000BE0  696E672069        imul bp,[bp+0x67],word 0x6920
00000BE5  7320              jnc 0xc07
00000BE7  2020              and [bx+si],ah
00000BE9  2020              and [bx+si],ah
00000BEB  2020              and [bx+si],ah
00000BED  2020              and [bx+si],ah
00000BEF  2020              and [bx+si],ah
00000BF1  2020              and [bx+si],ah
00000BF3  2020              and [bx+si],ah
00000BF5  2020              and [bx+si],ah
00000BF7  2020              and [bx+si],ah
00000BF9  2020              and [bx+si],ah
00000BFB  005072            add [bx+si+0x72],dl
00000BFE  657373            gs jnc 0xc74
00000C01  20616E            and [bx+di+0x6e],ah
00000C04  7920              jns 0xc26
00000C06  6B657920          imul sp,[di+0x79],byte +0x20
00000C0A  746F              jz 0xc7b
00000C0C  207377            and [bp+di+0x77],dh
00000C0F  6974636820        imul si,[si+0x63],word 0x2068
00000C14  746F              jz 0xc85
00000C16  2033              and [bp+di],dh
00000C18  3220              xor ah,[bx+si]
00000C1A  626974            bound bp,[bx+di+0x74]
00000C1D  206D6F            and [di+0x6f],ch
00000C20  6465202E2E2E      and [gs:0x2e2e],ch
00000C26  2000              and [bx+si],al
00000C28  50                push ax
00000C29  7265              jc 0xc90
00000C2B  7373              jnc 0xca0
00000C2D  20616E            and [bx+di+0x6e],ah
00000C30  7920              jns 0xc52
00000C32  6B657920          imul sp,[di+0x79],byte +0x20
00000C36  746F              jz 0xca7
00000C38  207265            and [bp+si+0x65],dh
00000C3B  626F6F            bound bp,[bx+0x6f]
00000C3E  7400              jz 0xc40
00000C40  2D2D2D            sub ax,0x2d2d
00000C43  2D2D2D            sub ax,0x2d2d
00000C46  2D2D2D            sub ax,0x2d2d
00000C49  2D2D2D            sub ax,0x2d2d
00000C4C  2D2D2D            sub ax,0x2d2d
00000C4F  2D2D2D            sub ax,0x2d2d
00000C52  2D2D2D            sub ax,0x2d2d
00000C55  2D2D2D            sub ax,0x2d2d
00000C58  2D2D2D            sub ax,0x2d2d
00000C5B  2D2D2D            sub ax,0x2d2d
00000C5E  2D2D2D            sub ax,0x2d2d
00000C61  2D2D2D            sub ax,0x2d2d
00000C64  2D2D2D            sub ax,0x2d2d
00000C67  2D2D2D            sub ax,0x2d2d
00000C6A  2D2D2D            sub ax,0x2d2d
00000C6D  2D2D2D            sub ax,0x2d2d
00000C70  2D2D2D            sub ax,0x2d2d
00000C73  2D2D2D            sub ax,0x2d2d
00000C76  2D2D2D            sub ax,0x2d2d
00000C79  2D2D2D            sub ax,0x2d2d
00000C7C  2D2D2D            sub ax,0x2d2d
00000C7F  2D2D2D            sub ax,0x2d2d
00000C82  2D2D2D            sub ax,0x2d2d
00000C85  2D2D2D            sub ax,0x2d2d
00000C88  2D2D2D            sub ax,0x2d2d
00000C8B  2D2D00            sub ax,0x2d
00000C8E  0000              add [bx+si],al
00000C90  2020              and [bx+si],ah
00000C92  2020              and [bx+si],ah
00000C94  2020              and [bx+si],ah
00000C96  2020              and [bx+si],ah
00000C98  2020              and [bx+si],ah
00000C9A  2020              and [bx+si],ah
00000C9C  2020              and [bx+si],ah
00000C9E  2020              and [bx+si],ah
00000CA0  2020              and [bx+si],ah
00000CA2  2020              and [bx+si],ah
00000CA4  2020              and [bx+si],ah
00000CA6  2020              and [bx+si],ah
00000CA8  2020              and [bx+si],ah
00000CAA  2020              and [bx+si],ah
00000CAC  204849            and [bx+si+0x49],cl
00000CAF  4C                dec sp
00000CB0  4F                dec di
00000CB1  57                push di
00000CB2  204865            and [bx+si+0x65],cl
00000CB5  6C                insb
00000CB6  6978204C6F        imul di,[bx+si+0x20],word 0x6f4c
00000CBB  61                popaw
00000CBC  64657220          gs jc 0xce0
00000CC0  2020              and [bx+si],ah
00000CC2  2020              and [bx+si],ah
00000CC4  2020              and [bx+si],ah
00000CC6  2020              and [bx+si],ah
00000CC8  2020              and [bx+si],ah
00000CCA  2020              and [bx+si],ah
00000CCC  2020              and [bx+si],ah
00000CCE  2020              and [bx+si],ah
00000CD0  2020              and [bx+si],ah
00000CD2  2020              and [bx+si],ah
00000CD4  2020              and [bx+si],ah
00000CD6  2020              and [bx+si],ah
00000CD8  2020              and [bx+si],ah
00000CDA  2020              and [bx+si],ah
00000CDC  2000              and [bx+si],al
00000CDE  50                push ax
00000CDF  7265              jc 0xd46
00000CE1  7373              jnc 0xd56
00000CE3  3A00              cmp al,[bx+si]
00000CE5  2020              and [bx+si],ah
00000CE7  2020              and [bx+si],ah
00000CE9  2020              and [bx+si],ah
00000CEB  3120              xor [bx+si],sp
00000CED  42                inc dx
00000CEE  6F                outsw
00000CEF  6F                outsw
00000CF0  7420              jz 0xd12
00000CF2  696E746F20        imul bp,[bp+0x74],word 0x206f
00000CF7  48                dec ax
00000CF8  656C              gs insb
00000CFA  6978200000        imul di,[bx+si+0x20],word 0x0
00000CFF  0020              add [bx+si],ah
00000D01  2020              and [bx+si],ah
00000D03  2020              and [bx+si],ah
00000D05  2032              and [bp+si],dh
00000D07  20426F            and [bp+si+0x6f],al
00000D0A  6F                outsw
00000D0B  7420              jz 0xd2d
00000D0D  696E746F20        imul bp,[bp+0x74],word 0x206f
00000D12  4F                dec di
00000D13  7468              jz 0xd7d
00000D15  657220            gs jc 0xd38
00000D18  4F                dec di
00000D19  7065              jo 0xd80
00000D1B  7261              jc 0xd7e
00000D1D  7469              jz 0xd88
00000D1F  6E                outsb
00000D20  67207379          and [ebx+0x79],dh
00000D24  7374              jnc 0xd9a
00000D26  656D              gs insw
00000D28  0000              add [bx+si],al
00000D2A  0000              add [bx+si],al
00000D2C  1400              adc al,0x0
00000D2E  0000              add [bx+si],al
00000D30  0000              add [bx+si],al
00000D32  0000              add [bx+si],al
00000D34  017A52            add [bp+si+0x52],di
00000D37  0001              add [bx+di],al
00000D39  7C08              jl 0xd43
00000D3B  011B              add [bp+di],bx
00000D3D  0C04              or al,0x4
00000D3F  0488              add al,0x88
00000D41  0100              add [bx+si],ax
00000D43  0028              add [bx+si],ch
00000D45  0000              add [bx+si],al
00000D47  001C              add [si],bl
00000D49  0000              add [bx+si],al
00000D4B  0095F3FF          add [di-0xd],dl
00000D4F  FF5900            call word far [bx+di+0x0]
00000D52  0000              add [bx+si],al
00000D54  00460C            add [bp+0xc],al
00000D57  0100              add [bx+si],ax
00000D59  4B                dec bx
00000D5A  1005              adc [di],al
00000D5C  027500            add dh,[di+0x0]
00000D5F  45                inc bp
00000D60  0F03757C          lsl si,[di+0x7c]
00000D64  06                push es
00000D65  7C0C              jl 0xd73
00000D67  0100              add [bx+si],ax
00000D69  41                inc cx
00000D6A  C5450C            lds ax,[di+0xc]
00000D6D  0404              add al,0x4
00000D6F  0014              add [si],dl
00000D71  0000              add [bx+si],al
00000D73  0000              add [bx+si],al
00000D75  0000              add [bx+si],al
00000D77  0001              add [bx+di],al
00000D79  7A52              jpe 0xdcd
00000D7B  0001              add [bx+di],al
00000D7D  7C08              jl 0xd87
00000D7F  011B              add [bp+di],bx
00000D81  0C04              or al,0x4
00000D83  0488              add al,0x88
00000D85  0100              add [bx+si],ax
00000D87  001C              add [si],bl
00000D89  0000              add [bx+si],al
00000D8B  001C              add [si],bl
00000D8D  0000              add [bx+si],al
00000D8F  00AAF3FF          add [bp+si-0xd],ch
00000D93  FF29              jmp word far [bx+di]
00000D95  0000              add [bx+si],al
00000D97  0000              add [bx+si],al
00000D99  42                inc dx
00000D9A  0E                push cs
00000D9B  08850243          or [di+0x4302],al
00000D9F  0D0563            or ax,0x6305
00000DA2  C50C              lds cx,[si]
00000DA4  0404              add al,0x4
00000DA6  0000              add [bx+si],al
00000DA8  2800              sub [bx+si],al
00000DAA  0000              add [bx+si],al
00000DAC  3C00              cmp al,0x0
00000DAE  0000              add [bx+si],al
00000DB0  B3F3              mov bl,0xf3
00000DB2  FF                db 0xff
00000DB3  FF09              dec word [bx+di]
00000DB5  0100              add [bx+si],ax
00000DB7  0000              add [bx+si],al
00000DB9  42                inc dx
00000DBA  0E                push cs
00000DBB  08850243          or [di+0x4302],al
00000DBF  0D054A            or ax,0x4a05
00000DC2  8703              xchg ax,[bp+di]
00000DC4  8604              xchg al,[si]
00000DC6  830502            add word [di],byte +0x2
00000DC9  F3C3              rep ret
00000DCB  42                inc dx
00000DCC  C642C742          mov byte [bp+si-0x39],0x42
00000DD0  C50C              lds cx,[si]
00000DD2  0404              add al,0x4
00000DD4  1C00              sbb al,0x0
00000DD6  0000              add [bx+si],al
00000DD8  680000            push word 0x0
00000DDB  0090F4FF          add [bx+si-0xc],dl
00000DDF  FF                db 0xff
00000DE0  BE0100            mov si,0x1
00000DE3  0000              add [bx+si],al
00000DE5  42                inc dx
00000DE6  0E                push cs
00000DE7  08850243          or [di+0x4302],al
00000DEB  0D0503            or ax,0x305
00000DEE  B801C5            mov ax,0xc501
00000DF1  0C04              or al,0x4
00000DF3  041C              add al,0x1c
00000DF5  0000              add [bx+si],al
00000DF7  00880000          add [bx+si+0x0],cl
00000DFB  002EF6FF          add [0xfff6],ch
00000DFF  FFC4              inc sp
00000E01  0000              add [bx+si],al
00000E03  0000              add [bx+si],al
00000E05  42                inc dx
00000E06  0E                push cs
00000E07  08850243          or [di+0x4302],al
00000E0B  0D0502            or ax,0x205
00000E0E  BEC50C            mov si,0xcc5
00000E11  0404              add al,0x4
00000E13  001C              add [si],bl
00000E15  0000              add [bx+si],al
00000E17  00A80000          add [bx+si+0x0],ch
00000E1B  00D2              add dl,dl
00000E1D  F6FF              idiv bh
00000E1F  FF6900            jmp word far [bx+di+0x0]
00000E22  0000              add [bx+si],al
00000E24  00420E            add [bp+si+0xe],al
00000E27  08850243          or [di+0x4302],al
00000E2B  0D0502            or ax,0x205
00000E2E  63C5              arpl bp,ax
00000E30  0C04              or al,0x4
00000E32  0400              add al,0x0
00000E34  1C00              sbb al,0x0
00000E36  0000              add [bx+si],al
00000E38  C8000000          enter 0x0,0x0
00000E3C  1BF7              sbb si,di
00000E3E  FF                db 0xff
00000E3F  FF4800            dec word [bx+si+0x0]
00000E42  0000              add [bx+si],al
00000E44  00420E            add [bp+si+0xe],al
00000E47  08850243          or [di+0x4302],al
00000E4B  0D0502            or ax,0x205
00000E4E  42                inc dx
00000E4F  C50C              lds cx,[si]
00000E51  0404              add al,0x4
00000E53  001C              add [si],bl
00000E55  0000              add [bx+si],al
00000E57  00E8              add al,ch
00000E59  0000              add [bx+si],al
00000E5B  0043F7            add [bp+di-0x9],al
00000E5E  FF                db 0xff
00000E5F  FF7100            push word [bx+di+0x0]
00000E62  0000              add [bx+si],al
00000E64  00420E            add [bp+si+0xe],al
00000E67  08850243          or [di+0x4302],al
00000E6B  0D0502            or ax,0x205
00000E6E  6BC50C            imul ax,bp,byte +0xc
00000E71  0404              add al,0x4
00000E73  001C              add [si],bl
00000E75  0000              add [bx+si],al
00000E77  0008              add [bx+si],cl
00000E79  0100              add [bx+si],ax
00000E7B  0094F7FF          add [si-0x9],dl
00000E7F  FF9A0000          call word far [bp+si+0x0]
00000E83  0000              add [bx+si],al
00000E85  42                inc dx
00000E86  0E                push cs
00000E87  08850243          or [di+0x4302],al
00000E8B  0D0502            or ax,0x205
00000E8E  94                xchg ax,sp
00000E8F  C50C              lds cx,[si]
00000E91  0404              add al,0x4
00000E93  0014              add [si],dl
00000E95  0000              add [bx+si],al
00000E97  0000              add [bx+si],al
00000E99  0000              add [bx+si],al
00000E9B  0001              add [bx+di],al
00000E9D  7A52              jpe 0xef1
00000E9F  0001              add [bx+di],al
00000EA1  7C08              jl 0xeab
00000EA3  011B              add [bp+di],bx
00000EA5  0C04              or al,0x4
00000EA7  0488              add al,0x88
00000EA9  0100              add [bx+si],ax
00000EAB  001C              add [si],bl
00000EAD  0000              add [bx+si],al
00000EAF  001C              add [si],bl
00000EB1  0000              add [bx+si],al
00000EB3  00F6              add dh,dh
00000EB5  F7FF              idiv di
00000EB7  FF14              call word [si]
00000EB9  0000              add [bx+si],al
00000EBB  0000              add [bx+si],al
00000EBD  42                inc dx
00000EBE  0E                push cs
00000EBF  08850243          or [di+0x4302],al
00000EC3  0D054E            or ax,0x4e05
00000EC6  C50C              lds cx,[si]
00000EC8  0404              add al,0x4
00000ECA  0000              add [bx+si],al
00000ECC  1C00              sbb al,0x0
00000ECE  0000              add [bx+si],al
00000ED0  3C00              cmp al,0x0
00000ED2  0000              add [bx+si],al
00000ED4  EAF7FFFF2C        jmp word 0x2cff:0xfff7
00000ED9  0000              add [bx+si],al
00000EDB  0000              add [bx+si],al
00000EDD  42                inc dx
00000EDE  0E                push cs
00000EDF  08850243          or [di+0x4302],al
00000EE3  0D0566            or ax,0x6605
00000EE6  C50C              lds cx,[si]
00000EE8  0404              add al,0x4
00000EEA  0000              add [bx+si],al
00000EEC  1C00              sbb al,0x0
00000EEE  0000              add [bx+si],al
00000EF0  5C                pop sp
00000EF1  0000              add [bx+si],al
00000EF3  00F6              add dh,dh
00000EF5  F7FF              idiv di
00000EF7  FF22              jmp word [bp+si]
00000EF9  0000              add [bx+si],al
00000EFB  0000              add [bx+si],al
00000EFD  42                inc dx
00000EFE  0E                push cs
00000EFF  08850243          or [di+0x4302],al
00000F03  0D055C            or ax,0x5c05
00000F06  C50C              lds cx,[si]
00000F08  0404              add al,0x4
00000F0A  0000              add [bx+si],al
00000F0C  1C00              sbb al,0x0
00000F0E  0000              add [bx+si],al
00000F10  7C00              jl 0xf12
00000F12  0000              add [bx+si],al
00000F14  F8                clc
00000F15  F7FF              idiv di
00000F17  FF4500            inc word [di+0x0]
00000F1A  0000              add [bx+si],al
00000F1C  00420E            add [bp+si+0xe],al
00000F1F  08850243          or [di+0x4302],al
00000F23  0D057F            or ax,0x7f05
00000F26  C50C              lds cx,[si]
00000F28  0404              add al,0x4
00000F2A  0000              add [bx+si],al
00000F2C  1C00              sbb al,0x0
00000F2E  0000              add [bx+si],al
00000F30  9C                pushfw
00000F31  0000              add [bx+si],al
00000F33  001D              add [di],bl
00000F35  F8                clc
00000F36  FF                db 0xff
00000F37  FF1B              call word far [bp+di]
00000F39  0000              add [bx+si],al
00000F3B  0000              add [bx+si],al
00000F3D  42                inc dx
00000F3E  0E                push cs
00000F3F  08850243          or [di+0x4302],al
00000F43  0D0555            or ax,0x5505
00000F46  C50C              lds cx,[si]
00000F48  0404              add al,0x4
00000F4A  0000              add [bx+si],al
00000F4C  1C00              sbb al,0x0
00000F4E  0000              add [bx+si],al
00000F50  BC0000            mov sp,0x0
00000F53  0018              add [bx+si],bl
00000F55  F8                clc
00000F56  FF                db 0xff
00000F57  FF9A0100          call word far [bp+si+0x1]
00000F5B  0000              add [bx+si],al
00000F5D  42                inc dx
00000F5E  0E                push cs
00000F5F  08850243          or [di+0x4302],al
00000F63  0D0503            or ax,0x305
00000F66  94                xchg ax,sp
00000F67  01C5              add bp,ax
00000F69  0C04              or al,0x4
00000F6B  041C              add al,0x1c
00000F6D  0000              add [bx+si],al
00000F6F  00DC              add ah,bl
00000F71  0000              add [bx+si],al
00000F73  0092F9FF          add [bp+si-0x7],dl
00000F77  FF                db 0xff
00000F78  3900              cmp [bx+si],ax
00000F7A  0000              add [bx+si],al
00000F7C  00420E            add [bp+si+0xe],al
00000F7F  08850243          or [di+0x4302],al
00000F83  0D0573            or ax,0x7305
00000F86  C50C              lds cx,[si]
00000F88  0404              add al,0x4
00000F8A  0000              add [bx+si],al
00000F8C  1C00              sbb al,0x0
00000F8E  0000              add [bx+si],al
00000F90  FC                cld
00000F91  0000              add [bx+si],al
00000F93  00ABF9FF          add [bp+di-0x7],ch
00000F97  FFA60000          jmp word [bp+0x0]
00000F9B  0000              add [bx+si],al
00000F9D  42                inc dx
00000F9E  0E                push cs
00000F9F  08850243          or [di+0x4302],al
00000FA3  0D0502            or ax,0x205
00000FA6  A0C50C            mov al,[0xcc5]
00000FA9  0404              add al,0x4
00000FAB  00E8              add al,ch
00000FAD  2100              and [bx+si],ax
00000FAF  E89B00            call word 0x104d
00000FB2  E8A201            call word 0x1157
00000FB5  06                push es
00000FB6  E89EF5            call word 0x557
00000FB9  07                pop es
00000FBA  A3F812            mov [0x12f8],ax
00000FBD  E80B01            call word 0x10cb
00000FC0  833EF81200        cmp word [0x12f8],byte +0x0
00000FC5  75F6              jnz 0xfbd
00000FC7  B400              mov ah,0x0
00000FC9  B002              mov al,0x2
00000FCB  B720              mov bh,0x20
00000FCD  CD10              int 0x10
00000FCF  C3                ret
00000FD0  E81300            call word 0xfe6
00000FD3  BB0100            mov bx,0x1
00000FD6  83FB17            cmp bx,byte +0x17
00000FD9  7D0A              jnl 0xfe5
00000FDB  E81900            call word 0xff7
00000FDE  43                inc bx
00000FDF  43                inc bx
00000FE0  E85900            call word 0x103c
00000FE3  EBF1              jmp short 0xfd6
00000FE5  C3                ret
00000FE6  B9A00F            mov cx,0xfa0
00000FE9  B800B8            mov ax,0xb800
00000FEC  8EC0              mov es,ax
00000FEE  B80000            mov ax,0x0
00000FF1  FC                cld
00000FF2  31FF              xor di,di
00000FF4  F3AB              rep stosw
00000FF6  C3                ret
00000FF7  B91900            mov cx,0x19
00000FFA  29D9              sub cx,bx
00000FFC  D1E9              shr cx,1
00000FFE  89C8              mov ax,cx
00001000  BA5000            mov dx,0x50
00001003  F7E2              mul dx
00001005  89C1              mov cx,ax
00001007  31FF              xor di,di
00001009  FC                cld
0000100A  BA00B8            mov dx,0xb800
0000100D  8EC2              mov es,dx
0000100F  B410              mov ah,0x10
00001011  B020              mov al,0x20
00001013  F3AB              rep stosw
00001015  89D9              mov cx,bx
00001017  89C8              mov ax,cx
00001019  BA5000            mov dx,0x50
0000101C  F7E2              mul dx
0000101E  89C1              mov cx,ax
00001020  A1E211            mov ax,[0x11e2]
00001023  F3AB              rep stosw
00001025  B91900            mov cx,0x19
00001028  29D9              sub cx,bx
0000102A  D1E1              shl cx,1
0000102C  89C8              mov ax,cx
0000102E  BA5000            mov dx,0x50
00001031  F7E2              mul dx
00001033  89C1              mov cx,ax
00001035  B410              mov ah,0x10
00001037  B020              mov al,0x20
00001039  F3AB              rep stosw
0000103B  C3                ret
0000103C  50                push ax
0000103D  52                push dx
0000103E  51                push cx
0000103F  B90200            mov cx,0x2
00001042  BAFF00            mov dx,0xff
00001045  B486              mov ah,0x86
00001047  CD15              int 0x15
00001049  59                pop cx
0000104A  5A                pop dx
0000104B  58                pop ax
0000104C  C3                ret
0000104D  BF6004            mov di,0x460
00001050  B95000            mov cx,0x50
00001053  B48F              mov ah,0x8f
00001055  B00F              mov al,0xf
00001057  F3AB              rep stosw
00001059  BF2008            mov di,0x820
0000105C  B95000            mov cx,0x50
0000105F  B48F              mov ah,0x8f
00001061  B00E              mov al,0xe
00001063  F3AB              rep stosw
00001065  BB0000            mov bx,0x0
00001068  83FB3C            cmp bx,byte +0x3c
0000106B  7D0A              jnl 0x1077
0000106D  E80800            call word 0x1078
00001070  43                inc bx
00001071  43                inc bx
00001072  E8C7FF            call word 0x103c
00001075  EBF1              jmp short 0x1068
00001077  C3                ret
00001078  BF0005            mov di,0x500
0000107B  B99001            mov cx,0x190
0000107E  B428              mov ah,0x28
00001080  B020              mov al,0x20
00001082  F3AB              rep stosw
00001084  BF0005            mov di,0x500
00001087  01DF              add di,bx
00001089  BEF111            mov si,0x11f1
0000108C  8B0E1D12          mov cx,[0x121d]
00001090  F3A4              rep movsb
00001092  BFA005            mov di,0x5a0
00001095  01DF              add di,bx
00001097  BE1F12            mov si,0x121f
0000109A  8B0E1D12          mov cx,[0x121d]
0000109E  F3A4              rep movsb
000010A0  BF4006            mov di,0x640
000010A3  01DF              add di,bx
000010A5  BE4B12            mov si,0x124b
000010A8  8B0E1D12          mov cx,[0x121d]
000010AC  F3A4              rep movsb
000010AE  BFE006            mov di,0x6e0
000010B1  01DF              add di,bx
000010B3  BE7712            mov si,0x1277
000010B6  8B0E1D12          mov cx,[0x121d]
000010BA  F3A4              rep movsb
000010BC  BF8007            mov di,0x780
000010BF  01DF              add di,bx
000010C1  BEA312            mov si,0x12a3
000010C4  8B0E1D12          mov cx,[0x121d]
000010C8  F3A4              rep movsb
000010CA  C3                ret
000010CB  51                push cx
000010CC  BF6009            mov di,0x960
000010CF  83C726            add di,byte +0x26
000010D2  B92000            mov cx,0x20
000010D5  B430              mov ah,0x30
000010D7  B020              mov al,0x20
000010D9  F3AB              rep stosw
000010DB  BFA00A            mov di,0xaa0
000010DE  83C726            add di,byte +0x26
000010E1  B92000            mov cx,0x20
000010E4  B430              mov ah,0x30
000010E6  B020              mov al,0x20
000010E8  F3AB              rep stosw
000010EA  BF120A            mov di,0xa12
000010ED  AB                stosw
000010EE  BF640A            mov di,0xa64
000010F1  AB                stosw
000010F2  BB1400            mov bx,0x14
000010F5  83FB32            cmp bx,byte +0x32
000010F8  7D20              jnl 0x111a
000010FA  E81F00            call word 0x111c
000010FD  43                inc bx
000010FE  43                inc bx
000010FF  43                inc bx
00001100  53                push bx
00001101  57                push di
00001102  06                push es
00001103  52                push dx
00001104  51                push cx
00001105  FF36F812          push word [0x12f8]
00001109  E893F4            call word 0x59f
0000110C  8F06F812          pop word [0x12f8]
00001110  A3F812            mov [0x12f8],ax
00001113  59                pop cx
00001114  5A                pop dx
00001115  07                pop es
00001116  5F                pop di
00001117  5B                pop bx
00001118  EBDB              jmp short 0x10f5
0000111A  59                pop cx
0000111B  C3                ret
0000111C  BF000A            mov di,0xa00
0000111F  B95000            mov cx,0x50
00001122  B400              mov ah,0x0
00001124  B020              mov al,0x20
00001126  F3AB              rep stosw
00001128  B430              mov ah,0x30
0000112A  BF260A            mov di,0xa26
0000112D  AB                stosw
0000112E  BF640A            mov di,0xa64
00001131  AB                stosw
00001132  BF000A            mov di,0xa00
00001135  01DF              add di,bx
00001137  01DF              add di,bx
00001139  B410              mov ah,0x10
0000113B  B020              mov al,0x20
0000113D  B90300            mov cx,0x3
00001140  F3AB              rep stosw
00001142  C3                ret
00001143  BEEB12            mov si,0x12eb
00001146  6631C0            xor eax,eax
00001149  0FA2              cpuid
0000114B  66891C            mov [si],ebx
0000114E  66895404          mov [si+0x4],edx
00001152  66894C08          mov [si+0x8],ecx
00001156  C3                ret
00001157  FC                cld
00001158  BFEE08            mov di,0x8ee
0000115B  BECF12            mov si,0x12cf
0000115E  8B0EE912          mov cx,[0x12e9]
00001162  F3A4              rep movsb
00001164  C3                ret
00001165  F9                stc
00001166  66B801E80000      mov eax,0xe801
0000116C  6631C9            xor ecx,ecx
0000116F  6631D2            xor edx,edx
00001172  6631DB            xor ebx,ebx
00001175  CD15              int 0x15
00001177  89D0              mov ax,dx
00001179  BB4000            mov bx,0x40
0000117C  F7E3              mul bx
0000117E  01C8              add ax,cx
00001180  83D200            adc dx,byte +0x0
00001183  92                xchg ax,dx
00001184  C3                ret
00001185  BB0000            mov bx,0x0
00001188  B40E              mov ah,0xe
0000118A  8A04              mov al,[si]
0000118C  46                inc si
0000118D  08C0              or al,al
0000118F  7404              jz 0x1195
00001191  CD10              int 0x10
00001193  EBF5              jmp short 0x118a
00001195  C3                ret
00001196  55                push bp
00001197  B40E              mov ah,0xe
00001199  BBA611            mov bx,0x11a6
0000119C  0E                push cs
0000119D  5D                pop bp
0000119E  D7                xlatb
0000119F  BB6400            mov bx,0x64
000011A2  CD10              int 0x10
000011A4  5D                pop bp
000011A5  C3                ret
000011A6  3031              xor [bx+di],dh
000011A8  3233              xor dh,[bp+di]
000011AA  3435              xor al,0x35
000011AC  3637              ss aaa
000011AE  3839              cmp [bx+di],bh
000011B0  41                inc cx
000011B1  42                inc dx
000011B2  43                inc bx
000011B3  44                inc sp
000011B4  45                inc bp
000011B5  46                inc si
000011B6  89C7              mov di,ax
000011B8  C1E80C            shr ax,byte 0xc
000011BB  E8D8FF            call word 0x1196
000011BE  89F8              mov ax,di
000011C0  C1E808            shr ax,byte 0x8
000011C3  83E00F            and ax,byte +0xf
000011C6  E8CDFF            call word 0x1196
000011C9  89F8              mov ax,di
000011CB  C1E804            shr ax,byte 0x4
000011CE  83E00F            and ax,byte +0xf
000011D1  E8C2FF            call word 0x1196
000011D4  89F8              mov ax,di
000011D6  83E00F            and ax,byte +0xf
000011D9  E8BAFF            call word 0x1196
000011DC  C3                ret
000011DD  EA007C0000        jmp word 0x0:0x7c00
000011E2  2000              and [bx+si],al
000011E4  2010              and [bx+si],dl
000011E6  48                dec ax
000011E7  204520            and [di+0x20],al
000011EA  4C                dec sp
000011EB  204920            and [bx+di+0x20],cl
000011EE  58                pop ax
000011EF  0900              or [bx+si],ax
000011F1  7C20              jl 0x1213
000011F3  2020              and [bx+si],ah
000011F5  2020              and [bx+si],ah
000011F7  2020              and [bx+si],ah
000011F9  7C20              jl 0x121b
000011FB  2020              and [bx+si],ah
000011FD  2B20              sub sp,[bx+si]
000011FF  2D202D            sub ax,0x2d20
00001202  2020              and [bx+si],ah
00001204  207C20            and [si+0x20],bh
00001207  2020              and [bx+si],ah
00001209  2020              and [bx+si],ah
0000120B  2020              and [bx+si],ah
0000120D  2020              and [bx+si],ah
0000120F  7C20              jl 0x1231
00001211  2020              and [bx+si],ah
00001213  7C20              jl 0x1235
00001215  2020              and [bx+si],ah
00001217  2020              and [bx+si],ah
00001219  2020              and [bx+si],ah
0000121B  7C20              jl 0x123d
0000121D  2C00              sub al,0x0
0000121F  7C20              jl 0x1241
00001221  2020              and [bx+si],ah
00001223  2020              and [bx+si],ah
00001225  2020              and [bx+si],ah
00001227  7C20              jl 0x1249
00001229  2020              and [bx+si],ah
0000122B  7C20              jl 0x124d
0000122D  2020              and [bx+si],ah
0000122F  2020              and [bx+si],ah
00001231  2020              and [bx+si],ah
00001233  7C20              jl 0x1255
00001235  2020              and [bx+si],ah
00001237  2020              and [bx+si],ah
00001239  2020              and [bx+si],ah
0000123B  2020              and [bx+si],ah
0000123D  7C20              jl 0x125f
0000123F  2020              and [bx+si],ah
00001241  2020              and [bx+si],ah
00001243  7C20              jl 0x1265
00001245  2020              and [bx+si],ah
00001247  7C20              jl 0x1269
00001249  2020              and [bx+si],ah
0000124B  2B20              sub sp,[bx+si]
0000124D  2D202D            sub ax,0x2d20
00001250  202D              and [di],ch
00001252  202B              and [bp+di],ch
00001254  2020              and [bx+si],ah
00001256  202B              and [bp+di],ch
00001258  202D              and [di],ch
0000125A  202D              and [di],ch
0000125C  2020              and [bx+si],ah
0000125E  207C20            and [si+0x20],bh
00001261  2020              and [bx+si],ah
00001263  2020              and [bx+si],ah
00001265  2020              and [bx+si],ah
00001267  2020              and [bx+si],ah
00001269  7C20              jl 0x128b
0000126B  2020              and [bx+si],ah
0000126D  2020              and [bx+si],ah
0000126F  2020              and [bx+si],ah
00001271  7C20              jl 0x1293
00001273  2020              and [bx+si],ah
00001275  2020              and [bx+si],ah
00001277  7C20              jl 0x1299
00001279  2020              and [bx+si],ah
0000127B  2020              and [bx+si],ah
0000127D  2020              and [bx+si],ah
0000127F  7C20              jl 0x12a1
00001281  2020              and [bx+si],ah
00001283  7C20              jl 0x12a5
00001285  2020              and [bx+si],ah
00001287  2020              and [bx+si],ah
00001289  2020              and [bx+si],ah
0000128B  7C20              jl 0x12ad
0000128D  2020              and [bx+si],ah
0000128F  2020              and [bx+si],ah
00001291  2020              and [bx+si],ah
00001293  2020              and [bx+si],ah
00001295  7C20              jl 0x12b7
00001297  2020              and [bx+si],ah
00001299  2020              and [bx+si],ah
0000129B  7C20              jl 0x12bd
0000129D  2020              and [bx+si],ah
0000129F  7C20              jl 0x12c1
000012A1  2020              and [bx+si],ah
000012A3  7C20              jl 0x12c5
000012A5  2020              and [bx+si],ah
000012A7  2020              and [bx+si],ah
000012A9  2020              and [bx+si],ah
000012AB  7C20              jl 0x12cd
000012AD  2020              and [bx+si],ah
000012AF  2B20              sub sp,[bx+si]
000012B1  5F                pop di
000012B2  205F20            and [bx+0x20],bl
000012B5  2020              and [bx+si],ah
000012B7  7C20              jl 0x12d9
000012B9  5F                pop di
000012BA  205F20            and [bx+0x20],bl
000012BD  5F                pop di
000012BE  2020              and [bx+si],ah
000012C0  207C20            and [si+0x20],bh
000012C3  2020              and [bx+si],ah
000012C5  7C20              jl 0x12e7
000012C7  2020              and [bx+si],ah
000012C9  2020              and [bx+si],ah
000012CB  2020              and [bx+si],ah
000012CD  7C20              jl 0x12ef
000012CF  4C                dec sp
000012D0  07                pop es
000012D1  6F                outsw
000012D2  07                pop es
000012D3  61                popaw
000012D4  07                pop es
000012D5  6407              fs pop es
000012D7  69076E07          imul ax,[bx],word 0x76e
000012DB  6707              pop es
000012DD  2007              and [bx],al
000012DF  2E07              cs pop es
000012E1  2E07              cs pop es
000012E3  2E07              cs pop es
000012E5  2E07              cs pop es
000012E7  2E07              cs pop es
000012E9  1A00              sbb al,[bx+si]
000012EB  0000              add [bx+si],al
000012ED  0000              add [bx+si],al
000012EF  0000              add [bx+si],al
000012F1  0000              add [bx+si],al
000012F3  0000              add [bx+si],al
000012F5  0000              add [bx+si],al
000012F7  0000              add [bx+si],al
000012F9  0000              add [bx+si],al
000012FB  0000              add [bx+si],al
000012FD  0000              add [bx+si],al
000012FF  0000              add [bx+si],al
00001301  0000              add [bx+si],al
00001303  0000              add [bx+si],al
00001305  0000              add [bx+si],al
00001307  0000              add [bx+si],al
00001309  0000              add [bx+si],al
0000130B  0000              add [bx+si],al
0000130D  0000              add [bx+si],al
0000130F  0000              add [bx+si],al
00001311  0000              add [bx+si],al
00001313  0000              add [bx+si],al
00001315  0000              add [bx+si],al
00001317  0000              add [bx+si],al
00001319  0000              add [bx+si],al
0000131B  0000              add [bx+si],al
0000131D  0000              add [bx+si],al
0000131F  0000              add [bx+si],al
00001321  0000              add [bx+si],al
00001323  0000              add [bx+si],al
00001325  0000              add [bx+si],al
00001327  0000              add [bx+si],al
00001329  0000              add [bx+si],al
0000132B  0000              add [bx+si],al
0000132D  0000              add [bx+si],al
0000132F  0000              add [bx+si],al
00001331  0000              add [bx+si],al
00001333  0000              add [bx+si],al
00001335  0000              add [bx+si],al
00001337  0000              add [bx+si],al
00001339  0000              add [bx+si],al
0000133B  0000              add [bx+si],al
0000133D  0000              add [bx+si],al
0000133F  0000              add [bx+si],al
00001341  0000              add [bx+si],al
00001343  0000              add [bx+si],al
00001345  0000              add [bx+si],al
00001347  0000              add [bx+si],al
00001349  0000              add [bx+si],al
0000134B  0000              add [bx+si],al
0000134D  0000              add [bx+si],al
0000134F  0000              add [bx+si],al
00001351  0000              add [bx+si],al
00001353  0000              add [bx+si],al
00001355  0000              add [bx+si],al
00001357  0000              add [bx+si],al
00001359  0000              add [bx+si],al
0000135B  0000              add [bx+si],al
0000135D  0000              add [bx+si],al
0000135F  0000              add [bx+si],al
00001361  0000              add [bx+si],al
00001363  0000              add [bx+si],al
00001365  0000              add [bx+si],al
00001367  0000              add [bx+si],al
00001369  0000              add [bx+si],al
0000136B  0000              add [bx+si],al
0000136D  0000              add [bx+si],al
0000136F  0000              add [bx+si],al
00001371  0000              add [bx+si],al
00001373  0000              add [bx+si],al
00001375  0000              add [bx+si],al
00001377  0000              add [bx+si],al
00001379  0000              add [bx+si],al
0000137B  0000              add [bx+si],al
0000137D  0000              add [bx+si],al
0000137F  0000              add [bx+si],al
00001381  0000              add [bx+si],al
00001383  0000              add [bx+si],al
00001385  0000              add [bx+si],al
00001387  0000              add [bx+si],al
00001389  0000              add [bx+si],al
0000138B  0000              add [bx+si],al
0000138D  0000              add [bx+si],al
0000138F  0000              add [bx+si],al
00001391  0000              add [bx+si],al
00001393  0000              add [bx+si],al
00001395  0000              add [bx+si],al
00001397  0000              add [bx+si],al
00001399  0000              add [bx+si],al
0000139B  0000              add [bx+si],al
0000139D  0000              add [bx+si],al
0000139F  0000              add [bx+si],al
000013A1  0000              add [bx+si],al
000013A3  0000              add [bx+si],al
000013A5  0000              add [bx+si],al
000013A7  0000              add [bx+si],al
000013A9  0000              add [bx+si],al
000013AB  0000              add [bx+si],al
000013AD  0000              add [bx+si],al
000013AF  0000              add [bx+si],al
000013B1  0000              add [bx+si],al
000013B3  0000              add [bx+si],al
000013B5  0000              add [bx+si],al
000013B7  0000              add [bx+si],al
000013B9  0000              add [bx+si],al
000013BB  0000              add [bx+si],al
000013BD  0000              add [bx+si],al
000013BF  0000              add [bx+si],al
000013C1  0000              add [bx+si],al
000013C3  0000              add [bx+si],al
000013C5  0000              add [bx+si],al
000013C7  0000              add [bx+si],al
000013C9  0000              add [bx+si],al
000013CB  0000              add [bx+si],al
000013CD  0000              add [bx+si],al
000013CF  0000              add [bx+si],al
000013D1  0000              add [bx+si],al
000013D3  0000              add [bx+si],al
000013D5  0000              add [bx+si],al
000013D7  0000              add [bx+si],al
000013D9  0000              add [bx+si],al
000013DB  0000              add [bx+si],al
000013DD  0000              add [bx+si],al
000013DF  0000              add [bx+si],al
000013E1  0000              add [bx+si],al
000013E3  0000              add [bx+si],al
000013E5  0000              add [bx+si],al
000013E7  0000              add [bx+si],al
000013E9  0000              add [bx+si],al
000013EB  0000              add [bx+si],al
000013ED  0000              add [bx+si],al
000013EF  0000              add [bx+si],al
000013F1  0000              add [bx+si],al
000013F3  0000              add [bx+si],al
000013F5  0000              add [bx+si],al
000013F7  0000              add [bx+si],al
000013F9  0000              add [bx+si],al
000013FB  0000              add [bx+si],al
000013FD  0000              add [bx+si],al
000013FF  0000              add [bx+si],al
00001401  0000              add [bx+si],al
00001403  0000              add [bx+si],al
00001405  0000              add [bx+si],al
00001407  0000              add [bx+si],al
00001409  0000              add [bx+si],al
0000140B  0000              add [bx+si],al
0000140D  0000              add [bx+si],al
0000140F  0000              add [bx+si],al
00001411  0000              add [bx+si],al
00001413  0000              add [bx+si],al
00001415  0000              add [bx+si],al
00001417  0000              add [bx+si],al
00001419  0000              add [bx+si],al
0000141B  0000              add [bx+si],al
0000141D  0000              add [bx+si],al
0000141F  0000              add [bx+si],al
00001421  0000              add [bx+si],al
00001423  0000              add [bx+si],al
00001425  0000              add [bx+si],al
00001427  0000              add [bx+si],al
00001429  0000              add [bx+si],al
0000142B  0000              add [bx+si],al
0000142D  0000              add [bx+si],al
0000142F  0000              add [bx+si],al
00001431  0000              add [bx+si],al
00001433  0000              add [bx+si],al
00001435  0000              add [bx+si],al
00001437  0000              add [bx+si],al
00001439  0000              add [bx+si],al
0000143B  0000              add [bx+si],al
0000143D  0000              add [bx+si],al
0000143F  0000              add [bx+si],al
00001441  0000              add [bx+si],al
00001443  0000              add [bx+si],al
00001445  0000              add [bx+si],al
00001447  0000              add [bx+si],al
00001449  0000              add [bx+si],al
0000144B  0000              add [bx+si],al
0000144D  0000              add [bx+si],al
0000144F  0000              add [bx+si],al
00001451  0000              add [bx+si],al
00001453  0000              add [bx+si],al
00001455  0000              add [bx+si],al
00001457  0000              add [bx+si],al
00001459  0000              add [bx+si],al
0000145B  0000              add [bx+si],al
0000145D  0000              add [bx+si],al
0000145F  0000              add [bx+si],al
00001461  0000              add [bx+si],al
00001463  0000              add [bx+si],al
00001465  0000              add [bx+si],al
00001467  0000              add [bx+si],al
00001469  0000              add [bx+si],al
0000146B  0000              add [bx+si],al
0000146D  0000              add [bx+si],al
0000146F  0000              add [bx+si],al
00001471  0000              add [bx+si],al
00001473  0000              add [bx+si],al
00001475  0000              add [bx+si],al
00001477  0000              add [bx+si],al
00001479  0000              add [bx+si],al
0000147B  0000              add [bx+si],al
0000147D  0000              add [bx+si],al
0000147F  0000              add [bx+si],al
00001481  0000              add [bx+si],al
00001483  0000              add [bx+si],al
00001485  0000              add [bx+si],al
00001487  0000              add [bx+si],al
00001489  0000              add [bx+si],al
0000148B  0000              add [bx+si],al
0000148D  0000              add [bx+si],al
0000148F  0000              add [bx+si],al
00001491  0000              add [bx+si],al
00001493  0000              add [bx+si],al
00001495  0000              add [bx+si],al
00001497  0000              add [bx+si],al
00001499  0000              add [bx+si],al
0000149B  0000              add [bx+si],al
0000149D  0000              add [bx+si],al
0000149F  0000              add [bx+si],al
000014A1  0000              add [bx+si],al
000014A3  0000              add [bx+si],al
000014A5  0000              add [bx+si],al
000014A7  0000              add [bx+si],al
000014A9  0000              add [bx+si],al
000014AB  0000              add [bx+si],al
000014AD  0000              add [bx+si],al
000014AF  0000              add [bx+si],al
000014B1  0000              add [bx+si],al
000014B3  0000              add [bx+si],al
000014B5  0000              add [bx+si],al
000014B7  0000              add [bx+si],al
000014B9  0000              add [bx+si],al
000014BB  0000              add [bx+si],al
000014BD  0000              add [bx+si],al
000014BF  0000              add [bx+si],al
000014C1  0000              add [bx+si],al
000014C3  0000              add [bx+si],al
000014C5  0000              add [bx+si],al
000014C7  0000              add [bx+si],al
000014C9  0000              add [bx+si],al
000014CB  0000              add [bx+si],al
000014CD  0000              add [bx+si],al
000014CF  0000              add [bx+si],al
000014D1  0000              add [bx+si],al
000014D3  0000              add [bx+si],al
000014D5  0000              add [bx+si],al
000014D7  0000              add [bx+si],al
000014D9  0000              add [bx+si],al
000014DB  0000              add [bx+si],al
000014DD  0000              add [bx+si],al
000014DF  0000              add [bx+si],al
000014E1  0000              add [bx+si],al
000014E3  0000              add [bx+si],al
000014E5  0000              add [bx+si],al
000014E7  0000              add [bx+si],al
000014E9  0000              add [bx+si],al
000014EB  0000              add [bx+si],al
000014ED  0000              add [bx+si],al
000014EF  0000              add [bx+si],al
000014F1  0000              add [bx+si],al
000014F3  0000              add [bx+si],al
000014F5  0000              add [bx+si],al
000014F7  0000              add [bx+si],al
000014F9  0000              add [bx+si],al
000014FB  0000              add [bx+si],al
000014FD  0000              add [bx+si],al
000014FF  0000              add [bx+si],al
00001501  0000              add [bx+si],al
00001503  0000              add [bx+si],al
00001505  0000              add [bx+si],al
00001507  0000              add [bx+si],al
00001509  0000              add [bx+si],al
0000150B  0000              add [bx+si],al
0000150D  0000              add [bx+si],al
0000150F  0000              add [bx+si],al
00001511  0000              add [bx+si],al
00001513  0000              add [bx+si],al
00001515  0000              add [bx+si],al
00001517  0000              add [bx+si],al
00001519  0000              add [bx+si],al
0000151B  0000              add [bx+si],al
0000151D  0000              add [bx+si],al
0000151F  0000              add [bx+si],al
00001521  0000              add [bx+si],al
00001523  0000              add [bx+si],al
00001525  0000              add [bx+si],al
00001527  0000              add [bx+si],al
00001529  0000              add [bx+si],al
0000152B  0000              add [bx+si],al
0000152D  0000              add [bx+si],al
0000152F  0000              add [bx+si],al
00001531  0000              add [bx+si],al
00001533  0000              add [bx+si],al
00001535  0000              add [bx+si],al
00001537  0000              add [bx+si],al
00001539  0000              add [bx+si],al
0000153B  0000              add [bx+si],al
0000153D  0000              add [bx+si],al
0000153F  0000              add [bx+si],al
00001541  0000              add [bx+si],al
00001543  0000              add [bx+si],al
00001545  0000              add [bx+si],al
00001547  0000              add [bx+si],al
00001549  0000              add [bx+si],al
0000154B  0000              add [bx+si],al
0000154D  0000              add [bx+si],al
0000154F  0000              add [bx+si],al
00001551  0000              add [bx+si],al
00001553  0000              add [bx+si],al
00001555  0000              add [bx+si],al
00001557  0000              add [bx+si],al
00001559  0000              add [bx+si],al
0000155B  0000              add [bx+si],al
0000155D  0000              add [bx+si],al
0000155F  0000              add [bx+si],al
00001561  0000              add [bx+si],al
00001563  0000              add [bx+si],al
00001565  0000              add [bx+si],al
00001567  0000              add [bx+si],al
00001569  0000              add [bx+si],al
0000156B  0000              add [bx+si],al
0000156D  0000              add [bx+si],al
0000156F  0000              add [bx+si],al
00001571  0000              add [bx+si],al
00001573  0000              add [bx+si],al
00001575  0000              add [bx+si],al
00001577  0000              add [bx+si],al
00001579  0000              add [bx+si],al
0000157B  0000              add [bx+si],al
0000157D  0000              add [bx+si],al
0000157F  0000              add [bx+si],al
00001581  0000              add [bx+si],al
00001583  0000              add [bx+si],al
00001585  0000              add [bx+si],al
00001587  0000              add [bx+si],al
00001589  0000              add [bx+si],al
0000158B  0000              add [bx+si],al
0000158D  0000              add [bx+si],al
0000158F  0000              add [bx+si],al
00001591  0000              add [bx+si],al
00001593  0000              add [bx+si],al
00001595  0000              add [bx+si],al
00001597  0000              add [bx+si],al
00001599  0000              add [bx+si],al
0000159B  0000              add [bx+si],al
0000159D  0000              add [bx+si],al
0000159F  0000              add [bx+si],al
000015A1  0000              add [bx+si],al
000015A3  0000              add [bx+si],al
000015A5  0000              add [bx+si],al
000015A7  0000              add [bx+si],al
000015A9  0000              add [bx+si],al
000015AB  0000              add [bx+si],al
000015AD  0000              add [bx+si],al
000015AF  0000              add [bx+si],al
000015B1  0000              add [bx+si],al
000015B3  0000              add [bx+si],al
000015B5  0000              add [bx+si],al
000015B7  0000              add [bx+si],al
000015B9  0000              add [bx+si],al
000015BB  0000              add [bx+si],al
000015BD  0000              add [bx+si],al
000015BF  0000              add [bx+si],al
000015C1  0000              add [bx+si],al
000015C3  0000              add [bx+si],al
000015C5  0000              add [bx+si],al
000015C7  0000              add [bx+si],al
000015C9  0000              add [bx+si],al
000015CB  0000              add [bx+si],al
000015CD  0000              add [bx+si],al
000015CF  0000              add [bx+si],al
000015D1  0000              add [bx+si],al
000015D3  0000              add [bx+si],al
000015D5  0000              add [bx+si],al
000015D7  0000              add [bx+si],al
000015D9  0000              add [bx+si],al
000015DB  0000              add [bx+si],al
000015DD  0000              add [bx+si],al
000015DF  0000              add [bx+si],al
000015E1  0000              add [bx+si],al
000015E3  0000              add [bx+si],al
000015E5  0000              add [bx+si],al
000015E7  0000              add [bx+si],al
000015E9  0000              add [bx+si],al
000015EB  0000              add [bx+si],al
000015ED  0000              add [bx+si],al
000015EF  0000              add [bx+si],al
000015F1  0000              add [bx+si],al
000015F3  0000              add [bx+si],al
000015F5  0000              add [bx+si],al
000015F7  0000              add [bx+si],al
000015F9  0000              add [bx+si],al
000015FB  0000              add [bx+si],al
000015FD  0000              add [bx+si],al
000015FF  0000              add [bx+si],al
00001601  0000              add [bx+si],al
00001603  0000              add [bx+si],al
00001605  0000              add [bx+si],al
00001607  0000              add [bx+si],al
00001609  0000              add [bx+si],al
0000160B  0000              add [bx+si],al
0000160D  0000              add [bx+si],al
0000160F  0000              add [bx+si],al
00001611  0000              add [bx+si],al
00001613  0000              add [bx+si],al
00001615  0000              add [bx+si],al
00001617  0000              add [bx+si],al
00001619  0000              add [bx+si],al
0000161B  0000              add [bx+si],al
0000161D  0000              add [bx+si],al
0000161F  0000              add [bx+si],al
00001621  0000              add [bx+si],al
00001623  0000              add [bx+si],al
00001625  0000              add [bx+si],al
00001627  0000              add [bx+si],al
00001629  0000              add [bx+si],al
0000162B  0000              add [bx+si],al
0000162D  0000              add [bx+si],al
0000162F  0000              add [bx+si],al
00001631  0000              add [bx+si],al
00001633  0000              add [bx+si],al
00001635  0000              add [bx+si],al
00001637  0000              add [bx+si],al
00001639  0000              add [bx+si],al
0000163B  0000              add [bx+si],al
0000163D  0000              add [bx+si],al
0000163F  0000              add [bx+si],al
00001641  0000              add [bx+si],al
00001643  0000              add [bx+si],al
00001645  0000              add [bx+si],al
00001647  0000              add [bx+si],al
00001649  0000              add [bx+si],al
0000164B  0000              add [bx+si],al
0000164D  0000              add [bx+si],al
0000164F  0000              add [bx+si],al
00001651  0000              add [bx+si],al
00001653  0000              add [bx+si],al
00001655  0000              add [bx+si],al
00001657  0000              add [bx+si],al
00001659  0000              add [bx+si],al
0000165B  0000              add [bx+si],al
0000165D  0000              add [bx+si],al
0000165F  0000              add [bx+si],al
00001661  0000              add [bx+si],al
00001663  0000              add [bx+si],al
00001665  0000              add [bx+si],al
00001667  0000              add [bx+si],al
00001669  0000              add [bx+si],al
0000166B  0000              add [bx+si],al
0000166D  0000              add [bx+si],al
0000166F  0000              add [bx+si],al
00001671  0000              add [bx+si],al
00001673  0000              add [bx+si],al
00001675  0000              add [bx+si],al
00001677  0000              add [bx+si],al
00001679  0000              add [bx+si],al
0000167B  0000              add [bx+si],al
0000167D  0000              add [bx+si],al
0000167F  0000              add [bx+si],al
00001681  0000              add [bx+si],al
00001683  0000              add [bx+si],al
00001685  0000              add [bx+si],al
00001687  0000              add [bx+si],al
00001689  0000              add [bx+si],al
0000168B  0000              add [bx+si],al
0000168D  0000              add [bx+si],al
0000168F  0000              add [bx+si],al
00001691  0000              add [bx+si],al
00001693  0000              add [bx+si],al
00001695  0000              add [bx+si],al
00001697  0000              add [bx+si],al
00001699  0000              add [bx+si],al
0000169B  0000              add [bx+si],al
0000169D  0000              add [bx+si],al
0000169F  0000              add [bx+si],al
000016A1  0000              add [bx+si],al
000016A3  0000              add [bx+si],al
000016A5  0000              add [bx+si],al
000016A7  0000              add [bx+si],al
000016A9  0000              add [bx+si],al
000016AB  0000              add [bx+si],al
000016AD  0000              add [bx+si],al
000016AF  0000              add [bx+si],al
000016B1  0000              add [bx+si],al
000016B3  0000              add [bx+si],al
000016B5  0000              add [bx+si],al
000016B7  0000              add [bx+si],al
000016B9  0000              add [bx+si],al
000016BB  0000              add [bx+si],al
000016BD  0000              add [bx+si],al
000016BF  0000              add [bx+si],al
000016C1  0000              add [bx+si],al
000016C3  0000              add [bx+si],al
000016C5  0000              add [bx+si],al
000016C7  0000              add [bx+si],al
000016C9  0000              add [bx+si],al
000016CB  0000              add [bx+si],al
000016CD  0000              add [bx+si],al
000016CF  0000              add [bx+si],al
000016D1  0000              add [bx+si],al
000016D3  0000              add [bx+si],al
000016D5  0000              add [bx+si],al
000016D7  0000              add [bx+si],al
000016D9  0000              add [bx+si],al
000016DB  0000              add [bx+si],al
000016DD  0000              add [bx+si],al
000016DF  0000              add [bx+si],al
000016E1  0000              add [bx+si],al
000016E3  0000              add [bx+si],al
000016E5  0000              add [bx+si],al
000016E7  0000              add [bx+si],al
000016E9  0000              add [bx+si],al
000016EB  0000              add [bx+si],al
000016ED  0000              add [bx+si],al
000016EF  0000              add [bx+si],al
000016F1  0000              add [bx+si],al
000016F3  0000              add [bx+si],al
000016F5  0000              add [bx+si],al
000016F7  0000              add [bx+si],al
000016F9  0000              add [bx+si],al
000016FB  0000              add [bx+si],al
000016FD  0000              add [bx+si],al
000016FF  0000              add [bx+si],al
00001701  0000              add [bx+si],al
00001703  0000              add [bx+si],al
00001705  0000              add [bx+si],al
00001707  0000              add [bx+si],al
00001709  0000              add [bx+si],al
0000170B  0000              add [bx+si],al
0000170D  0000              add [bx+si],al
0000170F  0000              add [bx+si],al
00001711  0000              add [bx+si],al
00001713  0000              add [bx+si],al
00001715  0000              add [bx+si],al
00001717  0000              add [bx+si],al
00001719  0000              add [bx+si],al
0000171B  0000              add [bx+si],al
0000171D  0000              add [bx+si],al
0000171F  0000              add [bx+si],al
00001721  0000              add [bx+si],al
00001723  0000              add [bx+si],al
00001725  0000              add [bx+si],al
00001727  0000              add [bx+si],al
00001729  0000              add [bx+si],al
0000172B  0000              add [bx+si],al
0000172D  0000              add [bx+si],al
0000172F  0000              add [bx+si],al
00001731  0000              add [bx+si],al
00001733  0000              add [bx+si],al
00001735  0000              add [bx+si],al
00001737  0000              add [bx+si],al
00001739  0000              add [bx+si],al
0000173B  0000              add [bx+si],al
0000173D  0000              add [bx+si],al
0000173F  0000              add [bx+si],al
00001741  0000              add [bx+si],al
00001743  0000              add [bx+si],al
00001745  0000              add [bx+si],al
00001747  0000              add [bx+si],al
00001749  0000              add [bx+si],al
0000174B  0000              add [bx+si],al
0000174D  0000              add [bx+si],al
0000174F  0000              add [bx+si],al
00001751  0000              add [bx+si],al
00001753  0000              add [bx+si],al
00001755  0000              add [bx+si],al
00001757  0000              add [bx+si],al
00001759  0000              add [bx+si],al
0000175B  0000              add [bx+si],al
0000175D  0000              add [bx+si],al
0000175F  0000              add [bx+si],al
00001761  0000              add [bx+si],al
00001763  0000              add [bx+si],al
00001765  0000              add [bx+si],al
00001767  0000              add [bx+si],al
00001769  0000              add [bx+si],al
0000176B  0000              add [bx+si],al
0000176D  0000              add [bx+si],al
0000176F  0000              add [bx+si],al
00001771  0000              add [bx+si],al
00001773  0000              add [bx+si],al
00001775  0000              add [bx+si],al
00001777  0000              add [bx+si],al
00001779  0000              add [bx+si],al
0000177B  0000              add [bx+si],al
0000177D  0000              add [bx+si],al
0000177F  0000              add [bx+si],al
00001781  0000              add [bx+si],al
00001783  0000              add [bx+si],al
00001785  0000              add [bx+si],al
00001787  0000              add [bx+si],al
00001789  0000              add [bx+si],al
0000178B  0000              add [bx+si],al
0000178D  0000              add [bx+si],al
0000178F  0000              add [bx+si],al
00001791  0000              add [bx+si],al
00001793  0000              add [bx+si],al
00001795  0000              add [bx+si],al
00001797  0000              add [bx+si],al
00001799  0000              add [bx+si],al
0000179B  0000              add [bx+si],al
0000179D  0000              add [bx+si],al
0000179F  0000              add [bx+si],al
000017A1  0000              add [bx+si],al
000017A3  0000              add [bx+si],al
000017A5  0000              add [bx+si],al
000017A7  0000              add [bx+si],al
000017A9  0000              add [bx+si],al
000017AB  0000              add [bx+si],al
000017AD  0000              add [bx+si],al
000017AF  0000              add [bx+si],al
000017B1  0000              add [bx+si],al
000017B3  0000              add [bx+si],al
000017B5  0000              add [bx+si],al
000017B7  0000              add [bx+si],al
000017B9  0000              add [bx+si],al
000017BB  0000              add [bx+si],al
000017BD  0000              add [bx+si],al
000017BF  0000              add [bx+si],al
000017C1  0000              add [bx+si],al
000017C3  0000              add [bx+si],al
000017C5  0000              add [bx+si],al
000017C7  0000              add [bx+si],al
000017C9  0000              add [bx+si],al
000017CB  0000              add [bx+si],al
000017CD  0000              add [bx+si],al
000017CF  0000              add [bx+si],al
000017D1  0000              add [bx+si],al
000017D3  0000              add [bx+si],al
000017D5  0000              add [bx+si],al
000017D7  0000              add [bx+si],al
000017D9  0000              add [bx+si],al
000017DB  0000              add [bx+si],al
000017DD  0000              add [bx+si],al
000017DF  0000              add [bx+si],al
000017E1  0000              add [bx+si],al
000017E3  0000              add [bx+si],al
000017E5  0000              add [bx+si],al
000017E7  0000              add [bx+si],al
000017E9  0000              add [bx+si],al
000017EB  0000              add [bx+si],al
000017ED  0000              add [bx+si],al
000017EF  0000              add [bx+si],al
000017F1  0000              add [bx+si],al
000017F3  0000              add [bx+si],al
000017F5  0000              add [bx+si],al
000017F7  0000              add [bx+si],al
000017F9  0000              add [bx+si],al
000017FB  0000              add [bx+si],al
000017FD  0000              add [bx+si],al
000017FF  0000              add [bx+si],al
00001801  0000              add [bx+si],al
00001803  0000              add [bx+si],al
00001805  0000              add [bx+si],al
00001807  0000              add [bx+si],al
00001809  0000              add [bx+si],al
0000180B  0000              add [bx+si],al
0000180D  0000              add [bx+si],al
0000180F  0000              add [bx+si],al
00001811  0000              add [bx+si],al
00001813  0000              add [bx+si],al
00001815  0000              add [bx+si],al
00001817  0000              add [bx+si],al
00001819  0000              add [bx+si],al
0000181B  0000              add [bx+si],al
0000181D  0000              add [bx+si],al
0000181F  0000              add [bx+si],al
00001821  0000              add [bx+si],al
00001823  0000              add [bx+si],al
00001825  0000              add [bx+si],al
00001827  0000              add [bx+si],al
00001829  0000              add [bx+si],al
0000182B  0000              add [bx+si],al
0000182D  0000              add [bx+si],al
0000182F  0000              add [bx+si],al
00001831  0000              add [bx+si],al
00001833  0000              add [bx+si],al
00001835  0000              add [bx+si],al
00001837  0000              add [bx+si],al
00001839  0000              add [bx+si],al
0000183B  0000              add [bx+si],al
0000183D  0000              add [bx+si],al
0000183F  0000              add [bx+si],al
00001841  0000              add [bx+si],al
00001843  0000              add [bx+si],al
00001845  0000              add [bx+si],al
00001847  0000              add [bx+si],al
00001849  0000              add [bx+si],al
0000184B  0000              add [bx+si],al
0000184D  0000              add [bx+si],al
0000184F  0000              add [bx+si],al
00001851  0000              add [bx+si],al
00001853  0000              add [bx+si],al
00001855  0000              add [bx+si],al
00001857  0000              add [bx+si],al
00001859  0000              add [bx+si],al
0000185B  0000              add [bx+si],al
0000185D  0000              add [bx+si],al
0000185F  0000              add [bx+si],al
00001861  0000              add [bx+si],al
00001863  0000              add [bx+si],al
00001865  0000              add [bx+si],al
00001867  0000              add [bx+si],al
00001869  0000              add [bx+si],al
0000186B  0000              add [bx+si],al
0000186D  0000              add [bx+si],al
0000186F  0000              add [bx+si],al
00001871  0000              add [bx+si],al
00001873  0000              add [bx+si],al
00001875  0000              add [bx+si],al
00001877  0000              add [bx+si],al
00001879  0000              add [bx+si],al
0000187B  0000              add [bx+si],al
0000187D  0000              add [bx+si],al
0000187F  0000              add [bx+si],al
00001881  0000              add [bx+si],al
00001883  0000              add [bx+si],al
00001885  0000              add [bx+si],al
00001887  0000              add [bx+si],al
00001889  0000              add [bx+si],al
0000188B  0000              add [bx+si],al
0000188D  0000              add [bx+si],al
0000188F  0000              add [bx+si],al
00001891  0000              add [bx+si],al
00001893  0000              add [bx+si],al
00001895  0000              add [bx+si],al
00001897  0000              add [bx+si],al
00001899  0000              add [bx+si],al
0000189B  0000              add [bx+si],al
0000189D  0000              add [bx+si],al
0000189F  0000              add [bx+si],al
000018A1  0000              add [bx+si],al
000018A3  0000              add [bx+si],al
000018A5  0000              add [bx+si],al
000018A7  0000              add [bx+si],al
000018A9  0000              add [bx+si],al
000018AB  0000              add [bx+si],al
000018AD  0000              add [bx+si],al
000018AF  0000              add [bx+si],al
000018B1  0000              add [bx+si],al
000018B3  0000              add [bx+si],al
000018B5  0000              add [bx+si],al
000018B7  0000              add [bx+si],al
000018B9  0000              add [bx+si],al
000018BB  0000              add [bx+si],al
000018BD  0000              add [bx+si],al
000018BF  0000              add [bx+si],al
000018C1  0000              add [bx+si],al
000018C3  0000              add [bx+si],al
000018C5  0000              add [bx+si],al
000018C7  0000              add [bx+si],al
000018C9  0000              add [bx+si],al
000018CB  0000              add [bx+si],al
000018CD  0000              add [bx+si],al
000018CF  0000              add [bx+si],al
000018D1  0000              add [bx+si],al
000018D3  0000              add [bx+si],al
000018D5  0000              add [bx+si],al
000018D7  0000              add [bx+si],al
000018D9  0000              add [bx+si],al
000018DB  0000              add [bx+si],al
000018DD  0000              add [bx+si],al
000018DF  0000              add [bx+si],al
000018E1  0000              add [bx+si],al
000018E3  0000              add [bx+si],al
000018E5  0000              add [bx+si],al
000018E7  0000              add [bx+si],al
000018E9  0000              add [bx+si],al
000018EB  0000              add [bx+si],al
000018ED  0000              add [bx+si],al
000018EF  0000              add [bx+si],al
000018F1  0000              add [bx+si],al
000018F3  0000              add [bx+si],al
000018F5  0000              add [bx+si],al
000018F7  0000              add [bx+si],al
000018F9  0000              add [bx+si],al
000018FB  0000              add [bx+si],al
000018FD  0000              add [bx+si],al
000018FF  0000              add [bx+si],al
00001901  0000              add [bx+si],al
00001903  0000              add [bx+si],al
00001905  0000              add [bx+si],al
00001907  0000              add [bx+si],al
00001909  0000              add [bx+si],al
0000190B  0000              add [bx+si],al
0000190D  0000              add [bx+si],al
0000190F  0000              add [bx+si],al
00001911  0000              add [bx+si],al
00001913  0000              add [bx+si],al
00001915  0000              add [bx+si],al
00001917  0000              add [bx+si],al
00001919  0000              add [bx+si],al
0000191B  0000              add [bx+si],al
0000191D  0000              add [bx+si],al
0000191F  0000              add [bx+si],al
00001921  0000              add [bx+si],al
00001923  0000              add [bx+si],al
00001925  0000              add [bx+si],al
00001927  0000              add [bx+si],al
00001929  0000              add [bx+si],al
0000192B  0000              add [bx+si],al
0000192D  0000              add [bx+si],al
0000192F  0000              add [bx+si],al
00001931  0000              add [bx+si],al
00001933  0000              add [bx+si],al
00001935  0000              add [bx+si],al
00001937  0000              add [bx+si],al
00001939  0000              add [bx+si],al
0000193B  0000              add [bx+si],al
0000193D  0000              add [bx+si],al
0000193F  0000              add [bx+si],al
00001941  0000              add [bx+si],al
00001943  0000              add [bx+si],al
00001945  0000              add [bx+si],al
00001947  0000              add [bx+si],al
00001949  0000              add [bx+si],al
0000194B  0000              add [bx+si],al
0000194D  0000              add [bx+si],al
0000194F  0000              add [bx+si],al
00001951  0000              add [bx+si],al
00001953  0000              add [bx+si],al
00001955  0000              add [bx+si],al
00001957  0000              add [bx+si],al
00001959  0000              add [bx+si],al
0000195B  0000              add [bx+si],al
0000195D  0000              add [bx+si],al
0000195F  0000              add [bx+si],al
00001961  0000              add [bx+si],al
00001963  0000              add [bx+si],al
00001965  0000              add [bx+si],al
00001967  0000              add [bx+si],al
00001969  0000              add [bx+si],al
0000196B  0000              add [bx+si],al
0000196D  0000              add [bx+si],al
0000196F  0000              add [bx+si],al
00001971  0000              add [bx+si],al
00001973  0000              add [bx+si],al
00001975  0000              add [bx+si],al
00001977  0000              add [bx+si],al
00001979  0000              add [bx+si],al
0000197B  0000              add [bx+si],al
0000197D  0000              add [bx+si],al
0000197F  0000              add [bx+si],al
00001981  0000              add [bx+si],al
00001983  0000              add [bx+si],al
00001985  0000              add [bx+si],al
00001987  0000              add [bx+si],al
00001989  0000              add [bx+si],al
0000198B  0000              add [bx+si],al
0000198D  0000              add [bx+si],al
0000198F  0000              add [bx+si],al
00001991  0000              add [bx+si],al
00001993  0000              add [bx+si],al
00001995  0000              add [bx+si],al
00001997  0000              add [bx+si],al
00001999  0000              add [bx+si],al
0000199B  0000              add [bx+si],al
0000199D  0000              add [bx+si],al
0000199F  0000              add [bx+si],al
000019A1  0000              add [bx+si],al
000019A3  0000              add [bx+si],al
000019A5  0000              add [bx+si],al
000019A7  0000              add [bx+si],al
000019A9  0000              add [bx+si],al
000019AB  0000              add [bx+si],al
000019AD  0000              add [bx+si],al
000019AF  0000              add [bx+si],al
000019B1  0000              add [bx+si],al
000019B3  0000              add [bx+si],al
000019B5  0000              add [bx+si],al
000019B7  0000              add [bx+si],al
000019B9  0000              add [bx+si],al
000019BB  0000              add [bx+si],al
000019BD  0000              add [bx+si],al
000019BF  0000              add [bx+si],al
000019C1  0000              add [bx+si],al
000019C3  0000              add [bx+si],al
000019C5  0000              add [bx+si],al
000019C7  0000              add [bx+si],al
000019C9  0000              add [bx+si],al
000019CB  0000              add [bx+si],al
000019CD  0000              add [bx+si],al
000019CF  0000              add [bx+si],al
000019D1  0000              add [bx+si],al
000019D3  0000              add [bx+si],al
000019D5  0000              add [bx+si],al
000019D7  0000              add [bx+si],al
000019D9  0000              add [bx+si],al
000019DB  0000              add [bx+si],al
000019DD  0000              add [bx+si],al
000019DF  0000              add [bx+si],al
000019E1  0000              add [bx+si],al
000019E3  0000              add [bx+si],al
000019E5  0000              add [bx+si],al
000019E7  0000              add [bx+si],al
000019E9  0000              add [bx+si],al
000019EB  0000              add [bx+si],al
000019ED  0000              add [bx+si],al
000019EF  0000              add [bx+si],al
000019F1  0000              add [bx+si],al
000019F3  0000              add [bx+si],al
000019F5  0000              add [bx+si],al
000019F7  0000              add [bx+si],al
000019F9  0000              add [bx+si],al
000019FB  0000              add [bx+si],al
000019FD  0000              add [bx+si],al
000019FF  0000              add [bx+si],al
00001A01  0000              add [bx+si],al
00001A03  0000              add [bx+si],al
00001A05  0000              add [bx+si],al
00001A07  0000              add [bx+si],al
00001A09  0000              add [bx+si],al
00001A0B  0000              add [bx+si],al
00001A0D  0000              add [bx+si],al
00001A0F  0000              add [bx+si],al
00001A11  0000              add [bx+si],al
00001A13  0000              add [bx+si],al
00001A15  0000              add [bx+si],al
00001A17  0000              add [bx+si],al
00001A19  0000              add [bx+si],al
00001A1B  0000              add [bx+si],al
00001A1D  0000              add [bx+si],al
00001A1F  0000              add [bx+si],al
00001A21  0000              add [bx+si],al
00001A23  0000              add [bx+si],al
00001A25  0000              add [bx+si],al
00001A27  0000              add [bx+si],al
00001A29  0000              add [bx+si],al
00001A2B  0000              add [bx+si],al
00001A2D  0000              add [bx+si],al
00001A2F  0000              add [bx+si],al
00001A31  0000              add [bx+si],al
00001A33  0000              add [bx+si],al
00001A35  0000              add [bx+si],al
00001A37  0000              add [bx+si],al
00001A39  0000              add [bx+si],al
00001A3B  0000              add [bx+si],al
00001A3D  0000              add [bx+si],al
00001A3F  0000              add [bx+si],al
00001A41  0000              add [bx+si],al
00001A43  0000              add [bx+si],al
00001A45  0000              add [bx+si],al
00001A47  0000              add [bx+si],al
00001A49  0000              add [bx+si],al
00001A4B  0000              add [bx+si],al
00001A4D  0000              add [bx+si],al
00001A4F  0000              add [bx+si],al
00001A51  0000              add [bx+si],al
00001A53  0000              add [bx+si],al
00001A55  0000              add [bx+si],al
00001A57  0000              add [bx+si],al
00001A59  0000              add [bx+si],al
00001A5B  0000              add [bx+si],al
00001A5D  0000              add [bx+si],al
00001A5F  0000              add [bx+si],al
00001A61  0000              add [bx+si],al
00001A63  0000              add [bx+si],al
00001A65  0000              add [bx+si],al
00001A67  0000              add [bx+si],al
00001A69  0000              add [bx+si],al
00001A6B  0000              add [bx+si],al
00001A6D  0000              add [bx+si],al
00001A6F  0000              add [bx+si],al
00001A71  0000              add [bx+si],al
00001A73  0000              add [bx+si],al
00001A75  0000              add [bx+si],al
00001A77  0000              add [bx+si],al
00001A79  0000              add [bx+si],al
00001A7B  0000              add [bx+si],al
00001A7D  0000              add [bx+si],al
00001A7F  0000              add [bx+si],al
00001A81  0000              add [bx+si],al
00001A83  0000              add [bx+si],al
00001A85  0000              add [bx+si],al
00001A87  0000              add [bx+si],al
00001A89  0000              add [bx+si],al
00001A8B  0000              add [bx+si],al
00001A8D  0000              add [bx+si],al
00001A8F  0000              add [bx+si],al
00001A91  0000              add [bx+si],al
00001A93  0000              add [bx+si],al
00001A95  0000              add [bx+si],al
00001A97  0000              add [bx+si],al
00001A99  0000              add [bx+si],al
00001A9B  0000              add [bx+si],al
00001A9D  0000              add [bx+si],al
00001A9F  0000              add [bx+si],al
00001AA1  0000              add [bx+si],al
00001AA3  0000              add [bx+si],al
00001AA5  0000              add [bx+si],al
00001AA7  0000              add [bx+si],al
00001AA9  0000              add [bx+si],al
00001AAB  0000              add [bx+si],al
00001AAD  0000              add [bx+si],al
00001AAF  0000              add [bx+si],al
00001AB1  0000              add [bx+si],al
00001AB3  0000              add [bx+si],al
00001AB5  0000              add [bx+si],al
00001AB7  0000              add [bx+si],al
00001AB9  0000              add [bx+si],al
00001ABB  0000              add [bx+si],al
00001ABD  0000              add [bx+si],al
00001ABF  0000              add [bx+si],al
00001AC1  0000              add [bx+si],al
00001AC3  0000              add [bx+si],al
00001AC5  0000              add [bx+si],al
00001AC7  0000              add [bx+si],al
00001AC9  0000              add [bx+si],al
00001ACB  0000              add [bx+si],al
00001ACD  0000              add [bx+si],al
00001ACF  0000              add [bx+si],al
00001AD1  0000              add [bx+si],al
00001AD3  0000              add [bx+si],al
00001AD5  0000              add [bx+si],al
00001AD7  0000              add [bx+si],al
00001AD9  0000              add [bx+si],al
00001ADB  0000              add [bx+si],al
00001ADD  0000              add [bx+si],al
00001ADF  0000              add [bx+si],al
00001AE1  0000              add [bx+si],al
00001AE3  0000              add [bx+si],al
00001AE5  0000              add [bx+si],al
00001AE7  0000              add [bx+si],al
00001AE9  0000              add [bx+si],al
00001AEB  0000              add [bx+si],al
00001AED  0000              add [bx+si],al
00001AEF  0000              add [bx+si],al
00001AF1  0000              add [bx+si],al
00001AF3  0000              add [bx+si],al
00001AF5  0000              add [bx+si],al
00001AF7  0000              add [bx+si],al
00001AF9  0000              add [bx+si],al
00001AFB  0000              add [bx+si],al
00001AFD  0000              add [bx+si],al
00001AFF  0000              add [bx+si],al
00001B01  0000              add [bx+si],al
00001B03  0000              add [bx+si],al
00001B05  0000              add [bx+si],al
00001B07  0000              add [bx+si],al
00001B09  0000              add [bx+si],al
00001B0B  0000              add [bx+si],al
00001B0D  0000              add [bx+si],al
00001B0F  0000              add [bx+si],al
00001B11  0000              add [bx+si],al
00001B13  0000              add [bx+si],al
00001B15  0000              add [bx+si],al
00001B17  0000              add [bx+si],al
00001B19  0000              add [bx+si],al
00001B1B  0000              add [bx+si],al
00001B1D  0000              add [bx+si],al
00001B1F  0000              add [bx+si],al
00001B21  0000              add [bx+si],al
00001B23  0000              add [bx+si],al
00001B25  0000              add [bx+si],al
00001B27  0000              add [bx+si],al
00001B29  0000              add [bx+si],al
00001B2B  0000              add [bx+si],al
00001B2D  0000              add [bx+si],al
00001B2F  0000              add [bx+si],al
00001B31  0000              add [bx+si],al
00001B33  0000              add [bx+si],al
00001B35  0000              add [bx+si],al
00001B37  0000              add [bx+si],al
00001B39  0000              add [bx+si],al
00001B3B  0000              add [bx+si],al
00001B3D  0000              add [bx+si],al
00001B3F  0000              add [bx+si],al
00001B41  0000              add [bx+si],al
00001B43  0000              add [bx+si],al
00001B45  0000              add [bx+si],al
00001B47  0000              add [bx+si],al
00001B49  0000              add [bx+si],al
00001B4B  0000              add [bx+si],al
00001B4D  0000              add [bx+si],al
00001B4F  0000              add [bx+si],al
00001B51  0000              add [bx+si],al
00001B53  0000              add [bx+si],al
00001B55  0000              add [bx+si],al
00001B57  0000              add [bx+si],al
00001B59  0000              add [bx+si],al
00001B5B  0000              add [bx+si],al
00001B5D  0000              add [bx+si],al
00001B5F  0000              add [bx+si],al
00001B61  0000              add [bx+si],al
00001B63  0000              add [bx+si],al
00001B65  0000              add [bx+si],al
00001B67  0000              add [bx+si],al
00001B69  0000              add [bx+si],al
00001B6B  0000              add [bx+si],al
00001B6D  0000              add [bx+si],al
00001B6F  0000              add [bx+si],al
00001B71  0000              add [bx+si],al
00001B73  0000              add [bx+si],al
00001B75  0000              add [bx+si],al
00001B77  0000              add [bx+si],al
00001B79  0000              add [bx+si],al
00001B7B  0000              add [bx+si],al
00001B7D  0000              add [bx+si],al
00001B7F  0000              add [bx+si],al
00001B81  0000              add [bx+si],al
00001B83  0000              add [bx+si],al
00001B85  0000              add [bx+si],al
00001B87  0000              add [bx+si],al
00001B89  0000              add [bx+si],al
00001B8B  0000              add [bx+si],al
00001B8D  0000              add [bx+si],al
00001B8F  0000              add [bx+si],al
00001B91  0000              add [bx+si],al
00001B93  0000              add [bx+si],al
00001B95  0000              add [bx+si],al
00001B97  0000              add [bx+si],al
00001B99  0000              add [bx+si],al
00001B9B  0000              add [bx+si],al
00001B9D  0000              add [bx+si],al
00001B9F  0000              add [bx+si],al
00001BA1  0000              add [bx+si],al
00001BA3  0000              add [bx+si],al
00001BA5  0000              add [bx+si],al
00001BA7  0000              add [bx+si],al
00001BA9  0000              add [bx+si],al
00001BAB  0000              add [bx+si],al
00001BAD  0000              add [bx+si],al
00001BAF  0000              add [bx+si],al
00001BB1  0000              add [bx+si],al
00001BB3  0000              add [bx+si],al
00001BB5  0000              add [bx+si],al
00001BB7  0000              add [bx+si],al
00001BB9  0000              add [bx+si],al
00001BBB  0000              add [bx+si],al
00001BBD  0000              add [bx+si],al
00001BBF  0000              add [bx+si],al
00001BC1  0000              add [bx+si],al
00001BC3  0000              add [bx+si],al
00001BC5  0000              add [bx+si],al
00001BC7  0000              add [bx+si],al
00001BC9  0000              add [bx+si],al
00001BCB  0000              add [bx+si],al
00001BCD  0000              add [bx+si],al
00001BCF  0000              add [bx+si],al
00001BD1  0000              add [bx+si],al
00001BD3  0000              add [bx+si],al
00001BD5  0000              add [bx+si],al
00001BD7  0000              add [bx+si],al
00001BD9  0000              add [bx+si],al
00001BDB  0000              add [bx+si],al
00001BDD  0000              add [bx+si],al
00001BDF  0000              add [bx+si],al
00001BE1  0000              add [bx+si],al
00001BE3  0000              add [bx+si],al
00001BE5  0000              add [bx+si],al
00001BE7  0000              add [bx+si],al
00001BE9  0000              add [bx+si],al
00001BEB  0000              add [bx+si],al
00001BED  0000              add [bx+si],al
00001BEF  0000              add [bx+si],al
00001BF1  0000              add [bx+si],al
00001BF3  0000              add [bx+si],al
00001BF5  0000              add [bx+si],al
00001BF7  0000              add [bx+si],al
00001BF9  0000              add [bx+si],al
00001BFB  0000              add [bx+si],al
00001BFD  0000              add [bx+si],al
00001BFF  0000              add [bx+si],al
00001C01  0000              add [bx+si],al
00001C03  0000              add [bx+si],al
00001C05  0000              add [bx+si],al
00001C07  0000              add [bx+si],al
00001C09  0000              add [bx+si],al
00001C0B  0000              add [bx+si],al
00001C0D  0000              add [bx+si],al
00001C0F  0000              add [bx+si],al
00001C11  0000              add [bx+si],al
00001C13  0000              add [bx+si],al
00001C15  0000              add [bx+si],al
00001C17  0000              add [bx+si],al
00001C19  0000              add [bx+si],al
00001C1B  0000              add [bx+si],al
00001C1D  0000              add [bx+si],al
00001C1F  0000              add [bx+si],al
00001C21  0000              add [bx+si],al
00001C23  0000              add [bx+si],al
00001C25  0000              add [bx+si],al
00001C27  0000              add [bx+si],al
00001C29  0000              add [bx+si],al
00001C2B  0000              add [bx+si],al
00001C2D  0000              add [bx+si],al
00001C2F  0000              add [bx+si],al
00001C31  0000              add [bx+si],al
00001C33  0000              add [bx+si],al
00001C35  0000              add [bx+si],al
00001C37  0000              add [bx+si],al
00001C39  0000              add [bx+si],al
00001C3B  0000              add [bx+si],al
00001C3D  0000              add [bx+si],al
00001C3F  0000              add [bx+si],al
00001C41  0000              add [bx+si],al
00001C43  0000              add [bx+si],al
00001C45  0000              add [bx+si],al
00001C47  0000              add [bx+si],al
00001C49  0000              add [bx+si],al
00001C4B  0000              add [bx+si],al
00001C4D  0000              add [bx+si],al
00001C4F  0000              add [bx+si],al
00001C51  0000              add [bx+si],al
00001C53  0000              add [bx+si],al
00001C55  0000              add [bx+si],al
00001C57  0000              add [bx+si],al
00001C59  0000              add [bx+si],al
00001C5B  0000              add [bx+si],al
00001C5D  0000              add [bx+si],al
00001C5F  0000              add [bx+si],al
00001C61  0000              add [bx+si],al
00001C63  0000              add [bx+si],al
00001C65  0000              add [bx+si],al
00001C67  0000              add [bx+si],al
00001C69  0000              add [bx+si],al
00001C6B  0000              add [bx+si],al
00001C6D  0000              add [bx+si],al
00001C6F  0000              add [bx+si],al
00001C71  0000              add [bx+si],al
00001C73  0000              add [bx+si],al
00001C75  0000              add [bx+si],al
00001C77  0000              add [bx+si],al
00001C79  0000              add [bx+si],al
00001C7B  0000              add [bx+si],al
00001C7D  0000              add [bx+si],al
00001C7F  0000              add [bx+si],al
00001C81  0000              add [bx+si],al
00001C83  0000              add [bx+si],al
00001C85  0000              add [bx+si],al
00001C87  0000              add [bx+si],al
00001C89  0000              add [bx+si],al
00001C8B  0000              add [bx+si],al
00001C8D  0000              add [bx+si],al
00001C8F  0000              add [bx+si],al
00001C91  0000              add [bx+si],al
00001C93  0000              add [bx+si],al
00001C95  0000              add [bx+si],al
00001C97  0000              add [bx+si],al
00001C99  0000              add [bx+si],al
00001C9B  0000              add [bx+si],al
00001C9D  0000              add [bx+si],al
00001C9F  0000              add [bx+si],al
00001CA1  0000              add [bx+si],al
00001CA3  0000              add [bx+si],al
00001CA5  0000              add [bx+si],al
00001CA7  0000              add [bx+si],al
00001CA9  0000              add [bx+si],al
00001CAB  0000              add [bx+si],al
00001CAD  0000              add [bx+si],al
00001CAF  0000              add [bx+si],al
00001CB1  0000              add [bx+si],al
00001CB3  0000              add [bx+si],al
00001CB5  0000              add [bx+si],al
00001CB7  0000              add [bx+si],al
00001CB9  0000              add [bx+si],al
00001CBB  0000              add [bx+si],al
00001CBD  0000              add [bx+si],al
00001CBF  0000              add [bx+si],al
00001CC1  0000              add [bx+si],al
00001CC3  0000              add [bx+si],al
00001CC5  0000              add [bx+si],al
00001CC7  0000              add [bx+si],al
00001CC9  0000              add [bx+si],al
00001CCB  0000              add [bx+si],al
00001CCD  0000              add [bx+si],al
00001CCF  0000              add [bx+si],al
00001CD1  0000              add [bx+si],al
00001CD3  0000              add [bx+si],al
00001CD5  0000              add [bx+si],al
00001CD7  0000              add [bx+si],al
00001CD9  0000              add [bx+si],al
00001CDB  0000              add [bx+si],al
00001CDD  0000              add [bx+si],al
00001CDF  0000              add [bx+si],al
00001CE1  0000              add [bx+si],al
00001CE3  0000              add [bx+si],al
00001CE5  0000              add [bx+si],al
00001CE7  0000              add [bx+si],al
00001CE9  0000              add [bx+si],al
00001CEB  0000              add [bx+si],al
00001CED  0000              add [bx+si],al
00001CEF  0000              add [bx+si],al
00001CF1  0000              add [bx+si],al
00001CF3  0000              add [bx+si],al
00001CF5  0000              add [bx+si],al
00001CF7  0000              add [bx+si],al
00001CF9  0000              add [bx+si],al
00001CFB  0000              add [bx+si],al
00001CFD  0000              add [bx+si],al
00001CFF  0000              add [bx+si],al
00001D01  0000              add [bx+si],al
00001D03  0000              add [bx+si],al
00001D05  0000              add [bx+si],al
00001D07  0000              add [bx+si],al
00001D09  0000              add [bx+si],al
00001D0B  0000              add [bx+si],al
00001D0D  0000              add [bx+si],al
00001D0F  0000              add [bx+si],al
00001D11  0000              add [bx+si],al
00001D13  0000              add [bx+si],al
00001D15  0000              add [bx+si],al
00001D17  0000              add [bx+si],al
00001D19  0000              add [bx+si],al
00001D1B  0000              add [bx+si],al
00001D1D  0000              add [bx+si],al
00001D1F  0000              add [bx+si],al
00001D21  0000              add [bx+si],al
00001D23  0000              add [bx+si],al
00001D25  0000              add [bx+si],al
00001D27  0000              add [bx+si],al
00001D29  0000              add [bx+si],al
00001D2B  0000              add [bx+si],al
00001D2D  0000              add [bx+si],al
00001D2F  0000              add [bx+si],al
00001D31  0000              add [bx+si],al
00001D33  0000              add [bx+si],al
00001D35  0000              add [bx+si],al
00001D37  0000              add [bx+si],al
00001D39  0000              add [bx+si],al
00001D3B  0000              add [bx+si],al
00001D3D  0000              add [bx+si],al
00001D3F  0000              add [bx+si],al
00001D41  0000              add [bx+si],al
00001D43  0000              add [bx+si],al
00001D45  0000              add [bx+si],al
00001D47  0000              add [bx+si],al
00001D49  0000              add [bx+si],al
00001D4B  0000              add [bx+si],al
00001D4D  0000              add [bx+si],al
00001D4F  0000              add [bx+si],al
00001D51  0000              add [bx+si],al
00001D53  0000              add [bx+si],al
00001D55  0000              add [bx+si],al
00001D57  0000              add [bx+si],al
00001D59  0000              add [bx+si],al
00001D5B  0000              add [bx+si],al
00001D5D  0000              add [bx+si],al
00001D5F  0000              add [bx+si],al
00001D61  0000              add [bx+si],al
00001D63  0000              add [bx+si],al
00001D65  0000              add [bx+si],al
00001D67  0000              add [bx+si],al
00001D69  0000              add [bx+si],al
00001D6B  0000              add [bx+si],al
00001D6D  0000              add [bx+si],al
00001D6F  0000              add [bx+si],al
00001D71  0000              add [bx+si],al
00001D73  0000              add [bx+si],al
00001D75  0000              add [bx+si],al
00001D77  0000              add [bx+si],al
00001D79  0000              add [bx+si],al
00001D7B  0000              add [bx+si],al
00001D7D  0000              add [bx+si],al
00001D7F  0000              add [bx+si],al
00001D81  0000              add [bx+si],al
00001D83  0000              add [bx+si],al
00001D85  0000              add [bx+si],al
00001D87  0000              add [bx+si],al
00001D89  0000              add [bx+si],al
00001D8B  0000              add [bx+si],al
00001D8D  0000              add [bx+si],al
00001D8F  0000              add [bx+si],al
00001D91  0000              add [bx+si],al
00001D93  0000              add [bx+si],al
00001D95  0000              add [bx+si],al
00001D97  0000              add [bx+si],al
00001D99  0000              add [bx+si],al
00001D9B  0000              add [bx+si],al
00001D9D  0000              add [bx+si],al
00001D9F  0000              add [bx+si],al
00001DA1  0000              add [bx+si],al
00001DA3  0000              add [bx+si],al
00001DA5  0000              add [bx+si],al
00001DA7  0000              add [bx+si],al
00001DA9  0000              add [bx+si],al
00001DAB  0000              add [bx+si],al
00001DAD  0000              add [bx+si],al
00001DAF  0000              add [bx+si],al
00001DB1  0000              add [bx+si],al
00001DB3  0000              add [bx+si],al
00001DB5  0000              add [bx+si],al
00001DB7  0000              add [bx+si],al
00001DB9  0000              add [bx+si],al
00001DBB  0000              add [bx+si],al
00001DBD  0000              add [bx+si],al
00001DBF  0000              add [bx+si],al
00001DC1  0000              add [bx+si],al
00001DC3  0000              add [bx+si],al
00001DC5  0000              add [bx+si],al
00001DC7  0000              add [bx+si],al
00001DC9  0000              add [bx+si],al
00001DCB  0000              add [bx+si],al
00001DCD  0000              add [bx+si],al
00001DCF  0000              add [bx+si],al
00001DD1  0000              add [bx+si],al
00001DD3  0000              add [bx+si],al
00001DD5  0000              add [bx+si],al
00001DD7  0000              add [bx+si],al
00001DD9  0000              add [bx+si],al
00001DDB  0000              add [bx+si],al
00001DDD  0000              add [bx+si],al
00001DDF  0000              add [bx+si],al
00001DE1  0000              add [bx+si],al
00001DE3  0000              add [bx+si],al
00001DE5  0000              add [bx+si],al
00001DE7  0000              add [bx+si],al
00001DE9  0000              add [bx+si],al
00001DEB  0000              add [bx+si],al
00001DED  0000              add [bx+si],al
00001DEF  0000              add [bx+si],al
00001DF1  0000              add [bx+si],al
00001DF3  0000              add [bx+si],al
00001DF5  0000              add [bx+si],al
00001DF7  0000              add [bx+si],al
00001DF9  0000              add [bx+si],al
00001DFB  0000              add [bx+si],al
00001DFD  0000              add [bx+si],al
00001DFF  0000              add [bx+si],al
00001E01  0000              add [bx+si],al
00001E03  0000              add [bx+si],al
00001E05  0000              add [bx+si],al
00001E07  0000              add [bx+si],al
00001E09  0000              add [bx+si],al
00001E0B  0000              add [bx+si],al
00001E0D  0000              add [bx+si],al
00001E0F  0000              add [bx+si],al
00001E11  0000              add [bx+si],al
00001E13  0000              add [bx+si],al
00001E15  0000              add [bx+si],al
00001E17  0000              add [bx+si],al
00001E19  0000              add [bx+si],al
00001E1B  0000              add [bx+si],al
00001E1D  0000              add [bx+si],al
00001E1F  0000              add [bx+si],al
00001E21  0000              add [bx+si],al
00001E23  0000              add [bx+si],al
00001E25  0000              add [bx+si],al
00001E27  0000              add [bx+si],al
00001E29  0000              add [bx+si],al
00001E2B  0000              add [bx+si],al
00001E2D  0000              add [bx+si],al
00001E2F  0000              add [bx+si],al
00001E31  0000              add [bx+si],al
00001E33  0000              add [bx+si],al
00001E35  0000              add [bx+si],al
00001E37  0000              add [bx+si],al
00001E39  0000              add [bx+si],al
00001E3B  0000              add [bx+si],al
00001E3D  0000              add [bx+si],al
00001E3F  0000              add [bx+si],al
00001E41  0000              add [bx+si],al
00001E43  0000              add [bx+si],al
00001E45  0000              add [bx+si],al
00001E47  0000              add [bx+si],al
00001E49  0000              add [bx+si],al
00001E4B  0000              add [bx+si],al
00001E4D  0000              add [bx+si],al
00001E4F  0000              add [bx+si],al
00001E51  0000              add [bx+si],al
00001E53  0000              add [bx+si],al
00001E55  0000              add [bx+si],al
00001E57  0000              add [bx+si],al
00001E59  0000              add [bx+si],al
00001E5B  0000              add [bx+si],al
00001E5D  0000              add [bx+si],al
00001E5F  0000              add [bx+si],al
00001E61  0000              add [bx+si],al
00001E63  0000              add [bx+si],al
00001E65  0000              add [bx+si],al
00001E67  0000              add [bx+si],al
00001E69  0000              add [bx+si],al
00001E6B  0000              add [bx+si],al
00001E6D  0000              add [bx+si],al
00001E6F  0000              add [bx+si],al
00001E71  0000              add [bx+si],al
00001E73  0000              add [bx+si],al
00001E75  0000              add [bx+si],al
00001E77  0000              add [bx+si],al
00001E79  0000              add [bx+si],al
00001E7B  0000              add [bx+si],al
00001E7D  0000              add [bx+si],al
00001E7F  0000              add [bx+si],al
00001E81  0000              add [bx+si],al
00001E83  0000              add [bx+si],al
00001E85  0000              add [bx+si],al
00001E87  0000              add [bx+si],al
00001E89  0000              add [bx+si],al
00001E8B  0000              add [bx+si],al
00001E8D  0000              add [bx+si],al
00001E8F  0000              add [bx+si],al
00001E91  0000              add [bx+si],al
00001E93  0000              add [bx+si],al
00001E95  0000              add [bx+si],al
00001E97  0000              add [bx+si],al
00001E99  0000              add [bx+si],al
00001E9B  0000              add [bx+si],al
00001E9D  0000              add [bx+si],al
00001E9F  0000              add [bx+si],al
00001EA1  0000              add [bx+si],al
00001EA3  0000              add [bx+si],al
00001EA5  0000              add [bx+si],al
00001EA7  0000              add [bx+si],al
00001EA9  0000              add [bx+si],al
00001EAB  0000              add [bx+si],al
00001EAD  0000              add [bx+si],al
00001EAF  0000              add [bx+si],al
00001EB1  0000              add [bx+si],al
00001EB3  0000              add [bx+si],al
00001EB5  0000              add [bx+si],al
00001EB7  0000              add [bx+si],al
00001EB9  0000              add [bx+si],al
00001EBB  0000              add [bx+si],al
00001EBD  0000              add [bx+si],al
00001EBF  0000              add [bx+si],al
00001EC1  0000              add [bx+si],al
00001EC3  0000              add [bx+si],al
00001EC5  0000              add [bx+si],al
00001EC7  0000              add [bx+si],al
00001EC9  0000              add [bx+si],al
00001ECB  0000              add [bx+si],al
00001ECD  0000              add [bx+si],al
00001ECF  0000              add [bx+si],al
00001ED1  0000              add [bx+si],al
00001ED3  0000              add [bx+si],al
00001ED5  0000              add [bx+si],al
00001ED7  0000              add [bx+si],al
00001ED9  0000              add [bx+si],al
00001EDB  0000              add [bx+si],al
00001EDD  0000              add [bx+si],al
00001EDF  0000              add [bx+si],al
00001EE1  0000              add [bx+si],al
00001EE3  0000              add [bx+si],al
00001EE5  0000              add [bx+si],al
00001EE7  0000              add [bx+si],al
00001EE9  0000              add [bx+si],al
00001EEB  0000              add [bx+si],al
00001EED  0000              add [bx+si],al
00001EEF  0000              add [bx+si],al
00001EF1  0000              add [bx+si],al
00001EF3  0000              add [bx+si],al
00001EF5  0000              add [bx+si],al
00001EF7  0000              add [bx+si],al
00001EF9  0000              add [bx+si],al
00001EFB  0000              add [bx+si],al
00001EFD  0000              add [bx+si],al
00001EFF  0000              add [bx+si],al
00001F01  0000              add [bx+si],al
00001F03  0000              add [bx+si],al
00001F05  0000              add [bx+si],al
00001F07  0000              add [bx+si],al
00001F09  0000              add [bx+si],al
00001F0B  0000              add [bx+si],al
00001F0D  0000              add [bx+si],al
00001F0F  0000              add [bx+si],al
00001F11  0000              add [bx+si],al
00001F13  0000              add [bx+si],al
00001F15  0000              add [bx+si],al
00001F17  0000              add [bx+si],al
00001F19  0000              add [bx+si],al
00001F1B  0000              add [bx+si],al
00001F1D  0000              add [bx+si],al
00001F1F  0000              add [bx+si],al
00001F21  0000              add [bx+si],al
00001F23  0000              add [bx+si],al
00001F25  0000              add [bx+si],al
00001F27  0000              add [bx+si],al
00001F29  0000              add [bx+si],al
00001F2B  0000              add [bx+si],al
00001F2D  0000              add [bx+si],al
00001F2F  0000              add [bx+si],al
00001F31  0000              add [bx+si],al
00001F33  0000              add [bx+si],al
00001F35  0000              add [bx+si],al
00001F37  0000              add [bx+si],al
00001F39  0000              add [bx+si],al
00001F3B  0000              add [bx+si],al
00001F3D  0000              add [bx+si],al
00001F3F  0000              add [bx+si],al
00001F41  0000              add [bx+si],al
00001F43  0000              add [bx+si],al
00001F45  0000              add [bx+si],al
00001F47  0000              add [bx+si],al
00001F49  0000              add [bx+si],al
00001F4B  0000              add [bx+si],al
00001F4D  0000              add [bx+si],al
00001F4F  0000              add [bx+si],al
00001F51  0000              add [bx+si],al
00001F53  0000              add [bx+si],al
00001F55  0000              add [bx+si],al
00001F57  0000              add [bx+si],al
00001F59  0000              add [bx+si],al
00001F5B  0000              add [bx+si],al
00001F5D  0000              add [bx+si],al
00001F5F  0000              add [bx+si],al
00001F61  0000              add [bx+si],al
00001F63  0000              add [bx+si],al
00001F65  0000              add [bx+si],al
00001F67  0000              add [bx+si],al
00001F69  0000              add [bx+si],al
00001F6B  0000              add [bx+si],al
00001F6D  0000              add [bx+si],al
00001F6F  0000              add [bx+si],al
00001F71  0000              add [bx+si],al
00001F73  0000              add [bx+si],al
00001F75  0000              add [bx+si],al
00001F77  0000              add [bx+si],al
00001F79  0000              add [bx+si],al
00001F7B  0000              add [bx+si],al
00001F7D  0000              add [bx+si],al
00001F7F  0000              add [bx+si],al
00001F81  0000              add [bx+si],al
00001F83  0000              add [bx+si],al
00001F85  0000              add [bx+si],al
00001F87  0000              add [bx+si],al
00001F89  0000              add [bx+si],al
00001F8B  0000              add [bx+si],al
00001F8D  0000              add [bx+si],al
00001F8F  0000              add [bx+si],al
00001F91  0000              add [bx+si],al
00001F93  0000              add [bx+si],al
00001F95  0000              add [bx+si],al
00001F97  0000              add [bx+si],al
00001F99  0000              add [bx+si],al
00001F9B  0000              add [bx+si],al
00001F9D  0000              add [bx+si],al
00001F9F  0000              add [bx+si],al
00001FA1  0000              add [bx+si],al
00001FA3  0000              add [bx+si],al
00001FA5  0000              add [bx+si],al
00001FA7  0000              add [bx+si],al
00001FA9  0000              add [bx+si],al
00001FAB  0000              add [bx+si],al
00001FAD  0000              add [bx+si],al
00001FAF  0000              add [bx+si],al
00001FB1  0000              add [bx+si],al
00001FB3  0000              add [bx+si],al
00001FB5  0000              add [bx+si],al
00001FB7  0000              add [bx+si],al
00001FB9  0000              add [bx+si],al
00001FBB  0000              add [bx+si],al
00001FBD  0000              add [bx+si],al
00001FBF  0000              add [bx+si],al
00001FC1  0000              add [bx+si],al
00001FC3  0000              add [bx+si],al
00001FC5  0000              add [bx+si],al
00001FC7  0000              add [bx+si],al
00001FC9  0000              add [bx+si],al
00001FCB  0000              add [bx+si],al
00001FCD  0000              add [bx+si],al
00001FCF  0000              add [bx+si],al
00001FD1  0000              add [bx+si],al
00001FD3  0000              add [bx+si],al
00001FD5  0000              add [bx+si],al
00001FD7  0000              add [bx+si],al
00001FD9  0000              add [bx+si],al
00001FDB  0000              add [bx+si],al
00001FDD  0000              add [bx+si],al
00001FDF  0000              add [bx+si],al
00001FE1  0000              add [bx+si],al
00001FE3  0000              add [bx+si],al
00001FE5  0000              add [bx+si],al
00001FE7  0000              add [bx+si],al
00001FE9  0000              add [bx+si],al
00001FEB  0000              add [bx+si],al
00001FED  0000              add [bx+si],al
00001FEF  0000              add [bx+si],al
00001FF1  0000              add [bx+si],al
00001FF3  0000              add [bx+si],al
00001FF5  0000              add [bx+si],al
00001FF7  0000              add [bx+si],al
00001FF9  0000              add [bx+si],al
00001FFB  0000              add [bx+si],al
00001FFD  0000              add [bx+si],al
00001FFF  0000              add [bx+si],al
00002001  0000              add [bx+si],al
00002003  0000              add [bx+si],al
00002005  0000              add [bx+si],al
00002007  0000              add [bx+si],al
00002009  0000              add [bx+si],al
0000200B  0000              add [bx+si],al
0000200D  0000              add [bx+si],al
0000200F  0000              add [bx+si],al
00002011  0000              add [bx+si],al
00002013  0000              add [bx+si],al
00002015  0000              add [bx+si],al
00002017  0000              add [bx+si],al
00002019  0000              add [bx+si],al
0000201B  0000              add [bx+si],al
0000201D  0000              add [bx+si],al
0000201F  0000              add [bx+si],al
00002021  0000              add [bx+si],al
00002023  0000              add [bx+si],al
00002025  0000              add [bx+si],al
00002027  0000              add [bx+si],al
00002029  0000              add [bx+si],al
0000202B  0000              add [bx+si],al
0000202D  0000              add [bx+si],al
0000202F  0000              add [bx+si],al
00002031  0000              add [bx+si],al
00002033  0000              add [bx+si],al
00002035  0000              add [bx+si],al
00002037  0000              add [bx+si],al
00002039  0000              add [bx+si],al
0000203B  0000              add [bx+si],al
0000203D  0000              add [bx+si],al
0000203F  0000              add [bx+si],al
00002041  0000              add [bx+si],al
00002043  0000              add [bx+si],al
00002045  0000              add [bx+si],al
00002047  0000              add [bx+si],al
00002049  0000              add [bx+si],al
0000204B  0000              add [bx+si],al
0000204D  0000              add [bx+si],al
0000204F  0000              add [bx+si],al
00002051  0000              add [bx+si],al
00002053  0000              add [bx+si],al
00002055  0000              add [bx+si],al
00002057  0000              add [bx+si],al
00002059  0000              add [bx+si],al
0000205B  0000              add [bx+si],al
0000205D  0000              add [bx+si],al
0000205F  0000              add [bx+si],al
00002061  0000              add [bx+si],al
00002063  0000              add [bx+si],al
00002065  0000              add [bx+si],al
00002067  0000              add [bx+si],al
00002069  0000              add [bx+si],al
0000206B  0000              add [bx+si],al
0000206D  0000              add [bx+si],al
0000206F  0000              add [bx+si],al
00002071  0000              add [bx+si],al
00002073  0000              add [bx+si],al
00002075  0000              add [bx+si],al
00002077  0000              add [bx+si],al
00002079  0000              add [bx+si],al
0000207B  0000              add [bx+si],al
0000207D  0000              add [bx+si],al
0000207F  0000              add [bx+si],al
00002081  0000              add [bx+si],al
00002083  0000              add [bx+si],al
00002085  0000              add [bx+si],al
00002087  0000              add [bx+si],al
00002089  0000              add [bx+si],al
0000208B  0000              add [bx+si],al
0000208D  0000              add [bx+si],al
0000208F  0000              add [bx+si],al
00002091  0000              add [bx+si],al
00002093  0000              add [bx+si],al
00002095  0000              add [bx+si],al
00002097  0000              add [bx+si],al
00002099  0000              add [bx+si],al
0000209B  0000              add [bx+si],al
0000209D  0000              add [bx+si],al
0000209F  0000              add [bx+si],al
000020A1  0000              add [bx+si],al
000020A3  0000              add [bx+si],al
000020A5  0000              add [bx+si],al
000020A7  0000              add [bx+si],al
000020A9  0000              add [bx+si],al
000020AB  0000              add [bx+si],al
000020AD  0000              add [bx+si],al
000020AF  0000              add [bx+si],al
000020B1  0000              add [bx+si],al
000020B3  0000              add [bx+si],al
000020B5  0000              add [bx+si],al
000020B7  0000              add [bx+si],al
000020B9  0000              add [bx+si],al
000020BB  0000              add [bx+si],al
000020BD  0000              add [bx+si],al
000020BF  0000              add [bx+si],al
000020C1  0000              add [bx+si],al
000020C3  0000              add [bx+si],al
000020C5  0000              add [bx+si],al
000020C7  0000              add [bx+si],al
000020C9  0000              add [bx+si],al
000020CB  0000              add [bx+si],al
000020CD  0000              add [bx+si],al
000020CF  0000              add [bx+si],al
000020D1  0000              add [bx+si],al
000020D3  0000              add [bx+si],al
000020D5  0000              add [bx+si],al
000020D7  0000              add [bx+si],al
000020D9  0000              add [bx+si],al
000020DB  0000              add [bx+si],al
000020DD  0000              add [bx+si],al
000020DF  0000              add [bx+si],al
000020E1  0000              add [bx+si],al
000020E3  0000              add [bx+si],al
000020E5  0000              add [bx+si],al
000020E7  0000              add [bx+si],al
000020E9  0000              add [bx+si],al
000020EB  0000              add [bx+si],al
000020ED  0000              add [bx+si],al
000020EF  0000              add [bx+si],al
000020F1  0000              add [bx+si],al
000020F3  0000              add [bx+si],al
000020F5  0000              add [bx+si],al
000020F7  0000              add [bx+si],al
000020F9  0000              add [bx+si],al
000020FB  0000              add [bx+si],al
000020FD  0000              add [bx+si],al
000020FF  0000              add [bx+si],al
00002101  0000              add [bx+si],al
00002103  0000              add [bx+si],al
00002105  0000              add [bx+si],al
00002107  0000              add [bx+si],al
00002109  0000              add [bx+si],al
0000210B  0000              add [bx+si],al
0000210D  0000              add [bx+si],al
0000210F  0000              add [bx+si],al
00002111  0000              add [bx+si],al
00002113  0000              add [bx+si],al
00002115  0000              add [bx+si],al
00002117  0000              add [bx+si],al
00002119  0000              add [bx+si],al
0000211B  0000              add [bx+si],al
0000211D  0000              add [bx+si],al
0000211F  0000              add [bx+si],al
00002121  0000              add [bx+si],al
00002123  0000              add [bx+si],al
00002125  0000              add [bx+si],al
00002127  0000              add [bx+si],al
00002129  0000              add [bx+si],al
0000212B  0000              add [bx+si],al
0000212D  0000              add [bx+si],al
0000212F  0000              add [bx+si],al
00002131  0000              add [bx+si],al
00002133  0000              add [bx+si],al
00002135  0000              add [bx+si],al
00002137  0000              add [bx+si],al
00002139  0000              add [bx+si],al
0000213B  0000              add [bx+si],al
0000213D  0000              add [bx+si],al
0000213F  0000              add [bx+si],al
00002141  0000              add [bx+si],al
00002143  0000              add [bx+si],al
00002145  0000              add [bx+si],al
00002147  0000              add [bx+si],al
00002149  0000              add [bx+si],al
0000214B  0000              add [bx+si],al
0000214D  0000              add [bx+si],al
0000214F  0000              add [bx+si],al
00002151  0000              add [bx+si],al
00002153  0000              add [bx+si],al
00002155  0000              add [bx+si],al
00002157  0000              add [bx+si],al
00002159  0000              add [bx+si],al
0000215B  0000              add [bx+si],al
0000215D  0000              add [bx+si],al
0000215F  0000              add [bx+si],al
00002161  0000              add [bx+si],al
00002163  0000              add [bx+si],al
00002165  0000              add [bx+si],al
00002167  0000              add [bx+si],al
00002169  0000              add [bx+si],al
0000216B  0000              add [bx+si],al
0000216D  0000              add [bx+si],al
0000216F  0000              add [bx+si],al
00002171  0000              add [bx+si],al
00002173  0000              add [bx+si],al
00002175  0000              add [bx+si],al
00002177  0000              add [bx+si],al
00002179  0000              add [bx+si],al
0000217B  0000              add [bx+si],al
0000217D  0000              add [bx+si],al
0000217F  0000              add [bx+si],al
00002181  0000              add [bx+si],al
00002183  0000              add [bx+si],al
00002185  0000              add [bx+si],al
00002187  0000              add [bx+si],al
00002189  0000              add [bx+si],al
0000218B  0000              add [bx+si],al
0000218D  0000              add [bx+si],al
0000218F  0000              add [bx+si],al
00002191  0000              add [bx+si],al
00002193  0000              add [bx+si],al
00002195  0000              add [bx+si],al
00002197  0000              add [bx+si],al
00002199  0000              add [bx+si],al
0000219B  0000              add [bx+si],al
0000219D  0000              add [bx+si],al
0000219F  0000              add [bx+si],al
000021A1  0000              add [bx+si],al
000021A3  0000              add [bx+si],al
000021A5  0000              add [bx+si],al
000021A7  0000              add [bx+si],al
000021A9  0000              add [bx+si],al
000021AB  0000              add [bx+si],al
000021AD  0000              add [bx+si],al
000021AF  0000              add [bx+si],al
000021B1  0000              add [bx+si],al
000021B3  0000              add [bx+si],al
000021B5  0000              add [bx+si],al
000021B7  0000              add [bx+si],al
000021B9  0000              add [bx+si],al
000021BB  0000              add [bx+si],al
000021BD  0000              add [bx+si],al
000021BF  0000              add [bx+si],al
000021C1  0000              add [bx+si],al
000021C3  0000              add [bx+si],al
000021C5  0000              add [bx+si],al
000021C7  0000              add [bx+si],al
000021C9  0000              add [bx+si],al
000021CB  0000              add [bx+si],al
000021CD  0000              add [bx+si],al
000021CF  0000              add [bx+si],al
000021D1  0000              add [bx+si],al
000021D3  0000              add [bx+si],al
000021D5  0000              add [bx+si],al
000021D7  0000              add [bx+si],al
000021D9  0000              add [bx+si],al
000021DB  0000              add [bx+si],al
000021DD  0000              add [bx+si],al
000021DF  0000              add [bx+si],al
000021E1  0000              add [bx+si],al
000021E3  0000              add [bx+si],al
000021E5  0000              add [bx+si],al
000021E7  0000              add [bx+si],al
000021E9  0000              add [bx+si],al
000021EB  0000              add [bx+si],al
000021ED  0000              add [bx+si],al
000021EF  0000              add [bx+si],al
000021F1  0000              add [bx+si],al
000021F3  0000              add [bx+si],al
000021F5  0000              add [bx+si],al
000021F7  0000              add [bx+si],al
000021F9  0000              add [bx+si],al
000021FB  0000              add [bx+si],al
000021FD  0000              add [bx+si],al
000021FF  0000              add [bx+si],al
00002201  0000              add [bx+si],al
00002203  0000              add [bx+si],al
00002205  0000              add [bx+si],al
00002207  0000              add [bx+si],al
00002209  0000              add [bx+si],al
0000220B  0000              add [bx+si],al
0000220D  0000              add [bx+si],al
0000220F  0000              add [bx+si],al
00002211  0000              add [bx+si],al
00002213  0000              add [bx+si],al
00002215  0000              add [bx+si],al
00002217  0000              add [bx+si],al
00002219  0000              add [bx+si],al
0000221B  0000              add [bx+si],al
0000221D  0000              add [bx+si],al
0000221F  0000              add [bx+si],al
00002221  0000              add [bx+si],al
00002223  0000              add [bx+si],al
00002225  0000              add [bx+si],al
00002227  0000              add [bx+si],al
00002229  0000              add [bx+si],al
0000222B  0000              add [bx+si],al
0000222D  0000              add [bx+si],al
0000222F  0000              add [bx+si],al
00002231  0000              add [bx+si],al
00002233  0000              add [bx+si],al
00002235  0000              add [bx+si],al
00002237  0000              add [bx+si],al
00002239  0000              add [bx+si],al
0000223B  0000              add [bx+si],al
0000223D  0000              add [bx+si],al
0000223F  0000              add [bx+si],al
00002241  0000              add [bx+si],al
00002243  0000              add [bx+si],al
00002245  0000              add [bx+si],al
00002247  0000              add [bx+si],al
00002249  0000              add [bx+si],al
0000224B  0000              add [bx+si],al
0000224D  0000              add [bx+si],al
0000224F  0000              add [bx+si],al
00002251  0000              add [bx+si],al
00002253  0000              add [bx+si],al
00002255  0000              add [bx+si],al
00002257  0000              add [bx+si],al
00002259  0000              add [bx+si],al
0000225B  0000              add [bx+si],al
0000225D  0000              add [bx+si],al
0000225F  0000              add [bx+si],al
00002261  0000              add [bx+si],al
00002263  0000              add [bx+si],al
00002265  0000              add [bx+si],al
00002267  0000              add [bx+si],al
00002269  0000              add [bx+si],al
0000226B  0000              add [bx+si],al
0000226D  0000              add [bx+si],al
0000226F  0000              add [bx+si],al
00002271  0000              add [bx+si],al
00002273  0000              add [bx+si],al
00002275  0000              add [bx+si],al
00002277  0000              add [bx+si],al
00002279  0000              add [bx+si],al
0000227B  0000              add [bx+si],al
0000227D  0000              add [bx+si],al
0000227F  0000              add [bx+si],al
00002281  0000              add [bx+si],al
00002283  0000              add [bx+si],al
00002285  0000              add [bx+si],al
00002287  0000              add [bx+si],al
00002289  0000              add [bx+si],al
0000228B  0000              add [bx+si],al
0000228D  0000              add [bx+si],al
0000228F  0000              add [bx+si],al
00002291  0000              add [bx+si],al
00002293  0000              add [bx+si],al
00002295  0000              add [bx+si],al
00002297  0000              add [bx+si],al
00002299  0000              add [bx+si],al
0000229B  0000              add [bx+si],al
0000229D  0000              add [bx+si],al
0000229F  0000              add [bx+si],al
000022A1  0000              add [bx+si],al
000022A3  0000              add [bx+si],al
000022A5  0000              add [bx+si],al
000022A7  0000              add [bx+si],al
000022A9  0000              add [bx+si],al
000022AB  0000              add [bx+si],al
000022AD  0000              add [bx+si],al
000022AF  0000              add [bx+si],al
000022B1  0000              add [bx+si],al
000022B3  0000              add [bx+si],al
000022B5  0000              add [bx+si],al
000022B7  0000              add [bx+si],al
000022B9  0000              add [bx+si],al
000022BB  0000              add [bx+si],al
000022BD  0000              add [bx+si],al
000022BF  0000              add [bx+si],al
000022C1  0000              add [bx+si],al
000022C3  0000              add [bx+si],al
000022C5  0000              add [bx+si],al
000022C7  0000              add [bx+si],al
000022C9  0000              add [bx+si],al
000022CB  0000              add [bx+si],al
000022CD  0000              add [bx+si],al
000022CF  0000              add [bx+si],al
000022D1  0000              add [bx+si],al
000022D3  0000              add [bx+si],al
000022D5  0000              add [bx+si],al
000022D7  0000              add [bx+si],al
000022D9  0000              add [bx+si],al
000022DB  0000              add [bx+si],al
000022DD  0000              add [bx+si],al
000022DF  0000              add [bx+si],al
000022E1  0000              add [bx+si],al
000022E3  0000              add [bx+si],al
000022E5  0000              add [bx+si],al
000022E7  0000              add [bx+si],al
000022E9  0000              add [bx+si],al
000022EB  0000              add [bx+si],al
000022ED  0000              add [bx+si],al
000022EF  0000              add [bx+si],al
000022F1  0000              add [bx+si],al
000022F3  0000              add [bx+si],al
000022F5  0000              add [bx+si],al
000022F7  0000              add [bx+si],al
000022F9  0000              add [bx+si],al
000022FB  0000              add [bx+si],al
000022FD  0000              add [bx+si],al
000022FF  0000              add [bx+si],al
00002301  0000              add [bx+si],al
00002303  0000              add [bx+si],al
00002305  0000              add [bx+si],al
00002307  0000              add [bx+si],al
00002309  0000              add [bx+si],al
0000230B  0000              add [bx+si],al
0000230D  0000              add [bx+si],al
0000230F  0000              add [bx+si],al
00002311  0000              add [bx+si],al
00002313  0000              add [bx+si],al
00002315  0000              add [bx+si],al
00002317  0000              add [bx+si],al
00002319  0000              add [bx+si],al
0000231B  0000              add [bx+si],al
0000231D  0000              add [bx+si],al
0000231F  0000              add [bx+si],al
00002321  0000              add [bx+si],al
00002323  0000              add [bx+si],al
00002325  0000              add [bx+si],al
00002327  0000              add [bx+si],al
00002329  0000              add [bx+si],al
0000232B  0000              add [bx+si],al
0000232D  0000              add [bx+si],al
0000232F  0000              add [bx+si],al
00002331  0000              add [bx+si],al
00002333  0000              add [bx+si],al
00002335  0000              add [bx+si],al
00002337  0000              add [bx+si],al
00002339  0000              add [bx+si],al
0000233B  0000              add [bx+si],al
0000233D  0000              add [bx+si],al
0000233F  0000              add [bx+si],al
00002341  0000              add [bx+si],al
00002343  0000              add [bx+si],al
00002345  0000              add [bx+si],al
00002347  0000              add [bx+si],al
00002349  0000              add [bx+si],al
0000234B  0000              add [bx+si],al
0000234D  0000              add [bx+si],al
0000234F  0000              add [bx+si],al
00002351  0000              add [bx+si],al
00002353  0000              add [bx+si],al
00002355  0000              add [bx+si],al
00002357  0000              add [bx+si],al
00002359  0000              add [bx+si],al
0000235B  0000              add [bx+si],al
0000235D  0000              add [bx+si],al
0000235F  0000              add [bx+si],al
00002361  0000              add [bx+si],al
00002363  0000              add [bx+si],al
00002365  0000              add [bx+si],al
00002367  0000              add [bx+si],al
00002369  0000              add [bx+si],al
0000236B  0000              add [bx+si],al
0000236D  0000              add [bx+si],al
0000236F  0000              add [bx+si],al
00002371  0000              add [bx+si],al
00002373  0000              add [bx+si],al
00002375  0000              add [bx+si],al
00002377  0000              add [bx+si],al
00002379  0000              add [bx+si],al
0000237B  0000              add [bx+si],al
0000237D  0000              add [bx+si],al
0000237F  0000              add [bx+si],al
00002381  0000              add [bx+si],al
00002383  0000              add [bx+si],al
00002385  0000              add [bx+si],al
00002387  0000              add [bx+si],al
00002389  0000              add [bx+si],al
0000238B  0000              add [bx+si],al
0000238D  0000              add [bx+si],al
0000238F  0000              add [bx+si],al
00002391  0000              add [bx+si],al
00002393  0000              add [bx+si],al
00002395  0000              add [bx+si],al
00002397  0000              add [bx+si],al
00002399  0000              add [bx+si],al
0000239B  0000              add [bx+si],al
0000239D  0000              add [bx+si],al
0000239F  0000              add [bx+si],al
000023A1  0000              add [bx+si],al
000023A3  0000              add [bx+si],al
000023A5  0000              add [bx+si],al
000023A7  0000              add [bx+si],al
000023A9  0000              add [bx+si],al
000023AB  0000              add [bx+si],al
000023AD  0000              add [bx+si],al
000023AF  0000              add [bx+si],al
000023B1  0000              add [bx+si],al
000023B3  0000              add [bx+si],al
000023B5  0000              add [bx+si],al
000023B7  0000              add [bx+si],al
000023B9  0000              add [bx+si],al
000023BB  0000              add [bx+si],al
000023BD  0000              add [bx+si],al
000023BF  0000              add [bx+si],al
000023C1  0000              add [bx+si],al
000023C3  0000              add [bx+si],al
000023C5  0000              add [bx+si],al
000023C7  0000              add [bx+si],al
000023C9  0000              add [bx+si],al
000023CB  0000              add [bx+si],al
000023CD  0000              add [bx+si],al
000023CF  0000              add [bx+si],al
000023D1  0000              add [bx+si],al
000023D3  0000              add [bx+si],al
000023D5  0000              add [bx+si],al
000023D7  0000              add [bx+si],al
000023D9  0000              add [bx+si],al
000023DB  0000              add [bx+si],al
000023DD  0000              add [bx+si],al
000023DF  0000              add [bx+si],al
000023E1  0000              add [bx+si],al
000023E3  0000              add [bx+si],al
000023E5  0000              add [bx+si],al
000023E7  0000              add [bx+si],al
000023E9  0000              add [bx+si],al
000023EB  0000              add [bx+si],al
000023ED  0000              add [bx+si],al
000023EF  0000              add [bx+si],al
000023F1  0000              add [bx+si],al
000023F3  0000              add [bx+si],al
000023F5  0000              add [bx+si],al
000023F7  0000              add [bx+si],al
000023F9  0000              add [bx+si],al
000023FB  0000              add [bx+si],al
000023FD  0000              add [bx+si],al
000023FF  0000              add [bx+si],al
00002401  0000              add [bx+si],al
00002403  0000              add [bx+si],al
00002405  0000              add [bx+si],al
00002407  0000              add [bx+si],al
00002409  0000              add [bx+si],al
0000240B  0000              add [bx+si],al
0000240D  0000              add [bx+si],al
0000240F  0000              add [bx+si],al
00002411  0000              add [bx+si],al
00002413  0000              add [bx+si],al
00002415  0000              add [bx+si],al
00002417  0000              add [bx+si],al
00002419  0000              add [bx+si],al
0000241B  0000              add [bx+si],al
0000241D  0000              add [bx+si],al
0000241F  0000              add [bx+si],al
00002421  0000              add [bx+si],al
00002423  0000              add [bx+si],al
00002425  0000              add [bx+si],al
00002427  0000              add [bx+si],al
00002429  0000              add [bx+si],al
0000242B  0000              add [bx+si],al
0000242D  0000              add [bx+si],al
0000242F  0000              add [bx+si],al
00002431  0000              add [bx+si],al
00002433  0000              add [bx+si],al
00002435  0000              add [bx+si],al
00002437  0000              add [bx+si],al
00002439  0000              add [bx+si],al
0000243B  0000              add [bx+si],al
0000243D  0000              add [bx+si],al
0000243F  0000              add [bx+si],al
00002441  0000              add [bx+si],al
00002443  0000              add [bx+si],al
00002445  0000              add [bx+si],al
00002447  0000              add [bx+si],al
00002449  0000              add [bx+si],al
0000244B  0000              add [bx+si],al
0000244D  0000              add [bx+si],al
0000244F  0000              add [bx+si],al
00002451  0000              add [bx+si],al
00002453  0000              add [bx+si],al
00002455  0000              add [bx+si],al
00002457  0000              add [bx+si],al
00002459  0000              add [bx+si],al
0000245B  0000              add [bx+si],al
0000245D  0000              add [bx+si],al
0000245F  0000              add [bx+si],al
00002461  0000              add [bx+si],al
00002463  0000              add [bx+si],al
00002465  0000              add [bx+si],al
00002467  0000              add [bx+si],al
00002469  0000              add [bx+si],al
0000246B  0000              add [bx+si],al
0000246D  0000              add [bx+si],al
0000246F  0000              add [bx+si],al
00002471  0000              add [bx+si],al
00002473  0000              add [bx+si],al
00002475  0000              add [bx+si],al
00002477  0000              add [bx+si],al
00002479  0000              add [bx+si],al
0000247B  0000              add [bx+si],al
0000247D  0000              add [bx+si],al
0000247F  0000              add [bx+si],al
00002481  0000              add [bx+si],al
00002483  0000              add [bx+si],al
00002485  0000              add [bx+si],al
00002487  0000              add [bx+si],al
00002489  0000              add [bx+si],al
0000248B  0000              add [bx+si],al
0000248D  0000              add [bx+si],al
0000248F  0000              add [bx+si],al
00002491  0000              add [bx+si],al
00002493  0000              add [bx+si],al
00002495  0000              add [bx+si],al
00002497  0000              add [bx+si],al
00002499  0000              add [bx+si],al
0000249B  0000              add [bx+si],al
0000249D  0000              add [bx+si],al
0000249F  0000              add [bx+si],al
000024A1  0000              add [bx+si],al
000024A3  0000              add [bx+si],al
000024A5  0000              add [bx+si],al
000024A7  0000              add [bx+si],al
000024A9  0000              add [bx+si],al
000024AB  0000              add [bx+si],al
000024AD  0000              add [bx+si],al
000024AF  0000              add [bx+si],al
000024B1  0000              add [bx+si],al
000024B3  0000              add [bx+si],al
000024B5  0000              add [bx+si],al
000024B7  0000              add [bx+si],al
000024B9  0000              add [bx+si],al
000024BB  0000              add [bx+si],al
000024BD  0000              add [bx+si],al
000024BF  0000              add [bx+si],al
000024C1  0000              add [bx+si],al
000024C3  0000              add [bx+si],al
000024C5  0000              add [bx+si],al
000024C7  0000              add [bx+si],al
000024C9  0000              add [bx+si],al
000024CB  0000              add [bx+si],al
000024CD  0000              add [bx+si],al
000024CF  0000              add [bx+si],al
000024D1  0000              add [bx+si],al
000024D3  0000              add [bx+si],al
000024D5  0000              add [bx+si],al
000024D7  0000              add [bx+si],al
000024D9  0000              add [bx+si],al
000024DB  0000              add [bx+si],al
000024DD  0000              add [bx+si],al
000024DF  0000              add [bx+si],al
000024E1  0000              add [bx+si],al
000024E3  0000              add [bx+si],al
000024E5  0000              add [bx+si],al
000024E7  0000              add [bx+si],al
000024E9  0000              add [bx+si],al
000024EB  0000              add [bx+si],al
000024ED  0000              add [bx+si],al
000024EF  0000              add [bx+si],al
000024F1  0000              add [bx+si],al
000024F3  0000              add [bx+si],al
000024F5  0000              add [bx+si],al
000024F7  0000              add [bx+si],al
000024F9  0000              add [bx+si],al
000024FB  0000              add [bx+si],al
000024FD  0000              add [bx+si],al
000024FF  0000              add [bx+si],al
00002501  0000              add [bx+si],al
00002503  0000              add [bx+si],al
00002505  0000              add [bx+si],al
00002507  0000              add [bx+si],al
00002509  0000              add [bx+si],al
0000250B  0000              add [bx+si],al
0000250D  0000              add [bx+si],al
0000250F  0000              add [bx+si],al
00002511  0000              add [bx+si],al
00002513  0000              add [bx+si],al
00002515  0000              add [bx+si],al
00002517  0000              add [bx+si],al
00002519  0000              add [bx+si],al
0000251B  0000              add [bx+si],al
0000251D  0000              add [bx+si],al
0000251F  0000              add [bx+si],al
00002521  0000              add [bx+si],al
00002523  0000              add [bx+si],al
00002525  0000              add [bx+si],al
00002527  0000              add [bx+si],al
00002529  0000              add [bx+si],al
0000252B  0000              add [bx+si],al
0000252D  0000              add [bx+si],al
0000252F  0000              add [bx+si],al
00002531  0000              add [bx+si],al
00002533  0000              add [bx+si],al
00002535  0000              add [bx+si],al
00002537  0000              add [bx+si],al
00002539  0000              add [bx+si],al
0000253B  0000              add [bx+si],al
0000253D  0000              add [bx+si],al
0000253F  0000              add [bx+si],al
00002541  0000              add [bx+si],al
00002543  0000              add [bx+si],al
00002545  0000              add [bx+si],al
00002547  0000              add [bx+si],al
00002549  0000              add [bx+si],al
0000254B  0000              add [bx+si],al
0000254D  0000              add [bx+si],al
0000254F  0000              add [bx+si],al
00002551  0000              add [bx+si],al
00002553  0000              add [bx+si],al
00002555  0000              add [bx+si],al
00002557  0000              add [bx+si],al
00002559  0000              add [bx+si],al
0000255B  0000              add [bx+si],al
0000255D  0000              add [bx+si],al
0000255F  0000              add [bx+si],al
00002561  0000              add [bx+si],al
00002563  0000              add [bx+si],al
00002565  0000              add [bx+si],al
00002567  0000              add [bx+si],al
00002569  0000              add [bx+si],al
0000256B  0000              add [bx+si],al
0000256D  0000              add [bx+si],al
0000256F  0000              add [bx+si],al
00002571  0000              add [bx+si],al
00002573  0000              add [bx+si],al
00002575  0000              add [bx+si],al
00002577  0000              add [bx+si],al
00002579  0000              add [bx+si],al
0000257B  0000              add [bx+si],al
0000257D  0000              add [bx+si],al
0000257F  0000              add [bx+si],al
00002581  0000              add [bx+si],al
00002583  0000              add [bx+si],al
00002585  0000              add [bx+si],al
00002587  0000              add [bx+si],al
00002589  0000              add [bx+si],al
0000258B  0000              add [bx+si],al
0000258D  0000              add [bx+si],al
0000258F  0000              add [bx+si],al
00002591  0000              add [bx+si],al
00002593  0000              add [bx+si],al
00002595  0000              add [bx+si],al
00002597  0000              add [bx+si],al
00002599  0000              add [bx+si],al
0000259B  0000              add [bx+si],al
0000259D  0000              add [bx+si],al
0000259F  0000              add [bx+si],al
000025A1  0000              add [bx+si],al
000025A3  0000              add [bx+si],al
000025A5  0000              add [bx+si],al
000025A7  0000              add [bx+si],al
000025A9  0000              add [bx+si],al
000025AB  0000              add [bx+si],al
000025AD  0000              add [bx+si],al
000025AF  0000              add [bx+si],al
000025B1  0000              add [bx+si],al
000025B3  0000              add [bx+si],al
000025B5  0000              add [bx+si],al
000025B7  0000              add [bx+si],al
000025B9  0000              add [bx+si],al
000025BB  0000              add [bx+si],al
000025BD  0000              add [bx+si],al
000025BF  0000              add [bx+si],al
000025C1  0000              add [bx+si],al
000025C3  0000              add [bx+si],al
000025C5  0000              add [bx+si],al
000025C7  0000              add [bx+si],al
000025C9  0000              add [bx+si],al
000025CB  0000              add [bx+si],al
000025CD  0000              add [bx+si],al
000025CF  0000              add [bx+si],al
000025D1  0000              add [bx+si],al
000025D3  0000              add [bx+si],al
000025D5  0000              add [bx+si],al
000025D7  0000              add [bx+si],al
000025D9  0000              add [bx+si],al
000025DB  0000              add [bx+si],al
000025DD  0000              add [bx+si],al
000025DF  0000              add [bx+si],al
000025E1  0000              add [bx+si],al
000025E3  0000              add [bx+si],al
000025E5  0000              add [bx+si],al
000025E7  0000              add [bx+si],al
000025E9  0000              add [bx+si],al
000025EB  0000              add [bx+si],al
000025ED  0000              add [bx+si],al
000025EF  0000              add [bx+si],al
000025F1  0000              add [bx+si],al
000025F3  0000              add [bx+si],al
000025F5  0000              add [bx+si],al
000025F7  0000              add [bx+si],al
000025F9  0000              add [bx+si],al
000025FB  0000              add [bx+si],al
000025FD  0000              add [bx+si],al
000025FF  0000              add [bx+si],al
00002601  0000              add [bx+si],al
00002603  0000              add [bx+si],al
00002605  0000              add [bx+si],al
00002607  0000              add [bx+si],al
00002609  0000              add [bx+si],al
0000260B  0000              add [bx+si],al
0000260D  0000              add [bx+si],al
0000260F  0000              add [bx+si],al
00002611  0000              add [bx+si],al
00002613  0000              add [bx+si],al
00002615  0000              add [bx+si],al
00002617  0000              add [bx+si],al
00002619  0000              add [bx+si],al
0000261B  0000              add [bx+si],al
0000261D  0000              add [bx+si],al
0000261F  0000              add [bx+si],al
00002621  0000              add [bx+si],al
00002623  0000              add [bx+si],al
00002625  0000              add [bx+si],al
00002627  0000              add [bx+si],al
00002629  0000              add [bx+si],al
0000262B  0000              add [bx+si],al
0000262D  0000              add [bx+si],al
0000262F  0000              add [bx+si],al
00002631  0000              add [bx+si],al
00002633  0000              add [bx+si],al
00002635  0000              add [bx+si],al
00002637  0000              add [bx+si],al
00002639  0000              add [bx+si],al
0000263B  0000              add [bx+si],al
0000263D  0000              add [bx+si],al
0000263F  0000              add [bx+si],al
00002641  0000              add [bx+si],al
00002643  0000              add [bx+si],al
00002645  0000              add [bx+si],al
00002647  0000              add [bx+si],al
00002649  0000              add [bx+si],al
0000264B  0000              add [bx+si],al
0000264D  0000              add [bx+si],al
0000264F  0000              add [bx+si],al
00002651  0000              add [bx+si],al
00002653  0000              add [bx+si],al
00002655  0000              add [bx+si],al
00002657  0000              add [bx+si],al
00002659  0000              add [bx+si],al
0000265B  0000              add [bx+si],al
0000265D  0000              add [bx+si],al
0000265F  0000              add [bx+si],al
00002661  0000              add [bx+si],al
00002663  0000              add [bx+si],al
00002665  0000              add [bx+si],al
00002667  0000              add [bx+si],al
00002669  0000              add [bx+si],al
0000266B  0000              add [bx+si],al
0000266D  0000              add [bx+si],al
0000266F  0000              add [bx+si],al
00002671  0000              add [bx+si],al
00002673  0000              add [bx+si],al
00002675  0000              add [bx+si],al
00002677  0000              add [bx+si],al
00002679  0000              add [bx+si],al
0000267B  0000              add [bx+si],al
0000267D  0000              add [bx+si],al
0000267F  0000              add [bx+si],al
00002681  0000              add [bx+si],al
00002683  0000              add [bx+si],al
00002685  0000              add [bx+si],al
00002687  0000              add [bx+si],al
00002689  0000              add [bx+si],al
0000268B  0000              add [bx+si],al
0000268D  0000              add [bx+si],al
0000268F  0000              add [bx+si],al
00002691  0000              add [bx+si],al
00002693  0000              add [bx+si],al
00002695  0000              add [bx+si],al
00002697  0000              add [bx+si],al
00002699  0000              add [bx+si],al
0000269B  0000              add [bx+si],al
0000269D  0000              add [bx+si],al
0000269F  0000              add [bx+si],al
000026A1  0000              add [bx+si],al
000026A3  0000              add [bx+si],al
000026A5  0000              add [bx+si],al
000026A7  0000              add [bx+si],al
000026A9  0000              add [bx+si],al
000026AB  0000              add [bx+si],al
000026AD  0000              add [bx+si],al
000026AF  0000              add [bx+si],al
000026B1  0000              add [bx+si],al
000026B3  0000              add [bx+si],al
000026B5  0000              add [bx+si],al
000026B7  0000              add [bx+si],al
000026B9  0000              add [bx+si],al
000026BB  0000              add [bx+si],al
000026BD  0000              add [bx+si],al
000026BF  0000              add [bx+si],al
000026C1  0000              add [bx+si],al
000026C3  0000              add [bx+si],al
000026C5  0000              add [bx+si],al
000026C7  0000              add [bx+si],al
000026C9  0000              add [bx+si],al
000026CB  0000              add [bx+si],al
000026CD  0000              add [bx+si],al
000026CF  0000              add [bx+si],al
000026D1  0000              add [bx+si],al
000026D3  0000              add [bx+si],al
000026D5  0000              add [bx+si],al
000026D7  0000              add [bx+si],al
000026D9  0000              add [bx+si],al
000026DB  0000              add [bx+si],al
000026DD  0000              add [bx+si],al
000026DF  0000              add [bx+si],al
000026E1  0000              add [bx+si],al
000026E3  0000              add [bx+si],al
000026E5  0000              add [bx+si],al
000026E7  0000              add [bx+si],al
000026E9  0000              add [bx+si],al
000026EB  0000              add [bx+si],al
000026ED  0000              add [bx+si],al
000026EF  0000              add [bx+si],al
000026F1  0000              add [bx+si],al
000026F3  0000              add [bx+si],al
000026F5  0000              add [bx+si],al
000026F7  0000              add [bx+si],al
000026F9  0000              add [bx+si],al
000026FB  0000              add [bx+si],al
000026FD  0000              add [bx+si],al
000026FF  0000              add [bx+si],al
00002701  0000              add [bx+si],al
00002703  0000              add [bx+si],al
00002705  0000              add [bx+si],al
00002707  0000              add [bx+si],al
00002709  0000              add [bx+si],al
0000270B  0000              add [bx+si],al
0000270D  0000              add [bx+si],al
0000270F  0000              add [bx+si],al
00002711  0000              add [bx+si],al
00002713  0000              add [bx+si],al
00002715  0000              add [bx+si],al
00002717  0000              add [bx+si],al
00002719  0000              add [bx+si],al
0000271B  0000              add [bx+si],al
0000271D  0000              add [bx+si],al
0000271F  0000              add [bx+si],al
00002721  0000              add [bx+si],al
00002723  0000              add [bx+si],al
00002725  0000              add [bx+si],al
00002727  0000              add [bx+si],al
00002729  0000              add [bx+si],al
0000272B  0000              add [bx+si],al
0000272D  0000              add [bx+si],al
0000272F  0000              add [bx+si],al
00002731  0000              add [bx+si],al
00002733  0000              add [bx+si],al
00002735  0000              add [bx+si],al
00002737  0000              add [bx+si],al
00002739  0000              add [bx+si],al
0000273B  0000              add [bx+si],al
0000273D  0000              add [bx+si],al
0000273F  00                db 0x00
