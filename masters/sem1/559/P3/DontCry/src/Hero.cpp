// CS559 Project 3 : Dont Cry
// author: priyananda( shenoy@cs.wisc.edu )
// date: 20 oct 2007
// random trivia:

#include "Hero.h"
#include "World.h"
#include <cmath>

#include <window.h>
#include <gl/gl.h>

//move direction towards "front"
void Hero::moveForward(float d)
{
	Vector3 direction = front - location;
	direction.normalize();

	location.x  += direction.x * d;
	location.z  += direction.z * d;
	front.x += direction.x * d;
	front.z += direction.z * d;

	float inc = location.y - World::getHeight(location.x,location.z);
	location.y -= inc;
	front.y -= inc;
}

//just expanded the matrix
//adapted from DigiBen's tutorials 
void Hero::turn(float x, float y, float z,float angle)
{
	Vector3 direction = front - location;

	float cosTheta = cosf(angle);
	float sinTheta = sinf(angle);

	front.x  = location.x;
	front.x += (cosTheta + (1 - cosTheta) * x * x)		* direction.x;
	front.x += ((1 - cosTheta) * x * y - z * sinTheta)	* direction.y;
	front.x += ((1 - cosTheta) * x * z + y * sinTheta)	* direction.z;

	front.y  = location.y;
	front.y += ((1 - cosTheta) * x * y + z * sinTheta)	* direction.x;
	front.y += (cosTheta + (1 - cosTheta) * y * y)		* direction.y;
	front.y += ((1 - cosTheta) * y * z - x * sinTheta)	* direction.z;

	front.z  = location.z;
	front.z += ((1 - cosTheta) * x * z - y * sinTheta)	* direction.x;
	front.z += ((1 - cosTheta) * y * z + x * sinTheta)	* direction.y;
	front.z += (cosTheta + (1 - cosTheta) * z * z)		* direction.z;
}

//turn around the Y axis
void Hero::turnH(float d)
{
	turn(0,1,0,d);
}
//turn in vertical direction
void Hero::turnV(float d)
{
	Vector3 axis = (front - location).cross(up);
	axis.normalize();

	turn(axis.x,axis.y,axis.z,d);
}
void Hero::strafe(float d)
{
	Vector3 axis = (front - location).cross(up);
	axis.normalize();

	location.x  += axis.x * d;
	location.z  += axis.z * d;
	front.x += axis.x * d;
	front.z += axis.z * d;

	float inc = location.y - World::getHeight(location.x,location.z);
	location.y -= inc;
	front.y -= inc;
}
void Hero::update()
{
	POINT mouse;
	int viewport[4] = {0,0,0,0};

	memset(&mouse,0,sizeof(POINT));
	
	::GetCursorPos(&mouse);
	glGetIntegerv(GL_VIEWPORT,viewport);
	
	int hcenter = viewport[2] / 2;
	int vcenter = viewport[3] / 2;

	float hangle = (hcenter - mouse.x)/1000.0f;
	float vangle = (vcenter - mouse.y)/1000.0f;

	turnH(hangle);
	turnV(vangle);

	::SetCursorPos(hcenter,vcenter);
}