// CS 536 : PA4
// author: priyananda( shenoy@cs.wisc.edu )
// date: 2 Nov 2008
// random quote: 

#ifndef CS536_SCOPE_LIST_H
#define CS536_SCOPE_LIST_H

#include "symboltable.h"

//list of symboltables for various scopes. Not really a list
//since only one level of nesting is allowed.
class ScopeList
{
public:
	ScopeList();
	
	//if the name exists in symbol table, returns a pointer to that
	//else returns NULL
	//if currentScopeOnly = true , looks only in function scope
	//else looks in function and global scope in that order.
	SymbolPtr Lookup(const string & name, bool currentScopeOnly);

	//entering a new scope
	void BeginScope();
	//exiting a scope
	void EndScope();
	
	//inserts a new symbol in the st
	void Insert(const string & name, SymbolType type);
	
	//clean up all the scopes
	~ScopeList();
private:
	SymbolTable globalScope;
	SymbolTable functionScope;
	bool inLocalScope;
};

#endif
