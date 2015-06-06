// CS559 Project 2 : Quantum Coaster
// author: priyananda( shenoy@cs.wisc.edu )
// date: 18 oct 2007
// random trivia: Playstation 3 has a peak computing power of ~2 TeraFLOPS, comparable to a supercomputer of the 80s.
#pragma once

class Window;

enum KeyStateEnum
{
	eKeyStatePressed,
	eKeyStateUp,
	eKeyStateDown
};

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
	virtual void handleInit(Window * window){}
	//called when key is pressed
	virtual void handleKey( int what, KeyStateEnum keyState ) = 0;
	//called when mouse is clicked
	virtual void handleMouse( MouseKeyEnum , int,int ) = 0;
	//called when we want to paint
	virtual void handlePaint(Window *) = 0;
	//called when there is nothing else to be done
	virtual void handleIdle(Window * w){handlePaint(w);}
};