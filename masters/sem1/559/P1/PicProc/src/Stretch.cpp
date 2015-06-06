// CS559 Project 1 : Picture Processor
// author: priyananda( shenoy@cs.wisc.edu )
// date: 15 sep 2007
// random quote: []

#include "Stretch.h"
#include "Extractor.h"
#include "TargaImage.h"
#include "ImageHelpers.h"
#include "SymbolTable.h"

bool Stretch::extract(const CommandLine & c)
{
	if( Extractor::checkArguments(c,errorString,5) &&
		Extractor::extractVariable(c,0,errorString,image) &&
		Extractor::extractPositiveInt(c,1,errorString,xa) &&
		Extractor::extractPositiveInt(c,2,errorString,xb) &&
		Extractor::extractPositiveInt(c,3,errorString,ya) &&
		Extractor::extractPositiveInt(c,4,errorString,yb)){
			varName = c[0][0];
			return true;
	}
	return false;
}

void Stretch::execute()
{
	//scale in x direction
	TargaImage * upx = ImageHelpers::upSampleH(image,xa);
	TargaImage * downx = ImageHelpers::downSampleH(upx,xb);
	//scale in y direction
	TargaImage * upy = ImageHelpers::upSampleV(downx,ya);
	TargaImage * downy = ImageHelpers::downSampleV(upy,yb);
	//change the variable
	SymbolTable::setSymbol(varName,downy);
}