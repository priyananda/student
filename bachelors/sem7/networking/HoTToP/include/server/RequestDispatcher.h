#ifndef HOTTOP_REQDISPATCHER_H
#define HOTTOP_REQDISPATCHER_H

#include <net/Socket.h>
#include <server/HttpRequest.h>
#include <server/VirtualDirectory.h>
#include <server/Handler.h>

#define ENOPAGE 500

class RequestDispatcher{
	Socket& soc;
	HttpRequest * hr;
	bool close;

	void clean(){ if(hr) delete hr; hr = 0; }

	const VirtualDirectory * findVDir(const string& path);
	int splitPath();
	int findFile();
	const Handler * findHandler();

public:
	RequestDispatcher(Socket& s) : soc(s), hr(NULL), close(false){}

	bool prepareRequest();
	bool dispatchRequest();

	~RequestDispatcher(){ clean(); }
};

#endif
