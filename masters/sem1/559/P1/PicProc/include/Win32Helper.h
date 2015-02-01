// CS559 Project 1 : Picture Processor
// author: priyananda( shenoy@cs.wisc.edu )
// date: 23 sep 2007
// random quote: [Gladiator] Lucilla: Today I saw a slave become more powerful than the Emperor of Rome. 
#pragma once

#include <windows.h>

//This class provides helper methods to show
//images in the interactive mode. Expect this
//code to be very dirty
class Win32Helper
{
public:
	//shows an image in a window. blocking call
	static void showImage(char varName);
};