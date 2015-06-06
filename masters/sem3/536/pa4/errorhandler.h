// CS 536 : PA2
// author: priyananda( shenoy@cs.wisc.edu )
// date: 3 Oct 2008
// random quote: 

#ifndef CS536_ERROR_HANDLER_H
#define CS536_ERROR_HANDLER_H

//Generic mechanism for handling errors and warnings
class ErrorHandler
{
public:
	//prints an error message on to stderr
	static void reportError(int line,int col, const char * message);
	
	//prints a warning message on to stderr
	static void reportWarning(int line,int col, const char * message);
};

#endif
