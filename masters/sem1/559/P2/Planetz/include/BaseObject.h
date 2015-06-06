// CS559 Project 2 : Quantum Coaster
// author: priyananda( shenoy@cs.wisc.edu )
// date: 18 oct 2007
// random trivia: Java was once called Oak.

#pragma once
#include "Vector.h"

//Root class for all objects in the system
//has a location, thats all
struct BaseObject
{
	Point location;
	
	BaseObject(){}
	BaseObject(const Point & p){this->location = p;}
	BaseObject(float x,float y,float z){
		location.x = x;
		location.y = y;
		location.z = z;
	}
};