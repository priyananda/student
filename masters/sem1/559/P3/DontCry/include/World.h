// CS559 Project 3 : Dont Cry
// author: priyananda( shenoy@cs.wisc.edu )
// date: oct 2007
// random trivia:
#pragma once

class Hero;
class PropObject;
class DayTimer;
class Cave;
enum PropObjectType;

#include <list>
using std::list;

#include "HeightMap.h"

// This has all the data about the worrld, where things are and all that
class World
{
public:
	static Hero hero;
	static HeightMap heightMap;
	static DayTimer timer;
	static list<PropObject *> objects;
	static Cave cave;
	static bool cavemode;
	static bool matrixmode;

	static void neww();
	static void clear();
	static void drawObjects();
	static void toggleCave();
	static float getHeight(float x,float y);
	static void startMatrixEffect();
	static void endMatrixEffect();
};