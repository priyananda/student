// CS559 Project 2 : Quantum Coaster
// author: priyananda( shenoy@cs.wisc.edu )
// date: 18 oct 2007
// random trivia: Rage will the first game to use the "ID Tech 5" engine.
#pragma once

#include "BaseObject.h"
#include <list>
using std::list;

// Solar System Object
class SSObject : public BaseObject
{
public:
	SSObject():selected(false),level(0),rotAngle(0),rotSpeed(0){}
	void draw();
	void addChild();
	void removeChild();
	void update();
private:
	void drawSomethingWhichLooksLikeACircle(float radius);

	int level;
	bool selected;
	list<SSObject *> children;
	float rotAngle;
	float rotSpeed;
};

#define FORALLKIDS(iter) for( list<SSObject *>::iterator iter = children.begin(); iter != children.end(); ++ iter )