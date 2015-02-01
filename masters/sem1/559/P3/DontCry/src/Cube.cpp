// CS559 Project 3 : Dont Cry
// author: priyananda( shenoy@cs.wisc.edu )
// date: oct 2007
// random trivia:
#include "Cube.h"
#include "windows.h"
#include "gl\gl.h"

void Cube::draw()
{
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	_draw();
	/*glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	dx += 0.001f;dy += 0.001f;dz += 0.001f;
	glColor3f(0,0,0);
	_draw();
	dx -= 0.001f;dy -= 0.001f;dz -= 0.001f;*/
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

}

void Cube::_draw()
{
	if( texture != NO_TEXTURE )
		TextureManager::bind(texture);

	glNormal3f(0.0, 0.0, -1.0);
	glBegin(GL_QUADS);
		glTexCoord2i(0,1);glVertex3f(location.x - dx , location.y - dy , location.z - dz );
		glTexCoord2i(1,0);glVertex3f(location.x + dx , location.y - dy , location.z - dz );
		glTexCoord2i(1,1);glVertex3f(location.x + dx , location.y + dy , location.z - dz );
		glTexCoord2i(1,0);glVertex3f(location.x - dx , location.y + dy , location.z - dz );
	glEnd();

	glNormal3f(0.0, 0.0, 1.0);
	glBegin(GL_QUADS);
		glTexCoord2i(0,1);glVertex3f(location.x - dx , location.y - dy , location.z + dz );
		glTexCoord2i(1,0);glVertex3f(location.x + dx , location.y - dy , location.z + dz );
		glTexCoord2i(1,1);glVertex3f(location.x + dx , location.y + dy , location.z + dz );
		glTexCoord2i(1,0);glVertex3f(location.x - dx , location.y + dy , location.z + dz );
	glEnd();

	glNormal3f(-1.0, 0.0, 0.0);
	glBegin(GL_QUADS);
		glTexCoord2i(0,1);glVertex3f(location.x - dx , location.y - dy , location.z - dz );
		glTexCoord2i(1,0);glVertex3f(location.x - dx , location.y - dy , location.z + dz );
		glTexCoord2i(1,1);glVertex3f(location.x - dx , location.y + dy , location.z + dz );
		glTexCoord2i(1,0);glVertex3f(location.x - dx , location.y + dy , location.z - dz );
	glEnd();

	glNormal3f(1.0, 0.0, 0.0);
	glBegin(GL_QUADS);
		glTexCoord2i(0,1);glVertex3f(location.x + dx , location.y - dy , location.z - dz );
		glTexCoord2i(1,0);glVertex3f(location.x + dx , location.y - dy , location.z + dz );
		glTexCoord2i(1,1);glVertex3f(location.x + dx , location.y + dy , location.z + dz );
		glTexCoord2i(1,0);glVertex3f(location.x + dx , location.y + dy , location.z - dz );
	glEnd();

	glNormal3f(0.0, 1.0, 0.0);
	glBegin(GL_QUADS);
		glTexCoord2i(0,1);glVertex3f(location.x - dx , location.y + dy , location.z - dz );
		glTexCoord2i(1,0);glVertex3f(location.x - dx , location.y + dy , location.z + dz );
		glTexCoord2i(1,1);glVertex3f(location.x + dx , location.y + dy , location.z + dz );
		glTexCoord2i(1,0);glVertex3f(location.x + dx , location.y + dy , location.z - dz );
	glEnd();

	glNormal3f(0.0, -1.0, 0.0);
	glBegin( GL_QUADS );
		glTexCoord2i(0,1);glVertex3f(location.x - dx , location.y - dy , location.z - dz );
		glTexCoord2i(1,0);glVertex3f(location.x - dx , location.y - dy , location.z + dz );
		glTexCoord2i(1,1);glVertex3f(location.x + dx , location.y - dy , location.z + dz );
		glTexCoord2i(1,0);glVertex3f(location.x + dx , location.y - dy , location.z - dz );
	glEnd();

	TextureManager::unbind();
}