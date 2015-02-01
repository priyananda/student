%{
// **********************************************************************
// Simple scanner specification.
// **********************************************************************
%}

DIGIT           [0-9]
LETTER          [a-zA-Z]
NEWLINE         [\n]
WHITESPACE      [ \t]

%{
#include <string>
#include <cstdlib>
#include <limits.h>
#include <float.h>
#include "scanner.h"
#include "message.h"
#include "gram.tab.h"	/* token definitions etc.
	 		 * this file will be generated from grammar spec by
			 * bison
			 */

static int curLine = 1; /* current line number */
static int curCol  = 1; /* current column number */

int StrToInt(char *S);  /* Auxiliary function for processing INTLITERAL */
float StrToFloat(char *S);  /* Auxiliary function for processing FLOATLITERAL */

%}

%%

%{
    /* Comments --------------------------------------- */
%}

"//"[^\n]*                           { curCol += yyleng; } 

%{
    /* String literals --------------------------------------- */
%}

["]([^\n"\\]|[\\][^\n])*["]         {
                                       yylval.strVal = new std::string(yytext);
                                       yylval.lineNum = curLine;
                                       yylval.colNum = curCol;
                                       curCol += yyleng;
                                       return(STRINGLITERAL);
                                     }

%{
    /* Unterminated string literals --------------------------------- */
%}

["]([^\n"\\]|[\\][^\n])*[\\]?        {
                                       ReportError(curLine, curCol,
                                            "ignoring unterminated string literal");
                                       curCol += yyleng;
                                     }

%{
    /* Reserved words --------------------------------------- */
%}

"int"                                {
                                       yylval.lineNum = curLine;
                                       yylval.colNum = curCol;
                                       curCol += yyleng;
                                       return(INTEGER);
                                     }
"float"                              {
                                       yylval.lineNum = curLine;
                                       yylval.colNum = curCol;
                                       curCol += yyleng;
                                       return(FLOAT);
                                     }
"bool"                               {
                                       yylval.lineNum = curLine;
                                       yylval.colNum = curCol;
                                       curCol += yyleng;
                                       return(BOOLEAN);
                                     }
"String"                             {
                                       yylval.lineNum = curLine;
                                       yylval.colNum = curCol;
                                       curCol += yyleng;
                                       return(STRING);
                                     }
"void"                               {
                                       yylval.lineNum = curLine;
                                       yylval.colNum = curCol;
                                       curCol += yyleng;
                                       return(VOID);
                                     }
"true"                               {
                                       yylval.lineNum = curLine;
                                       yylval.colNum = curCol;
                                       curCol += yyleng;
                                       return(TRUE);
                                     }
"false"                              {
                                       yylval.lineNum = curLine;
                                       yylval.colNum = curCol;
                                       curCol += yyleng;
                                       return(FALSE);
                                     }
"if"                                 {
                                       yylval.lineNum = curLine;
                                       yylval.colNum = curCol;
                                       curCol += yyleng;
                                       return(IF);
                                     }
"else"                               {
                                       yylval.lineNum = curLine;
                                       yylval.colNum = curCol;
                                       curCol += yyleng;
                                       return(ELSE);
                                     }
"while"                              {
                                       yylval.lineNum = curLine;
                                       yylval.colNum = curCol;
                                       curCol += yyleng;
                                       return(WHILE);
                                     }
"write"                              {
                                       yylval.lineNum = curLine;
                                       yylval.colNum = curCol;
                                       curCol += yyleng;
                                       return(WRITE);
                                     }
"return"                             {
                                       yylval.lineNum = curLine;
                                       yylval.colNum = curCol;
                                       curCol += yyleng;
                                       return(RETURN);
                                     }

%{
    /* Other patterns --------------------------------------- */
%}

"{"                                  { 
                                       yylval.lineNum = curLine;
                                       yylval.colNum = curCol;
                                       curCol += yyleng;
                                       return(LCURLY);
                                     }
"}"                                  {
                                       yylval.lineNum = curLine;
                                       yylval.colNum = curCol;
                                       curCol += yyleng;
                                       return(RCURLY);
                                     }
"("                                  {
                                       yylval.lineNum = curLine;
                                       yylval.colNum = curCol;
                                       curCol += yyleng;
                                       return(LPAREN);
                                     }
")"                                  {
                                       yylval.lineNum = curLine;
                                       yylval.colNum = curCol;
                                       curCol += yyleng;
                                       return(RPAREN);
                                     }
","                                  {
                                       yylval.lineNum = curLine;
                                       yylval.colNum = curCol;
                                       curCol += yyleng;
                                       return(COMMA);
                                     }
"="                                  {
                                       yylval.lineNum = curLine;
                                       yylval.colNum = curCol;
                                       curCol += yyleng;
                                       return(ASSIGN);
                                     }
";"                                  {
                                       yylval.lineNum = curLine;
                                       yylval.colNum = curCol;
                                       curCol += yyleng;
                                       return(SEMICOLON);
                                     }
