// CS559 Project 3 : Dont Cry
// author: priyananda( shenoy@cs.wisc.edu )
// date: 28 nov 2007
// random trivia:
#pragma once

//keeps track of the time of the day
class DayTimer
{
public:
	//initialize
	void init();
	//time of day in 0-119 units( 1 unit = 12 min )
	int getTime();
	//time of day in hh:mm format()
	void getTime(short & h,short & m);
private:
	long startTime;
}; 
