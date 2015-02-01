// CS559 Project 2 : Quantum Coaster
// author: priyananda( shenoy@cs.wisc.edu )
// date: oct 2007
// random trivia:

#include "Tree.h"
#include "TextureManager.h"
#include <windows.h>
#include <gl\gl.h>

//octagonal trunk and polygonal leaves
void Tree::draw()
{
	float side = 2.0f;
	Point lower[] =
	{
		Point(location.x,0,location.z+side),
		Point(location.x+side,0,location.z+side/2),
		Point(location.x+side,0,location.z-side/2),
		Point(location.x,0,location.z-side),
		Point(location.x-side,0,location.z-side/2),
		Point(location.x-side,0,location.z+side/2),
	};
	side /= 2;
	Point upper[] =
	{
		Point(location.x,20,location.z+side),
		Point(location.x+side,20,location.z+side/2),
		Point(location.x+side,20,location.z-side/2),
		Point(location.x,20,location.z-side),
		Point(location.x-side,20,location.z-side/2),
		Point(location.x-side,20,location.z+side/2),
	};
	TextureManager::bind(CRATE_TEXTURE);
	for( int i = 0 ; i < 6; ++i ){
		glBegin(GL_QUADS);
			glTexCoord2i(0,1);
			glVertex3fv((float*)&lower[i]);
			glTexCoord2i(1,1);
			glVertex3fv((float*)&lower[(i+1)%6]);
			glTexCoord2i(1,0);
			glVertex3fv((float*)&upper[(i+1)%6]);
			glTexCoord2i(0,0);
			glVertex3fv((float*)&upper[i]);
		glEnd();
	}
	glEnable(GL_BLEND);
	glBlendFunc ( GL_SRC_ALPHA , GL_ONE );
	TextureManager::bind(LEAF_TEXTURE);
		glBegin(GL_QUADS);
			glTexCoord2i(0,0);glVertex3f(location.x,location.y + 15,location.z - 20);
			glTexCoord2i(0,1);glVertex3f(location.x,location.y + 15,location.z + 20);
			glTexCoord2i(1,1);glVertex3f(location.x,location.y + 40,location.z + 20);
			glTexCoord2i(1,0);glVertex3f(location.x,location.y + 40,location.z - 20);
		glEnd();
		glBegin(GL_QUADS);
			glTexCoord2i(0,0);glVertex3f(location.x - 20,location.y + 15,location.z);
			glTexCoord2i(0,1);glVertex3f(location.x + 20,location.y + 15,location.z);
			glTexCoord2i(1,1);glVertex3f(location.x + 20,location.y + 40,location.z);
			glTexCoord2i(1,0);glVertex3f(location.x - 20,location.y + 40,location.z);
		glEnd();
	glDisable(GL_BLEND);
	TextureManager::unbind();
}

void Tree::serialize(char * buffer)
{
	sprintf_s(buffer,254,"tree %f %f %f",
		location.x,location.y,location.z
	);
}