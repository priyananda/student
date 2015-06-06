// CS559 Project 1 : Picture Processor
// author: priyananda( shenoy@cs.wisc.edu )
// date: 24 sep 2007
// random quote: [The Godfather] Don Corleone: I'll make him an offer he can't refuse

#include "Processor.h"

//just decides between batch and interactive mode
int main(int argc, char * argv[])
{
	argc--;++argv;
	Processor proc;
	if( argc == 0 )
		//no arguments: interactive mode
		proc.processInteractive();
	else
		//aha! batch mode
		proc.processBatch(argv[0]);
	return 0;
}