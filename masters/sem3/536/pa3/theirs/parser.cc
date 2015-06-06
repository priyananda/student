#include "parser.h"
#include "ast.h"
#include "message.h"

#undef __cplusplus
#include "gram.tab.c"

void yyerror(char *msg)
{
  ReportError(yylval.TOKENval.lineNum, yylval.TOKENval.colNum, msg);
}
