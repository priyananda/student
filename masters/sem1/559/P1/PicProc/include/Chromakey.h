// CS559 Project 1 : Picture Processor
// author: priyananda( shenoy@cs.wisc.edu )
// date: 23 sep 2007
// random quote: [The Maltese Falcon] Kasper Gutman: The best goodbyes are short. Adieu. 
#pragma once

#include "Command.h"

//forward declaration
class TargaImage;

//command behavior: makes specific color pixels transparent
//format: chromakey v r g b
class Chromakey : public Command
{
public:
	//overriding these fuctions
	bool extract(const CommandLine &c);
	void execute();
	int r,g,b;
	int threshold;
private:
	TargaImage * image;
};