// CS559 Project 2 : Quantum Coaster
// author: priyananda( shenoy@cs.wisc.edu )
// date: oct 2007
// random trivia:

#include "Window.h"
#include "Win32Helper.h"
#include <gl/gl.h>
#include "SSDirector.h"
#include <gl\glu.h>

void SSDirector::handleInit(Window * window)
{
	this->window = window;
	window->getViewPort(0)->switchTo2D();
	glShadeModel(GL_SMOOTH);
	glHint( GL_PERSPECTIVE_CORRECTION_HINT , GL_NICEST );
	glClearColor(0,0,0,1);
}

void SSDirector::handleKey( int what, KeyStateEnum keyState )
{
	if( what == VK_ESCAPE )
		PostQuitMessage(0);
	if( what == VK_SPACE && keyState == eKeyStateUp )
		bupdate = !bupdate;
	if( what == 'A' && keyState == eKeyStateUp )
		theSun.addChild();
	if( what == 'D' && keyState == eKeyStateUp )
		theSun.removeChild();
	if( what == 'T' && keyState == eKeyStateUp )
		trails = ! trails;
	if( what == VK_TAB && keyState == eKeyStateUp )
		theSun.selectNext();
	if( what == VK_UP && keyState == eKeyStateDown )
		theSun.moveKid(+5);
	if( what == VK_DOWN && keyState == eKeyStateDown )
		theSun.moveKid(-5);
}
void SSDirector::handlePaint( Window * p)
{
	if(!trails)
		glClear(GL_COLOR_BUFFER_BIT);
	writeText();
	theSun.draw();
	p->flush();
}
void SSDirector::handleMouse(MouseKeyEnum e, int x,int y)
{
}
void SSDirector::handleIdle(Window * p)
{
	theSun.location.x = float(p->width / 2);
	theSun.location.y = float(p->height / 2);
	if(bupdate){
		theSun.update();
		handlePaint(p);
	}
}
void SSDirector::writeText()
{
	Win32Helper::writeText("'A' to add planet",10,110);
	Win32Helper::writeText("'D' to delete planet",10,90);
	Win32Helper::writeText("SPACE to start/stop animation",10,70);
	Win32Helper::writeText("TAB to switch between planets",10,50);
	Win32Helper::writeText("UP/DOWN to move selected planet further/closer to the Sun",10,30);
	Win32Helper::writeText("'T' to see trails - nice shapes",10,10);
}