// CS559 Project 1 : Picture Processor
// author: priyananda( shenoy@cs.wisc.edu )
// date: 15 sep 2007
// random quote: []
#include "Opaque.h"
#include "Extractor.h"
#include "TargaImage.h"
#include "ImageHelpers.h"

bool Opaque::extract(const CommandLine & c)
{
	return Extractor::checkArguments(c,errorString,1) &&
		Extractor::extractVariable(c,0,errorString,image);
}

//oh! What would I not give to have closures in C++?
static void maxAlpha(Command *p, unsigned char * pixels)
{
	pixels[3] = 255;//A
}

void Opaque::execute()
{
	ImageHelpers::forEachPixel(this,image,maxAlpha);
}