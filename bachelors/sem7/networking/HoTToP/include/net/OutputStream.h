#ifndef H0TT0P_OUTPUTSTREAM_H
#define H0TT0P_OUTPUTSTREAM_H

#include <net/StreamBase.h>

class OutputStream : virtual public StreamBase{
public:
	virtual int write(const void * buff,int size) = 0;
	using StreamBase::close;
	virtual ~OutputStream(){}
};

#endif
