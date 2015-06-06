// CS559 Project 1 : Picture Processor
// author: priyananda( shenoy@cs.wisc.edu )
// date: 6 oct 2007
// random quote: [The Matrix] Buddist Kid: There is no spoon 

#include "ArbitWarp.h"
#include "TargaImage.h"

#include <cmath>

void ArbitWarp::warp()
{
	if(this->source == 0 || this->dest == 0)
		return;

	//default is bicubic
	interpolationType = FILTER_BICUBIC;

	int height = int(dest->height());
	int width = int(dest->width());
	float sx,sy;
	for(int x = 0; x < width; ++x )
		for(int y = 0; y < height; ++y ){
			sx = sy = -1;
			//do the reverse mapping
			this->mapPixel(x,y,sx,sy);
			//evaluate value at the possibly non-integral source pixel
			unsigned char * val = this->valueOf(sx,sy);
			//copy the value into destination
			unsigned char * pixel = dest->pixel(x,y);
			pixel[0] = val[0];
			pixel[1] = val[1];
			pixel[2] = val[2];
			pixel[3] = val[3];
		}
}

//bilinear interpolation
void ArbitWarp::bilinear(float sx,float sy,unsigned char * vals)
{
	int xi = int(floorf(sx));
	int yi = int(floorf(sy));
	int xj = int(ceilf(sx));//xi + 1;
	int yj = int(ceilf(sy));//yi + 1;
	int width = int(source->width());
	int height = int(source->height());

	if( xj >= width ) xj = xi;
	if( yj >= height ) yj = yi;

	//get weight ratios
	float xf = sx - xi , yf = sy - yi;

	if( xi > -1 && xi < width )
		if( yi > -1 && yi < height ){
			unsigned char * pii = source->pixel(xi,yi);
			unsigned char * pij = source->pixel(xi,yj);
			unsigned char * pji = source->pixel(xj,yi);
			unsigned char * pjj = source->pixel(xj,yj);
			for( int z = 0 ; z < 4 ;  ++z)
				vals[z] = unsigned char(
					//I calculate the weighed average of all the 4 pixels.
					//the nearer I am to a pixel, the greater the weight.
					pii[z] * ( 1 - xf ) * ( 1 - yf ) +
					pji[z] * xf * ( 1 - yf ) +
					pij[z] * ( 1 - xf ) * yf +
					pjj[z] * xf * yf
				);
		}
}

//matrix weights and general logic
//is from http://www.cs.helsinki.fi/group/goa/mallinnus/curves/curves.html
//also a little help from Ken Perlin's splines page
static void calculateCoefficients(int values[4],int coeffs[4])
{
	static int basis[4][4] = 
	{
		{ -1 , 3, -3, 1 },
		{  3 ,-6,  3, 0 },
		{ -3 , 0,  3, 0 },
		{  1 , 4,  1, 0 }
	};

	for(int j = 0 ; j < 4; ++j)
		coeffs[j] = 0;
	
	//premultiply basis to value matrix
	for(int j = 0 ; j < 4; ++j)
		for(int i = 0 ; i < 4; ++i)
			coeffs[i] += basis[i][j] * values[j];
}

//given a set of coefficients for x = f(t), calculate
//the values at given value
static int calculateCubic(int c[4], float x)
{
	float f  = x * (x * (x * c[0] + c[1] ) + c[2] ) + c[3];
	//6 is the sum of all matrix elements
	f /= 6;
	if( f < 0 ) return 0;
	if( f > 255 ) return 255;
	return int(f);
}

//computes wieghted average of 4x4 neighbourhood of the pixel
//uses a cubic curve to achieve smoothness.
//bicubic is separable so I first do it row-wise and then vertically
void ArbitWarp::bicubic(float sx, float sy, unsigned char * vals)
{
	static int values[4];
	static int coeffs[4];
	static int temp[4];
	
	int width = int(source->width());
	int height = int(source->height());

	if( sx < 0 || sy < 0 || sx >= width || sy >= height )
		return;

	int xi = int(floorf(sx));
	int yi = int(floorf(sy));

	for(int k = 0 ; k < 4; ++k ){
		//for each color channel
		for( int j = -1; j < 3; ++j ){
			int jj = yi + j;
			if( jj < 0 ) jj = 0; if( jj >= height ) jj = height - 1;
			for( int i = -1; i < 3; ++i ){
				int ii = xi + i;
				if( ii < 0 ) ii = 0; if( ii >= width ) ii = width - 1;
				values[i+1] = source->pixel(ii,jj)[k];
			}
			//we calculate coefficients of the cubic surface
			//for each row
			calculateCoefficients(values,coeffs);
			//calculate the value at intermediate point
			temp[j+1] = calculateCubic(coeffs,sx-xi);
		}
		//we now have values at each intermediate x-value in each row
		//create a new curve through these points
		calculateCoefficients(temp,coeffs);
		//calculate the value at intermediate point
		vals[k] = calculateCubic(coeffs,sy-yi);
	}
}

//nearest neighbour interpolation. I pick the pixel
//closest to the point.
//why did I implement this?
void ArbitWarp::nearest(float sx,float sy, unsigned char *vals)
{
	if( sx < 0 || sy < 0 || sx >= source->width() || sy >= source->height() )
		return;

	int sxi = sx < 0.5f ? int(sx) : int(ceilf(sx));
	int syi = sy < 0.5f ? int(sy) : int(ceilf(sy));
	unsigned char * pixel = source->pixel( sxi,syi);
	vals[0] = pixel[0];
	vals[1] = pixel[1];
	vals[2] = pixel[2];
	vals[3] = pixel[3];
}

//just decides between the various interpolation types
unsigned char * ArbitWarp::valueOf(float sx, float sy)
{
	static unsigned char vals[4];
	vals[0] = vals[1] = vals[2] = 0; vals[3] = 0xFF;
	switch(interpolationType)
	{
		case FILTER_NEAREST:
			nearest(sx,sy,vals);break;
		case FILTER_BILINEAR:
			bilinear(sx,sy,vals);
		case FILTER_BICUBIC:
		default:
			bicubic(sx,sy,vals);
	}
	return vals;
}