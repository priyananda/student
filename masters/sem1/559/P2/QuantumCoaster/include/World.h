// CS559 Project 2 : Quantum Coaster
// author: priyananda( shenoy@cs.wisc.edu )
// date: oct 2007
// random trivia:
#pragma once

class Train;
class Track;
class God;
class PropObject;
enum PropObjectType;

#include <list>
using std::list;

// This has all the data about the worrld, where things are and all that
class World
{
public:
	static God god;
	static Train train1;
	static Train train2;
	static Track track;
	static list<PropObject *> objects;

	static void neww();
	static void open(char * filename);
	static void save(char * filename);

	static void add(PropObject * p);
	static void add(PropObjectType t);
	static void remove(PropObject * p);
	static void clear();
	static PropObject * getSelectedObject();
	static void drawObjects();
	static void deleteSelectedObject();
}; 
