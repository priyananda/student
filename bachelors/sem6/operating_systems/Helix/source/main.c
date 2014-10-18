/* The starting point of the kernel */

#include <io/video.h>
#include <io/keyboard.h>
#include <io/pic.h>
#include <io/floppy.h>
#include <io/ports.h>

int printf(const char * str,...);
int do_main();
void halt();
void dispColorMessage(u8 * message);

void reboot(void){
	while(inb(0x64) & 0x02); /* try to reboot the computer */
	outb(0x64, 0xfe);
}

int main(){
	kb_set_leds(7);
	vd_setAttributes(FG_WHITE|BG_BLACK);
	vd_initializeVideoBuffer();
	dispColorMessage("\nVideo Driver Initialized");
	dispColorMessage("\nProgramming Interrupt Controller");
	InitPIC(0x20,0x28);
	dispColorMessage("\nInitailizing Interrupt Vector");
	populateIVT();
    if(getFreePort(0x3f8)==NOFREEPORT){
        printf("All com ports Exhausted");
    }
    portDetect();
	dispColorMessage("\nKernel Initialized");
	dispColorMessage("\nLoading File System");
	dispColorMessage("\nShell Loaded");
	kb_set_leds(0);
	vd_puts("\nPress any key...");
	getch();
	do_main();
	halt();
}

void halt(){
	int loop;
	vd_clearScreen();
	vd_setAttributes(4|128);
	vd_setXY(11,0);
	vd_puts(
	  "********************************************************************************"
	  "*                              System Shutdown                                 *"
	  "*                         You can safely turn off power                        *"
	  "********************************************************************************"
	);
	vd_setCursor(26,0);
	kb_set_leds(7);
	while(1);
}

void dispColorMessage(u8 * message){
	u8 mess[81]={' '};
	u32 i=0;
	mess[80] = 0;
	while(i<70){
		mess[i]='.';
		i++;
	}
	i=0;
	while(i<70 && message[i]){
		mess[i]=message[i];
		i++;
	}
	mess[70]=0;
	vd_puts(mess);
	for(i = 71;i < 79;i++)mess[i] = ' ';
	mess[70]='[';
	mess[79]=']';
	mess[74]='O';
	mess[75]='K';
	vd_setAttributes(BG_BLACK|FG_YELLOW);
	vd_puts(mess + 70);
	vd_setAttributes(BG_BLACK|FG_WHITE);
}
