// CS559 Project 3 : Dont Cry
// author: priyananda( shenoy@cs.wisc.edu )
// date: oct 2007
// random trivia:
#pragma once

#include "PropObject.h"
#include "Cube.h"

// a building
class Building : public PropObject
{
public:
	Building(float x,float y,float z,float l,float h,float w)
		:building(0,0,0,l,h,w){
		location.x = x;
		location.y = y;
		location.z = z;
		dx = l;dy = h; dz = w;
	}
	virtual void draw();
	virtual void drawForPicking(){draw();}
	virtual void serialize(char *);

	float dx,dy,dz;
	Cube building;
}; 
