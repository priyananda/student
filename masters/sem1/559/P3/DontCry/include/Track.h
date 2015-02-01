// CS559 Project 3 : Dont Cry
// author: priyananda( shenoy@cs.wisc.edu )
// date: 24 oct 2007
// random trivia:
#pragma once

#include "ControlPoint.h"
#include "Rail.h"
#include <vector>
using std::vector;
#include <algorithm>

struct CurvePoint : public Point
{
	float dx,dy,dz;//tangent
	float s;//arc length till now
	float ux,uy,uz;//up vector

	Vector3 tangent(){
		return Vector3(dx,dy,dz);
	}
	Vector3 up(){
		return Vector3(ux,uy,uz);
	}
};

class World;

//who wants to listen to events
class TrackEventClient
{
public:
	virtual void qstart() = 0;
	virtual void qend() = 0;
};

// The actual RC track
class Track
{
public:
	Track();
	void draw();
	void addNewControl(){
		ControlPoint * p = new ControlPoint(
			(controls[0]->location.x + controls[1]->location.x) / 2,
			(controls[0]->location.y + controls[1]->location.y) / 2,
			(controls[0]->location.z + controls[1]->location.z) / 2,
			(controls[0]->up.x + controls[1]->up.x) / 2,
			(controls[0]->up.y + controls[1]->up.y) / 2,
			(controls[0]->up.z + controls[1]->up.z) / 2
		);
		controls.insert(controls.begin()+1,p);
		PickableObjectRegistry::add(p);
	}
	void addControl(float x, float y, float z, float ux = 0, float uy = 1, float uz = 0, bool quant = false){
		ControlPoint *p = new ControlPoint(x,y,z,ux,uy,uz);
		if(quant)
			qcontrols.push_back(p);
		else
			controls.push_back(p);
		PickableObjectRegistry::add(p);
	}
	void deleteControl(ControlPoint * p){
		if( controls.size() <= 4 )
			return;
		controls.erase(std::find(controls.begin(),controls.end(),p));
		PickableObjectRegistry::remove(p);
		delete p;
	}
	void clearControls(){
		while(!controls.empty()){
			ControlPoint * p = controls.front();
			controls.erase(controls.begin());
			PickableObjectRegistry::remove(p);
			delete p;
		}
		if(!qcontrols.empty()){
			qcontrols.erase(qcontrols.begin());
			qcontrols.erase(qcontrols.begin());
			qcontrols.erase(qcontrols.begin());
			while(qcontrols.size() > 3){
				ControlPoint * p = qcontrols.front();
				qcontrols.erase(qcontrols.begin());
				PickableObjectRegistry::remove(p);
				delete p;
			}
			qcontrols.clear();
		}
	}
	int getControlCount(){
		return int(controls.size());
	}
	ControlPoint * getControl(int i){
		return controls[i];
	}
	ControlPoint * getSelectedControl(){
		int c = int(controls.size());
		while(c--)
			if( controls[c]->isSelected())
				return controls[c];
		return NULL;
	}
	void switchMode(){
		if(editMode){
			pointify();
			qpointify();
		}
		editMode = !editMode;
	}
	void getPoint(float s, OrientableObject & obj);
	void getQPoint(float s, OrientableObject & obj);

	TrackEventClient * eventHandler;
private:
	//edit mode "plain" drawing
	void drawSegment(
		const ControlPoint & p0,
		const ControlPoint & p1,
		const ControlPoint & p2,
		const ControlPoint & p3
	);
	void getPointInCurve(
		float u,
		const ControlPoint & p0,
		const ControlPoint & p1,
		const ControlPoint & p2,
		const ControlPoint & p3,
		CurvePoint & cp
	);
	void calculateRailPoints(CurvePoint & p, Point & left, Point & right);
	void calculateUpVector(CurvePoint & curr, CurvePoint & prev);
	
	//run mode optimizations
	void qpointify();
	void pointify();
	void drawPointArray();
	
	vector<ControlPoint*> controls;
	vector<ControlPoint*> qcontrols;
	
	CurvePoint * curvePoints;
	CurvePoint * alpPoints;
	Point * railPoints;
	
	CurvePoint * qCurvePoints;
	CurvePoint * qAlpPoints;
	Point * qRailPoints;

	int curvePointsCount;
	int alpPointsCount;
	int railPointsCount;
	
	int qCurvePointsCount;
	int qAlpPointsCount;
	int qRailPointsCount;

	float qStartS;
	float qEndS;
	float speedRatio;

	Point qStartPoint;
	Point qEndPoint;

	bool editMode;
	Rail bar;

	friend class World;
};