#include <utils/ConfigManager.h>
#include <utils/ConfigExtractor.h>
#include <utils/StringUtils.h>
#include <unistd.h>

// List of static variables.
string ConfigManager::config_dir;
string ConfigManager::server_dir;
string ConfigManager::serverRoot;
int ConfigManager::port;
list<PluginInfo> ConfigManager::pInfo;
list<Realm> ConfigManager::realms;
list<Handler> ConfigManager::handlers;
list<VirtualDirectory> ConfigManager::vDirs;
list<string> ConfigManager::indexFiles;
HttpErrorHandler ConfigManager::errHandler;

// TODO: Rewrite with a non hardcoded one.
void ConfigManager::init(int argc, char ** argv){
	char buff[1024]; 
	int len = readlink("/proc/self/exe",buff,1024);
	buff[len] = 0;
	server_dir = StringUtils::dirName(buff);
	config_dir = server_dir + "/config/";
}

void ConfigManager::load(){
	ConfigExtractor extractor;
	extractor.extract();
}

void ConfigManager::reset(){
	serverRoot = "";
	port = 0;
	pInfo.erase(pInfo.begin(), pInfo.end());
	realms.erase(realms.begin(), realms.end());
	handlers.erase(handlers.begin(), handlers.end());
	vDirs.erase(vDirs.begin(), vDirs.end());
	indexFiles.erase(indexFiles.begin(), indexFiles.end());
	errHandler.reset();
}
