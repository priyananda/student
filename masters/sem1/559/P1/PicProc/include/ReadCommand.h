// CS559 Project 1 : Picture Processor
// author: priyananda( shenoy@cs.wisc.edu )
// date: 13 sep 2007
// random quote: [300] Leonidas: THIS IS SPARTA!
#pragma once

#include "Command.h"

class TargaImage;

//this class reads a file and creates an image variable out of it
//format on command line is:
//read <variable> <filepath>
class ReadCommand : public Command
{
public:
	//overriding these functions
	virtual bool extract(const CommandLine &);
	virtual void execute();
private:
	TargaImage * image;
	char * filePath;
	char varName;
};

//writes an image into file. The variable doesn't get cleared
class WriteCommand  : public Command
{
public:
	//overriding these functions
	virtual bool extract(const CommandLine &);
	virtual void execute();
private:
	TargaImage * image;
	char * filePath;
};