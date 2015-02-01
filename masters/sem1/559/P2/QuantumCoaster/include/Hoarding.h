// CS559 Project 2 : Quantum Coaster
// author: priyananda( shenoy@cs.wisc.edu )
// date: 5 nov 2007
// random trivia:
#pragma once

#include "TextureManager.h"
#include "Cube.h"
#include "Polygon.h"
#include "PropObject.h"

// represents an advertisement billboard
class Hoarding : public PropObject
{
public:
	Hoarding(float x,float y,float z,float l,float h,float w,TextureType t);
	virtual void draw();
	virtual void drawForPicking(){draw();}
	virtual void serialize(char *);
private:
	float dx,dy,dz;
	Cube leg1,leg2;
	Polygone face,back;
	TextureType texture;
};
