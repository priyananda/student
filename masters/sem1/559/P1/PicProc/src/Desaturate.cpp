// CS559 Project 1 : Picture Processor
// author: priyananda( shenoy@cs.wisc.edu )
// date: 15 sep 2007
// random quote: []
#include "Desaturate.h"
#include "Extractor.h"
#include "TargaImage.h"
#include "ImageHelpers.h"

bool Desaturate::extract(const CommandLine & c)
{
	return Extractor::checkArguments(c,errorString,2) &&
		Extractor::extractVariable(c,0,errorString,image) &&
		Extractor::extractRangedFloat(c,1,errorString,0,1.0f,factor);
}

// weights obtained from http://www.poynton.com/notes/colour_and_gamma/ColorFAQ.html
// and http://en.wikipedia.org/wiki/Luminance_%28relative%29
static void desat(Command *p, unsigned char * pixels)
{
	float factor = static_cast<Desaturate *>(p)->desatFactor();

	if( pixels[0] + pixels[1] + pixels[2] > 0 ){
		//this is standard 601
		//int gray = ( 299 * pixels[0] + 587 * pixels[1] + 114 * pixels[2] ) / 1000;
		//this is standard 709.chose this coz this resembles ACDSee
		int gray = ( 213 * pixels[0] + 715 * pixels[1] + 72  * pixels[2] ) / 1000;
		pixels[0] = (unsigned char)( factor * gray + ( 1 - factor ) * pixels[0] );
		pixels[1] = (unsigned char)( factor * gray + ( 1 - factor ) * pixels[1] );
		pixels[2] = (unsigned char)( factor * gray + ( 1 - factor ) * pixels[2] );
	}
}

void Desaturate::execute()
{
	ImageHelpers::forEachPixel(this,image,desat);
}