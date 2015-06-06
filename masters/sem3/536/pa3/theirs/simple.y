/**********************************************************************
 Parser for Simple programs
 **********************************************************************/

// The types of the tokens and nonterminals
%union {
  TokenType                  TOKENval;   // type of all tokens
  DeclNode                   *DeclNodeval;
  TypeNode                   *TypeNodeval;
  IdNode                     *IdNodeval;
  List<ref_ptr<DeclNode> >   *DeclListval;
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

%type <DeclListval> program  declList
%type <DeclNodeval> decl varDecl
%type <TypeNodeval> type
%type <IdNodeval>   id
 
%start program

%%
program		: declList
                  { AST = new DeclListNode($1);
		  }
		;

declList 	: declList decl
                  { $$ = $1;
		    $$->AddToEnd($2);
		  }
		| /* epsilon */
                  { $$ = new List<ref_ptr<DeclNode> >; }
		;

decl		: varDecl
                  { $$ = $1; }
		;

varDecl		: type id SEMICOLON
                  { $$ = new VarDeclNode($1, $2); }
		;

type		: INTEGER
                  { $$ = new IntegerNode($1.lineNum, $1.colNum); }
	        | FLOAT
                  { $$ = new FloatNode($1.lineNum, $1.colNum); }
	        | BOOLEAN
                  { $$ = new BooleanNode($1.lineNum, $1.colNum); }
                | STRING
                  { $$ = new StringNode($1.lineNum, $1.colNum); }
		;

id              : ID
                  { $$ = new IdNode($1.lineNum, $1.colNum, $1.strVal); }
%%

