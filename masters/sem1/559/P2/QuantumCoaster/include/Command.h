// CS559 Project 2 : Quantum Coaster
// author: priyananda( shenoy@cs.wisc.edu )
// date: oct 2007
// random trivia:
#pragma once

#include <vector>
using std::vector;

//This class represents one line in the command sequence
class CommandLine
{
public:
	//the command to execute
	char * command;
	//argument count
	int numberOfArguments() const
	{
		return static_cast<int>(args.size());
	}
	//arguments
	char * operator[]( int index ) const
	{
		if( index < 0 || index >= numberOfArguments() ) return NULL;
		return args[index];
	}
	//takes in an extire (unparsed) command line and splits it
	//NOT a const char *
	CommandLine(char *);
private:
	//this is the actual splitting function.
	void parse(char *);
	vector<char *> args;
};