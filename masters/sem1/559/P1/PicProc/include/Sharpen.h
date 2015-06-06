// CS559 Project 1 : Picture Processor
// author: priyananda( shenoy@cs.wisc.edu )
// date: 15 sep 2007
// random quote: [Kill Bill 2] Bill: He hates Caucasians, despises Americans, and has nothing but contempt for women... so in your case, it might take a while. 
#pragma once

#include "Command.h"

//forward declaration
class TargaImage;

//command behavior: sharpens the image using unsharp mask
//format: sharpen <variable> <radius> <amount> <threshold>
class Sharpen : public Command
{
public:
	//overriding these fuctions
	bool extract(const CommandLine &c);
	void execute();
private:
	int radius;
	float amount;
	int threshold;
	TargaImage * image;
};