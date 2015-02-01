// CS559 Project 3 : Dont Cry
// author: priyananda( shenoy@cs.wisc.edu )
// date: oct 2007
// random trivia:
#include "World.h"
#include "Hero.h"
#include "Command.h"
#include "DayTimer.h"

#include "Tree.h"
#include "SignPost.h"
#include "Building.h"
#include "Gyro.h"
#include "Cave.h"
#include "SweepObject.h"

Hero World::hero;
HeightMap World::heightMap;
list<PropObject *> World::objects;
DayTimer World::timer;
bool World::cavemode;
bool World::matrixmode;
Cave World::cave;

//initializes whole lot of objects
void World::neww()
{
	hero.set(
		-115.43f,0,242.227f,
		-114.95f,0.32f,241.121f,
		0,1,0
	);
	objects.push_back(new SignPost(-40.6f,7.9f,134.7f,WELCOME_SIGN_TEXTURE,-45));
	objects.push_back(new SignPost(107.79f,20.0f,-180.92f,GYRO_SIGN_TEXTURE,-90));
	objects.push_back(new SignPost(-29.75f,7.43f,-133.16f,PORTAL_SIGN_TEXTURE,180));
	objects.push_back(new SignPost(-28.219f,105.0f,-50.0f,VOLCANO_SIGN_TEXTURE,0));
	objects.push_back(new SignPost(-57.697f,69.872f,-72.188f,LOD_SIGN_TEXTURE,0));
	objects.push_back(new Gyro(107.79f,20.0f,-173.92f));
	objects.push_back(new SweepObject(-79.15f,69.771f,-50.726f,"vase.sweep"));
	cave.construct();
	cavemode = false;
	matrixmode = false;
}

void World::drawObjects()
{
	for( list<PropObject *>::iterator iter = objects.begin(); iter != objects.end(); ++iter )
		(*iter)->draw();
}
void World::clear()
{
	while(!objects.empty()){
		PropObject * p = *objects.begin();
		objects.erase(objects.begin());
		delete p;
	}
}
//switch between the cave mode and the island mode
void World::toggleCave()
{
	if(cavemode){
		cavemode = false;
		hero.set(
			-8.287f,13,-126.284f,
			-8.328f,13,-127.528f,
			0,1,0
		);
	}else{
		cavemode = true;
		hero.set(
			-95,0,0,
			-90,0,0,
			0,1,0
		);
	}
}
float World::getHeight(float x, float y)
{
	if(cavemode)
		return 0;
	return heightMap.getHeight(x,y);
}
void World::startMatrixEffect()
{
	matrixmode = true;
	cave.startMatrixEffect();
}
void World::endMatrixEffect()
{
	matrixmode = false;
}