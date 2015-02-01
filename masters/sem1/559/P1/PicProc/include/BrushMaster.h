// CS559 Project 1 : Picture Processor
// author: priyananda( shenoy@cs.wisc.edu )
// date: 7 oct 2007
// random quote: [300] Leonidas: Tonight we dine in hell.

#include "TargaImage.h"
#include <cstdlib>

//manages brushes required for painting
class BrushMaster
{
public:
	//depends on sbrushes.tga!!!
	static const int NUMBER_OF_BRUSHES = 24;
	static const int BRUSHES_PER_ROW = 8;
	static const int BRUSH_WIDTH  = 24;
	
	static int getRandomBrush()
	{
		return rand() % NUMBER_OF_BRUSHES;
	}
	static unsigned char getBrushPixel(int brushNo,int i,int j)
	{
		int row = brushNo / BRUSHES_PER_ROW;
		int col = brushNo % BRUSHES_PER_ROW;
		return brushes->pixel( col * BRUSH_WIDTH + i , row * BRUSH_WIDTH + j )[3];
	}
	static bool initialize()
	{
		if( brushes == 0 ){
			brushes = TargaImage::readImage("sbrushes.tga");
			if(brushes == 0)
				return false;
		}
		return true;
	}
private:
	static TargaImage * brushes;
};