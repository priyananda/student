// CS559 Project 1 : Picture Processor
// author: priyananda( shenoy@cs.wisc.edu )
// date: 6 oct 2007
// random quote: []
#include "Painter.h"
#include "Extractor.h"
#include "TargaImage.h"
#include "SymbolTable.h"
#include "BrushMaster.h"

#include <iostream>
#include <list>
using namespace std;

bool Painter::extract(const CommandLine & c)
{
	//default values
	numIters = 3;
	blurWidth = 7;
	if( Extractor::checkArguments(c,errorString,1) &&
		Extractor::extractVariable(c,0,errorString,image) ){
		varName = c[0][0];
		if(!BrushMaster::initialize()){
			REPORT_ERROR(errorString,0,"Required file sbrushes.tga missing. Make sure that this file in in the current directory");
			return false;
		}
		if( c.numberOfArguments() > 1 )
			Extractor::extractPositiveInt(c,1,errorString,numIters);
		if( c.numberOfArguments() > 2 )
			Extractor::extractPositiveInt(c,2,errorString,blurWidth);
		return true;
	}
	return false;
}

//paints a brush with the sampled pixel
void Painter::splat(const Splat & s)
{
	int width = int(image->width());
	int height = int(image->height());

	if( s.x > width - 10 || s.y > height - 10 )
		return;

	//this is so bad: just sample the middle pixel
	int samplex = s.x + 5;
	int sampley = s.y + 5;

	unsigned char * pixel = image->pixel(samplex,sampley);

	for( int i = 0 ; i < BrushMaster::BRUSH_WIDTH; ++i )
		for( int j = 0 ; j < BrushMaster::BRUSH_WIDTH; ++j ){
			int mask = BrushMaster::getBrushPixel(s.mask,i,j);
			if(	s.x + i < width && s.y + j < height && mask > 0){
				unsigned char * dp = dest->pixel(s.x+i,s.y+j);
				unsigned char * ip = image->pixel(s.x+i,s.y+j);
				dp[0] = unsigned char( (pixel[0] * mask + ip[0] * ( 255 - mask ))/255 );
				dp[1] = unsigned char( (pixel[1] * mask + ip[1] * ( 255 - mask ))/255 );
				dp[2] = unsigned char( (pixel[2] * mask + ip[2] * ( 255 - mask ))/255 );
				dp[3] = unsigned char( (pixel[3] * mask + ip[3] * ( 255 - mask ))/255 );
			}
		}
}

#include "FilterKernel.h"

void Painter::execute()
{	
	int width = int(image->width());
	int height = int(image->height());

	dest = TargaImage::blankImage(width,height);
	
	for( int i = 0; i < width; i += 10 )
		for(int j = 0; j < height; j += 10 ){
			for( int z = 0 ; z < numIters; ++z ){
				Splat s;
				s.mask = BrushMaster::getRandomBrush();
				s.x = i;
				s.y = j;
				splat(s);
			}
		}
	if( blurWidth > 0 ){
		FilterKernel2D * g = FilterFactory::createGaussian(blurWidth,1.0f);
		g->convolve(dest);
		delete g;
	}
	SymbolTable::setSymbol(varName,dest);
}
