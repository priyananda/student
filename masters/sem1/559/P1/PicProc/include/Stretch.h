// CS559 Project 1 : Picture Processor
// author: priyananda( shenoy@cs.wisc.edu )
// date: 23 sep 2007
// random quote: [Goodfellas] Henry Hill:As far back as I can remember, I've always wanted to be a gangster.
#pragma once

#include "Command.h"

//forward declaration
class TargaImage;

//command behavior: resize the image with arbitrary rational fractions
//format: stretch v xa xb ya yb
class Stretch : public Command
{
public:
	//overriding these fuctions
	bool extract(const CommandLine &c);
	void execute();
private:
	TargaImage * image;
	char varName;
	int xa,xb,ya,yb;
};