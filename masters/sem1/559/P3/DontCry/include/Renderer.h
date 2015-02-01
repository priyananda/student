// CS559 Project 3 : Dont Cry
// author: priyananda( shenoy@cs.wisc.edu )
// date: 21 oct 2007
// random trivia:
#pragma once

#include "SkyDome.h"

class Camera;
class Frustum;

//Renders the scene
class Renderer
{
public:
	void init();
	void draw(Frustum & f);
	void enableFog();
private:
	SkyDome skyDome;
}; 
