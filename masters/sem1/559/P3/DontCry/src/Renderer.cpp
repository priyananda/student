// CS559 Project 3 : Dont Cry
// author: priyananda( shenoy@cs.wisc.edu )
// date: 21 oct 2007
// random trivia:

#include "Renderer.h"
#include "Window.h"
#include "Win32Helper.h"
#include <gl/gl.h>
#include "TextureManager.h"
#include "World.h"
#include "Cave.h"
#include "Frustum.h"
#include "glext.h"
#include "ExtensionManager.h"

//inits all required opengl stuff
void Renderer::init()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);
	glHint( GL_PERSPECTIVE_CORRECTION_HINT , GL_NICEST );
	glClearColor(0,0,0,1);
	glEnableClientState(GL_VERTEX_ARRAY);
	
	//this was a big gotcha. I had previously used
	//glActiveTextureARB which doesn't work for arrays
	glClientActiveTextureARB(GL_TEXTURE1_ARB);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	
	glClientActiveTextureARB(GL_TEXTURE0_ARB);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	
	skyDome.setDimension(800,10);
	enableFog();
}

void Renderer::draw(Frustum & f)
{
	if(World::cavemode){
		World::cave.drawWalls();
		World::cave.drawObjects();
	}else{
		skyDome.draw(f);
		World::heightMap.draw();
		World::drawObjects();
	}
}

void Renderer::enableFog()
{
	float fogColor[] = {0.8f,0,0,1.0f};
	glEnable(GL_FOG);
	glFogi(GL_FOG_MODE, GL_LINEAR);
	glFogfv(GL_FOG_COLOR,fogColor );
	glFogf(GL_FOG_START,  0.0f);
	glFogf(GL_FOG_END,    1.0f);
	glHint(GL_FOG_HINT, GL_NICEST);
	glFogi(GL_FOG_COORDINATE_SOURCE_EXT, GL_FOG_COORDINATE_EXT);
}