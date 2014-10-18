#include <stdio.h>
#include <conio.h>
#include <dos.h>
#include <time.h>

void getKey(unsigned char * scan,unsigned char * key){
	union REGS regs;
	regs.h.ah = 0;
	int86(0x16,&regs,&regs);
	*scan = regs.h.ah;
	*key = regs.h.al;
}

void revVideo(char * s,int x,int y,int index){
	textbackground(LIGHTGRAY);
	textcolor(BLACK);
	gotoxy(x,y);
	cprintf("%d - %s",index,s);
	textbackground(BLACK);
	textcolor(LIGHTGRAY);
}

void normal(char * s,int x,int y,int index){
	gotoxy(x,y);
	cprintf("%d - %s",index,s);
}

void blink(char * s,int x,int y,int index){
	textbackground(BLUE);
	textcolor(RED + BLINK);
	gotoxy(x,y);
	cprintf("%d - %s",index,s);
	delay(500);
	textbackground(BLACK);
	textcolor(LIGHTGRAY);
	gotoxy(x,y);
	cprintf("%d - %s",index,s);
	delay(500);
}

void animate(char * str,int x,int y){
	clock_t t = clock();
	int len = strlen(str);
	static int index = 0;
	float ts,tl = t/1.86;
	while(!kbhit()){
		t =  clock();
		ts = t/1.86;
		while(tl - ts < .1 && !kbhit()){
			t = clock();
			tl = t/1.86;
		}
		gotoxy(x,y);
		textcolor(LIGHTGRAY);
		cprintf("%s",str);
		gotoxy(index + x,y);
		textcolor(RED);
		cprintf("%c",str[index]);
		index = (index + 1)%len;
	}
	textcolor(LIGHTGRAY);
}

int menu(char * desc[],int max,int x,int y,char * header){
int current = 0,i;
unsigned char key,scan;
	clrscr();
	gotoxy(x,y);
	printf("%s",header);
	for(i=0;i<max;i++)
		normal(desc[i],x,y + i + 1,i + 1);
	revVideo(desc[0],x,y + 1,1);
	gotoxy(x,y + max + 1);
	cprintf("Your choice - 1%c",8);
	animate(header,x,y);
	getKey(&scan,&key);
	while(key != 13){
		if(key == 0){
			normal(desc[current],x,y + current + 1,current + 1);
			if(scan == 72)
				current = current == 0 ? max - 1:current - 1;
			else if(scan == 80)
				current = current == max - 1 ? 0 : current + 1;
			revVideo(desc[current],x,y + current + 1,current + 1);
			gotoxy(x + 14,y + max + 1);
			cprintf("%d",current + 1);
		}
		animate(header,x,y);
		getKey(&scan,&key);
	}
	blink(desc[current],x,y + current + 1,current +1);
	gotoxy(1,y + max + 3);
	return current + 1;
}
/*
int main(){
	char * mnu[] = {"Hello",
					"Feeling good",
					"Nasty boy",
					"Fourth"
					};
	int i = menu(mnu,4,10,12,"*****Select one*****");
	printf("You selected %s",mnu[i - 1]);
	getch();
	return 0;
}
*/