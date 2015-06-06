// CS559 Project 3 : Dont Cry
// author: priyananda( shenoy@cs.wisc.edu )
// date: 11 dec 2007
// random trivia:

#include "SweepObject.h"

#include <fstream>
using std::ifstream;
#include <vector>
using std::vector;
#define _USE_MATH_DEFINES
#include <cmath>
#include <windows.h>
#include <gl/gl.h>
#include "World.h"
#include "Hero.h"

//most of this taken from project 2
static const float BSPLINE_BASIS[4][4] =
{
	{ 1.0f/6.0f,	2.0f/3.0f,	1.0f/6.0f,	0			},
	{-1.0f/2.0f,	0,			1.0f/2.0f,	0			},
	{ 1.0f/2.0f,	-1,			1.0f/2.0f,	0			},
	{-1.0f/6.0f,	1.0f/2.0f,	-1.0f/2.0f,	1.0f/6.0f	}
};

//evaulates a point on the bspline curve
static Point eval(float u,
	Point & cp0,Point & cp1,
	Point & cp2,Point & cp3)
{
	const Point pn[] = {cp0,cp1,cp2,cp3};
	Point coeffs[4];

	for( int i = 0 ; i < 4; ++i ){
		coeffs[i] = 0;
		for( int j = 0 ; j < 4; ++j ){
			coeffs[i].x += BSPLINE_BASIS[i][j] * pn[j].x;
			coeffs[i].y += BSPLINE_BASIS[i][j] * pn[j].y;
			coeffs[i].z += BSPLINE_BASIS[i][j] * pn[j].z;
		}
	}

	//f(x) = a0 + a1 u + a2 u^2 + a3 u^3
	Point p;
	p.x = coeffs[0].x + coeffs[1].x * u + coeffs[2].x * u * u + coeffs[3].x * u * u * u;
	p.y = coeffs[0].y + coeffs[1].y * u + coeffs[2].y * u * u + coeffs[3].y * u * u * u;
	p.z = coeffs[0].z + coeffs[1].z * u + coeffs[2].z * u * u + coeffs[3].z * u * u * u;
	return p;
}

//sample the bspline at certain intervals
static void fillPoints(list< Point >& points,
	Point & cp0,Point & cp1,
	Point & cp2,Point & cp3)
{
	for(float u = 0 ; u <= 1.0f; u += .2f )
		points.push_back(eval(u,cp0,cp1,cp2,cp3));
}

//read the file to get control Points
SweepObject::SweepObject(float x,float y,float z,const char *filename)
{
	location.x = x;
	location.y = y;
	location.z = z;

	vector< Point > controlpoints;
	char buffer[255];
	ifstream f(filename);
	while(f.good()){
		f.getline(buffer,254);
		if(buffer[0] == '#')
			continue;
		sscanf_s(buffer,"%f %f",&x,&y);
		controlpoints.push_back(Point(x,y,0));
	}
	f.close();

	list< Point > points;
	for(int i = 0; i < int(controlpoints.size()) - 3; ++i)
		fillPoints(points,controlpoints[i],controlpoints[i+1],controlpoints[i+2],controlpoints[i+3]);
	
	vertices = new Point[points.size()*20];
	verticesCount = 0;

	float angleInc = float(M_PI/10);
	float twoPi = float(2*M_PI);

	for(list< Point >::iterator iter = points.begin(); iter != points.end();++iter){
		for(float angle = 0; angle < twoPi; angle += angleInc ){
			vertices[verticesCount].x = location.x + sinf(angle) * (*iter).y;
			vertices[verticesCount].y = location.y + (*iter).x;
			vertices[verticesCount].z = location.z + cosf(angle) * (*iter).y;
			++verticesCount;
		}
	}
	//3 levels of resolution
	generateTriangles(points,highResTrianglesCount,highResTriangles,1);
	generateTriangles(points,mediumResTrianglesCount,mediumResTriangles,3);
	generateTriangles(points,lowResTrianglesCount,lowResTriangles,6);
}
void SweepObject::generateTriangles(list< Point >& points, int & size,Triangle * & ptr,int res)
{
	size = int(2 * (points.size()/res  - 1) * 20);
	ptr  = new Triangle[size];
	int tIndex = 0;
	
	for(int i = res; i < int(points.size()); i += res ){
		int offset = i * 20;
		int poffset = (i-res) * 20;
		int j = 0;
		for(; j < 20 - 1; ++j ){
			ptr[tIndex++].set(offset+j,poffset+j,poffset+j+1);
			ptr[tIndex++].set(poffset+j+1,offset+j+1,offset+j);
		}
		ptr[tIndex++].set(offset+j,poffset+j,poffset+1);
		ptr[tIndex++].set(poffset+1,offset+1,offset+j);
	}
}
void SweepObject::draw()
{
	//fill mode looks bland .. cant make out anything
	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	glColor3ub(255,255,255);
	glVertexPointer(3,GL_FLOAT,sizeof(Point),vertices);

	float d2 = location.distance(World::hero.location);
	if(d2 <= 50)
		glDrawElements(
			GL_TRIANGLES,
			highResTrianglesCount * 3,
			GL_UNSIGNED_INT,
			highResTriangles
		);
	else if( d2 <= 70)
		glDrawElements(
			GL_TRIANGLES,
			mediumResTrianglesCount * 3,
			GL_UNSIGNED_INT,
			mediumResTriangles
		);
	else
		glDrawElements(
			GL_TRIANGLES,
			lowResTrianglesCount * 3,
			GL_UNSIGNED_INT,
			lowResTriangles
		);
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
}