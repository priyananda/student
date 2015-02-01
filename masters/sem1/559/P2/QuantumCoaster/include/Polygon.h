// CS559 Project 2 : Quantum Coaster
// author: priyananda( shenoy@cs.wisc.edu )
// date: 4 nov 2007
// random trivia:
#pragma once

#include <list>
using std::list;

#include "Vector.h"
#include "TextureManager.h"

struct Vertex : public Point
{
	float u,v;//texture
	Vertex(float x,float y,float z,float _u,float _v):Point(x,y,z),u(_u),v(_v){
	}
};

//represents a polygon
struct Polygone
{
	list<Vertex> vertices;
	TextureType texture;

	void addVertex(float x,float y, float z, float u = -1, float v = -1){
		vertices.push_back(Vertex(x,y,z,u,v));
	}
	void draw();
}; 
