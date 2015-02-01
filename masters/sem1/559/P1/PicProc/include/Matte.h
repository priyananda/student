// CS559 Project 1 : Picture Processor
// author: priyananda( shenoy@cs.wisc.edu )
// date: 7 oct 2007
// random quote: []
#pragma once

#include "Command.h"

//forward declaration
class TargaImage;

//command behavior: This tries to guess the matte ( alpha values )
//using the brightness as an indicator 
class Matte : public Command
{
public:
	//overriding these fuctions
	bool extract(const CommandLine &c);
	void execute();

	bool isBackGroundLight;
	int threshold;
private:
	TargaImage * image;
	char varName;
};