// CS559 Project 2 : Quantum Coaster
// author: priyananda( shenoy@cs.wisc.edu )
// date: 18 oct 2007
// random trivia: Playstation 3 has a peak computing power of ~2 TeraFLOPS, comparable to a supercomputer of the 80s.
#pragma once

class Window;

//what happened with the keyboard?
enum KeyStateEnum
{
	eKeyStatePressed,
	eKeyStateUp,
	eKeyStateDown
};

//what happened with the mouse
enum MouseKeyEnum
{
	eMouseLeftClick,
	eMouseRightClick,
	eMouseLeftDoubleClick,
	eMouseRightDoubleClick
};

// base class for anyone who wants to handle window events
class WindowEventHandler
{
public:
	//called when window is created. set all opengl options here
	virtual void handleInit(Window * p){window = p;}
	//called when key is pressed
	virtual void handleKey( int what, KeyStateEnum keyState ) = 0;
	//called when mouse is clicked
	virtual void handleMouse( MouseKeyEnum e, int x,int y ) = 0;
	//called when we want to paint
	virtual void handlePaint() = 0;
	//called when there is nothing else to be done
	virtual void handleIdle(){handlePaint();}
	//called when menu is clicked
	virtual void handleMenu(int command){}
	//drag/drop event
	virtual void handleDrop(MouseKeyEnum whichMouse, int dx, int dy){};
protected:
	Window * window;
};