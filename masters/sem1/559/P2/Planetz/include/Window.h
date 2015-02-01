// CS559 Project 2 : Quantum Coaster
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
	void setViewPorts(int number);
	void setCurrentViewPort(int idx);
	ViewPort * getViewPort(int idx);
	
	//shows a window. blocking call.
	void show();
	void setEventHandler(WindowEventHandler * p){eventHandler = p;}
	WindowEventHandler* getEventHandler(){return eventHandler;}
	void flush();

	int width,height;
private:
	static map<HWND,Window *> windows;
	static void registerClass();

	Window():viewports(0), eventHandler(0){}

	void createWindow(bool);
	void setPixelFormat();
	void initGL();
	void switchToFullScreen();
	void close();

	HWND hWnd;
	HDC  hDC;
	int bpp;
	ViewPort ** viewports;
	WindowEventHandler * eventHandler;
};