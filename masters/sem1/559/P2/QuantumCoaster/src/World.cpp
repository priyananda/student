// CS559 Project 2 : Quantum Coaster
// author: priyananda( shenoy@cs.wisc.edu )
// date: oct 2007
// random trivia:
#include "World.h"
#include "Train.h"
#include "Track.h"
#include "God.h"
#include "Command.h"
#include "ControlPoint.h"

#include "Tree.h"
#include "Hoarding.h"
#include "Building.h"
#include "Flag.h"

#include <fstream>
using std::ifstream;
using std::ofstream;
using std::endl;

Train World::train1;
Train World::train2;
Track World::track;
God World::god;
list<PropObject *> World::objects;

void World::neww()
{
	god.set(-211.887f,156.522f,191.781f,-186.771f,135.458f,168.489f,0,1,0);
	track.controls.clear();
	track.addControl(-100,2,-100);
	track.addControl(-100,2,100);
	track.addControl(100,2,100);
	track.addControl(100,2,-100);
	track.pointify();

	add( new Tree(-22,0,-106));
	add( new Hoarding(-31,-54,2,50,100,1,BANNER_TEXTURE));
	add( new Flag(68,0,44));
	add( new Building(-75,6,100,10,10,20));
}

#define _ATOF(x) float(atof(x))
#define EQ(a) _strcmpi(cl.command,a) == 0

void World::open(char *filename)
{
	ifstream file(filename);
	char buffer[255];
	bool first = true;
	int qcount = 0;

	clear();

	while(file.good()){
		file.getline(buffer,254);
		CommandLine cl(buffer);
		if(EQ("god"))
			god.set(
				_ATOF(cl[0]),_ATOF(cl[1]),_ATOF(cl[2]),
				_ATOF(cl[3]),_ATOF(cl[4]),_ATOF(cl[5]),
				_ATOF(cl[6]),_ATOF(cl[7]),_ATOF(cl[8])
			);
		else if (EQ("control")){
			if(first){
				first = false;
				track.clearControls();
			}
			track.addControl(
				_ATOF(cl[0]),_ATOF(cl[1]),_ATOF(cl[2]),
				_ATOF(cl[3]),_ATOF(cl[4]),_ATOF(cl[5])
			);
			if(qcount > 0){
				track.qcontrols.push_back(track.controls.back());
				--qcount;
			}
		}
		else if (EQ("qstart")){
			int c = int(track.controls.size());
			track.qcontrols.push_back(track.controls[c-3]);
			track.qcontrols.push_back(track.controls[c-2]);
			track.qcontrols.push_back(track.controls[c-1]);
		}
		else if (EQ("controlq")){
			track.addControl(
				_ATOF(cl[0]),_ATOF(cl[1]),_ATOF(cl[2]),
				_ATOF(cl[3]),_ATOF(cl[4]),_ATOF(cl[5]),
				true
			);
		}
		else if (EQ("qend")){
			qcount = 3;
		}
		else if(EQ("flag"))
			add( new Flag(
				_ATOF(cl[0]),_ATOF(cl[1]),_ATOF(cl[2])
			));
		else if(EQ("hoarding"))
			add( new Hoarding( 
				_ATOF(cl[0]),_ATOF(cl[1]),_ATOF(cl[2]),
				_ATOF(cl[3]),_ATOF(cl[4]),_ATOF(cl[5]),
				BANNER_TEXTURE
			));
		else if(EQ("building"))
			add( new Building(
				_ATOF(cl[0]),_ATOF(cl[1]),_ATOF(cl[2]),
				_ATOF(cl[3]),_ATOF(cl[4]),_ATOF(cl[5])
			));
		else if(EQ("tree"))
			add( new Tree(
				_ATOF(cl[0]),_ATOF(cl[1]),_ATOF(cl[2])
			));
	}
	file.close();
}

void World::save(char *filename)
{
	ofstream out(filename);
	out << "#buckyland file" << endl << "#Priyananda Shenoy : CS559 : QuantumCoaster" << endl;
	out << "god " << god.location.x << " " << god.location.y << " " << god.location.z << " ";
	out << god.front.x << " " << god.front.y << " " << god.front.z << " ";
	out << god.up.x << " " << god.up.y << " " << god.up.z << endl;
	out << endl;
	
	out << "#control points" << endl;
	int cpcount = track.getControlCount();
	for(int i = 0 ; i < cpcount; ++i ){
		ControlPoint * p = track.getControl(i);
		out << "control " << p->location.x << " " << p->location.y << " " << p->location.z << " ";
		out << p->up.x << " " << p->up.y << " " << p->up.z << endl;
	}
	char buffer[255];
	memset(buffer,0,255);
	for( list<PropObject *>::iterator i = objects.begin();i != objects.end(); ++i ){
		(*i)->serialize(buffer);
		out << buffer << endl;
	}
	out.close();
}

void World::add(PropObject * p)
{
	objects.push_back(p);
	PickableObjectRegistry::add(p);
}
void World::remove(PropObject *p)
{
	PickableObjectRegistry::remove(p);
	objects.remove(p);
	delete p;
}
PropObject * World::getSelectedObject()
{
	for( list<PropObject *>::iterator iter = objects.begin(); iter != objects.end(); ++iter )
		if((*iter)->isSelected())
			return *iter;
	return NULL;
}

void World::drawObjects()
{
	for( list<PropObject *>::iterator iter = objects.begin(); iter != objects.end(); ++iter )
		(*iter)->draw();
}
void World::clear()
{
	while(!objects.empty())
		remove(*objects.begin());
}

void World::add(PropObjectType t)
{
	switch(t){
		case PROP_TREE:
			add( new Tree(0,0,0));
			break;
		case PROP_HOARDING:
			add( new Hoarding(0,0,0,50,100,1,BANNER_TEXTURE));
			break;
		case PROP_FLAG:
			add( new Flag(0,0,0));
			break;
		case PROP_BUILDING:
			add( new Building(0,0,0,10,10,20));
			break;
	}
}
void World::deleteSelectedObject()
{
	PropObject * ps = getSelectedObject();
	if( ps != NULL ){
		remove(ps);
		return;
	}
	ControlPoint * cp = track.getSelectedControl();
	if(cp != NULL)
		track.deleteControl(cp);
}