// CS559 Project 1 : Picture Processor
// author: priyananda( shenoy@cs.wisc.edu )
// date: 22 sep 2007
// random quote: [Grindhouse] Stuntman Mike: The woods are lovely, dark, and deep, and I've got promises to keep.
#pragma once

#include "Command.h"
#include "ArbitWarp.h"

//forward declaration
class TargaImage;

//command behavior: rotates an image counter-clockwise with angle given in degrees
//format: rotate <variable> <angle>
class Rotate : public Command, public ArbitWarp
{
public:
	//overriding Command fuctions
	bool extract(const CommandLine &c);
	void execute();

	//overriding Warp functions
	void mapPixel(int x,int y,float &sx,float &sy);
private:
	char varName;
	float angle;
};