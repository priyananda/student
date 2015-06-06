// CS559 Project 2 : Quantum Coaster
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
	GRASS_TEXTURE = 0,
	SKY_EAST_TEXTURE,
	SKY_WEST_TEXTURE,
	SKY_NORTH_TEXTURE,
	SKY_SOUTH_TEXTURE,
	SKY_TOP_TEXTURE,
	CRATE_TEXTURE,
	BANNER_TEXTURE,
	LEAF_TEXTURE,
	WALL_TEXTURE,
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
	static void bind(TextureType which, TextureStretchType st = TextureStretchNone);
	static void unbind();
private:
	static void loadTextures();

	static Texture textures[TEXTURE_SIZE];
	static bool loaded;
};