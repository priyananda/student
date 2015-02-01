// CS559 Project 1 : Picture Processor
// author: priyananda( shenoy@cs.wisc.edu )
// date: 15 sep 2007
// random quote: []
#include "Dissolve.h"
#include "Extractor.h"
#include "TargaImage.h"
#include "ImageHelpers.h"

bool Dissolve::extract(const CommandLine & c)
{
	return Extractor::checkArguments(c,errorString,2) &&
		Extractor::extractVariable(c,0,errorString,image) &&
		Extractor::extractRangedFloat(c,1,errorString,0,1.0f,factor);
}

static void multAplha(Command * p, unsigned char * pixels)
{
	//static_cast is fine here since no one else will
	//call this function. besides dynamic_cast will
	//behave arbitly if /GR is not specified in command
	//line
	float factor = static_cast<Dissolve *>(p)->dissolveFactor();
	ImageHelpers::pixelMultiply(pixels[3],factor);
}

void Dissolve::execute()
{
	ImageHelpers::forEachPixel(this,image,multAplha);
}