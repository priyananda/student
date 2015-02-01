// **********************************************************************
// This is an incomplete version of the program needed to test your
// "Simple" scanner.
//
// When this program is run, it opens the file named on the command line,
// then calls the scanner (yylex) until it returns zero (indicating
// end-of-file).  For each token returned by the scanner, the token "name"
// is output; for the ID token, the actual identifier is also output.
//

#include <cstdio>
#include <iostream>
#include "scanner.h"
#include "gram.tab.h"

YYSTYPE yylval;
 
int main(int argc, char * argv[])
{
  FILE *inFile;  // NOTE: yylex requires a FILE *, not an ifstream
  int token;
  const int EndOfFile = 0;

  // CHECK FOR MISSING ARG; OPEN INPUT FILE
  if (argc < 2){
    std::cerr << "usage: " << argv[0] << " <file>" << std::endl;
    exit(1);
  }

  if ((inFile = fopen(argv[1], "r")) == NULL) {
    std::cerr << "Unable to open " << argv[1] << std::endl;
    exit(1);
  }

  // SCAN INPUT UNTIL EOF; WRITE EACH TOKEN SCANNED TO COUT
  yyin = inFile;
  token = yylex();
  while(token != EndOfFile) {
    switch (token) {
      case ID:
        std::cout << "ID (" << *(yylval.strVal) << ")" << std::endl;
        break;
      case LCURLY:
        std::cout << "LCURLY" << std::endl;
        break;
      default:
        std::cerr << "unknown token: " << token << std::endl;
        exit(1);     
    }
    token = yylex();
  }
  return 0;
}
