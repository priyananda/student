// CS559 Project 2 : Quantum Coaster
// author: priyananda( shenoy@cs.wisc.edu )
// date: oct 2007
// random trivia:
#pragma once

#include "SolidObject.h"
#include "Cube.h"

class Track;

//The RC train.
class Train : public SolidObject
{
public:
	Train():body(0,0,0,2,1,1),positionOnTrack(0),bogeys(1),visible(true),quant(false){
		body.texture = CRATE_TEXTURE;
	}
	virtual void draw(){draw(false);}
	void draw(bool shadows);
	void start(){
		positionOnTrack = (bogeys - 1)*5.0f;
	}
	void update(float speed){
		positionOnTrack += speed;
	}
	void chooBogey(bool add){
		if(add){
			++bogeys;
			positionOnTrack += 5;
		}else{
			if(bogeys <= 1)return;
			--bogeys;
		}
	}
	bool visible;
	bool quant;
private:
	void updatePos();

	Cube body;
	float positionOnTrack;
	int bogeys;
};