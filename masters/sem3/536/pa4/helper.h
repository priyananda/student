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

//helper class for name analysis phase
class NameAnalyzerHelper
{
public:
	//multiple declarations of a symbol
	static void errorRedeclaration(int line, int col);
	
	//Undeclared identifier 
	static void errorUndeclared(int line, int col);
	
	//no main function
	static void errorNoMain();
	
	//return number of errors
	static int getErrorCount(){ return errorCount; }
private:
	static int errorCount;
};

//helper class for type checking phase
class TypeCheckerHelper
{
public:
	//Assignment to a function
	static void errorAssignToFn(int line, int col);
	
	//Assignment from a function 
	static void errorAssignFromFn(int line, int col);
	
	//Attempt to write a function 
	static void errorWriteFn(int line, int col);
	
	//Comparison between two functions 
	static void errorCompareFn(int line, int col);
	
	//Attempt to call a non-function 
	static void errorCallNonFn(int line, int col);
	
	//Function call with wrong number of args 
	static void errorFnArgCount(int line, int col);
	
	//Type of actual does not match type of formal 
	static void errorFnArgType(int line, int col);
	
	//Arithmetic operator applied to non-numeric operand 
	static void errorNonNumArithmetic(int line, int col);
	
	//Relational operator applied to non-numeric operand 
	static void errorNonNumRelational(int line, int col);
	
	//Logical operator applied to non-bool operand 
	static void errorNonBoolLogical(int line, int col);
	
	//Non-bool expression used as an if condition 
	static void errorBoolIf(int line, int col);
	
	//Non-bool expression used as a while condition 
	static void errorNonBoolWhile(int line, int col);
	
	//Type mismatch 
	static void errorTypeMismatch(int line, int col);

	//return number of errors
	static int getErrorCount(){ return errorCount; }
private:
	static int errorCount;
};

#endif
