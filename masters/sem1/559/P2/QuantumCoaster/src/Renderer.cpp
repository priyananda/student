// CS559 Project 2 : Quantum Coaster
// author: priyananda( shenoy@cs.wisc.edu )
// date: 21 oct 2007
// random trivia:

#include "Renderer.h"
#include "Window.h"
#include "Win32Helper.h"
#include <gl/gl.h>
#include "TextureManager.h"
#include "PickableObject.h"
#include "World.h"
#include "Track.h"
#include "Train.h"

static float lightPos[] = {0,100,0,1};
static const float groundPlane[] = {0,1,0,0};//normal
GLfloat s[16];

//matrix from http://www.opengl.org/resources/code/samples/glut_examples/advanced/projshadow.c
void shadowMatrix(float fDestMat[16],const float fLightPos[4],const float fPlane[4])
{
    float dot;
    
    // dot product of plane and light position
    dot = fPlane[0] * fLightPos[0] + 
          fPlane[1] * fLightPos[1] + 
          fPlane[2] * fLightPos[2] + 
          fPlane[3] * fLightPos[3];

     // first column
    fDestMat[0] = dot - fLightPos[0] * fPlane[0];
    fDestMat[4] = 0.0f - fLightPos[0] * fPlane[1];
    fDestMat[8] = 0.0f - fLightPos[0] * fPlane[2];
    fDestMat[12] = 0.0f - fLightPos[0] * fPlane[3];

    // second column
    fDestMat[1] = 0.0f - fLightPos[1] * fPlane[0];
    fDestMat[5] = dot - fLightPos[1] * fPlane[1];
    fDestMat[9] = 0.0f - fLightPos[1] * fPlane[2];
    fDestMat[13] = 0.0f - fLightPos[1] * fPlane[3];

    // third column
    fDestMat[2] = 0.0f - fLightPos[2] * fPlane[0];
    fDestMat[6] = 0.0f - fLightPos[2] * fPlane[1];
    fDestMat[10] = dot - fLightPos[2] * fPlane[2];
    fDestMat[14] = 0.0f - fLightPos[2] * fPlane[3];

    // fourth column
    fDestMat[3] = 0.0f - fLightPos[3] * fPlane[0];
    fDestMat[7] = 0.0f - fLightPos[3] * fPlane[1];
    fDestMat[11] = 0.0f - fLightPos[3] * fPlane[2];
    fDestMat[15] = dot - fLightPos[3] * fPlane[3];
}

void Renderer::init()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);
	glHint( GL_PERSPECTIVE_CORRECTION_HINT , GL_NICEST );
	glClearColor(0,0,0,1);
	glEnableClientState(GL_VERTEX_ARRAY);	
	skyBox.setDimension(500,500,500);
	shadowMatrix(s,groundPlane,lightPos);
}

void Renderer::draw(bool runMode, bool shadows)
{
	skyBox.draw();

	if( runMode && shadows ){
		glPushMatrix();
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_TEXTURE);
		glMultMatrixf(s);
		glColor3f(0,0,0);

		World::track.draw();
		World::train1.draw(true);
		World::train2.draw(true);

		glColor3f(1,1,1);
		glColorMask(1,1,1,1);
		glEnable(GL_TEXTURE);
		glEnable(GL_DEPTH_TEST);
		glPopMatrix();
	}
	World::track.draw();
	World::drawObjects();
	if( runMode ){
		World::train1.draw(false);
		World::train2.draw(false);
	}
}

void Renderer::drawForPicking(int x,int y)
{
	PickableObjectRegistry::getObjectAt(x,y);
}