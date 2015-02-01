// CS559 Project 3 : Dont Cry
// author: priyananda( shenoy@cs.wisc.edu )
// date: 24 oct 2007
// random trivia:

#include "ControlPoint.h"
#include "windows.h"
#include "gl/gl.h"

void ControlPoint::draw()
{
	if( selected )
		glColor3f(1,1,1);
	else
		glColor3f(1,1,0);
	Cube::draw();
}