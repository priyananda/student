// CS559 Project 3 : Dont Cry
// author: priyananda( shenoy@cs.wisc.edu )
// date: nov 2007
// random trivia:
#include "OrientableObject.h"
#include <windows.h>
#include <gl\gl.h>

#define _USE_MATH_DEFINES
#include <cmath>

//orient the object
void OrientableObject::orient()
{
	Vector3 tangent = front - location;
	tangent.normalize();
	up.normalize();
	Vector3 htangent = tangent.cross(up);

	htangent.y = 0;

	float hangle = htangent.angle2D(Vector3::ZAxis);
	float vangle = up.angleBetween(Vector3::YAxis);

	if( location.y - front.y > 0.0f )
		vangle = -vangle;

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(location.x,location.y,location.z);
	glRotatef(hangle, 0,1,0);
	glRotatef(vangle, 0,0,1);
}

void OrientableObject::disorient()
{
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}