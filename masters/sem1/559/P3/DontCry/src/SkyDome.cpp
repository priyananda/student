// CS559 Project 3 : Dont Cry
// author: priyananda( shenoy@cs.wisc.edu )
// date: 24 nov 2007
// random trivia:

#include <windows.h>
#include <gl/gl.h>

#define _USE_MATH_DEFINES
#include <cmath>

#include "SkyDome.h"
#include "TextureManager.h"
#include "Hero.h"
#include "World.h"
#include "Shader.h"
#include "ExtensionManager.h"
#include "DayTimer.h"
#include "Frustum.h"

void SkyDome::construct()
{
	if(vertices != NULL){
		delete [] vertices;
		vertices = NULL;
	}
	if(triangles != NULL){
		delete [] triangles;
		triangles = NULL;
	}

	verticesCount = hdetail * vdetail + 1;//one for the center
	vertices = new Vertex[verticesCount];

	trianglesCount = 2 * hdetail * vdetail - hdetail + 1;
	triangles = new Triangle[trianglesCount];
	visibleTriangles = new Triangle[trianglesCount];

	int vIndex = 1;
	int tIndex = 0;

	//incrementing horiz and vert angles
	float vAngleInc = float(0.5 * M_PI / vdetail);
	float hAngleInc = float(0.5 * M_PI / vdetail);
	const float twoPi = float(2*M_PI);
	const float piByTwo = float(M_PI/2);

	//calculate the verticeas
	vertices[0] = Vertex(0,radius,0);//right at the top
	for( float vangle = vAngleInc ; vangle <= piByTwo ; vangle += vAngleInc ){
		float ypos = radius * cosf(vangle);
		for( float angle = 0; angle < twoPi; angle += hAngleInc ){
			float xpos = (radius - ypos) * sinf(angle);
			float zpos = (radius - ypos) * cosf(angle);
			vertices[vIndex++] = Vertex(xpos,ypos,zpos);
		}
	}

	//triangle fan at the top
	for(int i = 1; i <= hdetail; ++i )
		triangles[tIndex++].set(0,i,i+1);
	triangles[tIndex++].set(0,hdetail,1);

	//strips
	for(int i = 1; i < vdetail; ++i ){
		int offset = i * hdetail + 1;
		int poffset = (i-1) * hdetail + 1;
		int j = 0;
		for(; j < hdetail - 1; ++j ){
			triangles[tIndex++].set(offset+j,poffset+j,poffset+j+1);
			triangles[tIndex++].set(poffset+j+1,offset+j+1,offset+j);
		}
		triangles[tIndex++].set(offset+j,poffset+j,poffset+1);
		triangles[tIndex++].set(poffset+1,offset+1,offset+j);
	}

	skyProgram = ShaderManager::loadProgram("common.vsh","skydome.psh");
	waterProgram = ShaderManager::loadProgram("common.vsh","water.psh");
}

inline void SkyDome::vertex(Vertex & v)
{
	v.s1 = (v.x + cloudTextureDisp)/radius;
	v.t1 = v.z/radius;
	v.s2 = v.x/radius;
	v.t2 = (v.z + sunTextureDisp)/radius;
}

static void drawp(const Plane & p)
{
	glColor3ub(255,255,255);
	glBegin(GL_LINE);
		glVertex3fv((float *)&p.point);
		Point x = p.normal * -10 + p.point;
		glVertex3fv((float *)&x);
	glEnd();
}

