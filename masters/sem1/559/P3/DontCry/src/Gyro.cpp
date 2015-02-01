// CS559 Project 3 : Dont Cry
// author: priyananda( shenoy@cs.wisc.edu )
// date: oct 2007
// random trivia:
#include "Gyro.h"
#include <windows.h>
#include <gl/gl.h>

#define _USE_MATH_DEFINES
#include <cmath>

//3 rings
void Gyro::draw()
{
	glLineWidth(5);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(location.x,location.y,location.z);
	
	glRotatef(-xangle,1,0,0);
	glVertexPointer(3,GL_FLOAT,sizeof(Point),xring);
	glDrawArrays(GL_LINE_LOOP,0,40);
	
	glColor3ub(0,0,255);
	glRotatef(zangle,0,0,1);
	glVertexPointer(3,GL_FLOAT,sizeof(Point),zring);
	glDrawArrays(GL_LINE_LOOP,0,40);
	
	glRotatef(-zangle,0,0,1);
	glRotatef(xangle,1,0,0);
	
	glColor3ub(0,255,0);
	glRotatef(yangle,0,1,0);
	glVertexPointer(3,GL_FLOAT,sizeof(Point),yring);
	glDrawArrays(GL_LINE_LOOP,0,40);
	glRotatef(-yangle,0,1,0);
	
	glColor3ub(255,255,0);
	glBegin(GL_LINES);
		glVertex3f(0,radius,0);
		glVertex3f(0,-radius,0);
	glEnd();
	
	xangle++;
	yangle++;
	zangle++;
	
	glPopMatrix();
	glLineWidth(1);
}

void Gyro::serialize(char * buffer)
{
	sprintf_s(buffer,254,"flag %f %f %f",
		location.x,location.y,location.z
	);
}
void Gyro::construct()
{
	float angleInc = float(M_PI/20);
	float twoPi = float(2*M_PI);
	int i = 0;
	for(float angle = 0; angle < twoPi; angle += angleInc ){
		zring[i].x = sinf(angle) * radius;
		zring[i].y = 0;
		zring[i].z = cosf(angle) * radius;
		++i;
	}
	i = 0;
	radius *= .9f;
	for(float angle = 0; angle < twoPi; angle += angleInc ){
		xring[i].x = sinf(angle) * radius;
		xring[i].y = cosf(angle) * radius;
		xring[i].z = 0;
		++i;
	}
	i = 0;
	for(float angle = 0; angle < twoPi; angle += angleInc ){
		yring[i].x = 0;
		yring[i].y = cosf(angle) * radius;
		yring[i].z = sinf(angle) * radius;
		++i;
	}
}