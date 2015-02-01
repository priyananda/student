// CS559 Project 1 : Picture Processor
// author: priyananda( shenoy@cs.wisc.edu )
// date: 01 oct 2007
// random quote: [Natural Born Killers] Mickey: Frankenstein had to kill Dr. Frankenstein.
#pragma once

class TargaImage;

//Arbitrary warping code. Uses reverse-mapping.
//may or maynot be adaptive.
//abstract class. Actual warps must inherit and override.
class ArbitWarp
{
public:
	//does the actual warping
	void warp();
protected:
	//map destination pixel (x,y) to source pixel (sx,sy)
	virtual void mapPixel(int x,int y,float &sx,float &sy) = 0;
	//evaluates value at non-integer source pixel
	virtual unsigned char * valueOf(float sx,float sy);
	//source and dest image
	TargaImage * source, * dest;
	//flag to control what interpolation is used
private:
	//interpolation filters
	void bilinear(float sx,float sy,unsigned char * p);
	void bicubic(float sx,float sy,unsigned char * p);
	void nearest(float sx,float sy,unsigned char * p);
protected:
	//what should I use
	int interpolationType;

	static const int FILTER_NEAREST = 0, FILTER_BILINEAR = 1, FILTER_BICUBIC = 2;
};