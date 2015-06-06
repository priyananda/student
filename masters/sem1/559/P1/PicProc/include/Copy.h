// CS559 Project 1 : Picture Processor
// author: priyananda( shenoy@cs.wisc.edu )
// date: 15 sep 2007
// random quote: [ETOTSM] Mary: Blessed are the forgetful, for they get the better even of their blunders. 
#pragma once

#include "Command.h"

//forward declaration
class TargaImage;

//command behavior: copies an image from one variable to another
//format: copy <source> <dest>
class Copy : public Command
{
public:
	//overriding these fuctions
	bool extract(const CommandLine &c);
	void execute();
private:
	char destVarName;
	TargaImage * srcImage;
};