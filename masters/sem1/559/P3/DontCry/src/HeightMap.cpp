// CS559 Project 3 : Dont Cry
// author: priyananda( shenoy@cs.wisc.edu )
// date: 24 nov 2007
// random trivia:
#include "HeightMap.h"
#include "TargaImage.h"
#include "TextureManager.h"
#include <windows.h>
#include <gl/gl.h>

//expand the image 10 times in the x and z directions
#define PIXEL_TO_POINT 10.0f
//max height becomes 255/2 = 127
#define PIXEL_TO_HEIGHT (0.5f);

void HeightMap::loadFrom(const char * filename){
	TargaImage * tga = TargaImage::readImage(filename);
	
	if( vertices != 0 ){
		for(int i = 0; i < rowCount; ++i )
			delete [] vertices[i];
		delete [] vertices;
		vertices = 0;
	}
	vertices = new Point*[rowCount = tga->height()];
	colCount = tga->width();
	float lowest = 256 * PIXEL_TO_HEIGHT;
	for(int i = 0; i < rowCount; ++i ){
		vertices[i] = new Point[colCount];
		for(int j = 0 ; j < colCount; ++j ){
			vertices[i][j].x = (j - colCount/2) * PIXEL_TO_POINT;
			vertices[i][j].y = *(tga->pixel(j,i)) * PIXEL_TO_HEIGHT;
			vertices[i][j].z = (i - rowCount/2) * PIXEL_TO_POINT;
			if( vertices[i][j].y < lowest )
				lowest = vertices[i][j].y;
		}
	}
	lowest += 5;
	for(int i = 0; i < rowCount; ++i )
		for(int j = 0 ; j < colCount; ++j )
			vertices[i][j].y -= lowest;
}

#include "ExtensionManager.h"
void HeightMap::vertex(const Point &v, float s2,float t2){
	float s = v.x + colCount * PIXEL_TO_POINT / 2;
	s /= colCount * PIXEL_TO_POINT;
	float t = v.z + rowCount * PIXEL_TO_POINT / 2;
	t /= rowCount * PIXEL_TO_POINT;
	if(v.y > 112.0f)
		//this is in the volcano
		glFogCoordfEXT(0.6f);
	else
		glFogCoordfEXT(0);
	TextureManager::texcoords(s,t,s2,t2);
	glVertex3fv((float*)&v);
}

void HeightMap::draw()
{
	TextureManager::bind(TERRAIN_TEXTURE,DETAIL_TEXTURE);
	for(int i = 0; i < rowCount - 1; ++i ){
		glBegin(GL_TRIANGLE_STRIP);
		for(int j = 0 ; j < colCount - 1; ++j ){
			vertex(vertices[i][j],0,0);
			vertex(vertices[i+1][j],1,0);
			vertex(vertices[i][j+1],1,1);
			vertex(vertices[i+1][j+1],0,1);
		}
		glEnd();
	}
	TextureManager::unbindMulti();
}

float HeightMap::getHeight(float x, float z)
{
	x /= PIXEL_TO_POINT;
	z /= PIXEL_TO_POINT;
	
	z += rowCount/2;
	x += colCount/2;
	
	if( z < 0 || z >= rowCount - 1||
		x < 0 || x >= colCount - 1)
		return 0;

	int   ix = int(x);
	int   iz = int(z);
	float dx = x - ix;
	float dz = z - iz;

	return
		vertices[iz][ix].y * ( 1 - dx ) * ( 1 - dz )+
		vertices[iz+1][ix].y * (1 - dx ) * (dz )+
		vertices[iz][ix+1].y * (dx ) * (1 - dz )+
		vertices[iz+1][ix+1].y * (dx) * (dz);
}