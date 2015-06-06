// CS559 Project 2 : Quantum Coaster
// author: priyananda( shenoy@cs.wisc.edu )
// date: 21 oct 2007
// random trivia:
#pragma once

#include "SkyBox.h"

class Camera;

//Renders the scene
class Renderer
{
public:
	void init();
	void draw(bool runMode, bool shadows);
	void drawForPicking(int x,int y);
private:
	SkyBox skyBox;
}; 
