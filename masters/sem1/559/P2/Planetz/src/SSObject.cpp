// CS559 Project 2 : Quantum Coaster
// author: priyananda( shenoy@cs.wisc.edu )
// date: 18 oct 2007
// random trivia: Saturn's moon Titan is thought to have seas of liquid methane.

#include "SSObject.h"
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>

#define _USE_MATH_DEFINES
#include <math.h>

void SSObject::drawSomethingWhichLooksLikeACircle(float radius){
   glBegin(GL_TRIANGLE_FAN);
   for (int i = 0; i < 360; i += 30){
      float angle = float( i * M_PI / 180.0f );
      glVertex2f(
		  cosf(angle)*radius,
		  sinf(angle)*radius
	  );
   }
   glEnd();
}

void SSObject::draw()
{
	glPushMatrix();
	glRotatef(rotAngle, 0, 0, 1);
	glTranslatef(
		this->location.x,
		this->location.y,
		0
	);
	if( level == 0 )
		glColor3f(1,1,0);
	if( level == 1 )
		if( selected )
			glColor3f(0,0,0.5);
		else
			glColor3f(.4f,.5961f,1);
	if( level == 2 )
		glColor3f(1,0,0.2f);
	drawSomethingWhichLooksLikeACircle(25.0f/(level+1));
	FORALLKIDS(iter)
		(*iter)->draw();
	glPopMatrix();
}

void SSObject::addChild()
{
	SSObject * p = new SSObject();
	p->location.x = (this->location.x / 2) * ( 1 + 0.1f * (rand() % 6 - 3));
	p->location.y = 0;
	p->rotSpeed = float(.01f * ( rand() % 5 + 5));
	p->level = this->level + 1;
	this->children.push_back(p);
	if( level == 0 )
		p->addChild();
}
void SSObject::removeChild()
{
	if(!this->children.empty())
		this->children.pop_back();
}

void SSObject::update()
{
	this->rotAngle += rotSpeed;
	if( rotAngle > 360 )
		rotAngle -= 360;
	FORALLKIDS(iter)
		(*iter)->update();
}
void SSObject::selectNext()
{
	if( children.size() == 0 ) return;
	FORALLKIDS(iter){
		if( (*iter)->selected ){
			(*iter)->selected = false;
			list<SSObject *>::iterator k = iter;
			++k;
			if( k != children.end()){
				(*k)->selected = true;
				return;
			}
		}
	}
	(*(children.begin()))->selected = true;
}

void SSObject::moveKid(int x)
{
	SSObject * kid = NULL;
	FORALLKIDS(iter)
		if( (*iter)->selected )
			kid = *iter;
	if( kid == NULL ) return;
	kid->location.x += x;
}