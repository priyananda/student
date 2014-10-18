#include "boot1.h"
unsigned char * convertString(int number,int base);
void boot_prompt();
extern void jmp_in_dry_well();
void outString(char * str){
	asm{ mov si,[str]};
	put_string();
}

void puts(char * str){
	outString(str);
	outString("\n\r");
}

void putch(char ch1){
	asm{
		mov ah,0eh
		xor bx,bx
		mov al,ch1
		int 10h
	};
}
void putchx(unsigned char chl){
    chl &= 0xf;
    chl += (chl <= (unsigned char)9)? '0' : 'A' - 10;
    putch(chl);
}

int getch(void){
	char chx;
	asm{
		xor ah,ah
		int 16h
		mov chx,al
	}
	return chx;
}



void show_graphics(){
    int low,high;
    boot_prompt();
    show_gfx();
    get_mem_size();
    asm{
        mov high,ax
        mov low,dx
    }
    puts     ("+---------------------------------------------------------------------+");
    puts     ("|              Entering 16 Bit Initialization Routine                 |");
    puts     ("+---------------------------------------------------------------------+");
    puts     ("    Probing Memory ................................................... ");
    outString("        Size of main memory is                   [ 0x");
    putchx((unsigned char )(high >> 12));
    putchx((unsigned char )(high >> 8));
    putchx((unsigned char )(high >> 4));
    putchx((unsigned char )high );
    putchx((unsigned char )(low >> 12));
    putchx((unsigned char )(low >> 8));
    putchx((unsigned char )(low >> 4));
    putchx((unsigned char )low );
    puts(" ]");
    puts     ("   Probing Processor .................................................. ");
    outString("       Processor String is                     ");
    get_cpu();
    puts(cpu_str);
    puts     ("Press any key to switch to 32 bit mode ... ");
    getch();
}

void error_msg(const char * message){
    asm{
        mov ah,0
	    mov al,02
    	mov bh,0x20
        int 10h
    }
	puts(message);
	puts("Press any key to reboot");
	getch();
	reboot();
}

void boot_prompt(){
    char x=0;
    asm{
        mov ah,0
	    mov al,02
    	mov bh,0x20
        int 10h
    }
    puts("-----------------------------------------------------------------------------");
    puts("                             HILOW Helix Loader                              ");
    puts("-----------------------------------------------------------------------------");
    puts("Press:");
    puts("      1 Boot into Helix ");
    puts("      2 Boot into Other Operating system");
    x = getch();
    if (x == (char) '1')return;
    asm{
		mov ax,0x7C0
		mov es,ax
		mov ah,2
		mov al,1
		xor bx,bx
		mov dh,0
		mov dl,0x80
		mov ch,0
		mov cl,1
		int 0x13
	}
    jmp_in_dry_well();
}
