#ifndef HOTTOP_VDIR_H
#define HOTTOP_VDIR_H

#include <server/Handler.h>
#include <server/Realm.h>
#include <utils/StringUtils.h>

#include <string>
#include <vector>
using std::string;
using std::vector;

class VirtualDirectory{
	string vPath, rPath;
	Types type;

	// Optional
	vector<Handler> handlers;
	const Realm * realm;

public:

	void setVPath(const string& v){ vPath = StringUtils::normalize(v); }
	const string& getVPath() const { return vPath; }

	void setRPath(const string& r){ rPath = StringUtils::normalize(r); }
	const string& getRPath() const { return rPath; }

	void setType(Types t){ type = t;}
	Types getType() const { return type; }

	void setRealm(const Realm * r){ realm = r; }
	const Realm* getRealm() const { return realm; }

	void addHandler(const Handler& h){ handlers.push_back(h); }
	const vector<Handler>& getHandlers() const { return handlers; }

	int operator < (const VirtualDirectory& vDir) const {
		return vPath.length() > vDir.vPath.length();
	}
};

#endif
