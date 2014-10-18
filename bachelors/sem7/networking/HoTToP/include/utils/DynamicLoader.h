#ifndef HOTTOP_DYNAMIC_LOADER_H
#define HOTTOP_DYNAMIC_LOADER_H

#include <string>
using std::string;

class DynamicLoader{
	void * dlHandle;
public:
	DynamicLoader(const string& str);
	void * getSymbol(const string& str);
	void close();
	virtual ~DynamicLoader();
};

#endif
