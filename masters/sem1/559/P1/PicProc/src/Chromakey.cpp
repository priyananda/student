// CS559 Project 1 : Picture Processor
// author: priyananda( shenoy@cs.wisc.edu )
// date: 23 sep 2007
// random quote: [The Incredibles] Edna: Luck favors the prepared.

#include "Chromakey.h"
#include "Extractor.h"
#include "TargaImage.h"
#include "ImageHelpers.h"

//format:
//chromakey <r> <g> <b> <threshhold>
//if threshhold is not specified, then exact color
bool Chromakey::extract(const CommandLine & c)
{
	threshold = 0;
	if( Extractor::checkArguments(c,errorString,4) &&
		Extractor::extractVariable(c,0,errorString,image) &&
		Extractor::extractRangedInt(c,1,errorString,0,255,r) &&
		Extractor::extractRangedInt(c,2,errorString,0,255,g) &&
		Extractor::extractRangedInt(c,3,errorString,0,255,b)){
		if( c.numberOfArguments() > 4 )
			return Extractor::extractInt(c,4,errorString,threshold);
		return true;
	}
	return false;
}

//if color is r,g,b then transparent
//"is" can be made as flexible as the user wants
static void killEmAll(Command * command,unsigned char * pixel)
{
	Chromakey * p = static_cast<Chromakey *>(command);
	//calculate "distance" between colors
	int distance = ImageHelpers::colorDistance(
		p->r,p->g,p->b,
		pixel[0],pixel[1],pixel[2]
	);
	if( distance <= p->threshold )
		pixel[3] = 0;
}

void Chromakey::execute()
{
	ImageHelpers::forEachPixel(this,image,killEmAll);
}