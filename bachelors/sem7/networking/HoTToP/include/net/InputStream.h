#ifndef H0TT0P_INPUTSTREAM_H
#define H0TT0P_INPUTSTREAM_H

#include <net/StreamBase.h>

class InputStream : virtual public StreamBase{
public:
	virtual int read(void * buff, int size ) = 0;
	using StreamBase::close;
	virtual ~InputStream(){}
};

#endif
