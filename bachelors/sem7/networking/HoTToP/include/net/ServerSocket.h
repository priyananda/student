#ifndef	H0TT0P_SERVERSOCKET_H
#define	H0TT0P_SERVERSOCKET_H

#include <net/Socket.h>
#include <net/StreamBase.h>
#include <net/SocketInputStream.h>
#include <net/SocketOutputStream.h>

class ServerSocket{
	/** must be network byte order **/
	int port;
	socket_t sdesc;
	/** size of the listen window **/
	int listenSize;
public:
	/** creates an nvalid Server Socket **/
	ServerSocket();
	/** Binds to a port( in n/w byte-order) on local machine **/
	ServerSocket(const int port);
	/** change the size of the listen window **/
	void setListenSize(int _ls){
		listenSize = _ls;
	}
	~ServerSocket();
	/** returns a representation of remote socket **/
	Socket accept();
	void bind(int port);
	void close();
};

#endif
