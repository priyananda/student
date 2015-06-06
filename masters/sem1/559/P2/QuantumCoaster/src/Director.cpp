// CS559 Project 2 : Quantum Coaster
// author: priyananda( shenoy@cs.wisc.edu )
// date: oct 2007
// random trivia:

#include "resource.h"
#include "Window.h"
#include "Win32Helper.h"
#include <gl/gl.h>
#include "Director.h"
#include "World.h"
#include "PropObject.h"

//initialize everything
void Director::handleInit(Window * window)
{
	WindowEventHandler::handleInit(window);
	window->setMenuVisible(false);

	godCam.setParent(&World::god);

	train1Cam.setParent(&World::train1);
	train1Cam.offset = 5;

	train2Cam.setParent(&World::train2);
	train2Cam.offset = 5;
	World::train2.quant = true;
	World::train2.visible = false;

	World::neww();
	World::track.eventHandler = this;

	startTrain();
	animate = false;
	renderer.init();
}

void Director::handleKey( int what, KeyStateEnum keyState )
{
	if( keyState == eKeyStateDown ){
		//common keys
		switch(what){
			case VK_ESCAPE:
				PostQuitMessage(0);
				break;
			case VK_UP:
				World::god.moveForward(5);break;
			case VK_DOWN:
				World::god.moveForward(-5);break;
			case VK_LEFT:
				World::god.turnH(0.15f);break;
			case VK_RIGHT:
				World::god.turnH(-0.15f);break;
			case VK_PRIOR:
				World::god.turnV(0.15f);break;
			case VK_NEXT:
				World::god.turnV(-0.15f);break;
			case 'R':
				runMode = !runMode;
				animate = false;
				godMode = true;
				window->setMenuVisible(!runMode);
				World::track.switchMode();
				World::train1.start();
				World::train2.visible = false;
				splitScreen = false;
				break;
			case VK_RETURN:
				MessageBoxA(NULL,"42","Password to attain nirvana",0);
				break;
		}
		if(runMode){
			//run mode specific keys
			switch(what){
				case 'P':
					startTrain();break;
				case 'F':
					godMode = !godMode;break;
				case VK_OEM_PLUS:
					if( speed < 1.0f ) speed += 0.1f;
					break;
				case VK_OEM_MINUS:
					if( speed > 0.1f ) speed -= 0.1f;
					break;
				case VK_OEM_PERIOD:
					World::train1.chooBogey(true);
					World::train2.chooBogey(true);
					break;
				case VK_OEM_COMMA:
					World::train1.chooBogey(false);
					World::train2.chooBogey(false);
					break;
				case VK_SPACE:
					animate = !animate;
					break;
				case 'S':
					shadows = !shadows;
					break;
			}
		}else{
			//edit mode specific keys
			ControlPoint * p = World::track.getSelectedControl();
			PropObject * po = World::getSelectedObject();
			switch(what){
				case 'A':
					if(p)p->location.x += 1;
					if(po)po->location.x += 1;
					break;
				case 'D':
					if(p)p->location.x -= 1;
					if(po)po->location.x -= 1;
					break;
				case 'W':
					if(p)p->location.z += 1;
					if(po)po->location.z += 1;
					break;
				case 'S':
					if(p)p->location.z -= 1;
					if(po)po->location.z -= 1;
					break;
				case 'Q':
					if(p)p->location.y += 1;
					if(po)po->location.y += 1;
					break;
				case 'Z':
					if(p)p->location.y -= 1;
					if(po)po->location.y -= 1;
					break;
				case VK_DELETE:
					World::deleteSelectedObject();
					break;
				case 'N':
					World::track.addNewControl();break;
				case VK_TAB:
					setCamAtSpLoc();break;
			}
		}
	}
}
void Director::handlePaint()
{
	window->updateFPS();
	window->setCurrentViewPort(ViewPortMain);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	
	if(godMode){
		godCam.look();
		renderer.draw(runMode,shadows);
	}else{
		if(splitScreen){
			window->setCurrentViewPort(ViewPortLeft);
			train1Cam.look();
			renderer.draw(runMode,shadows);
			
			window->setCurrentViewPort(ViewPortRight);
			train2Cam.look();
			renderer.draw(runMode,shadows);

			window->setCurrentViewPort(ViewPortMain);
		}else{
			train1Cam.look();
			renderer.draw(runMode,shadows);
		}
	}
	if( animate )
		updateTrain();
	writeText();
	window->flush();
}
void Director::handleIdle()
{
	handlePaint();
}

