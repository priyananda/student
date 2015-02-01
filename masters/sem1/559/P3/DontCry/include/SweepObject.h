// CS559 Project 3 : Dont Cry
// author: priyananda( shenoy@cs.wisc.edu )
// date: 11 dec 2007
// random trivia:
#pragma once

#include "PropObject.h"

#include <list>
using std::list;


//An object obtained by rotating a bspline.
class SweepObject : public PropObject
{
public:
	SweepObject(float x,float y,float z,const char * filename);
	void draw();
	void drawForPicking(){}
	void serialize(char *){}

private:
	void generateTriangles(list< Point >& points, int & size,Triangle * & ptr,int res);

	Point * vertices;
	int verticesCount;
	
	Triangle * highResTriangles;
	int highResTrianglesCount;

	Triangle * mediumResTriangles;
	int mediumResTrianglesCount;

	Triangle * lowResTriangles;
	int lowResTrianglesCount;
};