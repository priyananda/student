// CS559 Project 1 : Picture Processor
// author: priyananda( shenoy@cs.wisc.edu )
// date: 7 oct 2007
// random quote: []
#include "Drops.h"
#include "Extractor.h"
#include "TargaImage.h"
#include "SymbolTable.h"

#ifndef _USE_MATH_DEFINES
	#define _USE_MATH_DEFINES // to get PI
#	endif
#include <cmath>

bool Drops::extract(const CommandLine & c)
{
	if( Extractor::checkArguments(c,errorString,4) &&
		Extractor::extractVariable(c,0,errorString,source) &&
		Extractor::extractFloat(c,1,errorString,wavelength) &&
		Extractor::extractRangedFloat(c,2,errorString,0,1.0F,amplitude) &&
		Extractor::extractFloat(c,3,errorString,radius)){
		varName = c[0][0];
		return true;
	}
	return false;
}
void Drops::execute()
{
	//create dest image
	dest = TargaImage::blankImage(source->width(),source->height());
	dest->fillAlpha(0xFF);

	//warp it!
	warp();

	//write image back into global symbol table
	SymbolTable::setSymbol(varName,dest);
}

void Drops::mapPixel(int x, int y, float &sx, float &sy)
{
	int xcenter = int(source->width()/2);
	int ycenter = int(source->height()/2);

	int dists = ( x - xcenter ) * ( x - xcenter ) + ( y - ycenter ) * ( y - ycenter );
	if( dists == 0 || dists >= radius * radius ){
		//outside our circle of influence
		sx = float(x);
		sy = float(y);
		return;
	}
	//distance from centre of drop
	float dist = sqrtf(float(dists));
	//y = a sin( theta )
	float displacement = float(amplitude * sin(2 * M_PI * dist / wavelength));
	//attenuate it
	displacement *= ( radius - dist ) / radius;
	displacement *= wavelength / dist;
	sx = float(x + (x - xcenter) * displacement);
	sy = float(y + (y - ycenter) * displacement);
}