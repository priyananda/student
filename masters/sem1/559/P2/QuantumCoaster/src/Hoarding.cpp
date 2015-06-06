// CS559 Project 2 : Quantum Coaster
// author: priyananda( shenoy@cs.wisc.edu )
// date: 5 nov 2007
// random trivia:
#include "Hoarding.h"

#include <windows.h>
#include <gl/gl.h>

//todo: draw the legs
Hoarding::Hoarding(float x,float y,float z, float l,float h,float w, TextureType t)
:texture(t){
	location.x = x;
	location.y = y;
	location.z = z;
	dx = l;dy = h; dz = w;
	face.texture = back.texture = BANNER_TEXTURE;
	if( l < w ){
		face.addVertex(0,h,0,0,1);
		face.addVertex(0,h,w,1,1);
		face.addVertex(0,h/2,w,1,0);
		face.addVertex(0,h/2,0,0,0);
		
		back.addVertex(0.5f,h,0,0,1);
		back.addVertex(0.5f,h,w,1,1);
		back.addVertex(0.5f,h/2,w,1,0);
		back.addVertex(0.5f,h/2,0,0,0);
	}else{
		face.addVertex(0,h,0,0,0);
		face.addVertex(l,h,0,1,0);
		face.addVertex(l,h/2,0,1,1);
		face.addVertex(0,h/2,0,0,1);
		
		back.addVertex(0,h,0.5f,0,0);
		back.addVertex(l,h,0.5f,1,0);
		back.addVertex(l,h/2,0.5f,1,1);
		back.addVertex(0,h/2,0.5f,0,1);
	}
}


void Hoarding::draw()
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(location.x,location.y,location.z);
	face.draw();
	back.draw();
	glPopMatrix();
}

void Hoarding::serialize(char * buffer)
{
	sprintf_s(buffer,254,"hoarding %f %f %f %f %f %f",
		location.x,location.y,location.z,
		dx,dy,dz
	);
}