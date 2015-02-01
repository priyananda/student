// CS559 Project 3 : Dont Cry
// author: priyananda( shenoy@cs.wisc.edu )
// date: 1 dec 2007
// random trivia:
// this code is mostly adapted from
// http://www.lighthouse3d.com/opengl/viewfrustum/index.php

#include "Plane.h"

void Plane::init(const Point &point, const Vector3 & normal)
{
	this->normal = normal;
	this->point = point;
	this->normal.normalize();
	this->intercept = - this->normal.dot(point);
}
bool Plane::isInside(const Point &p) const
{
	return normal.dot(p) + intercept >= 0;
}