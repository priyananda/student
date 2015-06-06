#ifndef SCANNER_GUARD
#define SCANNER_GUARD

#include <cstdio>
#include <string>

extern FILE *yyin;  // the file from which the scanner reads
int yylex();        // the scan function itsef

// The type of the value associated with each token
struct TokenType {
  int lineNum;
  int colNum;
  int  intVal;      // only for integer literals
  float floatVal;   // only for float literals
  std::string * strVal;  // only for string literals or identifiers
};

#endif