void Director::writeText()
{
	char buffer[255];
	float ht = float(this->window->height);
	ht -= 50;
	window->getViewPort(ViewPortMain).switchTo2D();

	if( this->runMode ){
		Win32Helper::writeText("You are in the RUN mode",10,ht); ht -= 20;
		Win32Helper::writeText("Press 'R' to go into EDIT mode",10,ht); ht -= 20;
		Win32Helper::writeText("Press 'F' to toggle GOD/TRAIN camera",10,ht); ht -= 20;
		Win32Helper::writeText("Press SPACE to toggle train animation",10,ht); ht -= 20;
		Win32Helper::writeText("Press 'P' to start train",10,ht); ht -= 20;
		Win32Helper::writeText("Press UP/DOWN/LEFT/RIGHT to move forward/backward/turn in GOD camera mode",10,ht); ht -= 20;
		Win32Helper::writeText("Press PGUP/PGDOWN to look up/down in GOD camera mode",10,ht); ht -= 20;
		Win32Helper::writeText("Press '+'/'-' to increase/decrease speed",10,ht); ht -= 20;
		Win32Helper::writeText("Press '<'/'>' to increase/decrease bogeys in the train",10,ht); ht -= 20;
		Win32Helper::writeText("Press 'S' to toggle shadows",10,ht); ht -= 20;
		Win32Helper::writeText("Press CTRL-SHIFT-ALT-BACKSPC-ENTER to attain nirvana",10,ht); ht -= 20;
	}else{
		Win32Helper::writeText("You are in the EDIT mode",10,ht); ht -= 20;
		Win32Helper::writeText("Press 'R' to go into RUN mode",10,ht); ht -= 20;
		Win32Helper::writeText("Press UP/DOWN/LEFT/RIGHT to move forward/backward/turn in GOD camera mode",10,ht); ht -= 20;
		Win32Helper::writeText("Press PGUP/PGDOWN to look up/down in GOD camera mode",10,ht); ht -= 20;
		Win32Helper::writeText("Press TAB to switch to next control point",10,ht); ht -= 20;
		Win32Helper::writeText("Click on a control point to select it(buggy)",10,ht); ht -= 20;
		Win32Helper::writeText("Click and drag control points and scenery objects to move(buggy) ",10,ht); ht -= 20;
		Win32Helper::writeText("Press 'A'/'D'/'W'/'S'/'Q'/'Z' to move selected control point/object",10,ht); ht -= 20;
		Win32Helper::writeText("Press DELETE to delete selected control point/scenery object",10,ht); ht -= 20;
		Win32Helper::writeText("Press N to add a new control point",10,ht); ht -= 20;
	}
	
	sprintf_s(buffer,254,"fps: %d",window->getFPS());
	Win32Helper::writeText(buffer,10,90);

	sprintf_s(buffer,254,"location: %3f %3f %3f",
		World::god.location.x,World::god.location.y,World::god.location.z);
	Win32Helper::writeText(buffer,10,70);

	sprintf_s(buffer,254,"front: %3f %3f %3f",
		World::god.front.x,World::god.front.y,World::god.front.z);
	Win32Helper::writeText(buffer,10,50);

	sprintf_s(buffer,254,"up: %3f %3f %3f",
		World::god.up.x,World::god.up.y,World::god.up.z);
	Win32Helper::writeText(buffer,10,30);

	drawSpeedo();
	
	window->getViewPort(ViewPortMain).restoreFrom2D();
}
void Director::handleMouse(MouseKeyEnum e,int x,int y)
{
	renderer.drawForPicking(x,y);
}
void Director::setCamAtSpLoc()
{
	if( currentControl >= World::track.getControlCount())
		currentControl = 0;
	ControlPoint * p = World::track.getControl(currentControl);
	World::god.set(
		p->location.x + 5,p->location.y,p->location.z + 5,
		p->location.x,p->location.y,p->location.z,
		0,1,0
	);
	++currentControl;
}
void Director::startTrain()
{
	World::train1.start();
	animate = true;
}
void Director::updateTrain()
{
	World::train1.update(speed);
	if(splitScreen)
		World::train2.update(speed);
}
void Director::drawSpeedo()
{
	int width = this->window->width - 30;
	int sp = int(speed * 10);
	if( sp > 10 ) sp = 10;
	int ht = 0, wt = 0;
	float r = 0, g = 1;
	while(sp-- > 0){
		glColor3f(r,g,0);
		glRecti(width - wt, ht + 10,width+20, ht + 30);
		ht += 25;
		wt += 5;
		r += 0.1f;
		g -= 0.1f;
	}
}

