// CS559 Project 1 : Picture Processor
// author: priyananda( shenoy@cs.wisc.edu )
// date: 17 sep 2007
// random quote: [The Matrix] Morpheus: Welcome to the desert of the real
#pragma once

#include "Command.h"

//forward declaration
class TargaImage;

//command behavior: applies a blur filter on the image
//format: blur <variable> <size of the kernel> <sd in case of gaussian>
class Blur : public Command
{
public:
	//overriding these fuctions
	bool extract(const CommandLine &c);
	void execute();
private:
	TargaImage * image;
	int k;
	float stddev;
};