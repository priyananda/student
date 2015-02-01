// CS559 Project 3 : Dont Cry
// author: priyananda( shenoy@cs.wisc.edu )
// date: 23 nov 2007
// random trivia:
#pragma once

//Manages vertex and pixel shaders
class ShaderManager
{
public:
	static int loadProgram(const char * vertexshader,const char * pixelshader);
	static void bindProgram(int programID);
	static void setUniformVar(int programID,const char * name,int var);
	static void setUniformVar(int programID,const char * name,float var[4]);
	static void unbind();
private:
	static int loadShader(const char * filename,int type);
};