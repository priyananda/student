// CS559 Project 3 : Dont Cry
// author: priyananda( shenoy@cs.wisc.edu )
// date: 26 nov 2007
// random trivia:
#pragma once

#include <windows.h>
#include <gl/gl.h>
#include "glext.h"

//Manages OpenGL Extensions
class ExtensionManager
{
public:
	static void init();
}; 

//functions for ARBMultitexture
extern PFNGLACTIVETEXTUREARBPROC				glActiveTextureARB;
extern PFNGLCLIENTACTIVETEXTUREARBPROC			glClientActiveTextureARB;
extern PFNGLMULTITEXCOORD2FARBPROC				glMultiTexCoord2fARB;

//for volumetric fog
extern PFNGLFOGCOORDFEXTPROC glFogCoordfEXT;

//glsl shaders
extern PFNGLCREATESHADERPROC	glCreateShader;
extern PFNGLCREATEPROGRAMPROC	glCreateProgram;
extern PFNGLCOMPILESHADERPROC	glCompileShader;
extern PFNGLATTACHSHADERPROC	glAttachShader;
extern PFNGLSHADERSOURCEPROC	glShaderSource;
extern PFNGLLINKPROGRAMPROC		glLinkProgram;
extern PFNGLUSEPROGRAMPROC		glUseProgram;
extern PFNGLUNIFORM1IPROC		glUniform1i;
extern PFNGLUNIFORM4FPROC		glUniform4f;
extern PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;