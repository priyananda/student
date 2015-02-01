// CS559 Project 2 : Quantum Coaster
// author: priyananda( shenoy@cs.wisc.edu )
// date: oct 2007
// random trivia:
#pragma once

#include "PropObject.h"

// a biological Tree
class Tree : public PropObject
{
public:
	Tree(float x,float y,float z){
		location.x = x;
		location.y = y;
		location.z = z;
	}
	virtual void draw();
	virtual void drawForPicking(){draw();}
	virtual void serialize(char *);
}; 
