// CS559 Project 1 : Picture Processor
// author: priyananda( shenoy@cs.wisc.edu )
// date: 17 sep 2007
// random quote: [The Matrix Reloaded] The Oracle: We can never see past the choices we don't understand. 

#include "Blur.h"
#include "Extractor.h"
#include "TargaImage.h"
#include "FilterKernel.h"

//format:
//for bspline blur: blur <width>
//for gaussian blur: blur <width> <std dev>
bool Blur::extract(const CommandLine & c)
{
	stddev = -1;
	if( Extractor::checkArguments(c,errorString,2) &&
		Extractor::extractVariable(c,0,errorString,image) &&
		Extractor::extractPositiveInt(c,1,errorString,k) ){
		if( c.numberOfArguments() > 2 )
			return Extractor::extractFloat(c,2,errorString,stddev);
		return true;
	}
	return false;
}

//uses a k-bspline or gaussian kernel to blur images
void Blur::execute()
{
	FilterKernel2D * filter = NULL;
	if( stddev < 0 )
		//aha! bspline
		filter = FilterFactory::createBSpline(k);
	else
		//no! gaussian
		filter = FilterFactory::createGaussian(k,stddev);
	filter->convolve(image);
	delete filter;
}