// CS 536 : HW1
// author: priyananda( shenoy@cs.wisc.edu )
// date: 10 Sep 2008
// random quote: [The Shawshank Redemption] Red: Hope is a dangerous thing.
//	 Hope can drive a man insane.

#include <string>
using std::string;

/*
 * Represents one token or symbol
 */
class Symbol
{
public:
	//holds the symbol.
	string symbolName;
public:
	//constructor
	Symbol(string S);
};
