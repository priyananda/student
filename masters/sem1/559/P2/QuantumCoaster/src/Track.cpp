// CS559 Project 2 : Quantum Coaster
// author: priyananda( shenoy@cs.wisc.edu )
// date: oct 2007
// random trivia:
#include "Track.h"
#include "windows.h"
#include <gl/gl.h>
#include "PickableObject.h"
#include "Cube.h"
#include "TextureManager.h"
#include <cmath>

static const float BSPLINE_BASIS[4][4] =
{
	{ 1.0f/6.0f,	2.0f/3.0f,	1.0f/6.0f,	0			},
	{-1.0f/2.0f,	0,			1.0f/2.0f,	0			},
	{ 1.0f/2.0f,	-1,			1.0f/2.0f,	0			},
	{-1.0f/6.0f,	1.0f/2.0f,	-1.0f/2.0f,	1.0f/6.0f	}
};

Track::Track():
	editMode(false),
	curvePoints(0),railPoints(0),alpPoints(0),
	curvePointsCount(0),railPointsCount(0),alpPointsCount(0),
	qCurvePoints(0),qRailPoints(0),qAlpPoints(0),
	qCurvePointsCount(0),qRailPointsCount(0),qAlpPointsCount(0),
	qStartS(0),qEndS(0),speedRatio(1.0f)
{
}

void Track::draw()
{
	int cpcount = int(controls.size());
	int qpcount = int(qcontrols.size());

	if( editMode ){
		for( int i = 0 ; i < cpcount; ++i ){
			controls[i]->draw();
			drawSegment(
				*controls[i],
				*controls[( i + 1 ) % cpcount ],
				*controls[( i + 2 ) % cpcount ],
				*controls[( i + 3 ) % cpcount ]
			);
		}
		if( qcontrols.size() > 0 )
			for( int i = 0 ; i < qpcount - 3; ++i ){
				qcontrols[i]->draw();
				drawSegment(
					*qcontrols[i],
					*qcontrols[i + 1],
					*qcontrols[i + 2],
					*qcontrols[i + 3]
				);
			}
		glColor3f(1,1,1);
	}
	else{
		drawPointArray();
	}
}

void Track::drawSegment(const ControlPoint & p0,const ControlPoint & p1,const ControlPoint & p2,const ControlPoint & p3)
{
	CurvePoint p;
	glColor3ub(0,0,0);
	glLineWidth(3);
 	glBegin(GL_LINE_STRIP);
	for( float u = 0 ; u <= 1 ; u += .01f ){
		getPointInCurve(u,p0,p1,p2,p3,p);
		glVertex3f(p.x,p.y,p.z);
	}
	glLineWidth(1);
	glEnd();
}

void Track::getPointInCurve(float u, const ControlPoint &p0, const ControlPoint &p1, const ControlPoint &p2, const ControlPoint &p3, CurvePoint & p)
{
	//X = u B P
	const ControlPoint pn[] = {p0,p1,p2,p3};
	Point coeffs[4];

	for( int i = 0 ; i < 4; ++i ){
		coeffs[i] = 0;
		for( int j = 0 ; j < 4; ++j ){
			coeffs[i].x += BSPLINE_BASIS[i][j] * pn[j].location.x;
			coeffs[i].y += BSPLINE_BASIS[i][j] * pn[j].location.y;
			coeffs[i].z += BSPLINE_BASIS[i][j] * pn[j].location.z;
		}
	}

	//f(x) = a0 + a1 u + a2 u^2 + a3 u^3
	p.x = coeffs[0].x + coeffs[1].x * u + coeffs[2].x * u * u + coeffs[3].x * u * u * u;
	p.y = coeffs[0].y + coeffs[1].y * u + coeffs[2].y * u * u + coeffs[3].y * u * u * u;
	p.z = coeffs[0].z + coeffs[1].z * u + coeffs[2].z * u * u + coeffs[3].z * u * u * u;
	
	//f'(x) = a1 + a2 2u + a3 3u^t
	p.dx = coeffs[1].x + coeffs[2].x * 2 * u + coeffs[3].x * 3 * u * u;
	p.dy = coeffs[1].y + coeffs[2].y * 2 * u + coeffs[3].y * 3 * u * u;
	p.dz = coeffs[1].z + coeffs[2].z * 2 * u + coeffs[3].z * 3 * u * u;

	//for( int i = 0 ; i < 4; ++i ){
	//	coeffs[i] = 0;
	//	for( int j = 0 ; j < 4; ++j ){
	//		coeffs[i].x += BSPLINE_BASIS[i][j] * pn[j].up.x;
	//		coeffs[i].y += BSPLINE_BASIS[i][j] * pn[j].up.y;
	//		coeffs[i].z += BSPLINE_BASIS[i][j] * pn[j].up.z;
	//	}
	//}

	////p.ux = coeffs[0].x + coeffs[1].x * u + coeffs[2].x * u * u + coeffs[3].x * u * u * u;
	//p.uy = coeffs[0].y + coeffs[1].y * u + coeffs[2].y * u * u + coeffs[3].y * u * u * u;
	//p.uz = coeffs[0].z + coeffs[1].z * u + coeffs[2].z * u * u + coeffs[3].z * u * u * u;
}

