%{
// CS 536 : PA3
// author: priyananda( shenoy@cs.wisc.edu )
// date: 23 Oct 2008
// random quote:

#include "scanner.h"
#include "ast.h"
#include "errorhandler.h"

void yyerror(char * message);

#define NEWLIST(X) new List< ref_ptr< X > > ()

%}

%union {
  TokenType                  TOKENval;   // type of all tokens
  DeclNode                   *DeclNodeval;
  TypeNode                   *TypeNodeval;
  IdNode                     *IdNodeval;
  List<ref_ptr<DeclNode> >   *DeclListval;
  FormalsListNode			 *FormalsListNodeval;
  List<ref_ptr<FormalNode> > *FormalsListval;
  List<ref_ptr<StmtNode> >   *StmtListval;
  List<ref_ptr<ExpNode> > 	 *ExpListval;
  FnBodyNode				 *FnBodyNodeval;
  StmtNode					 *StmtNodeval;
  ExpNode					 *ExpNodeval;
};

%token <TOKENval> INTEGER
%token <TOKENval> FLOAT
%token <TOKENval> BOOLEAN
%token <TOKENval> STRING
%token <TOKENval> VOID
%token <TOKENval> TRUE
%token <TOKENval> FALSE
%token <TOKENval> IF
%token <TOKENval> ELSE
%token <TOKENval> WHILE
%token <TOKENval> DO
%token <TOKENval> WRITE
%token <TOKENval> RETURN
%token <TOKENval> ID
%token <TOKENval> INTLITERAL
%token <TOKENval> FLOATLITERAL
%token <TOKENval> STRINGLITERAL
%token <TOKENval> LCURLY
%token <TOKENval> RCURLY
%token <TOKENval> LPAREN
%token <TOKENval> RPAREN
%token <TOKENval> COMMA
%token <TOKENval> ASSIGN
%token <TOKENval> SEMICOLON
%token <TOKENval> PLUS
%token <TOKENval> MINUS
%token <TOKENval> TIMES
%token <TOKENval> DIVIDE
%token <TOKENval> NOT
%token <TOKENval> AND
%token <TOKENval> OR
%token <TOKENval> EQUALS
%token <TOKENval> NOTEQUALS
%token <TOKENval> LESS
%token <TOKENval> GREATER
%token <TOKENval> LESSEQ
%token <TOKENval> GREATEREQ
%token <TOKENval> UMINUS

%type <DeclNodeval> decl varDecl fnDecl
%type <TypeNodeval> type
%type <IdNodeval>   id
%type <DeclListval> program declList varDeclList
%type <FormalsListNodeval> formals
%type <FormalsListval> formalList
%type <StmtListval> stmtList
%type <ExpListval> actualList
%type <FnBodyNodeval> fnBody
%type <StmtNodeval> stmt
%type <ExpNodeval> exp


%left	  AND OR
%nonassoc EQUALS NOTEQUALS LESS GREATER LESSEQ GREATEREQ
%left 	  PLUS   MINUS
%left	  TIMES  DIVIDE
%nonassoc UMINUS NOT


%start program

%%

program		: declList				{ AST = new DeclListNode($1);}
			;

declList 	: declList decl			{ $$ = $1; $$->AddToEnd($2); }
			| /* epsilon */         { $$ = NEWLIST(DeclNode); }
			;

decl		: varDecl				{ $$ = $1; }
			| fnDecl				{ $$ = $1; }
			;

varDecl		: type id SEMICOLON		{ $$ = new VarDeclNode($1, $2); }
			;

fnDecl		: VOID id formals fnBody { $$ = new FnDeclNode($2, $3, $4); }
			;

type		: INTEGER				{ $$ = new IntegerNode($1.lineNum, $1.colNum); }
	        | FLOAT					{ $$ = new FloatNode($1.lineNum, $1.colNum); }
	        | BOOLEAN				{ $$ = new BooleanNode($1.lineNum, $1.colNum); }
			| STRING                { $$ = new StringNode($1.lineNum, $1.colNum); }
			;

formals		: LPAREN RPAREN			{ $$ = new FormalsListNode( NEWLIST(FormalNode) );}
			| LPAREN formalList RPAREN	{ $$ = new FormalsListNode( $2 );}
			;

