#include "FilterKernel.h"
#include "TargaImage.h"

//allocate memory for holding values
SeparableKernel::SeparableKernel(int k):FilterKernel2D(k)
{
	this->values = new int[k];
}

//deallocate the memory
SeparableKernel::~SeparableKernel()
{
	delete [] this->values;
}

//apply a separable kernel to the whole image
void SeparableKernel::convolve(TargaImage * image)
{
	int width = int(image->width());
	int height = int(image->height());
	
	//allocate buffers for RGBA. This is to temporariliy store convoluted
	//values. should be big enough for both H and V directions
	unsigned char * buffer = new unsigned char[ (width > height ? width : height) * 4 ];
	unsigned char * pixel = image->pixels();
	
	//colvolve in H direction
	for( int y = 0; y < height; ++y ){
		unsigned char * rp = pixel + 4 * y * width;
		convolveRow( rp , width , height, buffer );
		//copy from buffer to source
		for( int x = 0; x < 4 * width; ++x )
			rp[x] = buffer[x];
	}
	
	//convolve in V direction
	for( int x = 0; x < width; ++x ){
		unsigned char * cp = pixel + 4 * x;
		convolveCol( pixel + 4 * x , width, height , buffer );
		//copy from buffer to source
		for( int y = 0; y < 4 * height; cp += 4 * width, y += 4){
			cp[0] = buffer[y+0];
			cp[1] = buffer[y+1];
			cp[2] = buffer[y+2];
			cp[3] = buffer[y+3];
		}
	}

	//deallocate the buffers
	delete [] buffer;
}

//apply a separable kernel filter on a single row
//the output goes to buffer
void SeparableKernel::convolveRow(unsigned char *pixel, int width, int height, unsigned char *buffer)
{
	//number of elements on left/top side of the origin
	int left = (k % 2 ? k : (k-1)) / 2;
	//number of elements on right/bottom side of the origin
	int right = k - left -1;

	for( int x = 0; x < width; ++x,buffer += 4,pixel += 4){
		int r = 0 ,g = 0 ,b = 0 ,a = 0;
		int count = 0;
		for( int i = -left; i <= right; ++i )
			if( x + i > -1 && x + i < width ){
				r += values[i+left] * (pixel + 4 * i)[0];
				g += values[i+left] * (pixel + 4 * i)[1];
				b += values[i+left] * (pixel + 4 * i)[2];
				a += values[i+left] * (pixel + 4 * i)[3];
				count += values[i+left];
			}
		if( count > 0){
			buffer[0] = unsigned char(r/count);
			buffer[1] = unsigned char(g/count);
			buffer[2] = unsigned char(b/count);
			buffer[3] = unsigned char(a/count);	
		}
	}
}

//apply a separable kernel filter on a single row
//the output goes to buffer
void SeparableKernel::convolveCol(unsigned char *pixel, int width, int height, unsigned char *buffer)
{
	//number of elements on left/top side of the origin
	int left = (k % 2 ? k : (k-1)) / 2;
	//number of elements on right/bottom side of the origin
	int right = k - left -1;

	for( int y = 0; y < height; ++y, buffer += 4,pixel += 4 * width ){
		int r = 0 ,g = 0 ,b = 0 ,a = 0, count = 0;
		for( int j = -left; j <= right; ++j )
			if( y + j > -1 && y + j < height ){
				r += values[j+left] * (pixel + 4 * width * j)[0];
				g += values[j+left] * (pixel + 4 * width * j)[1];
				b += values[j+left] * (pixel + 4 * width * j)[2];
				a += values[j+left] * (pixel + 4 * width * j)[3];
				count += values[j+left];
			}
		if(count > 0 ){
			buffer[0] = unsigned char(r/count);
			buffer[1] = unsigned char(g/count);
			buffer[2] = unsigned char(b/count);
			buffer[3] = unsigned char(a/count);	
		}
	}
}

//special convolution for upsampling.
void SeparableKernel::convolve(TargaImage * source,TargaImage * dest,int xfactor,int yfactor)
{
	int height = int(source->height());
	int width = int(source->width());
	int nheight = int(dest->height());
	int nwidth = int(dest->width());
	//number of elements on left/top side of the origin
	int left = (k % 2 ? k : (k-1)) / 2;
	//number of elements on right/bottom side of the origin
	int right = k - left -1;

	unsigned char * srcPixels = source->pixels();
	unsigned char * destPixels = dest->pixels();

	//in the H direction
	for( int y = 0 ; y < nheight; ++y )
		//convolve the row
		for( int x = 0 ; x < nwidth; ++x ){
			int r = 0 ,g = 0 ,b = 0 ,a = 0, count = 0;
			for( int i = -left; i <= right; ++i )
				if( x + i > -1 && x + i < nwidth ){
					int sx = x / xfactor;
					int sy = y / yfactor;
					r += values[i+left] * srcPixels[4 * ( width * sy + sx ) + 0];
					g += values[i+left] * srcPixels[4 * ( width * sy + sx ) + 1];
					b += values[i+left] * srcPixels[4 * ( width * sy + sx ) + 2];
					a += values[i+left] * srcPixels[4 * ( width * sy + sx ) + 3];
					count += values[i+left];
				}
			destPixels[4 * (nwidth * y + x ) + 0] = unsigned char(r/count);
			destPixels[4 * (nwidth * y + x ) + 1] = unsigned char(g/count);
			destPixels[4 * (nwidth * y + x ) + 2] = unsigned char(b/count);
			destPixels[4 * (nwidth * y + x ) + 3] = unsigned char(a/count);
		}

	for( int x = 0 ; x < nwidth; ++x )
		for( int y = 0 ; y < nheight; ++y ){
			int r = 0 ,g = 0 ,b = 0 ,a = 0, count = 0;
			for( int j = -left; j <= right; ++j )
				if( y + j > -1 && y + j < nheight ){
					int sx = x / xfactor;
					int sy = y / yfactor;
					r += values[j+left] * srcPixels[4 * ( width * sy + sx ) + 0];
					g += values[j+left] * srcPixels[4 * ( width * sy + sx ) + 1];
					b += values[j+left] * srcPixels[4 * ( width * sy + sx ) + 2];
					a += values[j+left] * srcPixels[4 * ( width * sy + sx ) + 3];
					count += values[j+left];
				}
			destPixels[4 * (nwidth * y + x ) + 0] = unsigned char(r/count);
			destPixels[4 * (nwidth * y + x ) + 1] = unsigned char(g/count);
			destPixels[4 * (nwidth * y + x ) + 2] = unsigned char(b/count);
			destPixels[4 * (nwidth * y + x ) + 3] = unsigned char(a/count);
		}
}