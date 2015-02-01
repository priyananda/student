// CS559 Project 3 : Dont Cry
// author: priyananda( shenoy@cs.wisc.edu )
// date: oct 2007
// random trivia:
#include "windows.h"
#include "gl/gl.h"
#include "gl/glu.h"
#include "PickableObject.h"
#include "Camera.h"

list<PickableObject *> PickableObjectRegistry::objects;

void PickableObjectRegistry::add(PickableObject * p)
{
	objects.push_back(p);
}

void PickableObjectRegistry::remove(PickableObject * p)
{
	objects.remove(p);
}

//picking logic is thanks to
//http://jerome.jouvie.free.fr/OpenGl/Tutorials/Tutorial27.php
PickableObject* PickableObjectRegistry::getObjectAt(int x,int y)
{
	PickableObject * ret = NULL;
	GLuint buffer[100];
	GLint view[4];
	float projection[16];
	int i = 1;

	glSelectBuffer (10, buffer);
	glRenderMode(GL_SELECT);
	
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	
	glGetFloatv(GL_PROJECTION_MATRIX, projection);
	glLoadIdentity();
 	
	glGetIntegerv(GL_VIEWPORT, view);
	gluPickMatrix(x - 5, view[3]- y -5, 10,10, view);
	glMultMatrixf(projection);
	
	glMatrixMode(GL_MODELVIEW);
	glInitNames();

	for( list<PickableObject *>::iterator iter = objects.begin(); iter != objects.end(); ++iter ){
		glPushName(i);
		(*iter)->name = i++;
		(*iter)->drawForPicking();
		glPopName();
	}
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glFlush();

	GLuint hits = glRenderMode(GL_RENDER);

	if( hits > 0 ){
		int sel = buffer[3];
		for( list<PickableObject *>::iterator iter = objects.begin(); iter != objects.end(); ++iter )
			if( (*iter)->name == sel ){
				if(!(*iter)->selected){
					(*iter)->selected = true;
					(*iter)->onSelectionChanged();
				}
				ret = *iter;
			}else{
				if( (*iter)->selected ){
					(*iter)->selected = false;
					(*iter)->onSelectionChanged();
				}
			}
	}

	return ret;
}