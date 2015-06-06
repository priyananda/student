// CS559 Project 2 : Quantum Coaster
// author: priyananda( shenoy@cs.wisc.edu )
// date: oct 2007
// random trivia:
#include "Building.h"
#include "TextureManager.h"

#include <windows.h>
#include <gl/gl.h >

//just a box
void Building::draw()
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(location.x,location.y,location.z);
	TextureManager::bind(WALL_TEXTURE,TextureStretchBoth);
	building.draw();
	TextureManager::unbind();
	glPopMatrix();
}

void Building::serialize(char * buffer)
{
	sprintf_s(buffer,254,"building %f %f %f %f %f %f",
		location.x,location.y,location.z,
		dx,dy,dz
	);
}
