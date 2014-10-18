#ifndef HOTTOP_EXCEPTION_H
#define HOTTOP_EXCEPTION_H

#include <string>
#include <errno.h>
using std::string;

class Exception{
	string msg;
public:
	Exception(): msg(""){}
	Exception(string m): msg(m){}

	const string& getErrorMessage(){ return msg; }
	void setErrorMessage(const string& s){ msg = s;}

	virtual string toString(){ return errno ? string(msg + strerror(errno)) : msg; }

	virtual ~Exception(){}
};

// Marker Classes
class EndOfFileException : Exception{};

#endif
