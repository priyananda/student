// CS559 Project 1 : Picture Processor
// author: priyananda( shenoy@cs.wisc.edu )
// date: 16 sep 2007
// random quote: [Fight Club] Narrator: No fear. No distractions. The ability to let that which does not matter truly slide.
#pragma once

#include "Command.h"

//forward declaration
class TargaImage;

//command behavior: creates a blank image
//format: blank <variable> <width> <height>
class Blank : public Command
{
public:
	//overriding these fuctions
	bool extract(const CommandLine &c);
	void execute();
private:
	int width,height;
	char varName;
};