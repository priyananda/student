// CS559 Project 3 : Dont Cry
// author: priyananda( shenoy@cs.wisc.edu )
// date: 23 nov 2007
// random trivia:
#include "Shader.h"
#include "ExtensionManager.h"
#include <fstream>
using std::ifstream;

static char * readEntireFile(const char * filename)
{
	unsigned long s = 0;
	s = GetCompressedFileSizeA(filename,&s);
	char * buffer = new char[s+1];
	memset(buffer,0,s+1);

	ifstream fs(filename);
	fs.getline(buffer,s,'\0');
	fs.close();

	return buffer;
}

//bundles a VS and a PS into a program
int ShaderManager::loadProgram(const char * vertexshader,const char * pixelshader)
{
	int programID = glCreateProgram();
	if(vertexshader != NULL ){
		int shaderID = loadShader(vertexshader,GL_VERTEX_SHADER);
		glAttachShader(programID,shaderID);
	}
	if(pixelshader != NULL ){
		int shaderID = loadShader(pixelshader,GL_FRAGMENT_SHADER);
		glAttachShader(programID,shaderID);
	}
	glLinkProgram(programID);
	return programID;
}

int ShaderManager::loadShader(const char *filename,int type)
{
	int shaderID = glCreateShader(type);
	const char * code = readEntireFile(filename);

	glShaderSource(shaderID,1,&code,NULL);
	glCompileShader(shaderID);
	//todo:check for errors

	delete [] code;

	return shaderID;
}
void ShaderManager::setUniformVar(int programID, const char *name, int var)
{
	int varID = glGetUniformLocation(programID,name);
	glUniform1i(varID,var);
}
void ShaderManager::setUniformVar(int programID, const char *name, float var[4])
{
	int varID = glGetUniformLocation(programID,name);
	glUniform4f(varID,var[0],var[1],var[2],var[3]);
}
void ShaderManager::bindProgram(int programID)
{
	glUseProgram(programID);
}

void ShaderManager::unbind()
{
	glUseProgram(0);
}