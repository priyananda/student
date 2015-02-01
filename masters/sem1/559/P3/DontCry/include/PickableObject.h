// CS559 Project 3 : Dont Cry
// author: priyananda( shenoy@cs.wisc.edu )
// date: oct 2007
// random trivia:
#pragma once

#include <list>
using std::list;

class PickableObjectRegistry;
class Camera;

// something which can be "picked" in SELECT mode
class PickableObject
{
public:
	bool isSelected(){ return selected;}
protected:
	PickableObject()
		:selected(false){}

	virtual void onSelectionChanged(){}
	virtual void drawForPicking() = 0;
	
	bool selected;
private:
	int name;
	friend class PickableObjectRegistry;
};

// registry of all pickable objects in the world
class PickableObjectRegistry
{
public:
	static PickableObject * getObjectAt(int x,int y);
	static void add(PickableObject *p);
	static void remove(PickableObject *p);
private:
	static list<PickableObject *> objects;
};