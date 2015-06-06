// CS559 Project 3 : Dont Cry
// author: priyananda( shenoy@cs.wisc.edu )
// date: 19 oct 2007
// random trivia: The story about Archimedes running around naked shouting "Eureka" is probably false.

#include "Window.h"
#include "Director.h"

#include "ExtensionManager.h"

int __stdcall WinMain(HINSTANCE h,HINSTANCE p, LPSTR cmd,int n)
{
	Window * window = Window::create(1024,768,3,true);
	ExtensionManager::init();
	window->setCaption("Dont Cry");
	window->setEventHandler(new Director());
	window->show();
}