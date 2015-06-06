// CS 536 : HW1
// author: priyananda( shenoy@cs.wisc.edu )
// date: 10 Sep 2008
// random quote: [Kill Bill 2] Bill: Clark Kent is Superman's
//		critique on the whole human race.

#include "symboltable.h"
#include <cstdlib>
#include <iostream>

SymbolTable::SymbolTable()
{
}

void SymbolTable::Insert(Symbol *sym)
{
	int index = hash(sym->symbolName);
	buckets[index].Reset();
	while(!buckets[index].AtEnd()){
		if(buckets[index].Current()->symbolName == sym->symbolName ){
			//there already exists a symbol with the same name
			//assert etc etc
			std::cout << sym->symbolName << " is repeated!" << std::endl;
			exit(42);
		}
		buckets[index].Next();
	}
	buckets[index].AddToEnd(sym);
}

Symbol* SymbolTable::Lookup(string S)
{
	int index = hash(S);
	buckets[index].Reset();
	while(!buckets[index].AtEnd()){
		if(buckets[index].Current()->symbolName == S)
			return buckets[index].Current();
		buckets[index].Next();
	}
	//didn't find anything
	return NULL;
}

void SymbolTable::Print(ostream & out)
{
	for(int i = 0 ; i < NUMBER_OF_BUCKETS; ++i){
		buckets[i].Reset();
		while(!buckets[i].AtEnd()){
			out << buckets[i].Current()->symbolName << std::endl;
			buckets[i].Next();
		}
	}
}

void SymbolTable::FreeTable()
{
	for(int i = 0 ; i < NUMBER_OF_BUCKETS; ++i)
		buckets[i].FreeList();
}

SymbolTable::~SymbolTable()
{
	FreeTable();
}

//rather arbitrary hash function
//whatever, it works
int SymbolTable::hash(const string & s)
{
	int sum = 0;
	int slength =int(s.length());
	for(int i = 0 ; i < slength; ++i )
		sum += ((i+1) * s[i]) % 9191;
	return sum % NUMBER_OF_BUCKETS;
}
