// CS559 Project 1 : Picture Processor
// author: priyananda( shenoy@cs.wisc.edu )
// date: 24 sep 2007
// random quote: [Pulp Fiction] Vincent: And you know what they call a Quarter Pounder with Cheese in Paris? 

#pragma once

#include <list>
using std::list;

//handles input in both batch or interactive mode
class Processor
{
public:
	void processBatch(const char * fileName);
	void processInteractive();
private:
	list<char *> lines;

	void processHelp();
	void processLoad(char * filename);
	void processRun();
	bool processStep();
	void processShow(char * varName);
	bool processCommand(char * commandLine);
	void processShowSymbolTable();
};