void SkyDome::draw(const Frustum & c)
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	this->cull(c);

	glTranslatef(
		World::hero.location.x,
		World::hero.location.y - 300,
		World::hero.location.z
	);
	
	getColor();

	TextureManager::bind(CLOUD_TEXTURE,SUN_TEXTURE);
	ShaderManager::bindProgram(skyProgram);
	ShaderManager::setUniformVar(skyProgram,"tex1",0);
	ShaderManager::setUniformVar(skyProgram,"tex2",1);
	ShaderManager::setUniformVar(skyProgram,"time",state);

	glVertexPointer(3,GL_FLOAT,sizeof(Vertex),vertices);
	
	glActiveTextureARB(GL_TEXTURE1_ARB);
	glClientActiveTextureARB(GL_TEXTURE1_ARB);
	glTexCoordPointer(2,GL_FLOAT,sizeof(Vertex),&vertices[0].s2);
	
	glActiveTextureARB(GL_TEXTURE0_ARB);
	glClientActiveTextureARB(GL_TEXTURE0_ARB);
	glTexCoordPointer(2,GL_FLOAT,sizeof(Vertex),&vertices[0].s1);

	glDrawElements(
		GL_TRIANGLES,
		visibleTrianglesCount * 3,
		GL_UNSIGNED_INT,
		visibleTriangles
	);

	/*drawp(c.farplane);
	drawp(c.nearplane);
	drawp(c.top);
	drawp(c.bottom);
	drawp(c.right);
	drawp(c.left);*/

	TextureManager::unbindMulti();
	ShaderManager::unbind();

	glTranslatef(
		0,
		300 - World::hero.location.y,
		0
	);
	drawWater();
	glColor3ub(255,255,255);
	glPopMatrix();

	cloudTextureDisp = (cloudTextureDisp + 1) % int(radius);
}
void SkyDome::drawWater()
{
	static float offset = 0;
	static bool  up = true;

	offset += up ? .001f:-.001f;
	if(offset >= 0.5f){
		offset = 0.5f;
		up = false;
	}else if(offset <= 0){
		offset = 0;
		up = true;
	}
	ShaderManager::bindProgram(waterProgram);
	ShaderManager::setUniformVar(waterProgram,"tex1",0);
	ShaderManager::setUniformVar(waterProgram,"tex2",1);

	TextureManager::bind(WAVE_TEXTURE,WATER_TEXTURE);
	glBegin(GL_QUADS);
		TextureManager::texcoords(0,0,0,0+offset);
		glVertex3f(-radius,0,-radius);
		TextureManager::texcoords(0,1,0,1+offset);
		glVertex3f(-radius,0,radius);
		TextureManager::texcoords(1,1,1,1+offset);
		glVertex3f(radius,0,radius);
		TextureManager::texcoords(1,0,1,0+offset);
		glVertex3f(radius,0,-radius);
	glEnd();
	TextureManager::unbind();
	ShaderManager::unbind();
}

#define FIVEAM	5  * 60
#define SEVENAM 7  * 60
#define FIVEPM	17 * 60
#define SEVENPM 19 * 60

void SkyDome::getColor()
{
	unsigned char r,g,b;
	int time = World::timer.getTime();
	if(time < FIVEAM){
		r = g = b = 45;
		state = Night;
	}else if(time < SEVENAM ){
		state = Dawn;
		r = (45 * (SEVENAM - time) + 255 * ( time - FIVEAM ))/(SEVENAM - FIVEAM);
		g = b = r/2;
	}else if(time < FIVEPM ){
		r = g = b = 255;
		state = Day;
	}else if(time < SEVENPM ){
		state = Dusk;
		r = (255 * (SEVENPM - time ) + 45 * ( time - FIVEPM ))/(SEVENPM - FIVEPM);
		g = b = r/2;
	}else{
		r = g = b = 45;
		state = Night;
	}
	if(state != Night )
		sunTextureDisp = radius * ( time - FIVEAM )/(SEVENPM - FIVEAM);
	else
		sunTextureDisp = 0;
	glColor3ub(r,g,b);
}
void SkyDome::cull(const Frustum &f)
{
	visibleTrianglesCount = 0;
	for(int i = 0; i < trianglesCount; ++i )
		//if(f.cull( vertices[triangles[i].v1],vertices[triangles[i].v2],vertices[triangles[i].v3]))
		{
			visibleTriangles[visibleTrianglesCount++] = triangles[i];
			vertex(vertices[triangles[i].v1]);
			vertex(vertices[triangles[i].v2]);
			vertex(vertices[triangles[i].v3]);
		}
}