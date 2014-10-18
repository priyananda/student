#include "cmdparse.h"
#include <conio.h>
#include <signal.h>

//////////////////////////////////////////////////////////////////////
/// Extremely Dangerous to do this , but the app keeps crashing 
//////////////////////////////////////////////////////////////////////
void SigSegVHandler(int __SigNumber){
    return;// I am ignoring all Segmentation faults 
}

void setUp(){
    signal(SIGSEGV,SigSegVHandler);
}
int main(){
    gppconio_init();
    setUp();
	CommandParser::init();
	while(1){
		CommandParser::getCommand();
		int c = CommandParser::parseCommand();
		CommandParser::executeCommand(c);
    }
    return 0;
}