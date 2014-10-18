#ifndef HOTTOP_CONFIGMANAGER_H
#define HOTTOP_CONFIGMANAGER_H

#include <server/Realm.h>
#include <server/Handler.h>
#include <server/PluginInfo.h>
#include <server/VirtualDirectory.h>
#include <server/HttpErrorHandler.h>

#include <string>
#include <list>
using std::string;
using std::list;

class ConfigManager{
	static string config_dir;
	static string server_dir;
	static int port;
	static string serverRoot;
	static list<PluginInfo> pInfo;
	static list<Realm> realms;
	static list<Handler> handlers;
	static list<VirtualDirectory> vDirs;
	static HttpErrorHandler errHandler;
	static list<string> indexFiles;
public:
	static void init(int argc, char ** argv);
	static void load();
	static void reset();

	static const string& getServerRoot(){ return serverRoot; }
	static const int getPort(){ return port; }

	static const list<PluginInfo>& getPlugins(){ return pInfo; }
	static const list<Realm>& getRealms(){ return realms; }
	static const list<Handler>& getHandlers(){ return handlers; }
	static const list<VirtualDirectory>& getVDirs(){ return vDirs; }
	static const HttpErrorHandler& getErrorHandler(){ return errHandler; }
	static const list<string>& getIndexFiles(){ return indexFiles; }
	friend class ConfigExtractor;
};

#endif

