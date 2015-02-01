// CS559 Project 1 : Picture Processor
// author: priyananda( shenoy@cs.wisc.edu )
// date: 15 sep 2007
// random quote: [Kill Bill 2] Bill: Clark Kent is Superman's critique on the whole human race.
#pragma once

#include "Command.h"

//forward declaration
class TargaImage;

//command behavior: makes image translucent
//format: dissolve <variable> <factor>
class Dissolve : public Command
{
public:
	//overriding these fuctions
	bool extract(const CommandLine &c);
	void execute();

	float dissolveFactor() const { return factor; }
private:
	TargaImage * image;
	float factor;
};