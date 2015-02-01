// CS559 Project 1 : Picture Processor
// author: priyananda( shenoy@cs.wisc.edu )
// date: 16 sep 2007
// random quote: [American History X] Danny: I believe in death, destruction, chaos, filth, and greed.
#pragma once

#include "Command.h"

//forward declaration
class TargaImage;

//command behavior: this command tries to imitate
//Andy Warhol's famous Che Guevara poster
//format:che <variable> <destfilename>
class Che : public Command
{
public:
	//overriding these fuctions
	bool extract(const CommandLine &c);
	void execute();
private:
	void warholify(int i,int j);

	TargaImage * image, * dest;
	char varName;
};