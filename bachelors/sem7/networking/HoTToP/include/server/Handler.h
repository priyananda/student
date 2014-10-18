#ifndef HOTTOP_HANDLER_H
#define HOTTOP_HANDLER_H

#include <server/PluginInfo.h>

#include <regex.h>
#include <string>
using std::string;


class Handler{
	regex_t cp;
	string match;
	const PluginInfo * pInfo;
	bool compiled;

	void clean();
public:
	Handler();
	Handler(const Handler& h);

	void setPluginInfo(const PluginInfo * p){ pInfo = p; }
	const PluginInfo * getPluginInfo() const { return pInfo; }

	void setMatch(const string& m);
	const string& getMatch() const { return match; }

	bool check(const string& m)const ;
	~Handler();
};

#endif