CurvePoint lerp(CurvePoint & s1,CurvePoint & s2,float s)
{
	if( s > s2.s || s < s1.s )
		s = s;
	float factor = ( s - s1.s ) / (s2.s - s1.s);
	CurvePoint ret;
	ret.x = ( 1 - factor ) * s1.x + factor * s2.x;
	ret.y = ( 1 - factor ) * s1.y + factor * s2.y;
	ret.z = ( 1 - factor ) * s1.z + factor * s2.z;
	ret.dx = ( 1 - factor ) * s1.dx + factor * s2.dx;
	ret.dy = ( 1 - factor ) * s1.dy + factor * s2.dy;
	ret.dz = ( 1 - factor ) * s1.dz + factor * s2.dz;
	ret.ux = ( 1 - factor ) * s1.ux + factor * s2.ux;
	ret.uy = ( 1 - factor ) * s1.uy + factor * s2.uy;
	ret.uz = ( 1 - factor ) * s1.uz + factor * s2.uz;
	ret.s = s;
	return ret;
}

void Track::pointify()
{
	if( curvePoints != NULL )
		delete [] curvePoints;
	if( railPoints != NULL )
		delete [] railPoints;
	if( alpPoints != NULL )
		delete [] alpPoints;
	
	int cpcount = int(controls.size());

	curvePoints = new CurvePoint[ cpcount * 400 ];
	curvePointsCount = 0;

	for( int i = 0 ; i < cpcount; ++i ){
		ControlPoint & p0 = *controls[i],
			& p1 = *controls[(i+1)% cpcount],
			& p2 = *controls[(i+2)% cpcount],
			& p3 = *controls[(i+3)% cpcount];
		for(float u = 0 ; u <= 1.0f; u += 0.01f ){
			getPointInCurve(u,p0,p1,p2,p3,curvePoints[curvePointsCount]);
			if(curvePointsCount == 0){
				curvePoints[curvePointsCount].s = 0;
				curvePoints[curvePointsCount].ux = 0;
				curvePoints[curvePointsCount].uy = 1;
				curvePoints[curvePointsCount].uz = 0;
			}else{
				curvePoints[curvePointsCount].s =
					curvePoints[curvePointsCount-1].s + 
					curvePoints[curvePointsCount].distance(curvePoints[curvePointsCount-1]);
				calculateUpVector(
					curvePoints[curvePointsCount],
					curvePoints[curvePointsCount-1]
				);
			}
			curvePointsCount++;
		}
	}

	alpPoints  = new CurvePoint[ (int)curvePoints[curvePointsCount-1].s  + 1];
	railPoints = new Point[ ((int)curvePoints[curvePointsCount-1].s) / 2 + 2];
	alpPointsCount = 1;
	railPointsCount = 1;

	alpPoints[0] = curvePoints[0];
	calculateRailPoints(alpPoints[0],railPoints[0],railPoints[1]);

	float currs = 0;
	int i = 1;

	while(i < curvePointsCount){
		if( currs + 1.0f < curvePoints[i].s ){
			alpPoints[alpPointsCount] = lerp(curvePoints[i],curvePoints[i-1],++currs);
			if( alpPointsCount % 4 == 0 ){
				calculateRailPoints(
					alpPoints[alpPointsCount],
					railPoints[2 * railPointsCount],
					railPoints[2 * railPointsCount+1]
				);
				++railPointsCount;
			}
			++alpPointsCount;
		}else{
			++i;
		}
	}
}

