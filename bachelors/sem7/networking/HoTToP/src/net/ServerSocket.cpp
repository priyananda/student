#include <unistd.h>
#include <fcntl.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cctype>
#include <cstdlib>
using namespace std;

#include <iostream>
#include <net/ServerSocket.h>
#include <config.h>


ServerSocket::ServerSocket(): port(-1),sdesc(-1),listenSize(10){}

ServerSocket::ServerSocket(const int prt):port(prt),sdesc(-1),listenSize(10){
	this->bind(port);
}

void ServerSocket::close(){
	if( sdesc != -1 ) ::close(sdesc);
	sdesc = -1;
}

ServerSocket::~ServerSocket(){
	this->close();
}

void ServerSocket::bind(int prt){
	struct sockaddr_in addr;
	if ( (sdesc = socket( AF_INET , SOCK_STREAM , 0) ) == -1 ){
		throw Exception("NetException :: Cannot create Server Socket" );
	}
	int val = 1;
	setsockopt( sdesc,SOL_SOCKET,SO_REUSEADDR,&val,sizeof(val));
	bzero( & addr , sizeof( struct sockaddr_in ) );
	addr.sin_family = AF_INET;
	addr.sin_port = htons(prt);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	if ( ::bind ( sdesc , (struct sockaddr * ) & addr , sizeof(addr) ) < 0){
		throw Exception("NetException :: Cannot bind to port") ;
	}
	listen(sdesc,listenSize);
}

Socket ServerSocket::accept(){
	if(sdesc == -1) throw Exception("Invalid ServerSocket");
	struct sockaddr_in  client;
	int cl_sd = -1 , cl_len = sizeof(client);
	if (( 
		cl_sd=::accept(sdesc,(struct sockaddr *)&client,(socklen_t*)&cl_len)
		) < 0 ){
		throw Exception("NetException :: Cannot accept client");
	}

	Socket x(cl_sd);
	x.host.setIP( (const char *)&client.sin_addr );
	socklen_t tt = sizeof(client);
	getsockname( cl_sd,(struct sockaddr *) & client,&tt);
	return x;
}
