// CS559 Project 3 : Dont Cry
// author: priyananda( shenoy@cs.wisc.edu )
// date: 9 dec 2007
// random trivia:
#pragma once

class PropObject;

#include "Polygon.h"
#include "MD3.h"

#include <list>
using std::list;

//The cave where we will show off bumpmapping and
//matrix effect
class Cave
{
public:
	void construct();
	void drawWalls();
	void drawObjects();
	void enter();
	void exit();
	void add(PropObject * p){
		this->objects.push_back(p);
	}
	void updateHero();
	void startMatrixEffect();
private:
	list<PropObject *> objects;
	Polygone top,bottom;

	//bumpmap effect
	int bumpProgram;
	float bulb[4];
	float bulbAngle;
	
	//matrix effect
	CModelMD3 lara;
	//this reminds me of U2's video for Elevation featuring Tomb Raider :)
	float elevation;
	//0=ground,1=rising,2=hovering,3=falling
	int state;
	float heroAngle;
	void animate();
};