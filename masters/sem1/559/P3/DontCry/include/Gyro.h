// CS559 Project 3 : Dont Cry
// author: priyananda( shenoy@cs.wisc.edu )
// date: 10 dec 2007
// random trivia:
#pragma once

#include "TextureManager.h"
#include "PropObject.h"

// represents a gyroscope
class Gyro : public PropObject
{
public:
	Gyro(float x,float y,float z):xangle(0),yangle(0),zangle(0){
		location.x = x;
		location.y = y;
		location.z = z;
		radius = 5;
		construct();
	}
	virtual void draw();
	virtual void drawForPicking(){draw();}
	virtual void serialize(char *);
private:
	float xangle;
	float yangle;
	float zangle;
	float radius;
	
	void construct();
	Point xring[40];
	Point yring[40];
	Point zring[40];
};
