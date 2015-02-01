// CS 536 : PA2
// author: priyananda( shenoy@cs.wisc.edu )
// date: 3 Oct 2008
// random quote: 

#ifndef CS536_HELPER_H
#define CS536_HELPER_H

#include "scanner.h"

//contains some methods which are used to by the lexer
class LexerHelper
{
private:
	//the current line number
	static int line_num;
	//the current column number
	static int col_num;
public:
	//sets the line and column numbers
	//of the token, and updates the global
	//line and column counter
	static void setLineColNumber(TokenType & yylval, int yyleng);

	//increments the global line counter and
	//reinitializes column counters
	static void newLine();

	//extracts the string from yytext into token
	static void extractString(TokenType & yylval,const char * yytext);

	//extracts the integer from yytext into token, after validation
	static void extractInt(TokenType & yylval,const char * yytext);

	//extracts the float from yytext into token, after validation
	static void extractFloat(TokenType & yylval,const char * yytext);

	//prints the token, depending on type of the token
	static void printToken(int tokenType, const TokenType & tt);

	//prints error message for unterminated strings
	static void errorUnterminatedString(const TokenType & yylval,const char * yytext);

	//prints error message for illegal characters
	static void errorIllegalCharacter(const TokenType & yylval,const char * yytext);
};
#endif
