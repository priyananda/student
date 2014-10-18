#ifndef HOTTOP_SERVER_H
#define HOTTOP_SERVER_H

#include <net/Socket.h>
#include <net/ServerSocket.h>

class Server{
	static volatile bool terminated;
	static volatile bool restarting;
	static ServerSocket soc;
public:
	static void start();
	static void restart();
	static void terminate();
};

#endif
