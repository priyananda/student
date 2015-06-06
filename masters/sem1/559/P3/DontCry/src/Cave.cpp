// CS559 Project 3 : Dont Cry
// author: priyananda( shenoy@cs.wisc.edu )
// date: 9 Dec 2007
// random trivia:

#include "Cave.h"
#include "Hero.h"
#include "World.h"
#include "SignPost.h"
#include "Shader.h"

#include <windows.h>
#include <gl/gl.h>

#define _USE_MATH_DEFINES
#include <cmath>

#define PI 3.14159265358979323846F

//top and bottom are not bump mapped
void Cave::construct()
{
	top.texture = bottom.texture = WALL_TEXTURE;

	bottom.addVertex(-100,0,-100,0,0);
	bottom.addVertex(-100,0, 100,0,1);
	bottom.addVertex( 100,0, 100,1,1);
	bottom.addVertex( 100,0,-100,1,0);

	top.addVertex(-100,100,-100,0,0);
	top.addVertex(-100,100,100,0,1);
	top.addVertex(100,100,100,1,1);
	top.addVertex(100,100,-100,1,0);

	bumpProgram = ShaderManager::loadProgram("bump.vsh","bump.psh");
	objects.push_back(new SignPost(90,0,50,BUMP_SIGN_TEXTURE,-90));
	objects.push_back(new SignPost(10,0,-60,LARA_SIGN_TEXTURE,-90));
	objects.push_back(new SignPost(-98,0,0,PORTAL_EXIT_SIGN_TEXTURE,90));

	bulbAngle = 0;
	bulb[0] = bulb[2] = 0;bulb[1] = 70; bulb[3] = 1;

	lara.LoadModel("lara","lara");
	elevation = 10;
	state = 0;
}

static void quad(float a,float b,float c,
				 float d,float e,float f,
				 float g,float h,float i,
				 float j,float k,float l,
				 int n,int val)
{
	float normal[3] = {0,0,0};normal[n] = float(val);
	TextureManager::texcoords(0,0,0,0);glNormal3fv(normal);glVertex3f(a,b,c);
	TextureManager::texcoords(1,0,1,0);glNormal3fv(normal);glVertex3f(d,e,f);
	TextureManager::texcoords(1,1,1,1);glNormal3fv(normal);glVertex3f(g,h,i);
	TextureManager::texcoords(0,1,0,1);glNormal3fv(normal);glVertex3f(j,k,l);
}

void Cave::drawWalls()
{
	glColor3ub(255,255,255);
	top.draw();
	bottom.draw();

	bulb[0] = 95 * cosf(bulbAngle);
	bulb[2] = 95 * sinf(bulbAngle);
	bulbAngle += .01f;

	TextureManager::bind(WALL_TEXTURE,WALL_BUMP_TEXTURE);
	ShaderManager::bindProgram(bumpProgram);
	ShaderManager::setUniformVar(bumpProgram,"tex1",0);
	ShaderManager::setUniformVar(bumpProgram,"tex2",1);
	ShaderManager::setUniformVar(bumpProgram,"bulb",bulb);
	glBegin(GL_QUADS);
		//back
		quad(
			100,0  ,-100,
			100,100,-100,
			100,100, 100,
			100,0  , 100,
			0,-1
		);
		quad(
			-100,0  ,-100,
			-100,100,-100,
			 100,100,-100,
			 100,0  ,-100,
			 2,1
		);
		quad(-100,0 ,100,
			-100,100,100,
			100,100,100,
			100,0 ,100,
			2,-1
		);
		quad(
			-100,0 ,-100,
			-100,100,-100,
			-100,100, 100,
			-100,0 , 100,
			0,1
		);
	glEnd();
	ShaderManager::unbind();
	TextureManager::unbindMulti();
	glColor3ub(255,255,255);
	glBegin(GL_TRIANGLES);
		glVertex3fv(bulb);
		glVertex3f(bulb[0],bulb[1]+2,bulb[2]+2);
		glVertex3f(bulb[0],bulb[1],bulb[2]+4);
	glEnd();

	glPushMatrix();
	glTranslatef(0,elevation,0);
	glScalef(.5f,.5f,.5f);
	glRotatef(180,0,1,0);
	lara.DrawModel();
	glPopMatrix();

	animate();
}
void Cave::drawObjects()
{
	for( list<PropObject *>::iterator iter = objects.begin(); iter != objects.end(); ++iter )
		(*iter)->draw();
}
void Cave::animate()
{
	switch(state){
	case 1:
		elevation += 0.8f;
		if(elevation >= 25)state = 2;
		break;
	case 2:
		heroAngle += 0.01f;
		if( heroAngle >= 0 )state = 3;
		break;
	case 3:
		elevation -= 0.8f;
		if(elevation <= 10){
			state = 0;
			World::endMatrixEffect();
		}
		break;
	}
}
void Cave::updateHero(){
	if(state==2)
		World::hero.set(
			60*sinf(heroAngle),0,60*cosf(heroAngle),
			0,10,0,
			0,1,0
		);
}
void Cave::startMatrixEffect(){
	state = 1;
	heroAngle = -PI;
}