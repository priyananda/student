// CS 536 : PA2
// author: priyananda( shenoy@cs.wisc.edu )
// date: 3 Oct 2008
// random quote: 

#include "errorhandler.h"
#include <cstdio>

void ErrorHandler::reportError(int line,int col, const char * message)
{
	fprintf(stderr,"%d:%d ERROR %s\n",line,col, message);
}

void ErrorHandler::reportWarning(int line,int col, const char * message)
{
	fprintf(stderr,"%d:%d WARNING %s\n",line,col, message);
}
