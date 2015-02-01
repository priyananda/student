// CS559 Project 1 : Picture Processor
// author: priyananda( shenoy@cs.wisc.edu )
// date: 7 oct 2007
// random quote: []
#pragma once

#include "Command.h"
#include "ArbitWarp.h"

//forward declaration
class TargaImage;

//command behavior:
//format:
class Escher : public Command,public ArbitWarp
{
public:
	//overriding these fuctions
	bool extract(const CommandLine &c);
	void execute();

	//overriding ArbitWarp Members
	void mapPixel(int,int,float&,float &);
private:
	char varName;
	float radius;
};