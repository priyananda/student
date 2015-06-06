// CS559 Project 1 : Picture Processor
// author: priyananda( shenoy@cs.wisc.edu )
// date: 15 sep 2007
// random quote: []
#include "Che.h"
#include "Extractor.h"
#include "TargaImage.h"
#include "SymbolTable.h"

bool Che::extract(const CommandLine & c)
{
	if( Extractor::checkArguments(c,errorString,1) &&
		Extractor::extractVariable(c,0,errorString,image)){
		varName = c[0][0];
		return true;
	}
	return false;
}

//maps background,dark and light colors for every quadrant
//why these colors? Ask Andy Warhol
int color[9][9] =
{
	{255,255,0,		0,0,0x6B,		0,0xAA,0 },
	{0,0,255,		0xE8,2,0x7C,	255,255,0 },
	{0,0,0x6B,		0xE3,8,0x1C,	0xF3,0x97,0xE6 },
	{0xF0,0xA2,7,	0x77,0x42,0x92,	0x7D,0xBB,0xF4 },
	{255,0,0,		0,0,0,			255,255,255 },
	{0x8A,0xB7,4,	0xEE,0x68,7,	255,0xFB,0xA0 },
	{0x24,0x6D,0x64,0xE3,3,0x76,	255,255,255 },
	{255,0xFB,9,	0xE9,0x22,0x27,	0x99,0xbe,0x33 },
	{0xE5,5,0x7F,	0x30,0x22,0x81,	0xEB,0x73,5 }
};

//changes the color depending on which quadrant we are in.
static void change(unsigned char * to,unsigned char * from, int i,int j)
{
	int num = 3 * j + i;
	to[3] = 255;
	if(from[3] == 0 ){
		to[0] = color[num][0];
		to[1] = color[num][1];
		to[2] = color[num][2];
	}else{
		int gray = (from[0]+from[2]+from[1])/3;
		if( gray < 140 ){
			to[0] = color[num][3];
			to[1] = color[num][4];
			to[2] = color[num][5];
		}else{
			to[0] = color[num][6];
			to[1] = color[num][7];
			to[2] = color[num][8];
		}
	}
}

//called for each quadrant. copies pixel by pixel
void Che::warholify(int i, int j)
{
	int width = (int)image->width();
	int height = (int)image->height();
	int xoffset = i * width;
	int yoffset = j * height;
	for( int y = 0 ; y < height; ++y ){
		unsigned char * to = dest->pixel(xoffset,y+yoffset);
		unsigned char * from = image->pixel(0,y);
		for( int x = 0 ; x < 4 * width; x += 4)
			change(to+x,from+x,i,j);
	}
}

//to see what this does, u need to have the andy warhol picture.
void Che::execute()
{
	dest = TargaImage::blankImage( 3 * image->width(), 3 * image->height() );
	for( int i = 0 ; i < 3 ; ++i )
		for( int j = 0 ; j < 3 ; ++j )
			warholify(i,j);
	SymbolTable::setSymbol(varName,dest);
}