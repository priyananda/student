// CS 536 : HW1
// author: priyananda( shenoy@cs.wisc.edu )
// date: 10 Sep 2008
// random quote: [ETOTSM] Mary: Blessed are the forgetful, for they get
//	the better even of their blunders.

#include "symboltable.h"

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include <fstream>
using std::ifstream;

#include <string>
using std::string;

int main(int argc, char * argv[])
{
	--argc;argv++;

	if( argc == 0 ){
		cerr << "please specify the input filename as argument." << endl;
		return 42;
	}
	
	ifstream file(argv[0]);
	if(file.bad() || file.fail() ){
		cerr << "file " << argv[0] << " doesn't exist. or you can't access it. or something." << endl;
		return 42;
	}
	
	SymbolTable table;
	string token;

	while(file >> token)
		table.Insert(new Symbol(token));

	file.close();
	
	table.Print(cout);

	return 0;
}
