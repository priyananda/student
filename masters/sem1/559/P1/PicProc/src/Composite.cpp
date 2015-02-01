// CS559 Project 1 : Picture Processor
// author: priyananda( shenoy@cs.wisc.edu )
// date: 23 sep 2007
// random quote: []

#include "Composite.h"
#include "Extractor.h"
#include "TargaImage.h"
#include "ImageHelpers.h"
#include "SymbolTable.h"

#define SETFUNC(name,src,dest)			\
	if( _stricmp(c[1],name) == 0){	\
		srcFunc = src;	\
		destFunc = dest;\
	}

//the names are from http://www.cs.wisc.edu/graphics/Courses/559-f2001/Project1/index.htm
bool Composite::extract(const CommandLine & c)
{
	if( Extractor::checkArguments(c,errorString,5) &&
		Extractor::extractVariable(c,0,errorString,srcImage) &&
		Extractor::extractVariable(c,2,errorString,destImage) &&
		Extractor::extractPositiveInt(c,3,errorString,x) &&
		Extractor::extractPositiveInt(c,4,errorString,y)){
	
		SETFUNC("clear",Zero,Zero)
		SETFUNC("first",One,Zero)
		SETFUNC("second",Zero,One)
		SETFUNC("over",One,OneMinusSrcAlpha)
		SETFUNC("under",OneMinusDestAlpha,One)
		SETFUNC("in",DestAlpha,Zero)
		SETFUNC("heldin",Zero,SrcAlpha)
		SETFUNC("out",OneMinusDestAlpha,Zero)
		SETFUNC("heldout",Zero,OneMinusSrcAlpha)
		SETFUNC("atop",DestAlpha,OneMinusSrcAlpha)
		SETFUNC("below",OneMinusDestAlpha,SrcAlpha)
		SETFUNC("xor",OneMinusDestAlpha,OneMinusSrcAlpha)
		return true;
	}
	return false;
}

//do all the 12 porter-and-duff compositing operations
void Composite::execute()
{
	int srcWidth = int(srcImage->width());
	int srcHeight= int(srcImage->height());

	int destWidth = int(destImage->width());
	int destHeight= int(destImage->height());

	int endx = x + srcWidth;
	int endy = y + srcHeight;

	if( endx >= destWidth ) endx = destWidth;
	if( endy >= destHeight ) endy = destHeight;

	for( int j = y; j < endy; ++j )
		for( int i = x; i < endx; ++i )
			calcNewValue(
				srcImage->pixel(i - x,j - y),
				destImage->pixel(i,j)
			);
}

//calculates new value of the pixels
//assumes input is not pre-multiply. ensures answer is not premultiplied
void Composite::calcNewValue( unsigned char * srcPixel, unsigned char * destPixel)
{
	int fa,fb;
	switch(srcFunc){
		case Zero: fa = 0;break;
		case One: fa = 255;break;
		case SrcAlpha: fa = srcPixel[3];break;
		case DestAlpha:fa = destPixel[3];break;
		case OneMinusSrcAlpha: fa = 255 - srcPixel[3];break;
		case OneMinusDestAlpha:fa = 255 - destPixel[3];break;
	}
	switch(destFunc){
		case Zero: fb = 0;break;
		case One: fb = 255;break;
		case SrcAlpha: fb = srcPixel[3];break;
		case DestAlpha:fb = destPixel[3];break;
		case OneMinusSrcAlpha: fb = 255 - srcPixel[3];break;
		case OneMinusDestAlpha:fb = 255 - destPixel[3];break;
	}

	//Fa = Fa * Aa
	fa *= srcPixel[3];
	//Fb = Fb * Ab
	fb *= destPixel[3];
	//first compute new Alpha
	destPixel[3] = (unsigned char)((fa + fb)/255);

	fb /= 255;
	fa /= 255;

	//Ca = Fa * Aa * Ca + Fb * Ab * Cb
	//un-pre-multiply alpha
	if( destPixel[3] != 0 ){
		destPixel[0] = (unsigned char)( (srcPixel[0] * fa + destPixel[0] * fb) / ( destPixel[3]) );
		destPixel[1] = (unsigned char)( (srcPixel[1] * fa + destPixel[1] * fb) / ( destPixel[3]) );
		destPixel[2] = (unsigned char)( (srcPixel[2] * fa + destPixel[2] * fb) / ( destPixel[3]) );
	}else{
		destPixel[0] = 0;
		destPixel[1] = 0;
		destPixel[2] = 0;
	}
}