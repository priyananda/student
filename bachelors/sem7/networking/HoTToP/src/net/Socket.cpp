#include <unistd.h>
#include <fcntl.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cctype>
#include <cstdlib>
using namespace std;

#include <net/Socket.h>
#include <config.h>

Socket::Socket():sdesc(-1){}

Socket::Socket(int sd):sdesc(sd){
	in = SocketInputStream(sdesc);
	out = SocketOutputStream(sdesc);
}

Socket::Socket(const string & _host , int _port )
	:port(_port),sdesc(-1){
	try{
		host = InetAddress::getInetAddress(_host);
		this->connect( _host , _port );
		in = SocketInputStream(sdesc);
		out = SocketOutputStream(sdesc);
	}catch(Exception ae){
		dprintf( ae.toString().c_str() );
		sdesc = -1;
	}
}

Socket::Socket(const InetAddress & ia ,int _port)
	:port(_port), host(ia), sdesc(-1){
	try{
		this->connect( ia,_port);
		in = SocketInputStream(sdesc);
		out = SocketOutputStream(sdesc);
	}catch(Exception ae){
		dprintf( ae.toString().c_str() );
		sdesc = -1;
	}
}

Socket::~Socket(){
	this->close();
}

void Socket::close(){
	if(sdesc != -1) ::close(sdesc);
	sdesc = -1;
}

InputStream	&  Socket::getInputStream(void){
	if(sdesc == -1)
		throw Exception("IOException : cannot create stream ");
	return in;
}

OutputStream & Socket::getOutputStream(void){
	if(sdesc == -1)
		throw Exception("IOException : cannot create stream ");
	return out;
}

void Socket::connect(const InetAddress & hst , int prt ){
	struct hostent * hp;
	struct sockaddr_in addr;
	IPAddress ad;
	if( sdesc != -1 )
		return ;
	if (( sdesc = ::socket( AF_INET , SOCK_STREAM , 0) ) < 0 )
		throw Exception("NetException :: Cannot create Socket" );

	bzero( & addr , sizeof( struct sockaddr_in ) );
	addr.sin_family = AF_INET;
	addr.sin_port = htons(prt);
	InetAddress::str2ip( hst.getIP() , ad );
	if (( hp = ::gethostbyaddr(ad,4,AF_INET) ) == NULL)
		throw Exception("NetException :: Cannot reach server") ;
	bcopy(hp->h_addr, &addr.sin_addr, hp->h_length);
	if ( ::connect( sdesc , (struct sockaddr *) & addr , sizeof(addr)) < 0 )
		throw Exception("NetException :: Cannot connect to  server") ;
}
