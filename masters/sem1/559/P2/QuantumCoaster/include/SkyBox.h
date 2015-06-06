// CS559 Project 2 : Quantum Coaster
// author: priyananda( shenoy@cs.wisc.edu )
// date: 21 oct 2007
// random trivia:
#pragma once

#include "SolidObject.h"

//Represents a box around the whole world
class SkyBox : public SolidObject
{
public:
	SkyBox(){ outsideVisible = false; }
	void setDimension(float x,float y,float z)
	{
		location.x = x / 2;
		location.y = y;
		location.z = z / 2;
	}
	void draw();
}; 