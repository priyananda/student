// CS559 Project 1 : Picture Processor
// author: priyananda( shenoy@cs.wisc.edu )
// date: 15 sep 2007
// random quote: []
#include "FlagWarp.h"
#include "Extractor.h"
#include "TargaImage.h"
#include "SymbolTable.h"

#ifndef _USE_MATH_DEFINES
	#define _USE_MATH_DEFINES // to get PI
#endif
#include <cmath>

bool FlagWarp::extract(const CommandLine & c)
{
	if( Extractor::checkArguments(c,errorString,1) &&
		Extractor::extractVariable(c,0,errorString,source) ){
		varName = c[0][0];
		return true;
	}
	return false;
}

void FlagWarp::execute()
{
	//create dest image
	dest = TargaImage::blankImage(source->width(),source->height() + 100 );
	dest->fillAlpha(0xFF);

	//warp it!
	warp();

	//write image back into global symbol table
	SymbolTable::setSymbol(varName,dest);
}

void FlagWarp::mapPixel(int x, int y, float &sx, float &sy)
{
	int width = int(dest->width());
	float angle = float( 2 * M_PI * x / width );
	float displacement = -sinf(angle) * 25 + 25;
	sx = float(x);
	sy = y - displacement;
}