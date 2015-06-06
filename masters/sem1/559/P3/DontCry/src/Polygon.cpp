// CS559 Project 3 : Dont Cry
// author: priyananda( shenoy@cs.wisc.edu )
// date: 5 Nov 2007
// random trivia:
#include "Polygon.h"
#include <windows.h>
#include <gl/gl.h>

void Polygone::draw()
{
	if( vertices.size() < 1 ) return;
	Vertex & v = vertices.front();
	if( texture != NO_TEXTURE )
		if( vertices.front().s1 >= 0 )
			TextureManager::bind(texture,TextureStretchNone);
		else
			TextureManager::bind(texture,TextureStretchBoth);
	glBegin(GL_POLYGON);
	for( list<Vertex>::iterator iter = vertices.begin(); iter !=  vertices.end(); ++iter ){
		glTexCoord2f((*iter).s1,(*iter).t1);
		glVertex3f( (*iter).x,(*iter).y,(*iter).z);
	}
	TextureManager::unbind();
	glEnd();
}