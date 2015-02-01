// CS559 Project 2 : Quantum Coaster
// author: priyananda( shenoy@cs.wisc.edu )
// date: 20 oct 2007
// random trivia:

#include "TextureManager.h"
#include <windows.h>
#include <gl/gl.h>
#include "TargaImage.h"

Texture TextureManager::textures[TEXTURE_SIZE];
bool TextureManager::loaded = false;

const char * filename[] =
{
	"grass.tga",
	"east.tga",
	"west.tga",
	"north.tga",
	"south.tga",
	"top.tga",
	"crate.tga",
	"banner.tga",
	"leaf.tga",
	"wall.tga"
};

void Texture::loadFrom(const char *fileName)
{
	TargaImage * tga = TargaImage::readImage(fileName);

	if( tga == NULL ){
		MessageBox(
			NULL,
			TEXT("Textures not found. Set Working Directory in Project->Properties->Debugging to 'bin'"),
			TEXT("Error"),
			0
		);
		exit(0);
	}
	
	glGenTextures(1, (GLuint*)(&textureID) );
	glBindTexture(GL_TEXTURE_2D, textureID );
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		tga->width(), tga->height(), 0,
		GL_RGBA, GL_UNSIGNED_BYTE, tga->pixels()
	);
}

void TextureManager::loadTextures()
{
	if(loaded) return;
	loaded = true;
	for(int i = 0; i < TEXTURE_SIZE; ++i )
		textures[i].loadFrom(filename[i]);
}

void TextureManager::bind(TextureType which, TextureStretchType t)
{
	loadTextures();

	GLint sv[4] = { 1,0,1,0 } , tv[4] = {0,1,1,0};
	
	int texid = textures[which].textureID;
	glBindTexture( GL_TEXTURE_2D , texid );
		
	if( t & TextureStretchHoriz ){
		glTexGeni( GL_S , GL_TEXTURE_GEN_MODE , GL_OBJECT_LINEAR );
		glTexGeniv( GL_S , GL_OBJECT_PLANE , sv );
		glEnable(GL_TEXTURE_GEN_S);
	}
	if( t & TextureStretchVert){
		glTexGeni( GL_T , GL_TEXTURE_GEN_MODE , GL_OBJECT_LINEAR );
		glTexGeniv( GL_T , GL_OBJECT_PLANE , tv );
		glEnable(GL_TEXTURE_GEN_T);
	}
}

void TextureManager::unbind()
{
	glBindTexture( GL_TEXTURE_2D , 0 );
	glDisable( GL_TEXTURE_GEN_S );
	glDisable( GL_TEXTURE_GEN_T );
}