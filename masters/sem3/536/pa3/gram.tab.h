/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     INTEGER = 258,
     FLOAT = 259,
     BOOLEAN = 260,
     STRING = 261,
     VOID = 262,
     TRUE = 263,
     FALSE = 264,
     IF = 265,
     ELSE = 266,
     WHILE = 267,
     DO = 268,
     WRITE = 269,
     RETURN = 270,
     ID = 271,
     INTLITERAL = 272,
     FLOATLITERAL = 273,
     STRINGLITERAL = 274,
     LCURLY = 275,
     RCURLY = 276,
     LPAREN = 277,
     RPAREN = 278,
     COMMA = 279,
     ASSIGN = 280,
     SEMICOLON = 281,
     PLUS = 282,
     MINUS = 283,
     TIMES = 284,
     DIVIDE = 285,
     NOT = 286,
     AND = 287,
     OR = 288,
     EQUALS = 289,
     NOTEQUALS = 290,
     LESS = 291,
     GREATER = 292,
     LESSEQ = 293,
     GREATEREQ = 294,
     UMINUS = 295
   };
#endif
/* Tokens.  */
#define INTEGER 258
#define FLOAT 259
#define BOOLEAN 260
#define STRING 261
#define VOID 262
#define TRUE 263
#define FALSE 264
#define IF 265
#define ELSE 266
#define WHILE 267
#define DO 268
#define WRITE 269
#define RETURN 270
#define ID 271
#define INTLITERAL 272
#define FLOATLITERAL 273
#define STRINGLITERAL 274
#define LCURLY 275
#define RCURLY 276
#define LPAREN 277
#define RPAREN 278
#define COMMA 279
#define ASSIGN 280
#define SEMICOLON 281
#define PLUS 282
#define MINUS 283
#define TIMES 284
#define DIVIDE 285
#define NOT 286
#define AND 287
#define OR 288
#define EQUALS 289
#define NOTEQUALS 290
#define LESS 291
#define GREATER 292
#define LESSEQ 293
#define GREATEREQ 294
#define UMINUS 295




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 17 "simple.y"
{
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
}
/* Line 1489 of yacc.c.  */
#line 144 "gram.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

