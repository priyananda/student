// CS559 Project 2 : Quantum Coaster
// author: priyananda( shenoy@cs.wisc.edu )
// date: 18 oct 2007
// random trivia: Newton solved the brachistrochrome problem in a day.

#pragma once
#include <string>
using std::string;

class Window;

//some helper methods related to windows
//only text as of how
class Win32Helper
{
public:
	static void writeText(const string & text, float x,float y);
private:
	static void setFont(const char * f);
	static int fontBase;
}; 
