// CS559 Project 1 : Picture Processor
// author: priyananda( shenoy@cs.wisc.edu )
// date: 2 oct 2007
// random quote: [Hook] Peter Pan: Don't mess with me man, I'm a lawyer.
#pragma once

#include "Command.h"
#include "ArbitWarp.h"

//forward declaration
class TargaImage;

//command behavior: warps the image with a convex mirror
//format: mirror <variable>
class Swirl : public Command, public ArbitWarp
{
public:
	//overriding Command fuctions
	bool extract(const CommandLine &c);
	void execute();
	
	//overriding ArbitWarp functions
	virtual void mapPixel(int x,int y,float &sx,float &sy);
private:
	char varName;
	float radius;
	float angle;
};