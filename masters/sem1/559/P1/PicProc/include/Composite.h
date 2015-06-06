// CS559 Project 1 : Picture Processor
// author: priyananda( shenoy@cs.wisc.edu )
// date: 23 sep 2007
// random quote: [Fight Club] Narrator: I am Jack's Medula Oblongata.
#pragma once

#include "Command.h"

//forward declaration
class TargaImage;

//Do you think this and opengl's glBlendFunc's constants having
//similar names is a coincidence?
enum BlendFunctions
{
	Zero,
	One,
	SrcAlpha,
	OneMinusSrcAlpha,
	DestAlpha,
	OneMinusDestAlpha
};

//command behavior: composites two images into one
//format: composite <srcimage> <operator> <destimage> x y
class Composite : public Command
{
public:
	//overriding these fuctions
	bool extract(const CommandLine &c);
	void execute();
private:
	TargaImage * srcImage, * destImage;
	char destVarName;
	//the compositing operator
	BlendFunctions srcFunc, destFunc;
	int x,y;

	void calcNewValue( unsigned char * srcPixel, unsigned char * destPixel);
};