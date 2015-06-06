// CS559 Project 1 : Picture Processor
// author: priyananda( shenoy@cs.wisc.edu )
// date: 14 sep 2007
// random quote: [V for Vendetta] V: Who? Who is but the form following the function of what and what I am is a man in a mask. 
#pragma once
#include "Command.h"

class TargaImage;

//this command fills a rectangular area of the image
//with some color
//format: fill <variable> x1 x2 y2 y2 r g b a
class FillCommand : public Command
{
	void execute();
	bool extract(const CommandLine & c);
private:
	TargaImage * image;
	int x1,y1,x2,y2;
	int r,g,b,a;
};