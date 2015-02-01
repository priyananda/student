#ifndef PARSER_GUARD
#define PARSER_GUARD

#include "ref_ptr_T.h"
#include "scanner.h" // defines TokenType
#include "ast.h"

int yyparse();     // the parse function
void yyerror(char *msg);

#endif
