#include <server/Plugin.h>

Plugin::Plugin(HttpRequest& req, HttpResponse& resp, Socket& s)
	:request(req), response(resp), socket(s){}

extern "C"{
typedef Plugin * (*FunctionCreatePlugin)(HttpRequest& req, HttpResponse& resp, Socket& s);
}

Plugin * Plugin::loadPlugin(DynamicLoader& dl, HttpRequest& req, HttpResponse& resp, Socket& s){
	FunctionCreatePlugin pFunc = (FunctionCreatePlugin)dl.getSymbol("createPlugin");
	if(pFunc != 0)return pFunc(req, resp, s);
	return 0;
}
