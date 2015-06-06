// CS559 Project 1 : Picture Processor
// author: priyananda( shenoy@cs.wisc.edu )
// date: 6 oct 2007
// random quote: []
#pragma once

#include "Command.h"

//forward declaration
class TargaImage;

//represents a splat
struct Splat
{
	int x,y,mask,z;
	//LessThanComparable for sorting
	bool operator <(const Splat & s){return z < s.z;}
};

//Emulates non-photorealistic rendering
//format: painter <variable>
class Painter : public Command
{
public:
	//overriding these fuctions
	bool extract(const CommandLine &c);
	void execute();
private:
	void splat(const Splat & c);

	char varName;
	TargaImage * image;
	TargaImage * dest;
	int numIters,blurWidth;
};