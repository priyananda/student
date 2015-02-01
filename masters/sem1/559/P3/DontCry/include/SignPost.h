// CS559 Project 3 : Dont Cry
// author: priyananda( shenoy@cs.wisc.edu )
// date: 6 dec 2007
// random trivia:
#pragma once

#include "TextureManager.h"
#include "Cube.h"
#include "Polygon.h"
#include "PropObject.h"

// represents a signpost
class SignPost : public PropObject
{
public:
	SignPost(float x,float y,float z,TextureType tex,float angle = 0);
	virtual void draw();
	virtual void drawForPicking(){draw();}
	virtual void serialize(char *);
private:
	Cube leg;
	Polygone face;
	float s1,t1,s2,t2;
	float angle;
};
