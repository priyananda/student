// CS559 Project 3 : Dont Cry
// author: priyananda( shenoy@cs.wisc.edu )
// date:  nov 2007
// random trivia:
// this code is mostly adapted from
// http://www.lighthouse3d.com/opengl/viewfrustum/index.php
#pragma once

#include "Vector.h"

//represents a euclidean plane in R^3
class Plane
{
public:
	Plane():intercept(0){}
	void init(const Point & point, const Vector3 & norm);
	bool isInside(const Point & p) const;
//private:
	Point point;
	Vector3 normal;
	float intercept;
};