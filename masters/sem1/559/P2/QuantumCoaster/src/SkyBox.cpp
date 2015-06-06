// CS559 Project 2 : Quantum Coaster
// author: priyananda( shenoy@cs.wisc.edu )
// date: oct 2007
// random trivia:

#include "SkyBox.h"
#include <windows.h>
#include <gl/gl.h>
#include "TextureManager.h"

void  SkyBox::draw()
{
	glColor3ub(255,255,255);
	TextureManager::bind(SKY_EAST_TEXTURE);
	glBegin(GL_QUADS);
		glTexCoord2i(0,1);glVertex3f(-location.x , 0 , -location.z );
		glTexCoord2i(1,1);glVertex3f(+location.x , 0 , -location.z );
		glTexCoord2i(1,0);glVertex3f(+location.x , location.y , -location.z );
		glTexCoord2i(0,0);glVertex3f(-location.x , location.y , -location.z );
	glEnd();
	
	TextureManager::bind(SKY_WEST_TEXTURE);
	glBegin(GL_QUADS);
		glTexCoord2i(1,1);glVertex3f(-location.x , 0 , location.z );
		glTexCoord2i(0,1);glVertex3f(+location.x , 0 , location.z );
		glTexCoord2i(0,0);glVertex3f(+location.x , location.y , location.z );
		glTexCoord2i(1,0);glVertex3f(-location.x , location.y , location.z );
	glEnd();

	TextureManager::bind(SKY_SOUTH_TEXTURE);
	glBegin(GL_QUADS);
		glTexCoord2i(1,1);glVertex3f(-location.x , 0 , -location.z );
		glTexCoord2i(0,1);glVertex3f(-location.x , 0 , +location.z );
		glTexCoord2i(0,0);glVertex3f(-location.x , location.y , +location.z );
		glTexCoord2i(1,0);glVertex3f(-location.x , location.y , -location.z );
	glEnd();

	TextureManager::bind(SKY_NORTH_TEXTURE);
	glBegin(GL_QUADS);
		glTexCoord2i(0,1);glVertex3f(+location.x , 0 , -location.z );
		glTexCoord2i(1,1);glVertex3f(+location.x , 0 , +location.z );
		glTexCoord2i(1,0);glVertex3f(+location.x , location.y , +location.z );
		glTexCoord2i(0,0);glVertex3f(+location.x , location.y , -location.z );
	glEnd();

	TextureManager::bind(SKY_TOP_TEXTURE);
	glBegin(GL_QUADS);
		glTexCoord2i(1,1);glVertex3f(-location.x , location.y , -location.z );
		glTexCoord2i(0,1);glVertex3f(-location.x , location.y , +location.z );
		glTexCoord2i(0,0);glVertex3f(+location.x , location.y , +location.z );
		glTexCoord2i(1,0);glVertex3f(+location.x , location.y , -location.z );
	glEnd();

	glNormal3f(0,1,0);
	TextureManager::bind(GRASS_TEXTURE,TextureStretchNone);
	glBegin( GL_QUADS );
		glTexCoord2i(1,1);glVertex3f(-location.x , 0 , -location.z );
		glTexCoord2i(0,1);glVertex3f(-location.x , 0 , +location.z );
		glTexCoord2i(0,0);glVertex3f(+location.x , 0 , +location.z );
		glTexCoord2i(1,0);glVertex3f(+location.x , 0 , -location.z );
	glEnd();

	TextureManager::unbind();
}