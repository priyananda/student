// CS 536 : PA4
// author: priyananda( shenoy@cs.wisc.edu )
// date: 2 Nov 2008
// random quote:

#include "scopelist.h"

ScopeList::ScopeList() : inLocalScope(false)
{
}

SymbolPtr ScopeList::Lookup(const string & name, bool currentScopeOnly)
{
	//first check in local
	if(inLocalScope){
		SymbolPtr entry = functionScope.Lookup(name);
		if(currentScopeOnly || entry != NULL)
			return entry;
	}
	
	//then check in global
	return globalScope.Lookup(name);
}

void ScopeList::BeginScope()
{
	inLocalScope = true;
}

void ScopeList::EndScope()
{
	inLocalScope = false;
	functionScope.FreeTable();
}

void ScopeList::Insert(const string & name, SymbolType type)
{
	if(inLocalScope)
		functionScope.Insert(new Symbol(name,type));
	else
		globalScope.Insert(new Symbol(name,type));
}

ScopeList::~ScopeList()
{
	functionScope.FreeTable();
	globalScope.FreeTable();
}