void Director::handleMenu(int command)
{
	char buffer[255];

	buffer[0] = 0;
	
	OPENFILENAMEA ofn;
	ZeroMemory(&ofn,sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.lpstrFilter = "Buckyland files(*.bucky)\0*.bucky\0\0";
	ofn.lpstrDefExt = ".bucky";
	ofn.nFilterIndex = 1;
	ofn.nMaxFile = 255;
	ofn.lpstrFile = buffer;
	ofn.lpstrTitle = "bucky";
	ofn.nMaxFileTitle = sizeof ("bucky");

	switch(command){
		case IDM_NEW:
			World::neww();
			break;
		case IDM_OPEN:
			if( GetOpenFileNameA(&ofn) != 0 )
				World::open(ofn.lpstrFile);
			break;
		case IDM_SAVE:
			if( GetSaveFileNameA(&ofn) != 0 )
				World::save(ofn.lpstrFile);
			break;
		case IDM_QUIT:
			PostQuitMessage(0);
			break;
		case IDM_ADD_HOARDING:
			World::add(PROP_HOARDING);
			break;
		case IDM_ADD_BUILDING:
			World::add(PROP_BUILDING);
			break;
		case IDM_ADD_TREE:
			World::add(PROP_TREE);
			break;
		case IDM_ADD_FLAG:
			World::add(PROP_FLAG);
	}
}
void Director::handleDrop(MouseKeyEnum which, int dx, int dy)
{
	ControlPoint * cp = World::track.getSelectedControl();
	PropObject * op = World::getSelectedObject();

	if( cp == NULL && op == NULL )
		return;

	Vector3 dir = (cp == NULL? op->location : cp->location) - World::god.location;
	dir.y = 0;
	dir.normalize();
	
	Vector3 right = dir.cross(Vector3::YAxis);
	right.normalize();
	dx /= 10;
	dy /= -10;

	if(cp){
		if( which == eMouseLeftClick ){
			cp->location.x += dy * dir.x + dx * right.x;
			cp->location.z += dy * dir.z + dx * right.z;
		}else{
			cp->location.y += dy;
		}
	}else if(op){
		if( which == eMouseLeftClick ){
			op->location.x += dy * dir.x + dx * right.x;
			op->location.z += dy * dir.z + dx * right.z;
		}else{
			op->location.y += dy;
		}
	}
}
void Director::qstart()
{
	if(splitScreen)return;
	splitScreen = true;
	World::train2.visible = true;
	World::train2.start();
}
void Director::qend()
{
	if(!splitScreen)return;
	World::train2.visible = false;
	splitScreen = false;
}