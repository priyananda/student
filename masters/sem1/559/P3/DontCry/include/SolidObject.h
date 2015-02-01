// CS559 Project 3 : Dont Cry
// author: priyananda( shenoy@cs.wisc.edu )
// date: 21 oct 2007
// random trivia:
#pragma once

#include "OrientableObject.h"

//something which can be drawn
class SolidObject : public OrientableObject
{
public:
	SolidObject():outsideVisible(true){}

	virtual void draw() = 0;
protected:
	//this says whether the outside faces are visible or the inside faces.
	//for most objects it is true. Only skybox has this false
	bool outsideVisible;
}; 
