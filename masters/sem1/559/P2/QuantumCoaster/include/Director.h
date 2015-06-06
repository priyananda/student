// CS559 Project 2 : Quantum Coaster
// author: priyananda( shenoy@cs.wisc.edu )
// date: 20 oct 2007
// random trivia:
#pragma once

#include "WindowEventHandler.h"
#include "God.h"
#include "Camera.h"
#include "Renderer.h"
#include "Train.h"
#include "Track.h"

enum Modes
{
	Edit,
	RunPaused,
	RunRunning,
	RunSplitScreen
};

// Manages the scene for the solar system
class Director : public WindowEventHandler, public TrackEventClient
{
public:
	Director()
		:splitScreen(false),runMode(true),currentControl(0),
		animate(false),godMode(true),speed(0.1f),shadows(false){}
	//overridden methods
	void handleInit(Window * window);
	void handleKey( int what, KeyStateEnum keyState );
	void handleMouse( MouseKeyEnum c,int x,int y );
	void handlePaint();
	void handleIdle();
	void handleMenu(int command);
	void handleDrop(MouseKeyEnum e, int dx,int dy);

	void qstart();
	void qend();
private:
	void writeText();
	void setCamAtSpLoc();
	void startTrain();
	void updateTrain();
	void drawSpeedo();

	Camera godCam;
	Camera train1Cam;
	Camera train2Cam;
	
	Renderer renderer;
	bool splitScreen;
	bool runMode;
	bool animate;
	bool godMode;
	bool shadows;
	int currentControl;
	float speed;
};