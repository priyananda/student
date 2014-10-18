#ifndef	H0TT0P_INETADDRESS_H
#define	H0TT0P_INETADDRESS_H

#include <net/StreamBase.h>

/**
 * This class represents all forms of an IP address
 * We consider only IPv4 addresses
 **/
class InetAddress{
	IPAddress addr;
	string hostname;
	/*
	 * Warning : Constructors declared unsafe . No inits may be done . Donot
	 * call these outside . This goes for friends too.
	 */
	InetAddress( const char * h,const char * ip):hostname(h){
		for(int i =0 ; i < 4 ; ++i )
			addr[i] = ip[i];
	}
	/** Notmuch of a copy constructor **/
	void setIP(const char * ip){
		for(int i =0 ; i < 4 ; ++i )
			addr[i] = ip[i];
	}
public :
	/** Invalid InetAddress , basically for arrays **/
	InetAddress(){}
	/** This returns it in the form "x.x.x.x" **/
	string getIP() const ;
	inline string getHostName() const{
		return hostname;
	}
	// Helper funcs
	/** This gets the address in any supported form **/
	static InetAddress getInetAddress(const string & host);
	static InetAddress getHostByName(const string & hname);
	/**
	 * This gives the address if the input is valid IP address
	 * in the form "x.x.x.x"
	 * throws InvalidIPAddress exception
	 **/
	static InetAddress getHostByIP(const string & ipaddr);
	/** Hardcoded, but perfectly right **/
	static inline InetAddress getLocalHost(){
		return getHostByIP("127.0.0.1");
	}
	/** checks for proper format **/
	static bool isValidIP(const string & host);
	static bool isUnicastIP(const string & host){
		return true;
	}
	/** I dont know the format of Multicast IP **/
	static bool isMulticastIP(const string & host){
		return false;// Eh ! , hardcoded for time being
	}
	/**
	 * String representation to IP address ie
	 * "192.168.1.168" to (unsigned char []) { 192,168,1,168 };
	 * throws InvalidIPException
	 **/
	static bool str2ip(const string & ,IPAddress &);
	friend class Socket;
	friend class ServerSocket;
};

#endif
