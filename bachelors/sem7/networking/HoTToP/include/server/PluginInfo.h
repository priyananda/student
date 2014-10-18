#ifndef HOTTOP_PLUGIN_INFO_H
#define HOTTOP_PLUGIN_INFO_H

#include <string>
using std::string;

enum Types { t_exec = 1, t_read, t_any };

class PluginInfo{
	string name, path, configFile;
	Types type;
public:

	void setType(Types t){ type = t;}
	Types getType() const {return type;}

	void setName(const string& n){ name = n;}
	const string& getName() const { return name;}

	void setPath(const string& p){ path = p; }
	const string& getPath() const { return path; }

	void setConfig(const string& config){ configFile = config; }
	const string& getConfig() const { return configFile; }
};

#endif
