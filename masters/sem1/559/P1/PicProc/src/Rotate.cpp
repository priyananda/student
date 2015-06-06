// CS559 Project 1 : Picture Processor
// author: priyananda( shenoy@cs.wisc.edu )
// date: 2 oct 2007
// random quote: [The Simpsons Movie] President Schwarzneggar: I am elected to lead, not to read.

#include "Rotate.h"
#include "Extractor.h"
#include "TargaImage.h"
#include "SymbolTable.h"

#ifndef _USE_MATH_DEFINES
	#define _USE_MATH_DEFINES // to get PI
#endif
#include <cmath>

//rotate <variable> <angle>
bool Rotate::extract(const CommandLine & c)
{
	float degrees = 0;
	if( Extractor::checkArguments(c,errorString,2) &&
		Extractor::extractVariable(c,0,errorString,source) &&
		Extractor::extractFloat(c,1,errorString,degrees) ){
		varName = c[0][0];
		//covert to radians. the negetive is because of reverse mapping
		angle = float(- 1 * M_PI * degrees / 180.0f );
		return true;
	}
	return false;
}


void Rotate::execute()
{
	//create dest image
	dest = TargaImage::blankImage(source->width(),source->height());
	dest->fillAlpha(0xFF);

	//warp it!
	warp();

	//write image back into global symbol table
	SymbolTable::setSymbol(varName,dest);
}


void Rotate::mapPixel(int x,int y,float &sx,float &sy)
{
	int width = source->width();
	int height = source->height();
	int xoff = width / 2;
	int yoff = height / 2;
			
	//0. ignore the middle, it doesn't get rotated
	if( x == xoff && y == yoff )
	{
		sx = float(x);
		sy = float(y);
		return;
	}
	//1. shift (0,0) to centre
	x -= xoff;
	y -= yoff;
			
	//2. change y direction to bottom-to-top
	y = -y;
	
	//3. calculate the new positions
	sx = x * cos(angle) - y * sin(angle);
	sy = x * sin(angle) + y * cos(angle); 
			
	//4.get centre back to (0,0)
	sy = -sy;
	sx += xoff;
	sy += yoff;		
}