// CS559 Project 3 : Dont Cry
// author: priyananda( shenoy@cs.wisc.edu )
// date: 24 nov 2007
// random trivia:
#pragma once

#include "Vector.h"

class Frustum;

enum DayTimeState
{
	Night,
	Dawn,
	Day,
	Dusk
};

//Represents a dome around the whole world
class SkyDome
{
public:
	SkyDome():
		vertices(0),verticesCount(0),
		skyProgram(0),waterProgram(0),state(Night),
		cloudTextureDisp(0),sunTextureDisp(0),
		triangles(0),trianglesCount(0),
		visibleTriangles(0),visibleTrianglesCount(0){}
	void setDimension(float rad, int gran){
		radius = rad;
		vdetail = gran;
		hdetail = 4 * gran;
		construct();
	}
	void draw(const Frustum &);
private:
	void getColor();
	void construct();
	void vertex(Vertex &);
	void drawWater();
	void cull(const Frustum & v);

	float radius;
	int hdetail;
	int vdetail;
	
	Vertex * vertices;
	int verticesCount;
	Triangle * triangles;
	int trianglesCount;
	Triangle * visibleTriangles;
	int visibleTrianglesCount;

	int skyProgram;
	int waterProgram;
	DayTimeState state;
	int cloudTextureDisp;
	float sunTextureDisp;
}; 