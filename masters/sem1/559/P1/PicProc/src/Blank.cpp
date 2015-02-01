// CS559 Project 1 : Picture Processor
// author: priyananda( shenoy@cs.wisc.edu )
// date: 15 sep 2007
// random quote: [Life of Brian]Arthur: I say you are Lord, and I should know. I've followed a few.

#include "Blank.h"
#include "Extractor.h"
#include "TargaImage.h"
#include "SymbolTable.h"
#include "ImageHelpers.h"

bool Blank::extract(const CommandLine & c)
{
	TargaImage * image;
	if( Extractor::checkArguments(c,errorString,3) &&
		Extractor::extractVariable(c,0,errorString,image,false) &&
		Extractor::extractPositiveInt(c,1,errorString,width) &&
		Extractor::extractPositiveInt(c,2,errorString,height))
	{
		varName = c[0][0];
		return true;
	}
	return false;
}

void Blank::execute()
{
	TargaImage * image = TargaImage::blankImage(width,height);
	//blankImage fills each pixel with (0,0,0,0) but we need (0,0,0,255)
	image->fillAlpha(255);
	SymbolTable::setSymbol(varName,image);
}