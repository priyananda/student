// CS559 Project 3 : Dont Cry
// author: priyananda( shenoy@cs.wisc.edu )
// date: 20 oct 2007
// random trivia:
#pragma once

//do we use texgen or specified text coords
enum TextureStretchType
{
	TextureStretchNone = 0,
	TextureStretchHoriz = 1,
	TextureStretchVert = 2,
	TextureStretchBoth = 3
};

//hardcoded enums of all loaded textures
enum TextureType
{
	NO_TEXTURE = -1,
	CLOUD_TEXTURE,
	SUN_TEXTURE,
	CRATE_TEXTURE,
	WELCOME_SIGN_TEXTURE,
	GYRO_SIGN_TEXTURE,
	PORTAL_SIGN_TEXTURE,
	PORTAL_EXIT_SIGN_TEXTURE,
	VOLCANO_SIGN_TEXTURE,
	BUMP_SIGN_TEXTURE,
	LARA_SIGN_TEXTURE,
	LOD_SIGN_TEXTURE,
	WALL_TEXTURE,
	WALL_BUMP_TEXTURE,
	TERRAIN_TEXTURE,
	DETAIL_TEXTURE,
	WATER_TEXTURE,
	WAVE_TEXTURE,
	TEXTURE_SIZE
};

//a single texture
struct Texture
{
	int textureID;
	Texture():textureID(0){}
	void loadFrom(const char * fileName);
};

//manages textures
class TextureManager
{
public:
	//bind single texture
	static void bind(TextureType which, TextureStretchType st = TextureStretchNone);
	//bind 2 multi textures
	static void bind(TextureType which0,TextureType which1);
	static void texcoords(float u1,float v1,float u2,float v2);
	static void unbind();
	static void unbindMulti();

	static int  createTexture(const char * file);
private:
	static void loadTextures();

	static Texture textures[TEXTURE_SIZE];
	static bool loaded;
};