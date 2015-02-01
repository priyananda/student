// CS559 Project 2 : Quantum Coaster
// author: priyananda( shenoy@cs.wisc.edu )
// date: 20 oct 2007
// random trivia:

#include "Camera.h"
#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>

void Camera::look()
{
	if( parent != 0 ){
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		
		Vector3 upn = parent->up;
		upn.normalize();
		upn = upn * offset;

		gluLookAt(
			parent->location.x + upn.x,
			parent->location.y + upn.y,
			parent->location.z + upn.z,
			parent->front.x + upn.x,
			parent->front.y + upn.y,
			parent->front.z + upn.z,
			parent->up.x,
			parent->up.y,
			parent->up.z
		);
	}
}