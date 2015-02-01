// CS 536 : PA3
// author: priyananda( shenoy@cs.wisc.edu )
// date: 23 Oct 2008
// random quote:

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include <cstdlib>

#include "ast.h"
#include "scanner.h"
#include "helper.h"

ref_ptr<ProgramNode> astRoot;

extern int yyparse();

int main(int argc, char * argv[])
{
	--argc;argv++;

	if (argc < 1){
		cerr << "input filename missing" << endl;
		exit(1);
	}

	if ((yyin = fopen(argv[0], "r")) == NULL) {
		cerr << "File " << argv[0] << " doesn't exist. or something." << endl;
		exit(1);
	}
	
	if(yyparse() == 0)
		if( astRoot->AnalyzeNames())
			astRoot->CheckTypes();

	fclose(yyin);

	return 0;
}
