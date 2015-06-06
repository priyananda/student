// CS559 Project 2 : Quantum Coaster
// author: priyananda( shenoy@cs.wisc.edu )
// date: 18 oct 2007
// random trivia: Duke Nukem Forever has been in production for over 10 years.

#pragma once

// A vector with 3 components.
class Vector3
{
public:
	float x,y,z;
	
	//constructor
	Vector3(float a = 0,float b = 0,float c = 0):x(a),y(b),z(c){}
	Vector3(const Vector3 & v){
		this->x = v.x;
		this->y = v.y;
		this->z = v.z;
	}

	//operators
	//length of the vector
	float magnitude() const;
	//divide by magnitude
	void normalize();
	//dot product
	Vector3 dot(const Vector3 & v) const;
	//cross product
	Vector3 cross(const Vector3 & v) const;
	//addition
	Vector3 operator+(const Vector3 &) const;
	//subtraction
	Vector3 operator-(const Vector3 &) const;
	//distance between vectors
	float distance(const Vector3 &) const;
};

typedef Vector3 Point;