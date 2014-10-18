#include <unistd.h>
#include <fcntl.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cctype>
#include <cstdlib>

#include <net/InetAddress.h>

InetAddress InetAddress::getInetAddress( const string & host ){
    if( isValidIP(host) )
        return getHostByIP(host);
    else
        return getHostByName(host);
}

InetAddress InetAddress::getHostByName(const string & host){
    struct hostent * hp;
    if ( (hp = gethostbyname(host.c_str())) == NULL ){
        throw Exception("NetException :: Host Unreachable") ;
    }
    return InetAddress( hp->h_name , hp->h_addr );
}

InetAddress InetAddress::getHostByIP(const string & host){
    struct hostent * hp;
	IPAddress ipt;
	try{
		InetAddress::str2ip( host , ipt);
	}catch(Exception ae){
		throw Exception("InvalidIPAddress");
	}
    if ( (hp = gethostbyaddr(ipt,4,AF_INET)) == NULL ){
        throw Exception("NetException :: Host Unreachable") ;
    }
    return InetAddress( hp->h_name , hp->h_addr );
}
/*
 * Warning ! hard-coding ahead.converts a proper string "192.168.1.101"
 * to unsigned char[4]. By the way ip[0] = 192 ... 
 */ 
bool InetAddress::str2ip(const string & str,IPAddress & ip){
	int pos[3] = { -1,-1,-1},cnt=0;
	for ( unsigned int i = 0 ; i < str.length() ; ++i){
		if( str[i] == (unsigned char)'.' ){  pos[cnt++] = i ;continue;}
		if( !::isdigit(str[i]) ) throw Exception("Invalid IP Address");
	}
	if( cnt != 3 ) throw Exception("Invalid IP Address");
	ip[0] = (unsigned char)
		::atoi( str.substr(0,pos[0]).c_str() );
	ip[1] = (unsigned char)
		::atoi( str.substr(pos[0] + 1,pos[1] - pos[0] - 1).c_str() );
	ip[2] = (unsigned char)
		::atoi( str.substr(pos[1] + 1,pos[2] - pos[1] - 1).c_str() );
	ip[3] = (unsigned char)
		::atoi( str.substr(pos[2] + 1,str.length() - pos[2] -1 ).c_str());
	return true;	
}
/**
 * Cheating ! abuse exception handling to get boolean 
 **/ 
bool InetAddress::isValidIP(const string & host){ 
	try{
		IPAddress temp;
		str2ip(host,temp);
		return true;
	}catch(Exception a){
		return false;
	}
}

string InetAddress::getIP() const{
	char buff[16] = {0};
	sprintf( buff,"%u.%u.%u.%u" , addr[0],addr[1],addr[2],addr[3] );
	return string(buff);
}
