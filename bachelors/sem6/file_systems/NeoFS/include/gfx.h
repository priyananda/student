#ifndef __GFX_H
#define __GFX_H

#include <stdio.h>
#include <conio.h>
#include <dos.h>
#include <graphics.h>
#include <stdlib.h>
#include <string.h>

enum Status{
	DISABLED , NORMAL , HIGH
};

typedef void (*ActionHandler) ();

class GraphicContext{
public:
	static int  maxX,maxY;
	static void init();
	static void showTitle(char * str);
	static void drawWindow();
	static void initMouse();
	static void hideMouse();
	static void getMouse(int *which , int *x , int *y);
	static void showSplash();
	static void close();
    static void showSidePanel();
    static void showMessage(char * str);
    static void clearMessage(char *);
};

class Button{
public:
	int x,y;
	int width , height;
	int state;
	char text[30];
	ActionHandler handler;
	Button(){ state = NORMAL ; handler = 0;}
	Button(char * _str){ strcpy(text,_str) ; state = NORMAL; handler = 0; }
	Button(char * _str , int _x,int _y,int _w , int _h){
		strcpy(text,_str) ; state = NORMAL;
		x = _x;y = _y; height = _h ; width = _w;
		handler = 0;
	}
	void draw();
	int  contains(int _x,int _y);
	void addActionHandler(ActionHandler x);
	void respond();
	void refresh(int _newstate);
};

class Container{
	char title[100];
	int x,y,bWidth,bHeight;
	Button * buttons;
	int numButtons;
	int titleColor;
public:
	Container(int _nButt, int _x, int _y,int _bw , int _bh);
	void setTitle(char * _str){ strcpy(title,_str) ;}
	void draw();
	void refresh();
	void doDisable(int _index);
	void doDisable();
	void doEnable(int _index);
	void doEnable();
	void checkForEvents(int ,int ,int);
	void setText(int _index , char * _str);
	void setText(char ** _str);
	void respond(int index);
};

class ProgressBar{
public:
	int  x,y;
	int  width , height;
	int  maxVal;
	int  currentVal;
	char text[20];
	int  color;
	int  changed;
	int  up;
public:
	ProgressBar(int _x,int _y,int _w , int _h , int _maxVal){
		x = _x;y = _y; height = _h ; width = _w;
		currentVal = 0;
		maxVal = _maxVal;
		color = BLUE;
		text[0] = 0;
		changed = 0;
		up = 1;
	}
	void setColor(int _color){color = _color; }
	void draw();
	void refresh();
	void refresh(int _step){ increment(_step);refresh();}
	void setValue(int _val){ if ( _val < maxVal ) currentVal = _val; }
    void setMax(int _val) { maxVal = _val ;}
	void increment(unsigned int step);
	void setText(char * _str){ strcpy(text,_str); }
	void undraw();
};
typedef enum _DIALOG_TYPES {
	OK_CANCEL_DIALOG,
	YES_NO_DIALOG,
	OK_DIALOG
}DIALOG_TYPES;

#define YES    1
#define NO     0
#define OK     1
#define CANCEL 0

//HardCoded Dialog Box !!!!!!!
class HCDialogBox{
public:
	int type;
	int x,y;
	char message[50],title[50];
	HCDialogBox( const char * _me , const char * _title ,int  _type ){
		strcpy(message , _me);
		strcpy(title,_title);
		type = _type;
	}
	int showDialog();
};

class TextBlock{
public:
	int x , y;
	int numRows;
	TextBlock(int _x ,int _y ){ x = _x ; y = _y ;numRows = 0 ;}
	char text[100][100];
	void draw();
	void setText(char *);
	void setText( int , char **);
	void appendText(char * );
};



#endif