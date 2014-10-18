#ifndef HOTTOP_PLUGIN_H
#define HOTTOP_PLUGIN_H

#include <server/HttpRequest.h>
#include <server/HttpResponse.h>
#include <net/Socket.h>
#include <utils/DynamicLoader.h>

class Plugin{
protected:
	HttpRequest& request;
	HttpResponse& response;
	Socket& socket;
public:
	Plugin(HttpRequest& req, HttpResponse& resp, Socket& sock);

	virtual void exec() = 0;

	~Plugin(){}
	
	static Plugin * loadPlugin(DynamicLoader& dl, HttpRequest& req,
		HttpResponse& resp, Socket& soc);
};

#endif
