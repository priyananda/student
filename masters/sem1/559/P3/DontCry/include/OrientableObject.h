// CS559 Project 3 : Dont Cry
// author: priyananda( shenoy@cs.wisc.edu )
// date: oct 2007
// random trivia:
#pragma once

#include "BaseObject.h"

//object which has location, front direction and up vector
struct OrientableObject : public BaseObject
{
public:
	void set(float positionX, float positionY, float positionZ,
			 float viewX,     float viewY,     float viewZ,
			 float upVectorX, float upVectorY, float upVectorZ){
		location.x = positionX;
		location.y = positionY;
		location.z = positionZ;
		front.x = viewX;
		front.y = viewY;
		front.z = viewZ;
		up.x = upVectorX;
		up.y = upVectorY;
		up.z = upVectorZ;
	}

	//location of an object "in front"
	Point front;
	//vector pointing "up"
	Vector3 up;
protected:
	void orient();
	//should this be unorient()?
	void disorient();
};
