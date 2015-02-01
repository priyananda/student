// CS559 Project 1 : Picture Processor
// author: priyananda( shenoy@cs.wisc.edu )
// date: 7 oct 2007
// random quote: []
#include "Escher.h"
#include "Extractor.h"
#include "TargaImage.h"
#include "SymbolTable.h"

#include <cmath>

bool Escher::extract(const CommandLine & c)
{
	if( Extractor::checkArguments(c,errorString,2) &&
		Extractor::extractVariable(c,0,errorString,source) &&
		Extractor::extractFloat(c,1,errorString,radius)){
		varName = c[0][0];
		return true;
	}
	return false;
}

void Escher::execute()
{
	//create dest image
	int width = int(source->width() > source->height() ? source->width() : source->height());
	dest = TargaImage::blankImage(width,width);
	dest->fillAlpha(0xFF);

	//warp it!
	warp();

	//write image back into global symbol table
	SymbolTable::setSymbol(varName,dest);
}


//The inverse Hyperbolic tangent function
//apparently they aren't in standard <cmath>.
//http://msdn.microsoft.com/library/default.asp?url=/library/en-us/vblr7/html/vagrpDerivedMath.asp
static float atanh(float x)
{
	return logf( ( 1 + x ) / ( 1 - x) ) / 2.0f;
}

void Escher::mapPixel(int x, int y, float & sx , float & sy)
{
	int width = int(dest->width());
	int center = width / 2;

	//relative to the centre
	int xp = ( x - center );
	int yp = ( center - y );

	if( xp * xp + yp * yp >= radius * radius )
		return;

	float angle = 0;
	angle = atan2f(float(yp),float(xp));
	
	float d = sqrtf(float(xp*xp+yp*yp));

	//scale distance by the atanh function
	//atanh rapidly increases to infinity near x = 1
	d *= atanh(d/radius);

	//get new position
	sx = center + d * cosf(angle);
	sy = center - d * sinf(angle);
}