// CS559 Project 3 : Dont Cry
// author: priyananda( shenoy@cs.wisc.edu )
// date: 17 oct 2007
// random trivia: The recommended strategy for Quake III Arena: Kill anything that isn't you.
#pragma once

#include <windows.h>
#include "ViewPort.h"
#include "WindowEventHandler.h"

#include <map>
using std::map;

class Win32Helper;

//hardcoded - one normal full-window VP and 2 half-splits
enum ViewPortType
{
	ViewPortMain,
	ViewPortLeft,
	ViewPortRight
};

//Represents a Win32 window. Can have multiple viewports.
//lots of dirty win32 code. you have been warned.
class Window 
{
public:
	//factory for creating windows
	static Window * create(int w,int h,int bpp,bool fullscreen = true);
	//get window for a HWND
	static Window * getWindow(HWND h){ return windows[h]; }
	
	//viewports related functions
	void setCurrentViewPort(ViewPortType vp);
	ViewPort & getViewPort(ViewPortType vp);
	
	//shows a window. blocking call.
	void show();
	void setEventHandler(WindowEventHandler * p){eventHandler = p;}
	WindowEventHandler* getEventHandler(){return eventHandler;}
	void flush();

	void setCaption(const char * p);
	void setMenuVisible(bool val = true);

	void updateFPS();
	int  getFPS(){return fps;}

	int width,height;
	bool dragging;
	int dragStartX,dragStartY;
private:
	static map<HWND,Window *> windows;
	static void registerClass();

	Window():eventHandler(0),hWnd(0),hDC(0),hMenu(0),bpp(3),fps(0)
		,dragging(false),dragStartX(0),dragStartY(0){}

	void createWindow(bool);
	void setPixelFormat();
	void initGL();
	void switchToFullScreen();
	void setupViewPorts();
	void close();

	HWND hWnd;
	HDC  hDC;
	HMENU hMenu;
	int bpp;
	int fps;
	ViewPort mainViewPort;
	ViewPort leftViewPort;
	ViewPort rightViewPort;
	WindowEventHandler * eventHandler;
};