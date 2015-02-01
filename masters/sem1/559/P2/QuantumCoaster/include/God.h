// CS559 Project 2 : Quantum Coaster
// author: priyananda( shenoy@cs.wisc.edu )
// date: 20 oct 2007
// random trivia:
#pragma once

#include "OrientableObject.h"

// Represents the freely moving entity.
// The "God mode" camera attaches to this.
class God : public OrientableObject
{
public:
	God(){
		set(
			0,0,0, // at origin
			1,0,0, // looking in +x direction
			0,1,0  // up is +y direction
		);
	}
	void moveForward(float d);
	void turnH(float d);
	void turnV(float d);
private:
	void turn(float x,float y, float z,float angle);
}; 
