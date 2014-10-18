#include <plugins/DefaultPlugin.h>
#include <iostream>
using namespace std;

extern "C" {

Plugin * createPlugin(HttpRequest& req, HttpResponse& resp, Socket& s){
	return new DefaultPlugin(req, resp, s);
}

}

DefaultPlugin::DefaultPlugin(HttpRequest& req, HttpResponse& resp, Socket& s)
	: Plugin(req, resp, s){
}

void DefaultPlugin::exec(){
	OutputStream& out = socket.getOutputStream();
	string line = "Hello from default plugin\n";
	out.write(line.c_str(), line.length());
	line = ConfigManager::getServerRoot();
	out.write(line.c_str(), line.length());
}

DefaultPlugin::~DefaultPlugin(){}
