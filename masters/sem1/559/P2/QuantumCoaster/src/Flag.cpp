// CS559 Project 2 : Quantum Coaster
// author: priyananda( shenoy@cs.wisc.edu )
// date: oct 2007
// random trivia:
#include "Flag.h"
#include <windows.h>
#include <gl/gl.h>

// a line and a rectangle
void Flag::draw()
{
	glColor3ub(0,224,116);
	glLineWidth(5.0f);
	glBegin( GL_LINES );
		glVertex3f( location.x, location.y , location.z );
		glVertex3f( location.x, location.y + 20, location.z );
	glEnd();
	glLineWidth(1.0f);
	glColor3ub(255,255,255);
	
	TextureManager::bind(CRATE_TEXTURE);
	glBegin(GL_QUADS);
		glTexCoord2i(0,1);glVertex3f(location.x,location.y + 15,location.z);
		glTexCoord2i(0,0);glVertex3f(location.x,location.y + 20,location.z);
		glTexCoord2i(1,0);glVertex3f(location.x + 5,location.y + 20,location.z);
		glTexCoord2i(1,1);glVertex3f(location.x + 5,location.y + 15,location.z);
	glEnd();
	TextureManager::unbind();
}

void Flag::serialize(char * buffer)
{
	sprintf_s(buffer,254,"flag %f %f %f",
		location.x,location.y,location.z
	);
}