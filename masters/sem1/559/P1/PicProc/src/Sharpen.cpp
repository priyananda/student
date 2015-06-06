// CS559 Project 1 : Picture Processor
// author: priyananda( shenoy@cs.wisc.edu )
// date: 26 sep 2007
// random quote: []
#include "Sharpen.h"
#include "Extractor.h"
#include "TargaImage.h"
#include "FilterKernel.h"

bool Sharpen::extract(const CommandLine & c)
{
	return Extractor::checkArguments(c,errorString,4) &&
		Extractor::extractVariable(c,0,errorString,image) &&
		Extractor::extractPositiveInt(c,1,errorString,radius) &&
		Extractor::extractFloat(c,2,errorString,amount) &&
		Extractor::extractPositiveInt(c,3,errorString,threshold);
}

//uses an unsharp mask to sharpen image
void Sharpen::execute()
{
	TargaImage * mask = image->clone();
	FilterKernel2D * kernel = FilterFactory::createGaussian(radius * 2 + 1,3.0f/radius);
	kernel->convolve(mask);
	delete kernel;
	
	int width = mask->width(), height = mask->height();
	unsigned char * maskPixel = mask->pixels();
	unsigned char * imagePixel = image->pixels();

	for(int y = 0 ; y < height; ++y )
		for(int x = 0 ; x < width; ++x )
			for( int i = 0; i < 4; ++i ){
				int rdiff = *imagePixel - *maskPixel;
				if( abs(rdiff) < threshold )
					//this pixel doesn't differ much from original, leave it
					rdiff = 0;
				int value = int(*imagePixel + amount * rdiff);
				if(value < 0 )
					*imagePixel = 0;
				else if(value > 255 )
					*imagePixel = 255;
				else
					*imagePixel = value;
				++maskPixel;
				++imagePixel;
			}
	delete mask;
}