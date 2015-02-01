// CS559 Project 1 : Picture Processor
// author: priyananda( shenoy@cs.wisc.edu )
// date: 16 sep 2007
// random quote: []

#include "FillCommand.h"
#include "Extractor.h"
#include "TargaImage.h"

//fill <variable> x1 y1 x2 y2 r g b a
bool FillCommand::extract(const CommandLine & c)
{
	return Extractor::checkArguments(c,errorString,9) &&
		Extractor::extractVariable(c,0,errorString,image) &&
		Extractor::extractInt(c,1,errorString,x1) &&
		Extractor::extractInt(c,2,errorString,y1) &&
		Extractor::extractInt(c,3,errorString,x2) &&
		Extractor::extractInt(c,4,errorString,y2) &&
		Extractor::extractRangedInt(c,5,errorString,0,255,r) &&
		Extractor::extractRangedInt(c,6,errorString,0,255,g) &&
		Extractor::extractRangedInt(c,7,errorString,0,255,b) &&
		Extractor::extractRangedInt(c,8,errorString,0,255,a);
}

void FillCommand::execute()
{
	int width = (int) image->width();
	int height = (int) image->height();
	//take care of invalid cases
	if( x1 > x2 )x1 ^= x2 ^= x1 ^= x2;//swap 'em
	if( y1 > y2 )y1 ^= y2 ^= y1 ^= y2;
	if( x1 < 0 ) x1 = 0;
	if( y1 < 0 ) y1 = 0;
	if( x2 < 0 ) return;
	if( y2 < 0 ) return;
	if( x1 >= width ) return;
	if( y1 >= height ) return;
	if( x2 >= width ) x2 = width - 1;
	if( y2 >= height ) y2 = height - 1;
	unsigned char * pixels = image->pixels();
	for(; y1 <= y2; ++y1){
		//fill this row by row
		unsigned char * start = pixels + (y1 * width + x1) * 4;
		int cols = x2 - x1 + 1;
		while(cols--){
			start[0] = r;
			start[1] = g;
			start[2] = b;
			start[3] = a;
			start += 4;
		}
	}
}