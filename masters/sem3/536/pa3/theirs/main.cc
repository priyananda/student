#include <cstdio>
#include <iostream>
#include "ref_ptr_T.h"
#include "scanner.h"
#include "parser.h"
#include "gram.tab.h"
#include "ast.h"
// **********************************************************************
// main program for testing the parser:
//     1. open file to be parsed (should be named on command line)
//     2. parse it (building AST)
//     3. if parse successful, unparse AST
// **********************************************************************


// GLOBAL variable: the root of the AST built by a (successful) parse)
   ref_ptr<DeclListNode> AST;

int main(int argc, char * argv[])
{
  FILE *inFile;
  int ans;

  // CHECK FOR MISSING ARG; OPEN INPUT FILE
  if (argc < 2){
    std::cerr << "usage: " << argv[0] << " <file>" << std::endl;
    exit(1);
  }

  if ((inFile = fopen(argv[1], "r")) == NULL) {
    std::cerr << "Unable to open " << argv[1] << std::endl;
    exit(1);
  }

  // PARSE INPUT
  yyin = inFile;
  ans = yyparse();
  if (ans == 0) {  // Successful parse
    AST->Unparse();
  }

  return ans;  
}
