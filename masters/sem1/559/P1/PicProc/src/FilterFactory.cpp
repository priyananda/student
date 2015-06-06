#include "FilterKernel.h"

#ifndef _USE_MATH_DEFINES
	#define _USE_MATH_DEFINES // to get PI
#endif
#include <cmath>


//A 2D b-spline kernel.
//eg: k=3
//     | 1 2 1 |
// 1/16| 2 4 2 |
//     | 1 2 1 |
FilterKernel2D * FilterFactory::createBSpline(int k)
{
	SeparableKernel * kernel = new SeparableKernel(k);
	int c = 1;
	//filling the row with binomial coefficients
	for (int i = 0; i < k; i++){
		kernel->values[i] = c;
		c = c *(k - i - 1) / (i + 1);
	}
	return kernel;
}

//A 2D box kernel.
//eg: k=3 
//     | 1 1 1 |
// 1/9 | 1 1 1 |
//     | 1 1 1 |
FilterKernel2D * FilterFactory::createBox(int k)
{
	SeparableKernel * kernel = new SeparableKernel(k);
	for(int i = 0 ; i < k; ++i)
		kernel->values[i] = 1;
	return kernel;
}

//create a gaussian filter with width k and standard deviation sd
//Eg: width = 5,sd = 1
// gaussian is given by g(x) = 1/(sd sqrt(2pi)) exp( - x^2 / 2 sd^2 )
//			|135	606		1000	606		135		|
//			|81810	367236	606000	367236	81810	|
//1/6160324	|135000	606000	1000000 606000	135000	|
//			|81810	367236	606000	367236	81810	|
//			|18225	81810	135000	81810	18225	|
FilterKernel2D * FilterFactory::createGaussian(int width,float sd)
{
	SeparableKernel * kernel = new SeparableKernel(width);
	int mid = width / 2;
	int samples = width / 2 + 1;
	if(width%2)
		kernel->values[mid++] = int( M_E * 100 );
	for( int i = 0; i < samples - 1 ; ++i )
	{
		float x = 3.0f * sd * (i + 1) / samples;
		float val = expf(float(- ( x * x ) / 2.0 * sd * sd));
		//100 means 2 decimal place precision
		kernel->values[mid + i] = int(val * 100);
	}
	for( int i = 0 ; i < width / 2 ; ++i )
		kernel->values[i] = kernel->values[width-i-1];
	return kernel;
}
//creates a Lanczos2 windowed sinc kernel
//L(x) = sin( pi * x ) sin ( pi * x / 2 )/( x * x / 2 );
FilterKernel2D * FilterFactory::createSinc(int width)
{
	SeparableKernel * kernel = new SeparableKernel(width);
	int mid = width / 2;
	int samples = width / 2 + 1;
	if(width % 2)
		kernel->values[mid++] = 100;
	for( int i = 0; i < samples - 1 ; ++i ){
		float x = 2.0f * (i+1) / samples;
		float val = float( sin( M_PI * x ) * sin( M_PI_2 * x ) / x * x );
		//100 means 2 decimal place precision
		kernel->values[mid + i] = int(val * 100);
	}
	for( int i = 0 ; i < width / 2 ; ++i )
		kernel->values[i] = kernel->values[width-i-1];
	return kernel;
}

FilterKernel2D * FilterFactory::createBicubic(int k)
{
	//todo: do this
	return 0;
}