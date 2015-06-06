// CS559 Project 3 : Dont Cry
// author: priyananda( shenoy@cs.wisc.edu )
// date: 1 dec 2007
// random trivia:

#include "Plane.h"
#include "Camera.h"
#include "Frustum.h"
#include "Window.h"

#define _USE_MATH_DEFINES
#include <cmath>

void Frustum::init(Window * p, Camera * c)
{
	ViewPort vp = p->getViewPort(ViewPortMain);
	vp.getFrustum(nearp,farp,angle);
	this->camera = c;

	float tang = float(tan(M_PI * angle / 360.f));
	float ratio = float(p->width) / p->height;
	nh = nearp * tang;
	nw = nh * ratio; 
	fh = farp  * tang;
	fw = fh * ratio;
}

void Frustum::prepare()
{
	//the camera coordinate system
	Vector3 zaxis = camera->parent->location - camera->parent->front;
	zaxis.normalize();
	Vector3 xaxis = camera->parent->up.cross(zaxis);
	xaxis.normalize();
	Vector3 yaxis = zaxis.cross(xaxis);
	yaxis.normalize();

	//centers
	Point nc = camera->parent->location - zaxis * nearp;
	Point fc = camera->parent->location - zaxis * farp;

	nearplane.init(nc,zaxis);
	farplane.init(fc,zaxis * -1);

	Vector3 aux,normal;

	(aux = (nc + yaxis * nh) - camera->parent->location).normalize();
	normal = aux.cross(xaxis);
	top.init(nc + yaxis * nh,normal);

	(aux = (nc - yaxis * nh) - camera->parent->location).normalize();
	normal = xaxis.cross(aux);
	bottom.init(nc - yaxis * nh,normal);
	
	(aux = (nc - xaxis * nw) - camera->parent->location).normalize();
	normal = aux.cross(yaxis);
	left.init(nc - xaxis * nw,normal);

	(aux = (nc + xaxis * nw) - camera->parent->location).normalize();
	normal = yaxis.cross(aux);
	right.init(nc + xaxis * nw,normal);
}
bool Frustum::cull(const Point &a, const Point &b, const Point &c) const
{
	return inside(a) || inside(b) || inside(c);
}
bool Frustum::cull(const Point &a, const Point &b, const Point &c, const Point &d) const
{
	return inside(a) || inside(b) || inside(c) || inside(d);
}
bool Frustum::inside(const Point & p) const
{
	return 
		top.isInside(p) &&
		bottom.isInside(p) &&
		left.isInside(p) &&
		right.isInside(p) &&
		nearplane.isInside(p) &&
		farplane.isInside(p);
}