#include <io/keyboard.h>
#include <io/video.h>
#include <klib.h>

#define CLI() __asm__ __volatile__("cli")
#define STI() __asm__ __volatile__("sti")

int getch(){
	int status = 0;
	while(status == 0){
		CLI();
		status = kb_get_status();
		STI();
	}
	CLI();
	status = kb_get_key();
	STI();
	return status;
}

int getche(){
	int ret = getch();
	vd_putchar(ret);
	return ret;
}

int gets(char * s){
	char ch = getch();
	int pos;
	int i = 0;
	while(ch != '\n'){
		if(ch == '\b'){
			if(i){
				pos = vd_getXY();
				vd_setXY((u8)(pos >> 16),(u8)pos - 1);
				vd_putchar(' ');
				vd_setXY((u8)(pos >> 16),(u8)pos - 1);
				i--;
			}
		}else{
			s[i++] = ch;
			vd_putchar(ch);
		}
		ch = getch();
	}
	s[i] = 0;
	return i;
}
