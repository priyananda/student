// CS559 Project 3 : Dont Cry
// author: priyananda( shenoy@cs.wisc.edu )
// date: 24 nov 2007
// random trivia:
#pragma once

#include "Vector.h"

//an image representing heights
class HeightMap
{
public:
	HeightMap():vertices(0),rowCount(0),colCount(0){}
	void loadFrom(const char * fileName);
	void draw();
	float getHeight(float x,float z);
	void vertex(const Point & p,float,float);
private:
	Point ** vertices;
	int rowCount;
	int colCount;
}; 
