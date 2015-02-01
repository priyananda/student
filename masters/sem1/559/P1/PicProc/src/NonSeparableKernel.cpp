#include "FilterKernel.h"
#include "TargaImage.h"

//allocate a 2D array
NonSeparableKernel::NonSeparableKernel(int k):FilterKernel2D(k)
{
	//array of arrays
	this->values = new int*[k];
	for(int i = 0;i < k; ++i )
		this->values[i] = new int[k];
}
//delete allocated memory
NonSeparableKernel::~NonSeparableKernel()
{
	for(int i = 0;i < k; ++i )
		delete [] this->values[i];
	delete [] this->values;
}

void NonSeparableKernel::convolve(TargaImage * image)
{
	//number of elements on left/top side of the origin
	int left = (k % 2 ? k : (k-1)) / 2;
	//number of elements on right/bottom side of the origin
	int right = k - left -1;
	int height = int(image->height());
	int width = int(image->width());

	unsigned char * buffer = new unsigned char[4 * width * height];
	unsigned char * pixels = image->pixels();

	for(int y = 0 ; y < height; ++y )
		for( int x = 0; y < width; ++ x){
			int r = 0, g = 0, b = 0, a = 0, count = 0;
			for( int i = -left; i <= right; ++i )
				for( int j = -left; j <= right; ++j )
					if( x + i > -1 && x + i < width )
						if( y + j > -1 && y + j < height ){
							unsigned char * pixel = image->pixel(i+x,y+j);
							r += values[i+left][j+left] * pixel[0];
							g += values[i+left][j+left] * pixel[1];
							b += values[i+left][j+left] * pixel[2];
							a += values[i+left][j+left] * pixel[3];
							count += values[i+left][j+left];
						}
			(buffer + 4 * ( width * y + x))[0] = unsigned char(r/count);
			(buffer + 4 * ( width * y + x))[1] = unsigned char(g/count);
			(buffer + 4 * ( width * y + x))[2] = unsigned char(b/count);
			(buffer + 4 * ( width * y + x))[3] = unsigned char(a/count);
		}
	int size = width * height * 4;
	while(size-- > 0)
		*pixels++ = *buffer++;

	delete [] buffer;
}