// CS559 Project 3 : Dont Cry
// author: priyananda( shenoy@cs.wisc.edu )
// date: 5 nov 2007
// random trivia:
#include "SignPost.h"

#include <windows.h>
#include <gl/gl.h>

static const float height = 15;
static const float width  = 6;

SignPost::SignPost(float x,float y,float z, TextureType t, float angle)
:leg(0,0,0,.5f,height,.5f)
{
	location.x = x;
	location.y = y;
	location.z = z;
	this->angle = angle;
	face.texture = t;
	leg.texture = CRATE_TEXTURE;

	face.addVertex(-width,height-width,0.7f,0,1);
	face.addVertex(-width,height+width,0.7f,0,0);
	face.addVertex( width,height+width,0.7f,1,0);
	face.addVertex( width,height-width,0.7f,1,1);
}
void SignPost::draw()
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(location.x,location.y,location.z);
	glRotatef(angle,0,1,0);
	face.draw();
	leg.draw();
	glPopMatrix();
}

void SignPost::serialize(char * buffer)
{
	sprintf_s(buffer,254,"signpost %f %f %f %f",
		location.x,location.y,location.z,
		angle
	);
}