// CS559 Project 1 : Picture Processor
// author: priyananda( shenoy@cs.wisc.edu )
// date: 03 oct 2007
// random quote: [Scarface] Narrator: He was Tony Montana. The world will remember him by another name...SCARFACE
#pragma once

#include "Command.h"

//forward declaration
class TargaImage;

//command behavior: cuts out a rectangle from an image
//format: crop <variable> <x1> <y1> <x2> <y2>
class Crop : public Command
{
public:
	//overriding these fuctions
	bool extract(const CommandLine &c);
	void execute();
private:
	char varName;
	TargaImage * image;
	int x1,y1,x2,y2;
};