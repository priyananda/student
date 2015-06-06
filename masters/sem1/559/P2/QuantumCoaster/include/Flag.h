// CS559 Project 2 : Quantum Coaster
// author: priyananda( shenoy@cs.wisc.edu )
// date: 5 nov 2007
// random trivia:
#pragma once

#include "TextureManager.h"
#include "PropObject.h"

// represents a flag
class Flag : public PropObject
{
public:
	Flag(float x,float y,float z){
		location.x = x;
		location.y = y;
		location.z = z;
	}
	virtual void draw();
	virtual void drawForPicking(){draw();}
	virtual void serialize(char *);
};
