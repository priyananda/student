asm(".code16\n");
#include "boot1.h"

int main(){
	show_graphics();
	puts("\n\rSetting up 32 bit Environment");
	copy_gdt();
	puts("Switching to 32 bit mode");
	switch_prot(); // Bye, Bye real mode ...
	/* Control never comes here */
	reboot();
	return 0;
}
