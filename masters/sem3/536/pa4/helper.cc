// CS 536 : PA2
// author: priyananda( shenoy@cs.wisc.edu )
// date: 3 Oct 2008
// random quote: 

#include "helper.h"
#include "ast.h"
#include "gram.tab.h"

#include <string>
using std::string;

#include <cstring>
#include <cstdlib>

//for INT_MAX, FLT_MaX
#include <climits>
#include <cfloat>

//for errno, strtof
#include <cerrno>
#include <cmath>

#include "errorhandler.h"

int LexerHelper::line_num = 1;
int LexerHelper::col_num = 1;

void LexerHelper::setLineColNumber(TokenType & yylval, int yyleng)
{
	yylval.lineNum = line_num;
	yylval.colNum = col_num;
	col_num += yyleng;
}

void LexerHelper::newLine()
{
	++line_num;
	col_num = 1;
}

void LexerHelper::extractString(TokenType & yylval,const char * yytext)
{
	yylval.strVal = new string(yytext);
}

void LexerHelper::extractInt(TokenType & yylval,const char * yytext)
{
	//todo check for range
	long long what = atoll(yytext);

	if( strlen(yytext) > 10 || what > (long long)INT_MAX ){
		ErrorHandler::reportWarning(yylval.lineNum,yylval.colNum,"integer literal too large; using max value");
		yylval.intVal = INT_MAX;
	}else{
		yylval.intVal = (int) what;
	}
}

void LexerHelper::extractFloat(TokenType & yylval,const char * yytext)
{
	errno = 0;
	yylval.floatVal = strtof(yytext,NULL);
	if(errno == ERANGE){
		if( yylval.floatVal == HUGE_VALF ){
			//overflow happened
			ErrorHandler::reportWarning(yylval.lineNum,yylval.colNum,"float literal too large; using max value");
			yylval.floatVal = FLT_MAX;
		}else{
			//underflow happened
			ErrorHandler::reportWarning(yylval.lineNum,yylval.colNum,"float literal too small; using min value");
			yylval.floatVal = FLT_MIN;
		}
	}
}

static const char * tokenTypeNames[] = {
	"",
	"INTEGER",
	"BOOLEAN",
	"STRING",
	"VOID",
	"TRUE",
	"FALSE",
	"IF",
	"ELSE",
	"WHILE",
	"WRITE",
	"RETURN",
	"ID",
	"INTLITERAL",
	"STRINGLITERAL",
	"LCURLY",
	"RCURLY",
	"LPAREN",
	"RPAREN",
	"COMMA",
	"ASSIGN",
	"SEMICOLON",
	"PLUS",
	"MINUS",
	"TIMES",
	"DIVIDE",
	"NOT",
	"AND",
	"OR",
	"EQUALS",
	"NOTEQUALS",
	"LESS",
	"GREATER",
	"LESSEQ",
	"GREATEREQ",
	"FLOAT",
	"FLOATLITERAL"
};
void LexerHelper::printToken(int tokenType,const TokenType & token)
{
	printf("%d:%d %s",token.lineNum, token.colNum, tokenTypeNames[tokenType]);
	
	if(tokenType == ID || tokenType == STRINGLITERAL)
		printf("( %s )", token.strVal->c_str());
	else if (tokenType == INTLITERAL)
		printf("( %d )", token.intVal);
	else if (tokenType == FLOATLITERAL)
		printf("( %f )", token.floatVal);
	
	//for newline
	puts("");
}

void LexerHelper::errorUnterminatedString(const TokenType & yylval,const char * yytext)
{
	ErrorHandler::reportError(yylval.lineNum,yylval.colNum,"ignoring unterminated string literal");
}

void LexerHelper::errorIllegalCharacter(const TokenType & yylval,const char * yytext)
{
	ErrorHandler::reportError(yylval.lineNum,yylval.colNum,"ignoring illegal character");
}


int NameAnalyzerHelper::errorCount = 0;

void NameAnalyzerHelper::errorRedeclaration(int line, int col)
{
	ErrorHandler::reportError(line,col,"Multiply declared identifier");
	++errorCount;
}
void NameAnalyzerHelper::errorUndeclared(int line, int col)
{
	ErrorHandler::reportError(line,col,"Undeclared identifier");
	++errorCount;
}
void NameAnalyzerHelper::errorNoMain()
{
	ErrorHandler::reportError(0,0,"No main function declared");
	++errorCount;
}

int TypeCheckerHelper::errorCount = 0;

//Assignment to a function
void TypeCheckerHelper::errorAssignToFn(int line, int col)
{
	ErrorHandler::reportError(line,col,"Assignment to a function"); ++errorCount;
}

//Assignment from a function 
void TypeCheckerHelper::errorAssignFromFn(int line, int col)
{
	ErrorHandler::reportError(line,col,"Assignment from a function"); ++errorCount;
}

//Attempt to write a function 
void TypeCheckerHelper::errorWriteFn(int line, int col)
{
	ErrorHandler::reportError(line,col,"Attempt to write a function"); ++errorCount;
}

//Comparison between two functions 
void TypeCheckerHelper::errorCompareFn(int line, int col)
{
	ErrorHandler::reportError(line,col,"Comparison between two functions"); ++errorCount;
}

//Attempt to call a non-function 
void TypeCheckerHelper::errorCallNonFn(int line, int col)
{
	ErrorHandler::reportError(line,col,"Attempt to call a non-function"); ++errorCount;
}

//Function call with wrong number of args 
void TypeCheckerHelper::errorFnArgCount(int line, int col)
{
	ErrorHandler::reportError(line,col,"Function call with wrong number of args"); ++errorCount;
}

//Type of actual does not match type of formal 
void TypeCheckerHelper::errorFnArgType(int line, int col)
{
	ErrorHandler::reportError(line,col,"Type of actual does not match type of formal"); ++errorCount;
}

//Arithmetic operator applied to non-numeric operand 
void TypeCheckerHelper::errorNonNumArithmetic(int line, int col)
{
	ErrorHandler::reportError(line,col,"Arithmetic operator applied to non-numeric operand"); ++errorCount;
}

//Relational operator applied to non-numeric operand 
void TypeCheckerHelper::errorNonNumRelational(int line, int col)
{
	ErrorHandler::reportError(line,col,"Relational operator applied to non-numeric operand"); ++errorCount;
}

//Logical operator applied to non-bool operand 
void TypeCheckerHelper::errorNonBoolLogical(int line, int col)
{
	ErrorHandler::reportError(line,col,"Logical operator applied to non-bool operand"); ++errorCount;
}

//Non-bool expression used as an if condition 
void TypeCheckerHelper::errorBoolIf(int line, int col)
{
	ErrorHandler::reportError(line,col,"Non-bool expression used as an if condition"); ++errorCount;
}

//Non-bool expression used as a while condition 
void TypeCheckerHelper::errorNonBoolWhile(int line, int col)
{
	ErrorHandler::reportError(line,col,"Non-bool expression used as a while condition"); ++errorCount;
}

//Type mismatch 
void TypeCheckerHelper::errorTypeMismatch(int line, int col) {ErrorHandler::reportError(line,col,"Type mismatch"); ++errorCount; }
