// CS559 Project 1 : Picture Processor
// author: priyananda( shenoy@cs.wisc.edu )
// date: 3 oct 2007
// random quote: [Fight Club] Tyler Durden: F**k damnation, man! F**k redemption! We are God's unwanted children? So be it! 
#include "Crop.h"
#include "Extractor.h"
#include "TargaImage.h"
#include "SymbolTable.h"

bool Crop::extract(const CommandLine & c)
{
	if( Extractor::checkArguments(c,errorString,5) &&
		Extractor::extractVariable(c,0,errorString,image) &&
		Extractor::extractPositiveInt(c,1,errorString,x1) &&
		Extractor::extractPositiveInt(c,2,errorString,y1) &&
		Extractor::extractPositiveInt(c,3,errorString,x2) &&
		Extractor::extractPositiveInt(c,4,errorString,y2)){
		varName = c[0][0];
		return true;
	}
	return false;
}

//copied a rectangle (x1,y1)->(x2,y2) from old image to (0,0) of new image
void Crop::execute()
{
	int width = x2 - x1 + 1;
	int height = y2 - y1 + 1;
	TargaImage * dest = TargaImage::blankImage( width, height);
	for( int j = 0 ; j < height; ++j )
		//row by row
		for( int i = 0 ; i < width; ++i ){
			//copy columns
			unsigned char * s = image->pixel(x1+i,y1+j);
			unsigned char * d = dest->pixel(i,j);
			d[0] = s[0];
			d[1] = s[1];
			d[2] = s[2];
			d[3] = s[3];
		}
	SymbolTable::setSymbol(varName,dest);
}