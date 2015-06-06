// CS 536 : PA4
// author: priyananda( shenoy@cs.wisc.edu )
// date: 2 Nov 2008
// random quote:

#ifndef CS536_PA4_TYPE_CHECKER_H
#define CS536_PA4_TYPE_CHECKER_H

#include <list>
using std::list;

#include <map>
using std::map;

#include "symbol.h"

//list of argument types
struct FunctionSignature
{
	list<SymbolType> arguments;
};

//map of fn name to signatures
class FunctionTable
{
public:
	//only works if such a function exists.beware!
	FunctionSignature & getSignature(string & fnname)
	{
		return fnmap[fnname];
	}
	void addSignature(string & name, FunctionSignature & sig)
	{
		fnmap[name] = sig;
	}

private:
	map<string, FunctionSignature> fnmap;
};

#endif