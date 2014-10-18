#include<iostream.h>
#include<math.h>
#include<stdio.h>
#include<dos.h>
#include<fstream.h>
#include<conio.h>
#include<string.h>
#include<graphics.h>
#include<stdlib.h>
#include<ctype.h>
#include<graphics.h>

#include"student.h"
#include"iobuf.h"
#include"inter.h"

//Main function
void main(){
  int gd=DETECT,gm;
  initgraph(&gd,&gm,"");
  int ch,x=getmaxx(),y=getmaxy();
  char mesg[100];
  interface face;
  setbkcolor(BLACK);
  int p=0,q=0,r=getmaxx(),s=getmaxy();
  setcolor(LIGHTBLUE);
  settextstyle(1,0,3);
  outtextxy(90,60,"+------------------------------------------------+");
  outtextxy(90,75,"| F I L E   S T R U C T U R E S   P R O J E C T  |");
  outtextxy(90,90,"+------------------------------------------------+");
 outtextxy(90,150,"                 (Student records)                ");
  settextstyle(1,0,2);
  rectangle(160,250,450,390);
  setfillstyle(SOLID_FILL,BLUE);
  bar(162,252,448,265);
  setcolor(YELLOW);
  outtextxy(180,254,"By");
  setcolor(CYAN);
  outtextxy(175,300,"Naveen B N         (1RV00IS017)");
  outtextxy(175,350,"Priyananda Shenoy P(1RV00IS021)");
  settextstyle(0,0,0);
  getch();
  int i;
  do{
	setcolor(0);
	cleardevice();
	setcolor(WHITE);
	rectangle(0,0,x,y);
	rectangle(2,3,x-2,y-2);
	settextstyle(4,0,2);
	settextstyle(0,0,0);
	setfillstyle(SOLID_FILL,BLUE);
	bar(x/2-120,120,x/2+100,300);
	setcolor(WHITE);
	rectangle(x/2-118,122,x/2+98,338);
	setfillstyle(SOLID_FILL,YELLOW);
	bar(x/2 - 98 , 112,x/2+78,132);
	rectangle(x/2 - 100 , 110,x/2 + 80 , 134);
	setcolor(BLUE);
	outtextxy(x/2 - 50 , 117 , "Choices");
	setcolor(YELLOW);
	outtextxy(x/2-72,160,"1. Add new record");
	outtextxy(x/2-72,180,"2. Delete a record");
	outtextxy(x/2-72,200,"3. Change a record");
	outtextxy(x/2-72,220,"4. Search for record");
	outtextxy(x/2-72,240,"5. Show all records");
	outtextxy(x/2-72,260,"6. EXIT");
	outtextxy(x/2-92,320,"Enter your choice : ");
	gotoxy(50,21);
	cin >> ch;
	switch(ch){
	  case 1: face.add(); // To add a new unique record
		  break;
	  case 2: face.del(); // To delete record(s) based on reg.no or name
		  break;
	  case 3: face.modify(); // Modify a record
		  break;
	  case 4: face.search();  // Search record(s) based on reg.no or name
		  break;
	  case 5: face.displayall();
		  break;
	  case 6: strcpy(mesg,"++++");
		  break;
	  default:strcpy(mesg,"Invalid Usage");
		  break;
	}
	settextstyle(0,0,2);
	if(!(ch>=1&&ch<=5)){
	  int len=strlen(mesg);
	  mesg[len]='\0';
	  setcolor(10);
	  outtextxy(x/2-25-15*len/2,y-100,mesg);
	  getch();
	}
	settextstyle(0,0,0);
  }while(ch!=6);
  face.update(); // To remove the temporarily deleted records permanently*/
  closegraph();
  restorecrtmode();
}// End of main