#ifndef H0TT0P_SOCKET_H
#define H0TT0P_SOCKET_H

#include <net/StreamBase.h>
#include <net/SocketInputStream.h>
#include <net/SocketOutputStream.h>
#include <net/InetAddress.h>

class Socket{
public:
	InetAddress host;
	/** port must be in network byte order **/
	int port;
	socket_t sdesc;
	SocketInputStream in;
	SocketOutputStream out;
public:
	Socket();
	/** Creates and connects a socket , throws NetException **/
	Socket(const string & host,int port);
	/** Creates and connects a socket , throws NetException **/
	Socket(const InetAddress & ia , int port);
	/** Basically a copy constructor , Unsafe for other fields **/
	Socket(int sd);
	/** kills the Socket,calls close **/
	~Socket();
	/** establishes a connection , throws NetException **/
	void connect(const string  & host,int port ){
		this->connect( InetAddress::getInetAddress(host) , port );
	}
	void connect(const InetAddress & host,int port );
	void close();
	// gets the InputStream handle , throws IOException
	InputStream  & getInputStream ();
	// gets the OutputStream handle , throws IOException
	OutputStream & getOutputStream();
	// get Remote Port
	inline int getPort(){
		return port;
	}
	friend class ServerSocket;
};

#endif
