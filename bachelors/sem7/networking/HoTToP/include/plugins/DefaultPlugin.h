#ifndef HOTTOP_DEFAULT_PLUGIN_H
#define HOTTOP_DEFAULT_PLUGIN_H

#include <server/Plugin.h>

class DefaultPlugin : public Plugin {
public:
	DefaultPlugin(HttpRequest& hReq, HttpResponse& hResp, Socket& soc);
	virtual void exec();
	virtual ~DefaultPlugin();
};

#endif
