// CS559 Project 2 : Quantum Coaster
// author: priyananda( shenoy@cs.wisc.edu )
// date: 20 oct 2007
// random trivia:

#include "God.h"
#include <cmath>

//move direction towards "front"
void God::moveForward(float d)
{
	Vector3 direction = front - location;
	direction.normalize();

	location.x  += direction.x * d;
	location.z  += direction.z * d;
	location.y  += direction.y * d;
	front.x += direction.x * d;
	front.z += direction.z * d;
	front.y += direction.y * d;
}

//just expanded the matrix
//adapted from DigiBen's tutorials 
void God::turn(float x, float y, float z,float angle)
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
void God::turnH(float d)
{
	turn(0,1,0,d);
}
//turn in verticle direction
void God::turnV(float d)
{
	Vector3 axis = (front - location).cross(up);
	axis.normalize();

	turn(axis.x,axis.y,axis.z,d);
}