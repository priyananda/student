#ifndef	H0TT0P_SERVERINPUTSTREAM_H
#define	H0TT0P_SERVERINPUTSTREAM_H

#include <net/InputStream.h>

class SocketInputStream : virtual public InputStream{
	socket_t sd;
public:
	SocketInputStream();
	SocketInputStream(socket_t _sd);
	virtual int read(void * , int);
	virtual void close();
	virtual ~SocketInputStream();
};

#endif
