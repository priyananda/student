#ifndef H0TT0P_STRINGWRITER_H
#define H0TT0P_STRINGWRITER_H

#include <net/OutputStream.h>

class StringWriter{
	OutputStream& myOut;
public:
	StringWriter(OutputStream & out):myOut(out){}
	void write(const string & str);
	void write(const char * buff);
	void write(const char arr[] , int size);
	void write(const char ch);
	inline void writeLine( const string & str){
		this->writeLine(str.c_str());
	}
	void writeLine( const char * str);
};

#endif
