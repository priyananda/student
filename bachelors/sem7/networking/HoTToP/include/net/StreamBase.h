#ifndef HOTTOP_IO_BASE_H
#define HOTTOP_IO_BASE_H

#include <utils/Exception.h>
#include <string>

using std::string;
typedef int socket_t;
typedef unsigned char IPAddress [4];

class StreamBase{
protected:
	virtual void close(void) = 0;
};

#endif
