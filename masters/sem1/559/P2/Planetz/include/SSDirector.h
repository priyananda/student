// CS559 Project 2 : Quantum Coaster
// author: priyananda( shenoy@cs.wisc.edu )
// date: oct 2007
// random trivia:
#pragma once

#include "WindowEventHandler.h"
#include "SSObject.h"

// Manages the scene for the solar system
class SSDirector : public WindowEventHandler
{
public:
	SSDirector():bupdate(true),trails(false){}
	//overridden methods
	void handleInit(Window * window);
	void handleKey( int what, KeyStateEnum keyState );
	void handleMouse( MouseKeyEnum ,int,int );
	void handlePaint( Window * p);
	void handleIdle(Window * p);
private:
	void writeText();

	SSObject theSun;
	bool bupdate, trails;
	Window * window;
};