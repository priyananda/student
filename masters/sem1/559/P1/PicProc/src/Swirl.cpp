// CS559 Project 1 : Picture Processor
// author: priyananda( shenoy@cs.wisc.edu )
// date: 07 oct 2007
// random quote: []
#include "Swirl.h"
#include "Extractor.h"
#include "TargaImage.h"
#include "SymbolTable.h"

#ifndef _USE_MATH_DEFINES
	#define _USE_MATH_DEFINES // to get PI
#endif
#include <cmath>

bool Swirl::extract(const CommandLine & c)
{
	if( Extractor::checkArguments(c,errorString,3) &&
		Extractor::extractVariable(c,0,errorString,source) &&
		Extractor::extractFloat(c,1,errorString,radius) &&
		Extractor::extractFloat(c,2,errorString,angle)){
		varName = c[0][0];
		angle = float(M_PI * angle / 180);
		return true;
	}
	return false;
}

void Swirl::execute()
{
	//create dest image
	dest = TargaImage::blankImage(source->width(),source->height());
	dest->fillAlpha(0xFF);

	//warp it!
	warp();

	//write image back into global symbol table
	SymbolTable::setSymbol(varName,dest);
}

void Swirl::mapPixel(int x, int y, float &sx, float &sy)
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
	//calculate effective angle of rotation
	//float a = (float)atan2f(( y - ycenter ),( x - xcenter )) + (angle * (radius - dist)) / radius;
	float effangle = atan2f( float(x - xcenter) , float(y - ycenter));
	//add user specified angle, scaled by distance from center
	effangle += angle * ( 1 - dist / radius );
	sx = xcenter + dist * cosf(effangle);
	sy = ycenter + dist * sinf(effangle);
}