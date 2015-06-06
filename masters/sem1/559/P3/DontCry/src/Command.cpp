// CS559 Project 3 : Dont Cry
// author: priyananda( shenoy@cs.wisc.edu )
// date: oct 2007
// random trivia:
#include "Command.h"

CommandLine::CommandLine(char * s)
{
	parse(s);
}

//copied almost verbatim from Prof Gleicher's sample code
void CommandLine::parse(char * p)
{
	bool first = true;

	// stop when we hit the end of the string
	while(*p){
		// skip over leading whitespace - stop at the first character or end of string
		while (*p && *p<=' ') p++;

		// now we're pointing at the first thing after the spaces
		// make sure its not a comment, and that we're not at the end of the string
		// (that's actually the same thing)
		if (! (*p) || *p == '#')
			break;

		// so we're pointing at a word! add it to the word list
		if( first ){
			first = false;
			this->command = p;
		}else{
			this->args.push_back(p);
		}

		// now find the end of the word
		while(*p > ' ') p++;	// stop at space or end of string

		// if its ethe end of the string, we're done
		if (! *p) break;

		// otherwise, turn this space into and end of string (to end the word)
		// and keep going
		*p = 0;
		p++;
	}
	if(first){
		//this is a blank/commented out line
		this->command = "null";
	}
}