// CS559 Project 2 : Quantum Coaster
// author: priyananda( shenoy@cs.wisc.edu )
// date: nov 2007
// random trivia:
#include "SolidObject.h"
#include <windows.h>
#include <gl\gl.h>

#define _USE_MATH_DEFINES
#include <cmath>

//orient the object
//todo: shouldn't this be in orientable object
void SolidObject::beforeDraw()
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

void SolidObject::afterDraw()
{
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}