// CS559 Project 1 : Picture Processor
// author: priyananda( shenoy@cs.wisc.edu )
// date: 7 oct 2007
// random quote: []
#include "Matte.h"
#include "Extractor.h"
#include "TargaImage.h"
#include "SymbolTable.h"
#include "Imagehelpers.h"

bool Matte::extract(const CommandLine & c)
{
	if (Extractor::checkArguments(c,errorString,3) &&
		Extractor::extractVariable(c,0,errorString,image) &&
		Extractor::extractPositiveInt(c,1,errorString,threshold) &&
		Extractor::extractBoolean(c,2,errorString,isBackGroundLight)){
		varName = c[0][0];
		return true;
	}
	return false;
}

static void checkLuma(Command * p, unsigned char * pixel)
{
	bool isBGLight = static_cast<Matte*>(p)->isBackGroundLight;
	int threshold  = static_cast<Matte*>(p)->threshold;
	int luma = ( 213 * pixel[0] + 715 * pixel[1] + 72  * pixel[2] ) / 1000;
	if(isBGLight){
		//background is light. so higher brighness pixels are to be made
		//more transparent
		if( luma > 255 - threshold )
			pixel[3] = 0;
	}else{
		//background is light
		if( luma < threshold )
			pixel[3] = 0;
	}
}

void Matte::execute()
{
	ImageHelpers::forEachPixel(this,image,checkLuma);
}