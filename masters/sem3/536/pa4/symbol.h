// CS 536 : PA4
// author: priyananda( shenoy@cs.wisc.edu )
// date: 2 Nov 2008
// random quote: [The Shawshank Redemption] Red: Hope is a dangerous thing.
//	 Hope can drive a man insane.

#ifndef CS536_PA4_SYMBOL_H
#define CS536_PA4_SYMBOL_H

#include <string>
using std::string;

#include "ref_ptr_T.h"

enum SymbolType
{
	IntType,
	FloatType,
	BoolType,
	StringType,
	FnType,
	ErrorType,
	NoType = 100
};

/*
 * Represents one token or symbol
 */
class Symbol
{
public:
	//constructor
	Symbol(string S, SymbolType type);

	//holds the symbol.
	string symbolName;
	
	//reference counter
	RefCounter count;

	//type of the symbol	
	SymbolType type;
};

typedef ref_ptr< Symbol > SymbolPtr;

#endif
