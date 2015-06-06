// CS559 Project 3 : Dont Cry
// author: priyananda( shenoy@cs.wisc.edu )
// date: nov 2007
// random trivia:
#include "ExtensionManager.h"

const char * required[] =
{
	"GL_ARB_multitexture",
	"GL_ARB_vertex_program",
	"GL_ARB_fragment_program",
	"GL_EXT_fog_coord"
};

void ExtensionManager::init()
{
	const char * allExtensions = (const char *)glGetString(GL_EXTENSIONS);
	int n = sizeof(required)/sizeof(required[0]);
	for(int i = 0 ; i < n; ++i )
		if( strstr(allExtensions,required[i]) == NULL ){
			MessageBoxA(NULL,"Required Extention is missing","Dont Cry",0);
			exit(0);
		}
	//load arb_multitexture functions
	glMultiTexCoord2fARB	= (PFNGLMULTITEXCOORD2FARBPROC)		wglGetProcAddress("glMultiTexCoord2fARB");
	glActiveTextureARB		= (PFNGLACTIVETEXTUREARBPROC)		wglGetProcAddress("glActiveTextureARB");
	glClientActiveTextureARB= (PFNGLCLIENTACTIVETEXTUREARBPROC)	wglGetProcAddress("glClientActiveTextureARB");

	//load volumetrix fog functions
	glFogCoordfEXT			   = (PFNGLFOGCOORDFEXTPROC) wglGetProcAddress("glFogCoordfEXT");

	//glsl shaders
	glCreateShader	= (PFNGLCREATESHADERPROC)	wglGetProcAddress("glCreateShader");
	glCreateProgram = (PFNGLCREATEPROGRAMPROC)	wglGetProcAddress("glCreateProgram");
	glCompileShader = (PFNGLCOMPILESHADERPROC)	wglGetProcAddress("glCompileShader");
	glAttachShader	= (PFNGLATTACHSHADERPROC)	wglGetProcAddress("glAttachShader");
	glShaderSource	= (PFNGLSHADERSOURCEPROC)	wglGetProcAddress("glShaderSource");
	glLinkProgram	= (PFNGLLINKPROGRAMPROC)	wglGetProcAddress("glLinkProgram");
	glUseProgram	= (PFNGLUSEPROGRAMPROC)		wglGetProcAddress("glUseProgram");
	glUniform1i		= (PFNGLUNIFORM1IPROC)		wglGetProcAddress("glUniform1i");
	glUniform4f		= (PFNGLUNIFORM4FPROC)		wglGetProcAddress("glUniform4f");
	glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC) wglGetProcAddress("glGetUniformLocation");
}

//volumetric fog
PFNGLFOGCOORDFEXTPROC				glFogCoordfEXT = NULL;

//multi texturing
PFNGLMULTITEXCOORD2FARBPROC		glMultiTexCoord2fARB	= NULL;
PFNGLACTIVETEXTUREARBPROC		glActiveTextureARB		= NULL;
PFNGLCLIENTACTIVETEXTUREARBPROC glClientActiveTextureARB= NULL;

//glsl shaders
PFNGLCREATESHADERPROC	glCreateShader = NULL;
PFNGLCREATEPROGRAMPROC	glCreateProgram = NULL;
PFNGLCOMPILESHADERPROC	glCompileShader = NULL;
PFNGLATTACHSHADERPROC	glAttachShader = NULL;
PFNGLSHADERSOURCEPROC	glShaderSource = NULL;
PFNGLLINKPROGRAMPROC	glLinkProgram = NULL;
PFNGLUSEPROGRAMPROC		glUseProgram = NULL;
PFNGLUNIFORM1IPROC		glUniform1i = NULL;
PFNGLUNIFORM4FPROC		glUniform4f = NULL;
PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation = NULL;