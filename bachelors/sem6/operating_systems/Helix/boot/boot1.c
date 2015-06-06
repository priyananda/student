asm(".code16gcc\n");
#include "boot1.h"
unsigned char * convertString(int number,int base);
void boot_prompt();
extern void jmp_in_dry_well();
void outString(const char * str){
	__asm__ __volatile__(
		"mov %0  , %%ax\n"
		"mov %%ax, %%si\n"
		:
		: "m" (str)
	);
	put_string();
}

void puts(const char * str){
	outString(str);
	outString("\n\r");
}

void putch(char ch1){
	__asm__ __volatile__(
		"mov $0x0E, %%ah\n"
		"xor %%bx , %%bx\n"
		"movb %0  , %%al\n"
		"int $0x10\n"
		:
		:"r"(ch1)
	);
}	
void putchx(unsigned char chl){
    chl &= 0xf;
    chl += (chl <= (unsigned char)9)? '0' : 'A' - 10;
    putch(chl);
}

int getch(void){
	char chx;
	__asm__ __volatile__(
		"xor %%ah, %%ah\n"
		"int $0x16\n"
		"mov %%al, %0\n"
		: "=r"(chx)
		: 
	);
	return chx;
}

void show_graphics(){
    short low,high;
    boot_prompt();
    show_gfx();
    get_mem_size();
    __asm__ __volatile__(
        "mov %%ax, %0\n"
        "mov %%dx, %1\n"
        : "=r"(high), "=r"(low)
        : 
    );
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
    outString("Press any key to switch to 32 bit mode ... ");
    getch();
}

void error_msg(const char * message){
    __asm__ __volatile__(
        "xor %%ah , %%ah\n"
	    "mov $0x02, %%al\n"
    	"mov $0x20, %%bh\n"
        "int $0x10\n"
        :
    );
	puts(message);
	puts("Press any key to reboot");
	getch();
	reboot();
}

void boot_prompt(){
    char x = 0;
    __asm__ __volatile__(
        "xor %%ah , %%ah\n"
	    "mov $0x02, %%al\n"
    	"mov $0x20, %%bh\n"
        "int $0x10\n"
        :
    );
    puts("-----------------------------------------------------------------------------");
    puts("                             HILOW Helix Loader                              ");
    puts("-----------------------------------------------------------------------------");
    puts("Press:");
    puts("      1 Boot into Helix ");
    puts("      2 Boot into Other Operating system");
    x = getch();
    if (x == (char) '1')return;
    __asm__ __volatile__(
		"mov $0x7C0, %%ax\n"
		"mov %%ax  , %%es\n"
		"mov $0x2  , %%ah\n"
		"mov $0x1  , %%al\n"
		"xor %%bx  , %%bx\n"
		"xor %%dh  , %%dh\n"
		"mov $0x80 , %%dl\n"
		"xor %%ch  , %%ch\n"
		"mov $0x1  , %%cl\n"
		"int $0x13\n"
		:
	);
    jmp_in_dry_well();
}
