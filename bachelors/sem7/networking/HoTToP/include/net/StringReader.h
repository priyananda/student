#ifndef H0TT0P_STRINGREADER_H
#define H0TT0P_STRINGREADER_H

#include <net/InputStream.h>

class StringReader{
	InputStream & myIn;
public:
	StringReader(InputStream & in):myIn(in){}
	int read();
	string readString();
	string readLine(char delim = '\n');
};

#endif