void Track::qpointify()
{
	if( qCurvePoints != NULL )
		delete [] qCurvePoints;
	if( qRailPoints != NULL )
		delete [] qRailPoints;
	if( qAlpPoints != NULL )
		delete [] qAlpPoints;

	qCurvePoints = NULL;
	qRailPoints = NULL;
	qAlpPoints = NULL;

	qCurvePointsCount = 0;
	qAlpPointsCount = 0;
	qRailPointsCount = 0;
	
	int cpcount = int(qcontrols.size());

	if(cpcount == 0)
		return;

	qCurvePoints = new CurvePoint[ cpcount * 400 ];
	qCurvePointsCount = 0;

	for( int i = 0 ; i < cpcount - 3; ++i ){
		ControlPoint
			& p0 = *qcontrols[i],
			& p1 = *qcontrols[(i+1)],
			& p2 = *qcontrols[(i+2)],
			& p3 = *qcontrols[(i+3)];
		for(float u = 0 ; u <= 1.0f; u += 0.01f ){
			getPointInCurve(u,p0,p1,p2,p3,qCurvePoints[qCurvePointsCount]);
			if(qCurvePointsCount == 0){
				qCurvePoints[qCurvePointsCount].s = 0;
				qCurvePoints[qCurvePointsCount].ux = 0;
				qCurvePoints[qCurvePointsCount].uy = 1;
				qCurvePoints[qCurvePointsCount].uz = 0;
			}else{
				qCurvePoints[qCurvePointsCount].s =
					qCurvePoints[qCurvePointsCount-1].s + 
					qCurvePoints[qCurvePointsCount].distance(qCurvePoints[qCurvePointsCount-1]);
				calculateUpVector(
					qCurvePoints[qCurvePointsCount],
					qCurvePoints[qCurvePointsCount-1]
				);
			}
			qCurvePointsCount++;
		}
	}

	qAlpPoints  = new CurvePoint[ (int)qCurvePoints[qCurvePointsCount-1].s  + 1];
	qRailPoints = new Point[ ((int)qCurvePoints[qCurvePointsCount-1].s) / 2 + 2];
	qAlpPointsCount = 1;
	qRailPointsCount = 1;

	qAlpPoints[0] = qCurvePoints[0];
	calculateRailPoints(qAlpPoints[0],qRailPoints[0],qRailPoints[1]);

	float currs = 0;
	int i = 1;

	while(i < qCurvePointsCount){
		if( currs + 1.0f < qCurvePoints[i].s ){
			qAlpPoints[qAlpPointsCount] = lerp(qCurvePoints[i],qCurvePoints[i-1],++currs);
			if( qAlpPointsCount % 4 == 0 ){
				calculateRailPoints(
					qAlpPoints[qAlpPointsCount],
					qRailPoints[2 * qRailPointsCount],
					qRailPoints[2 * qRailPointsCount+1]
				);
				++qRailPointsCount;
			}
			++qAlpPointsCount;
		}else{
			++i;
		}
	}

	int ncount = int(controls.size());
	int qsindex = -1, qeindex = -1;
	for(int i = 0 ; i < ncount; ++i){
		if(controls[i] == qcontrols[0])
			qsindex = i;
		else if(controls[i] == qcontrols[cpcount-3])
			qeindex = i;
	}
	qStartS = curvePoints[qsindex*100].s;
	qEndS = curvePoints[qeindex*100].s;
	qStartPoint = curvePoints[qsindex*100];
	qEndPoint = curvePoints[qeindex*100];
	speedRatio = qCurvePoints[qCurvePointsCount-1].s / (qEndS - qStartS);
}

