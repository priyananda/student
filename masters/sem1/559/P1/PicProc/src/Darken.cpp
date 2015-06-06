#include "Darken.h"
#include "Extractor.h"
#include "TargaImage.h"
#include "ImageHelpers.h"

bool Darken::extract(const CommandLine & cl)
{
	return Extractor::checkArguments(cl,errorString,2) &&
		Extractor::extractVariable(cl,0,errorString,image) &&
		Extractor::extractRangedFloat(cl,1,errorString,0,1.0f,factor);
}

//copied almost verbatim from Prof Gleicher's sample code
static void darkenPixel(Command * p, unsigned char * pixels )
{	
	float factor = (static_cast<Darken *>(p))->darkenFactor();
	ImageHelpers::pixelMultiply(pixels[0],factor);//R
	ImageHelpers::pixelMultiply(pixels[1],factor);//G
	ImageHelpers::pixelMultiply(pixels[2],factor);//B
}

void Darken::execute()
{
	ImageHelpers::forEachPixel(this,image,darkenPixel);
}