// CS559 Project 2 : Quantum Coaster
// author: priyananda( shenoy@cs.wisc.edu )
// date: oct 2007
// random trivia:
#include "Train.h"
#include "Track.h"
#include "World.h"

#include <windows.h>
#include <gl/gl.h>

//todo: clean this
void Train::draw(bool shadows)
{
	if(!visible)
		return;
	for(int i = 0; i < bogeys; ++i ){
		if(quant)
			World::track.getQPoint(positionOnTrack-i*5,*this);
		else
			World::track.getPoint(positionOnTrack-i*5,*this);
		beforeDraw();
		glTranslatef(0,2.0f,0);
		if(shadows)
			glColor3ub(0,0,0);
		else if(i == 0)
			glColor3ub(255,0,0);
		else
			glColor3ub(255,255,255);
		body.draw();
		afterDraw();
	}
}