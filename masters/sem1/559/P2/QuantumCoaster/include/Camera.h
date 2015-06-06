// CS559 Project 2 : Quantum Coaster
// author: priyananda( shenoy@cs.wisc.edu )
// date: 20 oct 2007
// random trivia:
#pragma once

#include "OrientableObject.h"

// A camera is not a free entity. It needs an object whose
// position and orientation is used to "look"
class Camera
{
public:
	Camera():parent(0),offset(0){}
	Camera(OrientableObject * p):parent(p){}

	void setParent(OrientableObject * p){parent = p;}
	void look();

	float offset;
private:
	OrientableObject * parent;
};