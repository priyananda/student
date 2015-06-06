// CS559 Project 3 : Dont Cry
// author: priyananda( shenoy@cs.wisc.edu )
// date: 16 oct 2007
// random trivia: The word "geek" has its origins in the word "geck", which means a fool or simpleton.
#pragma once

class Window;

//A section of the window. This defines the "view"
class ViewPort
{
public:
	ViewPort()
	{
		setFrustrum(0.1f,1000.0f,fov);
	}
	void set(Window *);
	void setSize( int w,int h)
	{
		width = w;
		height = h;
	}
	void set(int a,int b)
	{
		x = a; y = b;
	}
	void setFrustrum(float nearp, float farp, float angle )
	{
		nearPlane = nearp;
		farPlane  = farp;
		fov = angle;
	}
	void getFrustum(float& nearp, float& farp, float& angle )
	{
		nearp = nearPlane;
		farp  = farPlane;
		angle = fov;
	}
	void switchTo2D();
	void restoreFrom2D();
private:
	int x,y;
	int width,height;
	float nearPlane, farPlane, fov;
};