// CS559 Project 3 : Dont Cry
// author: priyananda( shenoy@cs.wisc.edu )
// date: 20 oct 2007
// random trivia:

#include "TextureManager.h"
#include <windows.h>
#include <gl/gl.h>
#include "TargaImage.h"
#include "ExtensionManager.h"

Texture TextureManager::textures[TEXTURE_SIZE];
bool TextureManager::loaded = false;

const char * filename[] =
{
	"cloud.tga",
	"sun.tga",
	"crate.tga",
	"welcome.tga",
	"gyro.tga",
	"portal.tga",
	"portalexit.tga",
	"volcano.tga",
	"bump.tga",
	"lara.tga",
	"lodsign.tga",
	"rock.tga",
	"rockbump.tga",
	"terrain.tga",
	"detail.tga",
	"water.tga",
	"wateranim.tga"
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

	glEnable(GL_TEXTURE_2D);
}

void TextureManager::bind(TextureType which0, TextureType which1)
{
	loadTextures();

	int texid0 = textures[which0].textureID;
	int texid1 = textures[which1].textureID;

	glActiveTextureARB(GL_TEXTURE0_ARB);
	glBindTexture( GL_TEXTURE_2D ,texid0);

	glActiveTextureARB(GL_TEXTURE1_ARB);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,texid1);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE_EXT);
	glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE0_RGB_EXT, GL_PREVIOUS_EXT);
	glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND0_RGB_EXT, GL_SRC_COLOR);
	glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_RGB_EXT, GL_MODULATE);
	glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE1_RGB_EXT, GL_TEXTURE);
	glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND1_RGB_EXT, GL_SRC_COLOR);
	glTexEnvf(GL_TEXTURE_ENV, GL_RGB_SCALE_EXT, 2.0f);
}
void TextureManager::unbindMulti()
{
	glActiveTextureARB(GL_TEXTURE1_ARB);
	glBindTexture(GL_TEXTURE_2D,0);
	glDisable(GL_TEXTURE_2D);

	glActiveTextureARB(GL_TEXTURE0_ARB);
	glBindTexture(GL_TEXTURE_2D,0);
}
void TextureManager::texcoords(float u1, float v1, float u2, float v2)
{
	glMultiTexCoord2fARB(GL_TEXTURE0_ARB, u1,v1);
	glMultiTexCoord2fARB(GL_TEXTURE1_ARB, u2,v2);
}
int TextureManager::createTexture(const char * filename)
{
	Texture t;
	t.loadFrom(filename);
	return t.textureID;
}