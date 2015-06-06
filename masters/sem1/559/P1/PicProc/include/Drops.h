// CS559 Project 1 : Picture Processor
// author: priyananda( shenoy@cs.wisc.edu )
// date: 7 oct 2007
// random quote: [Hook] Peter Pan: Don't mess with me man, I'm a lawyer.
#pragma once

#include "Command.h"
#include "ArbitWarp.h"

//forward declaration
class TargaImage;

//command behavior: simulates water drops effect
//format: drops <variable> <wavelength> <amplitude> <radius>
class Drops : public Command, public ArbitWarp
{
public:
	//overriding Command fuctions
	bool extract(const CommandLine &c);
	void execute();
	
	//overriding ArbitWarp functions
	virtual void mapPixel(int x,int y,float &sx,float &sy);
private:
	char varName;
	float wavelength;
	float amplitude;
	float radius;
};