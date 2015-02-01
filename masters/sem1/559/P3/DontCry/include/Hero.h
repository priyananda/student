// CS559 Project 3 : Dont Cry
// author: priyananda( shenoy@cs.wisc.edu )
// date: 24 nov 2007
// random trivia:
#pragma once

#include "OrientableObject.h"

// Represents the freely moving entity.
// The "Hero mode" camera attaches to this.
// He is not "God", he cant fly :(
class Hero : public OrientableObject
{
public:
	Hero(){
		set(
			0,0,0, // at origin
			1,0,0, // looking in +x direction
			0,1,0  // up is +y direction
		);
	}
	void moveForward(float d);
	void strafe(float d);
	void update();
private:
	void turnH(float);
	void turnV(float);
	void turn(float x,float y, float z,float angle);
}; 
