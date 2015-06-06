// CS559 Project 2 : Quantum Coaster
// author: priyananda( shenoy@cs.wisc.edu )
// date: 16 oct 2007
// random trivia: Caligula, the much hates Roman emperor, was actually very popular among his citizens.

#include "ViewPort.h"
#include "Window.h"
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>

void ViewPort::set(Window * p)
{
	glViewport(x,y,width,height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0f,(GLfloat)width/(GLfloat)height, 0.1f ,1000.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
//go from perspective to orthographic project
void ViewPort::switchTo2D()
{
	glDisable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0,width,0,height,-1,1);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
}
//just pop the matrix
void ViewPort::restoreFrom2D()
{
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glEnable(GL_DEPTH_TEST);
}