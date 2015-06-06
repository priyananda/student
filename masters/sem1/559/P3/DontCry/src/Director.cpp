// CS559 Project 3 : Dont Cry
// author: priyananda( shenoy@cs.wisc.edu )
// date: oct 2007
// random trivia:

#include "resource.h"
#include "Window.h"
#include "Win32Helper.h"
#include <gl/gl.h>
#include "Director.h"
#include "World.h"
#include "PropObject.h"
#include "DayTimer.h"
#include "Frustum.h"
#include "Cave.h"

//initialize everything
void Director::handleInit(Window * window)
{
	WindowEventHandler::handleInit(window);
	window->setMenuVisible(false);

	World::neww();
	heroCam.parent = &World::hero;
	heroCam.offset = 15;
	heroFrustum.init(window,&heroCam);

	World::heightMap.loadFrom("hmap.tga");
	renderer.init();

	World::timer.init();
}

void Director::handleKey( int what, KeyStateEnum keyState )
{
	if( keyState == eKeyStateDown ){
		//common keys
		switch(what){
			case VK_ESCAPE:
				PostQuitMessage(0);
				break;
			case VK_UP: case 'W':
				World::hero.moveForward(5);break;
			case VK_DOWN: case 'S':
				World::hero.moveForward(-5);break;
			case VK_LEFT: case 'A':
				World::hero.strafe(-5.0f);break;
			case VK_RIGHT: case 'D':
				World::hero.strafe(+5.0f);break;
			case VK_RETURN:
				World::toggleCave();break;
			case VK_SPACE:
				World::startMatrixEffect();break;
		}
	}
}
void Director::handlePaint()
{
	window->updateFPS();
	window->setCurrentViewPort(ViewPortMain);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	if(World::matrixmode)
		World::cave.updateHero();
	else
		World::hero.update();
	heroCam.look();
	heroFrustum.prepare();
	renderer.draw(heroFrustum);

	writeText();
	window->flush();
}
void Director::handleIdle()
{
	handlePaint();
}

void Director::writeText()
{
	char buffer[255];
	float ht = float(this->window->height);
	ht -= 50;
	window->getViewPort(ViewPortMain).switchTo2D();

	Win32Helper::writeText("Press UP or W,DOWN or S to move forward/backward",10,ht); ht -= 20;
	Win32Helper::writeText("Press LEFT or A,RIGHT or D to strafe left/right",10,ht); ht -= 20;
	Win32Helper::writeText("Move mouse horizontally to turn",10,ht); ht -= 20;
	Win32Helper::writeText("Move mouse vertically to look up/down",10,ht); ht -= 20;

	short h=0,m=0;
	World::timer.getTime(h,m);
	sprintf_s(buffer,254,"time: %2d:%2d",h,m);
	Win32Helper::writeText(buffer,10,110);
	
	sprintf_s(buffer,254,"fps: %d",window->getFPS());
	Win32Helper::writeText(buffer,10,90);

	sprintf_s(buffer,254,"location: %3f %3f %3f",
		World::hero.location.x,World::hero.location.y,World::hero.location.z);
	Win32Helper::writeText(buffer,10,70);

	sprintf_s(buffer,254,"front: %3f %3f %3f",
		World::hero.front.x,World::hero.front.y,World::hero.front.z);
	Win32Helper::writeText(buffer,10,50);

	sprintf_s(buffer,254,"up: %3f %3f %3f",
		World::hero.up.x,World::hero.up.y,World::hero.up.z);
	Win32Helper::writeText(buffer,10,30);
	
	window->getViewPort(ViewPortMain).restoreFrom2D();
}
void Director::handleMouse(MouseKeyEnum e,int x,int y)
{
}

void Director::handleMenu(int command)
{
}
void Director::handleDrop(MouseKeyEnum which, int dx, int dy)
{
}