// CS559 Project 2 : Quantum Coaster
// author: priyananda( shenoy@cs.wisc.edu )
// date: 17 oct 2007
// random trivia: XNA stands for XNA is Not an Acronym.

#include "Win32Helper.h"
#include "Window.h"
#include <windows.h>
#include <gl/gl.h>

int Win32Helper::fontBase = -1;

//http://msdn2.microsoft.com/en-us/library/ms970775.aspx
void  Win32Helper::setFont(const char * fontName)
{
	fontBase = glGenLists(127);
	HFONT font = CreateFont(
		-12,
		0,
		0,				// Angle Of Escapement
		0,				// Orientation Angle
		FW_BOLD,		// Font Weight
		FALSE,				// Italic
		FALSE,				// Underline
		FALSE,				// Strikeout
		ANSI_CHARSET,			// Character Set Identifier
		OUT_TT_PRECIS,			// Output Precision
		CLIP_DEFAULT_PRECIS,		// Clipping Precision
		ANTIALIASED_QUALITY,		// Output Quality
		FF_DONTCARE|DEFAULT_PITCH,	// Family And Pitch
		L"Tahoma"
	);
 	HDC hDC = wglGetCurrentDC();
	SelectObject(hDC,font);
	int x = wglUseFontOutlines(	
		hDC,
		__toascii(' '),		// Starting Character
		__toascii(' ') + 126,// Number Of Display Lists To Build
		fontBase,			// Starting Display Lists
		0.0f,				// Deviation From The True Outlines
		0.2f,				// Font Thickness In The Z Direction
		WGL_FONT_POLYGONS,	// Use Polygons, Not Lines
		NULL
	);
	DeleteObject(font);
}


void Win32Helper::writeText(const string & text, float x,float y)
{
	if( fontBase < 0 )
		setFont("Arial");
	glPushMatrix();
	glTranslatef(x,y,0);
	glScalef(15,15,15);
	glListBase(fontBase - __toascii(' '));
	glColor3f(0,1,0);
	glCallLists(GLsizei(text.length()), GL_UNSIGNED_BYTE, text.c_str());
	glPopMatrix();
}