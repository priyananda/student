// CS559 Project 1 : Picture Processor
// author: priyananda( shenoy@cs.wisc.edu )
// date: 24 sep 2007
// random quote: [Matrix Reloaded] The Architect: The problem is choice.

#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::flush;

#include <fstream>
using std::ifstream;

#include "Processor.h"
#include "Command.h"
#include "Win32Helper.h"
#include "SymbolTable.h"
#include "TargaImage.h"

//batch mode. read a file line by line and execute
//each command. Stop at first failure.
void Processor::processBatch(const char * fileName)
{
	ifstream file(fileName);
	char buffer[255];
	while(file.good()){
		file.getline(buffer,254);
		cout << "Executing:" << buffer << endl;
		if(!processCommand(buffer))
			break;
	}
	file.close();
}

//1. ask for user input
//2. execute it and repeat
//3. quit when user types "quit"
void Processor::processInteractive()
{
	char buffer[255];
	cout << "PicProc - picture processing tool - shenoy@cs.wisc.edu " << endl
		 << "type help to see list of commands" << endl;
	while(true){
		cout << ">>" << flush;
		cin.getline(buffer,254);
		if( _stricmp("help",buffer) == 0)
			processHelp();
		else if( _stricmp("quit",buffer) == 0 )
			return;
		else if( _strnicmp("load",buffer,4) == 0 )
			processLoad(buffer + 4);
		else if( _stricmp("run",buffer) == 0 )
			processRun();
		else if( _stricmp("step",buffer) == 0 )
			processStep();
		else if( _strnicmp("show",buffer,4) == 0 )
			processShow(buffer+4);
		else if( _strnicmp("images",buffer,6) == 0 )
			processShowSymbolTable();
		else processCommand(buffer);
	}
}

void Processor::processHelp()
{
	cout << "Commands available are:" << endl;
	cout << "\tload FILENAME => loads commands from a file into buffer" << endl;
	cout << "\thelp => shows this" << endl;
	cout << "\trun => executes all lines in buffer" << endl;
	cout << "\tstep => executes the first line in buffer" << endl;
	cout << "\timages => shows all images loaded in the variables" << endl;
	cout << "\tshow VARNAME => shows the image in a variable" << endl;
	cout << "You can also type in valid picproc commands" << endl;
}
//loads the contents of a file into the buffer
void Processor::processLoad(char * fileName )
{
	while(*fileName && isspace(*fileName))fileName++;
	if(! *fileName ){
		cout << "No file to load" << endl;
		return;
	}
	ifstream file(fileName);
	while(file.good()){
		char * buffer = new char[255];
		file.getline(buffer,254);
		lines.push_back(buffer);
	}
	file.close();
	cout << "Loaded file:" << fileName << endl;
}
//try to execute whatever user typed as a command
bool Processor::processCommand(char * commandLine)
{
	CommandLine cl(commandLine);
	Command * cmd = CommandFactory::createCommand(cl);
	if( cmd == NULL ){
		cout << "No, I'm not smart enough to understand the gibberish you just wrote. Type a correct command." << endl;
		return false;
	}
	return cmd->process(cl);
}
//run till error or end of buffer
void Processor::processRun()
{
	while(!lines.empty())
		//execute the next command
		if(!processStep())
			return;
}
//shows an image in a window
void Processor::processShow(char * s)
{
	while(*s && isspace(*s))s++;
	if(! *s ){
		cout << "No image to show" << endl;
		return;
	}
	Win32Helper::showImage(s[0]);
}
//execute one command from front of the buffer
bool Processor::processStep()
{
	char * line = lines.front();
	cout << "Executing: " << line << endl;
	if(!processCommand(line))
		return false;
	lines.pop_front();
	delete [] line;
	return true;
}

//shows the details of an image
static void showImage(char var, TargaImage * p)
{
	printf("%c\t%3dx%3d\n",var,p->width(),p->height());
}

//show contents of symbol table
void Processor::processShowSymbolTable()
{
	SymbolTable::enumerate(showImage);
}