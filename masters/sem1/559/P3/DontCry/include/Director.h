// CS559 Project 3 : Dont Cry
// author: priyananda( shenoy@cs.wisc.edu )
// date: 20 oct 2007
// random trivia:
#pragma once

#include "WindowEventHandler.h"
#include "Hero.h"
#include "Camera.h"
#include "Renderer.h"
#include "Frustum.h"

// Manages the scene for the solar system
class Director : public WindowEventHandler
{
public:
	Director():speed(0.1f){}
	//overridden methods
	void handleInit(Window * window);
	void handleKey( int what, KeyStateEnum keyState );
	void handleMouse( MouseKeyEnum c,int x,int y );
	void handlePaint();
	void handleIdle();
	void handleMenu(int command);
	void handleDrop(MouseKeyEnum e, int dx,int dy);

private:
	void writeText();

	Camera heroCam;
	Frustum heroFrustum;

	Renderer renderer;
	float speed;
};