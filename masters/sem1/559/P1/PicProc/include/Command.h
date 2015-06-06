// CS559 Project 1 : Picture Processor
// author: priyananda( shenoy@cs.wisc.edu )
// date: 13 sep 2007
// random quote: [Pulp Fiction] Jules: I'm sorry, did I break your concentration?
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

//This is the base class for all Commands.
//Each command needs to override extract and execute
class Command
{
public:
	//this the fuction people call
	bool process(const CommandLine &);
protected:
	//extract the arguments and also validate
	virtual bool extract(const CommandLine &) = 0;
	//execute the command
	virtual void execute() = 0;
	//place to store what went wrong
	char errorString[255];
};

//This creates instances of Command objects based on
//what was specified in the command line
class CommandFactory
{
public:
	static Command * createCommand(const CommandLine &);
};

//this is for blank/commented lines
class EmptyCommand : public Command
{
public:
	bool extract(const CommandLine & c){return true;}
	void execute(){}
};