void Track::drawPointArray()
{
	for( int i = 0 ; i < alpPointsCount; i += 4 ){
		CurvePoint & p = alpPoints[i];
		bar.draw(
			p.x,p.y,p.z,
			p.x + p.dx, p.y + p.dy, p.z + p.dz,
			p.ux,p.uy,p.uz
		);
	}
	for( int i = 0 ; i < qAlpPointsCount; i += 4 ){
		CurvePoint & p = qAlpPoints[i];
		bar.draw(
			p.x,p.y,p.z,
			p.x + p.dx, p.y + p.dy, p.z + p.dz,
			p.ux,p.uy,p.uz
		);
	}
	TextureManager::unbind();
	glVertexPointer(3,GL_FLOAT,sizeof(Point)*2,railPoints);
	glDrawArrays(
		GL_LINE_LOOP,
		0,
		railPointsCount
	);
	glVertexPointer(3,GL_FLOAT,sizeof(Point)*2,railPoints+1);
	glDrawArrays(
		GL_LINE_LOOP,
		0,
		railPointsCount
	);
	if(qcontrols.size() > 0 ){
		glVertexPointer(3,GL_FLOAT,sizeof(Point)*2,qRailPoints);
		glDrawArrays(
			GL_LINE_STRIP,
			0,
			qRailPointsCount
		);
		glVertexPointer(3,GL_FLOAT,sizeof(Point)*2,qRailPoints+1);
		glDrawArrays(
			GL_LINE_STRIP,
			0,
			qRailPointsCount
		);
		glColor3ub(0,0,255);
		Cube c(qStartPoint.x,qStartPoint.y,qStartPoint.z,3,3,3);
		c.draw();
		Cube d(qEndPoint.x,qEndPoint.y,qEndPoint.z,3,3,3);
		d.draw();
	}
}
void Track::getPoint(float s, OrientableObject & obj)
{
	while( s > curvePoints[curvePointsCount-1].s )
		s -= (int)curvePoints[curvePointsCount-1].s;
	int idx = int(s);
	CurvePoint out = lerp(alpPoints[idx],alpPoints[(idx+1)%alpPointsCount],s);
	obj.location.x = out.x;
	obj.location.y = out.y;
	obj.location.z = out.z;
	obj.front.x = out.x + out.dx;
	obj.front.y = out.y + out.dy;
	obj.front.z = out.z + out.dz;
	obj.up.x = out.ux;
	obj.up.y = out.uy;
	obj.up.z = out.uz;
	if( qcontrols.size() > 0  && eventHandler != NULL){
		if( s >= qEndS )
			eventHandler->qend();
		else if( s >= qStartS )
			eventHandler->qstart();
	}
}
void Track::getQPoint(float s, OrientableObject & obj)
{
	while( s > qCurvePoints[qCurvePointsCount-1].s )
		s -= (int)qCurvePoints[qCurvePointsCount-1].s;
	s *= speedRatio;
	int idx = int(s);
	CurvePoint out = lerp(qAlpPoints[idx],qAlpPoints[(idx+1)%qAlpPointsCount],s);
	obj.location.x = out.x;
	obj.location.y = out.y;
	obj.location.z = out.z;
	obj.front.x = out.x + out.dx;
	obj.front.y = out.y + out.dy;
	obj.front.z = out.z + out.dz;
	obj.up.x = out.ux;
	obj.up.y = out.uy;
	obj.up.z = out.uz;
}

void Track::calculateRailPoints(CurvePoint &p, Point &left, Point &right)
{
	Vector3 hv = p.up().cross( p.tangent() );
	hv.normalize();

	left.x = p.x + hv.x;
	left.y = p.y + hv.y;
	left.z = p.z + hv.z;
	right.x = p.x - hv.x;
	right.y = p.y - hv.y;
	right.z = p.z - hv.z;
}
void Track::calculateUpVector(CurvePoint & curr,CurvePoint & prev)
{
	Vector3 tc = curr.tangent();
	Vector3 tp = prev.tangent();

	tc.normalize();
	tp.normalize();

	Vector3 cross = tp.cross(tc);
	if(FEQUALS(cross.magnitude(),0.0f)){
		curr.ux = prev.ux;
		curr.uy = prev.uy;
		curr.uz = prev.uz;
	}else{
		float angle = tp.angleBetween(tc);
		Point rot = Vector3::rotateAround(cross,prev.up(),angle);
		curr.ux = rot.x;
		curr.uy = rot.y;
		curr.uz = rot.z;
	}
}