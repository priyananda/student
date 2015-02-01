%{
// CS 536 : PA3
// author: priyananda( shenoy@cs.wisc.edu )
// date: 23 Oct 2008
// random quote:
%}

DIGIT		[0-9]
LETTER		[a-zA-Z]
WHITESPACE	[ \t]
NEWLINE		[ \n]

%{
#include <string>
using std::string;

#include "scanner.h"
#include "ast.h"
#include "gram.tab.h"
#include "helper.h"

//some helper methods. to reduce typing
static inline void set_lc()
{
	LexerHelper::setLineColNumber(yylval.TOKENval,yyleng);
}
static inline void new_line()
{
	LexerHelper::newLine();
}
static inline void extract_string()
{
	LexerHelper::extractString(yylval.TOKENval,yytext);
}
static inline void extract_int()
{
	LexerHelper::extractInt(yylval.TOKENval,yytext);
}
static inline void extract_float()
{
	LexerHelper::extractFloat(yylval.TOKENval,yytext);
}

//Macros are evil. I use macros. Therefore I am evil.
//Muhahahahaha
#define OP_RETURN(x) set_lc(); return x;

%}

%%

"{"	 	 {OP_RETURN(LCURLY)}
"}"	 	 {OP_RETURN(RCURLY)}
"("	 	 {OP_RETURN(LPAREN)}
")"	 	 {OP_RETURN(RPAREN)}
","	 	 {OP_RETURN(COMMA)}
"="	 	 {OP_RETURN(ASSIGN)}
";"	 	 {OP_RETURN(SEMICOLON)}
"+"	 	 {OP_RETURN(PLUS)}
"-"	 	 {OP_RETURN(MINUS)}
"*"	 	 {OP_RETURN(TIMES)}
"/"	 	 {OP_RETURN(DIVIDE)}
"!"	 	 {OP_RETURN(NOT)}
"&&" 	 {OP_RETURN(AND)}
"||" 	 {OP_RETURN(OR)}
"==" 	 {OP_RETURN(EQUALS)}
"!=" 	 {OP_RETURN(NOTEQUALS)}
"<"	 	 {OP_RETURN(LESS)}
">"	 	 {OP_RETURN(GREATER)}
"<=" 	 {OP_RETURN(LESSEQ)}
">=" 	 {OP_RETURN(GREATEREQ)}

"int"    {OP_RETURN(INTEGER)}
"float"  {OP_RETURN(FLOAT)}
"bool"   {OP_RETURN(BOOLEAN)}
"String" {OP_RETURN(STRING)}
"void"   {OP_RETURN(VOID)}
"true"   {OP_RETURN(TRUE)}
"false"  {OP_RETURN(FALSE)}
"if"     {OP_RETURN(IF)}
"else"   {OP_RETURN(ELSE)}
"while"  {OP_RETURN(WHILE)}
"write"  {OP_RETURN(WRITE)}
"return" {OP_RETURN(RETURN)}

{WHITESPACE}+			    		{ set_lc();   }
{NEWLINE}							{ new_line(); }
"//"(.*)({NEWLINE}|$)				{ new_line(); /* comment, ignore it */ }

({LETTER}|_)({LETTER}|{DIGIT}|_)*   { set_lc(); extract_string(); 	return ID; }
{DIGIT}+							{ set_lc(); extract_int(); 		return INTLITERAL; }
{DIGIT}*"."{DIGIT}+				    { set_lc(); extract_float(); 	return FLOATLITERAL; }
\"([^"\n\\]|(\\.))*\"				{ set_lc(); extract_string(); 	return STRINGLITERAL; }

%{//handle unterminated strings %}
["]([^\n"\\]|[\\][^\n])*[\\]?		{ set_lc(); new_line(); LexerHelper::errorUnterminatedString(yylval.TOKENval,yytext);}

%{//handle illegal characters%}
.									{ set_lc(); LexerHelper::errorIllegalCharacter(yylval.TOKENval,yytext);}
%%
