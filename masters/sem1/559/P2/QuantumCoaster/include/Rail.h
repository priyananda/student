// CS559 Project 2 : Quantum Coaster
// author: priyananda( shenoy@cs.wisc.edu )
// date: oct 2007
// random trivia:
#pragma once

#include "Cube.h"
#include <windows.h>
#include <gl/gl.h>

//The Holy Rail :D
//rail is that piece of wood between the tracks
class Rail : public Cube
{
public:
	Rail():Cube(0,0,0,.25f,.25f,1){
		texture = CRATE_TEXTURE;
	}
	void draw(float x,float y,float z,float fx,float fy,float fz,float ux,float uy,float uz){
		set(x,y,z,fx,fy,fz,ux,uy,uz);
		beforeDraw();
		location = Point(0,0,0);
		Cube::draw();
		glBegin(GL_LINES);
			glVertex3f(0,0,0);
			glVertex3f(0,1,0);
		glEnd();
		afterDraw();
	}
}; 
