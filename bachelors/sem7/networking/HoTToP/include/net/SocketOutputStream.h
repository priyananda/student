#ifndef	H0TT0P_SERVEROUTPUTSTREAM_H
#define	H0TT0P_SERVEROUTPUTSTREAM_H

#include <net/OutputStream.h>

class SocketOutputStream : virtual public OutputStream{
	socket_t sd;
public:
	SocketOutputStream();
	SocketOutputStream(socket_t _sd);
	virtual int write( const void * , int);
	virtual void close();
	virtual ~SocketOutputStream();
};

#endif
