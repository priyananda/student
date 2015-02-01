// CS559 Project 3 : Dont Cry
// author: priyananda( shenoy@cs.wisc.edu )
// date: oct 2007
// random trivia:
#pragma once

#include "SolidObject.h"
#include "TextureManager.h"

//Represents a cube, duh!
class Cube : public SolidObject
{
public:
	Cube(float x = 0, float y = 0, float z = 0,float l = 0, float h = 0, float w = 0){
		this->location.x = x;
		this->location.y = y;
		this->location.z = z;
		this->dx = l;
		this->dy = h;
		this->dz = w;
		texture = NO_TEXTURE;
	}
	virtual void draw();
	
	float dx,dy,dz;//length,height,width
	TextureType texture;//texture
private:
	void _draw();
}; 
