// CS559 Project 2 : Quantum Coaster
// author: priyananda( shenoy@cs.wisc.edu )
// date: oct 2007
// random trivia:
#pragma once

#include "PickableObject.h"
#include "SolidObject.h"

enum PropObjectType
{
	PROP_HOARDING,
	PROP_BUILDING,
	PROP_TREE,
	PROP_FLAG
};

//an object which can be added to the world.
//stupid name for a class, isn't it?
class PropObject : public SolidObject,public PickableObject
{
public:
	virtual void serialize(char *) = 0;
}; 
