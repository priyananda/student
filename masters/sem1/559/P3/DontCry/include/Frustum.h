// CS559 Project 3 : Dont Cry
// author: priyananda( shenoy@cs.wisc.edu )
// date: 1 dec 2007
// random trivia:
// code mostly adapted from
// http://www.lighthouse3d.com/opengl/viewfrustum/index.php
#pragma once

#include "Plane.h"

class Window;
class Camera;

//chopped off pyramid defining the viewing volume
class Frustum
{
public:
	Frustum():camera(0){}
	void init(Window * w,Camera * c);
	void prepare();
	//triangle
	bool cull(const Point &,const Point &,const Point &) const;
	//quad
	bool cull(const Point &,const Point &,const Point &,const Point &) const;
//private:
	bool inside(const Point& p) const;

	Camera * camera;
	float nearp,farp,angle;
	Plane nearplane,farplane,top,bottom,left,right;
	float nh,nw,fh,fw;
};
