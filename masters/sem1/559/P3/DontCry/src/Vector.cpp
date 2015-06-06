// CS559 Project 3 : Dont Cry
// author: priyananda( shenoy@cs.wisc.edu )
// date: oct 2007
// random trivia:

#define _USE_MATH_DEFINES
#include <cmath>
#include "Vector.h"

Vector3 Vector3::XAxis(1,0,0);
Vector3 Vector3::YAxis(0,1,0);
Vector3 Vector3::ZAxis(0,0,1);

float Vector3::magnitude() const
{
	return sqrtf(x*x + y*y + z*z);
}

//divide by magnitude
void Vector3::normalize()
{
	float mag = this->magnitude();
	if( mag == 0 ) return;
	x /= mag;
	y /= mag;
	z /= mag;
}

//dot product
float Vector3::dot(const Vector3 & v) const
{
	return this->x * v.x + this->y * v.y + this->z * v.z;
}

//cross product
Vector3 Vector3::cross(const Vector3 & v) const
{
	return Vector3(
		this->y * v.z - this->z * v.y,
		this->z * v.x - this->x * v.z,
		this->x * v.y - this->y * v.x
	);
}

//addition
Vector3 Vector3::operator+(const Vector3 & v) const
{
	return Vector3(
		this->x + v.x,
		this->y + v.y,
		this->z + v.z
	);
}

//subtraction
Vector3 Vector3::operator-(const Vector3 & v) const
{
	return Vector3(
		this->x - v.x,
		this->y - v.y,
		this->z - v.z
	);
}

//distance between vectors
float Vector3::distance(const Vector3 & v) const
{
	return sqrtf(
		(this->x - v.x) * (this->x - v.x) +
		(this->y - v.y) * (this->y - v.y) + 
		(this->z - v.z) * (this->z - v.z)
	);
}

//directed angle
float Vector3::angleBetween(const Vector3 & v) const
{
	float dotp = this->dot(v);
	float mag = this->magnitude() * v.magnitude();
	if( mag == 0 || mag < dotp )
		return 0;
	return float(::acos(dotp/mag) * 180.0 / M_PI);
};

float Vector3::angle2D(const Vector3 & v) const
{
	float ans = 0;
	if(FEQUALS(x,v.x))
		ans = atan2f(v.z,v.y) - atan2f(z,y);
	else if(FEQUALS(y,v.y))
		ans = atan2f(v.z,v.x) - atan2f(z,x);
	else if(FEQUALS(z,v.z))
		ans = atan2f(v.y,v.x) - atan2f(y,x);
	else
		return angleBetween(v);
	return float(ans * 180.0f / M_PI);
}

Vector3 Vector3::operator *(float m) const
{
	return Vector3(x*m,y*m,z*m);
}
Vector3 Vector3::rotateAround(Vector3 & line,const Vector3 & point,float angle)
{
	line.normalize();

	float sinAngle = float(sin(angle * M_PI /180.0f ));
	float cosAngle = float(cos(angle * M_PI /180.0f ));
	float oneMinusCosAngle = 1.0f - cosAngle;

	Vector3 row0,row1,row2;
	
	row0.x = (line.x)*(line.x) + cosAngle*(1-(line.x)*(line.x));
	row0.y = (line.x)*(line.y)*(oneMinusCosAngle) - sinAngle*line.z;
	row0.z = (line.x)*(line.z)*(oneMinusCosAngle) + sinAngle*line.y;

	row1.x = (line.x)*(line.y)*(oneMinusCosAngle) + sinAngle*line.z;
	row1.y = (line.y)*(line.y) + cosAngle*(1-(line.y)*(line.y));
	row1.z = (line.y)*(line.z)*(oneMinusCosAngle) - sinAngle*line.x;
	
	row2.x = (line.x)*(line.z)*(oneMinusCosAngle) - sinAngle*line.y;
	row2.y = (line.y)*(line.z)*(oneMinusCosAngle) + sinAngle*line.x;
	row2.z = (line.z)*(line.z) + cosAngle*(1-(line.z)*(line.z));

	return Vector3(
		point.dot(row0),
		point.dot(row1),
		point.dot(row2)
	);
}