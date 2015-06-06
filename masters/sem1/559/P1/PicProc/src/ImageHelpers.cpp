#include "ImageHelpers.h"
#include "TargaImage.h"
#include "Command.h"
#include "FilterKernel.h"
#include <algorithm>
#include <cmath>

//loops overs all the pixels in an image
void ImageHelpers::forEachPixel(Command * command,TargaImage * image, PerPixelFunction  f )
{
	if( f == NULL || image == NULL )
		return;

	unsigned char * pixels = image->pixels();
	unsigned int size = image->height() * image->width();
	while(size-- > 0){
		f(command,pixels);
		pixels += 4;
	}
}

//upsamples an image(increase in size) in 2D
//with arbitrary x and y factors
TargaImage * ImageHelpers::upSample(TargaImage * src,int xfactor, int yfactor)
{
	if( xfactor == 1 && yfactor == 1 )
		return src->clone();

	TargaImage * newImage = TargaImage::blankImage(
		src->width() * xfactor,
		src->height() * yfactor
	);

	int minf = xfactor < yfactor ? xfactor : yfactor;
	FilterKernel2D * k = FilterFactory::createSinc(2 * minf + 1);
	k->convolve(src,newImage,xfactor,yfactor);
	delete k;
	return newImage;
}
//downsamples an image(decrease in size) in 2D
//with arbitrary x and y factors
TargaImage * ImageHelpers::downSample(TargaImage * src,int xfactor, int yfactor)
{
	if(xfactor == 1 && yfactor == 1)
		return src->clone();
	
	TargaImage * newImage = TargaImage::blankImage(
		src->width() / xfactor,
		src->height() / yfactor
	);

	int srcHeight = int(src->height());
	int srcWidth = int(src->width());
	int newHeight = int(newImage->height());
	int newWidth = int(newImage->width());

	//1. apply a low pass filter
	int minf = xfactor > yfactor ? xfactor : yfactor;
	FilterKernel2D * k = FilterFactory::createBSpline(2 * minf - 2);
	k->convolve(src);
	delete k;

	//2. take 1 in every factor pixels and drop the rest
	int ny = 0;
	for( int y = 0 ; y < srcHeight; y += yfactor){
		int nx = 0;
		for( int x = 0 ; x < srcWidth; x += xfactor){
			unsigned char * newPixel = newImage->pixel(nx,ny);
			unsigned char * srcPixel = src->pixel(x,y);
			newPixel[0] = srcPixel[0];
			newPixel[1] = srcPixel[1];
			newPixel[2] = srcPixel[2];
			newPixel[3] = srcPixel[3];
			++nx;
		}
		++ny;
	}

	return newImage;
}


//increases the size in x direction
TargaImage * ImageHelpers::upSampleH(TargaImage * src,int factor)
{
	return upSample(src,factor,1);
}
//decreases the size in x direction
TargaImage * ImageHelpers::downSampleH(TargaImage * src,int factor)
{
	return downSample(src,factor,1);
}
//increases the size in y direction
TargaImage * ImageHelpers::upSampleV(TargaImage * src,int factor)
{
	return upSample(src,1,factor);
}
//decreases the size in y direction
TargaImage * ImageHelpers::downSampleV(TargaImage * src,int factor)
{
	return downSample(src,1,factor);
}
//increases the size in both directions
TargaImage * ImageHelpers::upSample2D(TargaImage * src,int factor)
{
	return upSample(src,factor,factor);
}
//decreases the size in both directions
TargaImage * ImageHelpers::downSample2D(TargaImage * src,int factor)
{
	return downSample(src,factor,factor);
}

//distance between 2 colors
//why isn't this simply RGB cube distance?
//read http://www.compuphase.com/cmetric.htm
//code taken from that site
int ImageHelpers::colorDistance(int r1, int g1, int b1, int r2, int g2, int b2)
{
	int rmean = (r1 + r2)/ 2;
	int r = r1 - r2;
	int g = g1 - g2;
	int b = b1 - b2;
	//max distance (0,0,0) -> (255,255,255) comes to 764, so dividing by 7.64
	//to scale it to 0-100 range
	return int(
		sqrtf(float((((512+rmean)*r*r) >> 8) + 4*g*g + (((767-rmean)*b*b)>>8)))
		/7.64f
	);
}

//Conversion done using: http://en.wikipedia.org/wiki/HSV_color_space
void ImageHelpers::RGBToHSV(int r,int g,int b, float &h,float &s, float &v)
{
	int max = std::max<int>(std::max<int>(r,g),b);
	int min = std::min<int>(std::min<int>(r,g),b);

	if( max == 0 ){
		//black pixel. this has to be handled elsewhere
		h = s = v = 0;
		return;
	}

	s = 1.0f - (float)min/(float)max;
	v = (float)max;

	//h is complicated
	if( max == r )
		h = (float)(g-b)/(float)(max-min) + 6 * ( g < b );
	else if( max == g )
		h = (float)(b-r)/(float)(max-min) + 2;
	else
		h = (float)(g-b)/(float)(max-min) + 4;
	//h is NOT scaled by 60.
}

void ImageHelpers::HSBToRGB(float h,float s,float v,int & r, int & g , int & b )
{
	int hi = ((int)::floorf(h)) % 6;
	float f = h - hi;
	float p = v * ( 1.0f - s );
	float q = v * ( 1.0f - f * s );
	float t = v * ( 1.0f - (1.0f - f) * s );
	float rf,gf,bf;
	switch(hi){
		case 0:
			rf = v; gf = t; bf = p;
			break;
		case 5:
			rf = v; gf = p; bf = q;
			break;
		case 1:
			rf = q; gf = v; bf = p;
			break;
		case 2:
			rf = p; gf = v; bf = t;
			break;
		case 3:
			rf = t; gf = p; bf = v;
			break;
		case 4:
			rf = q; gf = p; bf = v;
			break;
	}
	r = (int)rf;g = (int)gf;b = (int)bf;
}