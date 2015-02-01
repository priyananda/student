// CS559 Project 1 : Picture Processor
// author: priyananda( shenoy@cs.wisc.edu )
// date: 23 sep 2007
// random quote: [The Incredibles] Edna: Milan, darling, Milan!	
#pragma once

#include "Command.h"

//forward declaration
class TargaImage;

//command behavior: resizes the image by a rational fraction
//format: resize <variable> <numerator> <denominator>
class Resize : public Command
{
public:
	//overriding these fuctions
	bool extract(const CommandLine &c);
	void execute();
private:
	//numerator,denominator
	int num,den;
	char varName;
	TargaImage * image;
};