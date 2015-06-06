// CS559 Project 3 : Dont Cry
// author: priyananda( shenoy@cs.wisc.edu )
// date: oct 2007
// random trivia:
#pragma once

#include "PickableObject.h"
#include "Cube.h"

// the control points for the track
class ControlPoint : public Cube,public PickableObject
{
public:
	ControlPoint(const Point & loc, const Vector3 & upd ):Cube(loc.x,loc.y,loc.z,.25f,.25f,.25f){
		this->up.x = upd.x;
		this->up.z = upd.z;
		this->up.y = upd.y;
	}
	ControlPoint(float x=0, float y=0, float z=0, float upx = 0, float upy = 1, float upz = 0)
		:Cube(x,y,z,.25f,.25f,.25f)
	{
		this->up.x = upx;
		this->up.z = upz;
		this->up.y = upy;
	}
	void draw();
	void drawForPicking(){
		draw();
	}
}; 