formalList	: type id				{ $$ = NEWLIST(FormalNode); $$->AddToEnd( new FormalNode($1,$2) ); }
			| formalList COMMA type id { $$ = $1; $$->AddToEnd( new FormalNode($3,$4) ); }
			;

fnBody		: LCURLY varDeclList stmtList RCURLY { $$ = new FnBodyNode(new DeclListNode($2),new StmtListNode($3) ); }
			;

varDeclList	: varDeclList varDecl	{ $$ = $1; $$->AddToEnd($2); }
			| /* epsilon */			{ $$ = NEWLIST(DeclNode); }
			;

stmtList	: stmtList stmt			{ $$ = $1; $$->AddToEnd($2); }
			| /* epsilon */			{ $$ = NEWLIST(StmtNode); }
			;

stmt		: WRITE LPAREN exp RPAREN SEMICOLON
									{ $$ = new WriteStmtNode($3); }
	        | id ASSIGN exp SEMICOLON
	        						{ $$ = new AssignStmtNode($1,$3); }
	        | IF LPAREN exp RPAREN LCURLY stmtList RCURLY
	        						{ $$ = new IfStmtNode($3, new StmtListNode($6) ); }
	        | IF LPAREN exp RPAREN LCURLY stmtList RCURLY ELSE LCURLY stmtList RCURLY
	        						{ $$ = new IfElseStmtNode($3,new StmtListNode($6),new StmtListNode($10) ); }
	        | WHILE LPAREN exp RPAREN LCURLY stmtList RCURLY
	        						{ $$ = new WhileStmtNode( $3, new StmtListNode($6) ); }
			| RETURN SEMICOLON 
									{ $$ = new ReturnStmtNode($1.lineNum, $2.colNum); }
	        | id LPAREN RPAREN SEMICOLON
	        						{ $$ = new CallStmtNode($1,new ExpListNode( NEWLIST(ExpNode) ) ); }
	        | id LPAREN actualList RPAREN SEMICOLON
	        						{ $$ = new CallStmtNode($1,new ExpListNode($3) ); }
			;

exp			: id					{ $$ = $1; }
	        | INTLITERAL			{ $$ = new IntLitNode($1.lineNum,$1.colNum,$1.intVal); }
	        | FLOATLITERAL			{ $$ = new FloatLitNode($1.lineNum,$1.colNum,$1.floatVal); }
	        | STRINGLITERAL			{ $$ = new StrLitNode($1.lineNum,$1.colNum,$1.strVal); }
	        | TRUE					{ $$ = new TrueNode($1.lineNum,$1.colNum); }
	        | FALSE					{ $$ = new FalseNode($1.lineNum,$1.colNum); }
			| MINUS exp	%prec UMINUS { $$ = new UnaryMinusExpNode($2); }
	        | exp PLUS exp			{ $$ = new PlusExpNode($1,$3); }
	        | exp MINUS exp			{ $$ = new MinusExpNode($1,$3); }
	        | exp TIMES exp			{ $$ = new TimesExpNode($1,$3); }
	        | exp DIVIDE exp		{ $$ = new DivideExpNode($1,$3); }
	        | NOT exp				{ $$ = new NotExpNode($2); }
	        | exp AND exp			{ $$ = new AndExpNode($1,$3); }
	        | exp OR exp			{ $$ = new OrExpNode($1,$3); }
			| exp EQUALS exp		{ $$ = new EqualsExpNode($1,$3); }
			| exp NOTEQUALS exp		{ $$ = new NotEqualsExpNode($1,$3); }
			| exp LESS exp			{ $$ = new LessExpNode($1,$3); }
			| exp GREATER exp		{ $$ = new GreaterExpNode($1,$3); }
			| exp LESSEQ exp		{ $$ = new LessEqExpNode($1,$3); }
			| exp GREATEREQ exp		{ $$ = new GreaterEqExpNode($1,$3); }
	        | LPAREN exp RPAREN		{ $$ = $2; }
			;

actualList	: exp					{ $$ = NEWLIST(ExpNode); $$->AddToEnd($1); }
			| actualList COMMA exp	{ $$ = $1; $$->AddToEnd($3); }
			;

id          : ID					{ $$ = new IdNode($1.lineNum, $1.colNum, $1.strVal); }
			;
%%

void yyerror(char * message)
{
	ErrorHandler::reportError( yylval.TOKENval.lineNum, yylval.TOKENval.colNum, message);
}
