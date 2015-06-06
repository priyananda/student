// CS559 Project 3 : Dont Cry
// author: priyananda( shenoy@cs.wisc.edu )
// date: 28 nov 2007
// random trivia:
#include "DayTimer.h"
#include <windows.h>

//24 hours = 2 minutes
#define SECONDS_PER_DAY 120

void DayTimer::init()
{
	this->startTime = timeGetTime() - 20000;
}

//number of minutes
int DayTimer::getTime()
{
	long seconds = timeGetTime() - startTime;
	seconds = seconds * 3 / 250;//coz it is in milliseconds
	return seconds % (SECONDS_PER_DAY*12);
}
void DayTimer::getTime(short &h, short &m)
{
	int t = getTime();
	h = t / 60;
	m = t % 60;
}