"+"                                  {
                                       yylval.lineNum = curLine;
                                       yylval.colNum = curCol;
                                       curCol += yyleng;
                                       return(PLUS);
                                     }
"-"                                  {
                                       yylval.lineNum = curLine;
                                       yylval.colNum = curCol;
                                       curCol += yyleng;
                                       return(MINUS);
                                     }
"*"                                  {
                                       yylval.lineNum = curLine;
                                       yylval.colNum = curCol;
                                       curCol += yyleng;
                                       return(TIMES);
                                     }
"/"                                  {
                                       yylval.lineNum = curLine;
                                       yylval.colNum = curCol;
                                       curCol += yyleng;
                                       return(DIVIDE);
                                     }
"!"                                  {
                                       yylval.lineNum = curLine;
                                       yylval.colNum = curCol;
                                       curCol += yyleng;
                                       return(NOT);
                                     }
"&&"                                 {
                                       yylval.lineNum = curLine;
                                       yylval.colNum = curCol;
                                       curCol += yyleng;
                                       return(AND);
                                     }
"||"                                 {
                                       yylval.lineNum = curLine;
                                       yylval.colNum = curCol;
                                       curCol += yyleng;
                                       return(OR);
                                     }
"=="                                 {
                                       yylval.lineNum = curLine;
                                       yylval.colNum = curCol;
                                       curCol += yyleng;
                                       return(EQUALS);
                                     }
"!="                                 {
                                       yylval.lineNum = curLine;
                                       yylval.colNum = curCol;
                                       curCol += yyleng;
                                       return(NOTEQUALS);
                                     }
"<"                                  {
                                       yylval.lineNum = curLine;
                                       yylval.colNum = curCol;
                                       curCol += yyleng;
                                       return(LESS);
                                     }
">"                                  {
                                       yylval.lineNum = curLine;
                                       yylval.colNum = curCol;
                                       curCol += yyleng;
                                       return(GREATER);
                                     }
"<="                                 {
                                       yylval.lineNum = curLine;
                                       yylval.colNum = curCol;
                                       curCol += yyleng;
                                       return(LESSEQ);
                                     }
">="                                 {
                                       yylval.lineNum = curLine;
                                       yylval.colNum = curCol;
                                       curCol += yyleng;
                                       return(GREATEREQ);
                                     }

%{
    /* Identifiers --------------------------------------- */
%}

({LETTER}|_)({LETTER}|{DIGIT}|_)*    {
                                       yylval.strVal = new std::string(yytext);
                                       yylval.lineNum = curLine;
                                       yylval.colNum = curCol;
                                       curCol += yyleng;
                                       return(ID);
                                     }

%{
    /* Integers --------------------------------------- */
%}

{DIGIT}+                             {
                                       yylval.intVal = StrToInt(yytext);
                                       yylval.lineNum = curLine;
                                       yylval.colNum = curCol;
                                       curCol += yyleng;
                                       return(INTLITERAL);

                                     }

{DIGIT}*[.]{DIGIT}+                  {
                                       yylval.floatVal = StrToFloat(yytext);
                                       yylval.lineNum = curLine;
                                       yylval.colNum = curCol;
                                       curCol += yyleng;
                                       return(FLOATLITERAL);

                                     }

%{
    /* Whitespace --------------------------------------- */
%}

{NEWLINE}+                          { 
                                       curLine += yyleng;
                                       curCol = 1;
                                     }
{WHITESPACE}+                        { curCol += yyleng; }

%{
    /* Default --------------------------------------- */
%}

.                                    { ReportError(curLine, curCol,
                                            "ignoring illegal character");
                                       curCol++;
                                     }

%%

// **********************************************************************
// StrToInt
//    given: a (C-style) string that represents an integer literal
//    return: the corresponding value if within range;
//            otherwise, issue a warning and return INT_MAX
// **********************************************************************
int StrToInt(char *S)
{
  double val;
  
  val = atof(S);
  if (val > INT_MAX) {
      ReportWarning(curLine, curCol,
                    "integer literal too large; using max value");
        return(INT_MAX);
  }
  return(int(val));
}


// **********************************************************************
// StrToFloat
//    given: a (C-style) string that represents a float literal
//    return:
//       0.0 if the string represents 0.0;
//       the corresponding value if within the range [FLT_MIN .. FLT_MAX];
//       otherwise, issue a warning and returns FLT_MAX or FLT_MIN
//       depending on whether the value is too large or too small, respectively.
// **********************************************************************
float StrToFloat(char *S)
{
  double val;
  
  val = atof(S);
  if (val == 0.0) {
      return(float(val));
  }
  if (val > FLT_MAX) {
      ReportWarning(curLine, curCol,
                    "float literal too large; using max value");
        return(FLT_MAX);
  }
  if (val < FLT_MIN) {
      ReportWarning(curLine, curCol,
                    "float literal too small; using min value");
        return(FLT_MIN);
  }
  return(float(val));
}
