// CS559 Project 1 : Picture Processor
// author: priyananda( shenoy@cs.wisc.edu )
// date: 15 sep 2007
// random quote: [To kill a mockingbird] Atticus Finch: In the name of God, believe Tom Robinson. 
#pragma once

#include "Command.h"

//forward declaration
class TargaImage;

//command behavior: removes color from an image
//format: desaturate <variable> <factor>
class Desaturate : public Command
{
public:
	//overriding these fuctions
	bool extract(const CommandLine &c);
	void execute();

	float desatFactor() const {return factor;}
private:
	float factor;
	TargaImage * image;
};