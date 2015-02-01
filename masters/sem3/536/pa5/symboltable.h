// CS 536 : HW1
// author: priyananda( shenoy@cs.wisc.edu )
// date: 10 Sep 2008
// random quote: [Sunset Boulevard] Joe Gillis: There's nothing tragic
//	 about being fifty. Not unless you're trying to be twenty-five.  

#include <fstream>
using std::ostream;

#include "list_T.h"
#include "symbol.h"

/*
 * Represents a collection of symbols
 */
class SymbolTable
{
private:
	//number of buckets in the table
	static const int NUMBER_OF_BUCKETS = 100;
	//actual buckets
	List<SymbolPtr> buckets[NUMBER_OF_BUCKETS];
public:
	//constructor
	SymbolTable();

	//insert the given (pointer to a) Symbol into the SymbolTable. If
	//there is already a Symbol in the table with the same name, you
	//should give an error message and quit (you can use a call to
	//assert to accomplish this --- in that case, you must include
	//<cassert>). Note that case is important, so for example
	//"variableName" is not the same name as "variablename"
	//(but you won't have to worry about this if you just use the
	//``=='' operator to compare two strings). 
	void Insert(SymbolPtr sym);

	// If there is a Symbol in the table with the given name, then
	// return a pointer to that Symbol; otherwise,
	// return NULL (to use NULL, you should include <fstream>). 
	SymbolPtr Lookup(string S);

	//This operation is for debugging. It should print the names
	//of all of the Symbols currently in the table to the given
	//ostream, one per line. It should not print anything else! 
	void Print(ostream & out);

	//Re-initialize the table to be empty by freeing the storage used by
	//each linked list in the array. (You can free the storage used
	//by an individual list L using the function call L.FreeList().) 
	void FreeTable();

	//This is the destructor function; it should just call FreeTable.
	~SymbolTable();

private:
	//calculates a hash for a string. returns a value between 0 and
	//NUMBER_OF_BUCKETS - 1 exculsive
	int hash(const string & s);	
};
