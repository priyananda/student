// CS559 Project 1 : Picture Processor
// author: priyananda( shenoy@cs.wisc.edu )
// date: 23 sep 2007
// random quote: [Sunset Boulevard] Joe Gillis: There's nothing tragic about being fifty. Not unless you're trying to be twenty-five.  
#pragma once

class TargaImage;
class Command;

//some helper functions
class ImageHelpers
{
public:
	//copied verbatim from Prof Gleicher's sample code
	static void pixelMultiply(unsigned char& v, const float f)
	{
		v = static_cast<unsigned char>( f * static_cast<float>(v) );
	}

	//function pointer for forEachPixel. All per-pixel operations
	//should be done in a non-class function with two arguments
	//the command object and the pixel.
	typedef void (*PerPixelFunction) (Command * pCommand, unsigned char *);
	
	//iterates over all pixels and calls "function" on each
	static void forEachPixel(Command * pCommand, TargaImage * image , PerPixelFunction function );

	//upsamples an image(increase in size) in 2D
	static TargaImage * upSample2D(TargaImage * src,int factor);
	//downsamples an image(decrease in size) in 2D
	static TargaImage * downSample2D(TargaImage * src,int factor);

	//upsamples an image(increase in size) in x direction
	static TargaImage * upSampleH(TargaImage * src,int factor);
	//downsamples an image(decrease in size) in x direction
	static TargaImage * downSampleH(TargaImage * src,int factor);

	//upsamples an image(increase in size) in y direction
	static TargaImage * upSampleV(TargaImage * src,int factor);
	//downsamples an image(decrease in size) in y direction
	static TargaImage * downSampleV(TargaImage * src,int factor);
	
	//distance between colors
	static int colorDistance(int r1,int g1,int b1,int r2,int g2,int b2);

	//unused
	void RGBToHSV(int r,int g,int b, float &h,float &s, float &v);
	void HSBToRGB(float h,float s,float v,int & r, int & g , int & b );
private:
	//actual implementations
	static TargaImage * upSample(TargaImage * src,int xfactor,int yfactor);
	static TargaImage * downSample(TargaImage * src,int xfactor,int yfactor);	
};