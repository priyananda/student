// CS 536 : PA2
// author: priyananda( shenoy@cs.wisc.edu )
// date: 3 Oct 2008
// random quote:

// This is an incomplete version of the program needed to test your
// "Simple" scanner.
//
// When this program is run, it opens the file named on the command line,
// then calls the scanner (yylex) until it returns zero (indicating
// end-of-file).  For each token returned by the scanner, the token "name"
// is output; for the ID token, the actual identifier is also output.
//

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include <cstdlib>

#include "gram.tab.h"
#include "helper.h"

YYSTYPE yylval;

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
  
  int token = 0;
  while((token = yylex()) != 0)
  	LexerHelper::printToken(token,yylval);
  	
  fclose(yyin);

  return 0;
}
