// CS559 Project 2 : Quantum Coaster
// author: priyananda( shenoy@cs.wisc.edu )
// date: 19 oct 2007
// random trivia: The story about Archimedes running around naked shouting "Eureka" is probably false.

#include "Window.h"
#include "SSDirector.h"

int __stdcall WinMain(HINSTANCE h,HINSTANCE p, LPSTR cmd,int n)
{
	Window * window = Window::create(800,600,3,false);
	window->setEventHandler(new SSDirector());
	window->show();
}