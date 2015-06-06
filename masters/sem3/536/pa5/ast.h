#ifndef ASTGUARD
#define ASTGUARD

#include "ref_ptr_T.h"
#include "list_T.h"
#include "scopelist.h"
#include "type-checker.h"
#include "codegen.h"

#include <string>

// **********************************************************************
// The ASTnode class defines the nodes of the abstract-syntax tree that
// represents a "Simple" program.
//
// Internal nodes of the tree contain pointers to children, organized
// either in a list (for nodes that may have a variable number of children)
// or as a fixed set of data members.  Leaf nodes contain line and column
// information; for string literals and identifiers, they also contain a
// string; for integer literals, they also contain an integer value.
//
// Here are all the different kinds of AST nodes and what kinds of children
// they have.  All of these kinds of AST nodes are subclasses of "ASTnode".
// Indentation indicates further subclassing:
//
//     Subclass            Kids
//     --------            ----
//     DeclListNode        list of DeclNode
//     FormalsListNode     list of FormalNode
//     FnBodyNode          DeclListNode, StmtListNode
//     StmtListNode        list of StmtNode
//     ExpListNode         list of ExpNode
//
//     DeclNode:
//       VarDeclNode       TypeNode, IdNode
//       FnDeclNode        IdNode, FormalsListNode, FnBodyNode
//
//     FormalNode          TypeNode, IdNode
//
//     TypeNode:
//       IntegerNode         -- none --
//       FloatNode         -- none --
//       BooleanNode         -- none --
//       StringNode          -- none --
//
//     StmtNode:
//       WriteStmtNode       ExpNode
//       AssignStmtNode      IdNode, ExpNode
//       IfStmtNode          ExpNode, StmtListNode
//       IfElseStmtNode      ExpNode, StmtListNode, StmtListNode
//       WhileStmtNode       ExpNode, StmtListNode
//       CallStmtNode        IdNode, ExpListNode
//       ReturnStmtNode      -- none --
//
//     ExpNode:
//       IntLitNode          -- none --
//       FloatLitNode        -- none --
//       StrLitNode          -- none --
//       TrueNode            -- none --
//       FalseNode           -- none --
//       IdNode              -- none --
//       UnaryMinusExpNode   ExpNode
//       NotExpNode          ExpNode
//       PlusExpNode         ExpNode, ExpNode
//       MinusExpNode        ExpNode, ExpNode
//       TimesExpNode        ExpNode, ExpNode
//       DivideExpNode       ExpNode, ExpNode
//       AndExpNode          ExpNode, ExpNode
//       OrExpNode           ExpNode, ExpNode
//       EqualsExpNode       ExpNode, ExpNode
//       NotEqualsExpNode    ExpNode, ExpNode
//       LessExpNode         ExpNode, ExpNode
//       GreaterExpNode      ExpNode, ExpNode
//       LessEqExpNode       ExpNode, ExpNode
//       GreaterEqExpNode    ExpNode, ExpNode
//
// Here are the different kinds of AST nodes again, organized according to
// whether they are leaves, internal nodes with lists of kids, or internal
// nodes with a fixed number of kids:
//
// (1) Leaf nodes:
//        IntegerNode, FloatNode, BooleanNode, StringNode, IntLitNode,
//	  FloatLitNode, StrLitNode, TrueNode, FalseNode, IdNode, ReturnStmtNode
//
// (2) Internal nodes with (possibly empty) lists of children:
//        FormalsListNode, DeclListNode, StmtListNode, ExpListNode
//
// (3) Internal nodes with fixed numbers of kids:
//        FnBodyNode,     DeclNode,      VarDeclNode,    FnDeclNode,
//        FormalNode,     WriteStmtNode,
//        AssignStmtNode, IfStmtNode,    IfElseStmtNode, WhileStmtNode,
//        CallStmtNode,   UnaryMinusExpNode,
//        NotExpNode,     PlusExpNode,   MinusExpNode,   TimesExpNode,
//        DivideExpNode,  AndExpNode,    OrExpNode,      EqualsExpNode,
//        NotEqualsExpNode,              LessExpNode,    GreaterExpNode,
//        LessEqExpNode,  GreaterEqExpNode 
//
// **********************************************************************

// **********************************************************************
// ASTnode class (base class for all other kinds of nodes)
// **********************************************************************
class ASTnode
{ 
 public:
  ASTnode() {};
  virtual ~ASTnode() {};
  RefCounter count;

  //every subtype must provide an Unparse operation
  virtual void Unparse(int indent = 0) = 0;
  
  //name analysis phase
  virtual void ProcessNames(ScopeList & list) = 0;  

  //type check phase
  virtual SymbolType CheckTypes(FunctionTable & fnt) = 0;
  
  //code gen phase
  virtual void GenerateCode(CodeGenContext & context) = 0;

 private:
  ASTnode(const ASTnode & T);               // copy constructor hidden
  ASTnode & operator = (const ASTnode & T); // assignment hidden
};

// **********************************************************************
// subclasses of ASTnode having to do with statements and expressions
// **********************************************************************

class StmtNode: public ASTnode
{
};

class StmtListNode: public ASTnode
{
 public:
  StmtListNode(List<ref_ptr<StmtNode> > *L);
  void Unparse(int indent=0);
  
  //name analysis phase
  virtual void ProcessNames(ScopeList & list);
  
  //type check phase
  virtual SymbolType CheckTypes(FunctionTable & fnt);
  
  //code gen phase
  virtual void GenerateCode(CodeGenContext & context);

 private:
  // list of kids
  List<ref_ptr<StmtNode> > *myKids;
};

class ExpNode: public ASTnode
{
public:
  //dummy constructor
  ExpNode(): expressionType(NoType){}

  //get the position of this expression
  virtual void getLineColNumber(int & line, int & col) const = 0;

  //type of this expression
  SymbolType expressionType;
};

class ExpListNode: public ASTnode
{
 public:
  ExpListNode(List<ref_ptr<ExpNode> > *L);
  
  void Unparse(int indent=0);
  
  //name analysis phase
  virtual void ProcessNames(ScopeList & list);
  
  //type check phase
  virtual SymbolType CheckTypes(FunctionTable & fnt);
  
  //code gen phase
  virtual void GenerateCode(CodeGenContext & context);
  
  //number of children
  int kidsCount() const { return myKids->Length(); }
  
  //check for types of each function
  void matchTypes(FunctionTable & fnt,FunctionSignature & sig);
 private:
  // list of kids
  List<ref_ptr<ExpNode> > *myKids;
};


// **********************************************************************
// Subclasses of ExpNode
// **********************************************************************

class IntLitNode: public ExpNode
{
 public:
  IntLitNode(int lineNum, int colNum, int intVal);
  void Unparse(int indent=0);
  
  //name analysis phase
  virtual void ProcessNames(ScopeList & list);
  
  //type check phase
  virtual SymbolType CheckTypes(FunctionTable & fnt);
  
  //code gen phase
  virtual void GenerateCode(CodeGenContext & context);
  
  //for error reporting
  virtual void getLineColNumber(int & line, int & col) const;

 private:
  int myLineNum;
  int myColNum;
  int myIntVal;
};

class FloatLitNode: public ExpNode
{
 public:
  FloatLitNode(int lineNum, int colNum, float floatVal);
  void Unparse(int indent=0);
  
  //name analysis phase
  virtual void ProcessNames(ScopeList & list);
  
  //type check phase
  virtual SymbolType CheckTypes(FunctionTable & fnt);
  
  //for error reporting
  virtual void getLineColNumber(int & line, int & col) const;
  
  //code gen phase
  virtual void GenerateCode(CodeGenContext & context);
 private:
  int myLineNum;
  int myColNum;
  float myFloatVal;
};

class StrLitNode: public ExpNode
{
 public:
  StrLitNode(int lineNum, int colNum, std::string *strVal);
  void Unparse(int indent=0);
  
  //name analysis phase
  virtual void ProcessNames(ScopeList & list);
  
  //type check phase
  virtual SymbolType CheckTypes(FunctionTable & fnt);
  
  //code gen phase
  virtual void GenerateCode(CodeGenContext & context);
  
  //for error reporting
  virtual void getLineColNumber(int & line, int & col) const;
 private:
  int myLineNum;
  int myColNum;
  std::string *myStrVal;
};

class TrueNode: public ExpNode
{
 public:
  TrueNode(int lineNum, int colNum);
  void Unparse(int indent=0);
  
  //name analysis phase
  virtual void ProcessNames(ScopeList & list);
  
  //type check phase
  virtual SymbolType CheckTypes(FunctionTable & fnt);
  
  //code gen phase
  virtual void GenerateCode(CodeGenContext & context);
  
  //for error reporting
  virtual void getLineColNumber(int & line, int & col) const;
 private:
  int myLineNum;
  int myColNum;
};

class FalseNode: public ExpNode
{
 public:
  FalseNode(int lineNum, int colNum);
  void Unparse(int indent=0);
  
  //name analysis phase
  virtual void ProcessNames(ScopeList & list);
  
  //type check phase
  virtual SymbolType CheckTypes(FunctionTable & fnt);
  
  //code gen phase
  virtual void GenerateCode(CodeGenContext & context);
  
  //for error reporting
  virtual void getLineColNumber(int & line, int & col) const;
 private:
  int myLineNum;
  int myColNum;
};

class IdNode: public ExpNode
{
 public:
  IdNode(int lineNum, int colNum, std::string *strVal);
  void Unparse(int indent=0);
  
  //name analysis phase
  virtual void ProcessNames(ScopeList & list);
  
  //type check phase
  virtual SymbolType CheckTypes(FunctionTable & fnt);
  
  //code gen phase
  virtual void GenerateCode(CodeGenContext & context);
  
  //for error reporting
  virtual void getLineColNumber(int & line, int & col) const;
  
  const string & strVal() const {return *myStrVal;}
  
  SymbolPtr & symbol(){ return mySymbol; }
 private:
  int myLineNum;
  int myColNum;
  std::string * myStrVal;
  SymbolPtr mySymbol;
};

// Unary operators -----------------------------------
class UnaryMinusExpNode: public ExpNode
{
 public:
  UnaryMinusExpNode(ref_ptr<ExpNode> exp);
  void Unparse(int indent=0);

  //name analysis phase
  virtual void ProcessNames(ScopeList & list);
  
  //type check phase
  virtual SymbolType CheckTypes(FunctionTable & fnt);
  
  //code gen phase
  virtual void GenerateCode(CodeGenContext & context);
  
  //for error reporting
  virtual void getLineColNumber(int & line, int & col) const;
 private:
  // 1 kid
  ref_ptr<ExpNode> myExp;
};

class NotExpNode: public ExpNode
{
 public:
  NotExpNode(ref_ptr<ExpNode> exp);
  void Unparse(int indent=0);

  //name analysis phase
  virtual void ProcessNames(ScopeList & list);

  //type check phase
  virtual SymbolType CheckTypes(FunctionTable & fnt);

  //code gen phase
  virtual void GenerateCode(CodeGenContext & context);

  //for error reporting
  virtual void getLineColNumber(int & line, int & col) const;
 private:
  // 1 kid
  ref_ptr<ExpNode> myExp;
};

// Binary operators -----------------------------------
class PlusExpNode: public ExpNode
{
 public:
  PlusExpNode(ref_ptr<ExpNode> exp1, ref_ptr<ExpNode> exp2);
  void Unparse(int indent=0);
  
  //name analysis phase
  virtual void ProcessNames(ScopeList & list);
  
  //type check phase
  virtual SymbolType CheckTypes(FunctionTable & fnt);
  
  //code gen phase
  virtual void GenerateCode(CodeGenContext & context);
  
  //for error reporting
  virtual void getLineColNumber(int & line, int & col) const;
 private:
  // 2 kids
  ref_ptr<ExpNode> myExp1;
  ref_ptr<ExpNode> myExp2;
};

class MinusExpNode: public ExpNode
{
 public:
  MinusExpNode(ref_ptr<ExpNode> exp1, ref_ptr<ExpNode> exp2);
  void Unparse(int indent=0);
  
  //name analysis phase
  virtual void ProcessNames(ScopeList & list);
  
  //type check phase
  virtual SymbolType CheckTypes(FunctionTable & fnt);
  
  //code gen phase
  virtual void GenerateCode(CodeGenContext & context);
  
  //for error reporting
  virtual void getLineColNumber(int & line, int & col) const;
 private:
  // 2 kids
  ref_ptr<ExpNode> myExp1;
  ref_ptr<ExpNode> myExp2;
};

class TimesExpNode: public ExpNode
{
 public:
  TimesExpNode(ref_ptr<ExpNode> exp1, ref_ptr<ExpNode> exp2);
  void Unparse(int indent=0);
  
  //name analysis phase
  virtual void ProcessNames(ScopeList & list);
  
  //type check phase
  virtual SymbolType CheckTypes(FunctionTable & fnt);
  
  //code gen phase
  virtual void GenerateCode(CodeGenContext & context);
  
  //for error reporting
  virtual void getLineColNumber(int & line, int & col) const;
 private:
  // 2 kids
  ref_ptr<ExpNode> myExp1;
  ref_ptr<ExpNode> myExp2;
};

class DivideExpNode: public ExpNode
{
 public:
  DivideExpNode(ref_ptr<ExpNode> exp1, ref_ptr<ExpNode> exp2);
  void Unparse(int indent=0);
  
  //name analysis phase
  virtual void ProcessNames(ScopeList & list);
  
  //type check phase
  virtual SymbolType CheckTypes(FunctionTable & fnt);
  
  //code gen phase
  virtual void GenerateCode(CodeGenContext & context);
  
  //for error reporting
  virtual void getLineColNumber(int & line, int & col) const;
 private:
  // 2 kids
  ref_ptr<ExpNode> myExp1;
  ref_ptr<ExpNode> myExp2;
};

class AndExpNode: public ExpNode
{
 public:
  AndExpNode(ref_ptr<ExpNode> exp1, ref_ptr<ExpNode> exp2);
  void Unparse(int indent=0);
  
  //name analysis phase
  virtual void ProcessNames(ScopeList & list);
  
  //type check phase
  virtual SymbolType CheckTypes(FunctionTable & fnt);
  
  //code gen phase
  virtual void GenerateCode(CodeGenContext & context);
  
  //for error reporting
  virtual void getLineColNumber(int & line, int & col) const;
 private:
  // 2 kids
  ref_ptr<ExpNode> myExp1;
  ref_ptr<ExpNode> myExp2;
};

class OrExpNode: public ExpNode
{
 public:
  OrExpNode(ref_ptr<ExpNode> exp1, ref_ptr<ExpNode> exp2);
  void Unparse(int indent=0);
  
  //name analysis phase
  virtual void ProcessNames(ScopeList & list);
  
  //type check phase
  virtual SymbolType CheckTypes(FunctionTable & fnt);
  
  //code gen phase
  virtual void GenerateCode(CodeGenContext & context);
  
  //for error reporting
  virtual void getLineColNumber(int & line, int & col) const;
 private:
  // 2 kids
  ref_ptr<ExpNode> myExp1;
  ref_ptr<ExpNode> myExp2;
};

class EqualsExpNode: public ExpNode
{
 public:
  EqualsExpNode(ref_ptr<ExpNode> exp1, ref_ptr<ExpNode> exp2);
  void Unparse(int indent=0);
  
  //name analysis phase
  virtual void ProcessNames(ScopeList & list);
  
  //type check phase
  virtual SymbolType CheckTypes(FunctionTable & fnt);
  
  //code gen phase
  virtual void GenerateCode(CodeGenContext & context);
  
  //for error reporting
  virtual void getLineColNumber(int & line, int & col) const;
 private:
  // 2 kids
  ref_ptr<ExpNode> myExp1;
  ref_ptr<ExpNode> myExp2;
};

class NotEqualsExpNode: public ExpNode
{
 public:
  NotEqualsExpNode(ref_ptr<ExpNode> exp1, ref_ptr<ExpNode> exp2);
  void Unparse(int indent=0);
  
  //name analysis phase
  virtual void ProcessNames(ScopeList & list);
  
  //type check phase
  virtual SymbolType CheckTypes(FunctionTable & fnt);
  
  //code gen phase
  virtual void GenerateCode(CodeGenContext & context);
  
  //for error reporting
  virtual void getLineColNumber(int & line, int & col) const;
 private:
  // 2 kids
  ref_ptr<ExpNode> myExp1;
  ref_ptr<ExpNode> myExp2;
};

class LessExpNode: public ExpNode
{
 public:
  LessExpNode(ref_ptr<ExpNode> exp1, ref_ptr<ExpNode> exp2);
  void Unparse(int indent=0);
  
  //name analysis phase
  virtual void ProcessNames(ScopeList & list);
  
  //type check phase
  virtual SymbolType CheckTypes(FunctionTable & fnt);
  
  //code gen phase
  virtual void GenerateCode(CodeGenContext & context);
  
  //for error reporting
  virtual void getLineColNumber(int & line, int & col) const;
 private:
  // 2 kids
  ref_ptr<ExpNode> myExp1;
  ref_ptr<ExpNode> myExp2;
};

class GreaterExpNode: public ExpNode
{
 public:
  GreaterExpNode(ref_ptr<ExpNode> exp1, ref_ptr<ExpNode> exp2);
  void Unparse(int indent=0);
  
  //name analysis phase
  virtual void ProcessNames(ScopeList & list);
  
  //type check phase
  virtual SymbolType CheckTypes(FunctionTable & fnt);
  
  //code gen phase
  virtual void GenerateCode(CodeGenContext & context);
  
  //for error reporting
  virtual void getLineColNumber(int & line, int & col) const;
 private:
  // 2 kids
  ref_ptr<ExpNode> myExp1;
  ref_ptr<ExpNode> myExp2;
};

class LessEqExpNode: public ExpNode
{
 public:
  LessEqExpNode(ref_ptr<ExpNode> exp1, ref_ptr<ExpNode> exp2);
  void Unparse(int indent=0);
  
  //name analysis phase
  virtual void ProcessNames(ScopeList & list);
  
  //type check phase
  virtual SymbolType CheckTypes(FunctionTable & fnt);
  
  //code gen phase
  virtual void GenerateCode(CodeGenContext & context);
  
  //for error reporting
  virtual void getLineColNumber(int & line, int & col) const;
 private:
  // 2 kids
  ref_ptr<ExpNode> myExp1;
  ref_ptr<ExpNode> myExp2;
};

class GreaterEqExpNode: public ExpNode
{
 public:
  GreaterEqExpNode(ref_ptr<ExpNode> exp1, ref_ptr<ExpNode> exp2);
  void Unparse(int indent=0);
  
  //name analysis phase
  virtual void ProcessNames(ScopeList & list);
  
  //type check phase
  virtual SymbolType CheckTypes(FunctionTable & fnt);
  
  //code gen phase
  virtual void GenerateCode(CodeGenContext & context);
  
  //for error reporting
  virtual void getLineColNumber(int & line, int & col) const;
 private:
  // 2 kids
  ref_ptr<ExpNode> myExp1;
  ref_ptr<ExpNode> myExp2;
};

// **********************************************************************
// Subclasses of StmtNode
// **********************************************************************
class WriteStmtNode: public StmtNode
{
 public:
  WriteStmtNode(ref_ptr<ExpNode> exp);
  void Unparse(int indent=0);
  
  //name analysis phase
  virtual void ProcessNames(ScopeList & list);
  
  //type check phase
  virtual SymbolType CheckTypes(FunctionTable & fnt);

  //code gen phase
  virtual void GenerateCode(CodeGenContext & context);
 private:
  // 1 kid
  ref_ptr<ExpNode> myExp;
};

class AssignStmtNode: public StmtNode
{
 public:
  AssignStmtNode(ref_ptr<IdNode> id, ref_ptr<ExpNode> exp);
  void Unparse(int indent=0);

  //name analysis phase
  virtual void ProcessNames(ScopeList & list);

  //type check phase
  virtual SymbolType CheckTypes(FunctionTable & fnt);

  //code gen phase
  virtual void GenerateCode(CodeGenContext & context);

 private:
  // 2 kids
  ref_ptr<IdNode> myId;
  ref_ptr<ExpNode> myExp;
};

class IfStmtNode: public StmtNode
{
 public:
  IfStmtNode(ref_ptr<ExpNode> exp, ref_ptr<StmtListNode> stmtList);
  void Unparse(int indent=0);

  //name analysis phase
  virtual void ProcessNames(ScopeList & list);

  //type check phase
  virtual SymbolType CheckTypes(FunctionTable & fnt);

  //code gen phase
  virtual void GenerateCode(CodeGenContext & context);

 private:
  // 2 kids
  ref_ptr<ExpNode> myExp;
  ref_ptr<StmtListNode> myStmtList;
};

class IfElseStmtNode: public StmtNode
{
 public:
  IfElseStmtNode(ref_ptr<ExpNode> exp,
                 ref_ptr<StmtListNode> thenStmtList,
                 ref_ptr<StmtListNode> elseStmtList);
  void Unparse(int indent=0);

  //name analysis phase
  virtual void ProcessNames(ScopeList & list);

  //type check phase
  virtual SymbolType CheckTypes(FunctionTable & fnt);
  
  //code gen phase
  virtual void GenerateCode(CodeGenContext & context);

 private:
  // 3 kids
  ref_ptr<ExpNode> myExp;
  ref_ptr<StmtListNode> myThenStmtList;
  ref_ptr<StmtListNode> myElseStmtList;
};

class WhileStmtNode: public StmtNode
{
 public:
  WhileStmtNode(ref_ptr<ExpNode> exp, ref_ptr<StmtListNode> stmtList);
  void Unparse(int indent=0);

  //name analysis phase
  virtual void ProcessNames(ScopeList & list);

  //type check phase
  virtual SymbolType CheckTypes(FunctionTable & fnt);
  
  //code gen phase
  virtual void GenerateCode(CodeGenContext & context);

 private:
  // 2 kids
  ref_ptr<ExpNode> myExp;
  ref_ptr<StmtListNode> myStmtList;
};

class CallStmtNode: public StmtNode
{
 public:
  CallStmtNode(ref_ptr<IdNode> id, ref_ptr<ExpListNode> expList);
  void Unparse(int indent=0);

  //name analysis phase
  virtual void ProcessNames(ScopeList & list);

  //type check phase
  virtual SymbolType CheckTypes(FunctionTable & fnt);
  
  //code gen phase
  virtual void GenerateCode(CodeGenContext & context);

 private:
  // 2 kids
  ref_ptr<IdNode> myId;
  ref_ptr<ExpListNode> myExpList;
};

class ReturnStmtNode: public StmtNode
{
 public:
  ReturnStmtNode(int lineNum, int colNum);
  void Unparse(int indent=0);
  
  //name analysis phase
  virtual void ProcessNames(ScopeList & list);
  
  //code gen phase
  virtual void GenerateCode(CodeGenContext & context);
  
  //type check phase
  virtual SymbolType CheckTypes(FunctionTable & fnt);    

 private:
  int myLineNum;
  int myColNum;
};

// **********************************************************************
// TypeNode and its Subclasses
// **********************************************************************
class TypeNode: public ASTnode
{
public:
	virtual SymbolType getTypeSpecifier() = 0;
};

class IntegerNode: public TypeNode
{
 public:
  IntegerNode(int lineNum, int colNum);
  void Unparse(int indent=0);
  
  //name analysis phase
  virtual void ProcessNames(ScopeList & list);
  
  //type check phase
  virtual SymbolType CheckTypes(FunctionTable & fnt);
  
  //code gen phase
  virtual void GenerateCode(CodeGenContext & context);
  
  virtual SymbolType getTypeSpecifier();

 private:
  int myLineNum;
  int myColNum;
};

class FloatNode: public TypeNode
{
 public:
  FloatNode(int lineNum, int colNum);
  void Unparse(int indent=0);

  //name analysis phase
  virtual void ProcessNames(ScopeList & list);

  //type check phase
  virtual SymbolType CheckTypes(FunctionTable & fnt);
  
  //code gen phase
  virtual void GenerateCode(CodeGenContext & context);
  
  virtual SymbolType getTypeSpecifier();

 private:
  int myLineNum;
  int myColNum;
};

class BooleanNode: public TypeNode
{
 public:
  BooleanNode(int lineNum, int colNum);
  void Unparse(int indent=0);

  //name analysis phase
  virtual void ProcessNames(ScopeList & list);

  //type check phase
  virtual SymbolType CheckTypes(FunctionTable & fnt);

  //code gen phase
  virtual void GenerateCode(CodeGenContext & context);
  
  virtual SymbolType getTypeSpecifier();

 private:
  int myLineNum;
  int myColNum;
};

class StringNode: public TypeNode
{
 public:
  StringNode(int lineNum, int colNum);
  void Unparse(int indent=0);
  
  //name analysis phase
  virtual void ProcessNames(ScopeList & list);
  
  //type check phase
  virtual SymbolType CheckTypes(FunctionTable & fnt);
  
  //code gen phase
  virtual void GenerateCode(CodeGenContext & context);
  
  virtual SymbolType getTypeSpecifier();

 private:
  int myLineNum;
  int myColNum;
};

// **********************************************************************
// FormalNode and its Subclasses
// **********************************************************************
class FormalNode: public ASTnode
{
 public:
  FormalNode(ref_ptr<TypeNode> type, ref_ptr<IdNode> id);
  void Unparse(int indent=0);
  
  //name analysis phase
  virtual void ProcessNames(ScopeList & list);
  
  //type check phase
  virtual SymbolType CheckTypes(FunctionTable & fnt);
  
  //code gen phase
  virtual void GenerateCode(CodeGenContext & context);
  
  SymbolType getArgumentType()
  {
  	return myType->getTypeSpecifier();
  }
  SymbolPtr symbol()
  {
  	return myId->symbol();
  }

 private:
  // 2 kids
  ref_ptr<TypeNode> myType;
  ref_ptr<IdNode> myId;
};

// **********************************************************************
// more subclasses of ASTnode:
//   DeclNode, DeclListNode, FnBodyNode, and FormalsListNode
// **********************************************************************
class DeclNode: public ASTnode
{
};

class DeclListNode: public ASTnode
{
 public:
  DeclListNode(List<ref_ptr<DeclNode> > *L);
  void Unparse(int indent=0);
  
  //name analysis phase
  virtual void ProcessNames(ScopeList & list);
  
  //type check phase
  virtual SymbolType CheckTypes(FunctionTable & fnt);

  //code gen phase
  virtual void GenerateCode(CodeGenContext & context);
  
  //number of Kids
  int kidsCount() const{ return myKids->Length(); }
  
  //kids
  List<ref_ptr<DeclNode> > * getDeclarations(){ return myKids;}
 private:
  // list of kids
  List<ref_ptr<DeclNode> > *myKids;
};

class FnBodyNode: public ASTnode
{
 public:
  FnBodyNode(ref_ptr<DeclListNode> declList, ref_ptr<StmtListNode> stmtList);
  void Unparse(int indent=0);
  
  //name analysis phase
  virtual void ProcessNames(ScopeList & list);
  
  //type check phase
  virtual SymbolType CheckTypes(FunctionTable & fnt);

  //code gen phase
  virtual void GenerateCode(CodeGenContext & context);
  
  //number of local variables
  int numberOfLocals() const { return myDeclList->kidsCount(); }
 private:
  // 2 kids
  ref_ptr<DeclListNode> myDeclList;
  ref_ptr<StmtListNode> myStmtList;
};

class FormalsListNode: public ASTnode
{
 public:
  FormalsListNode(List<ref_ptr<FormalNode> > *L);
  void Unparse(int indent=0);
  
  //name analysis phase
  virtual void ProcessNames(ScopeList & list);
  
  //type check phase
  virtual SymbolType CheckTypes(FunctionTable & fnt);
  
  //code gen phase
  virtual void GenerateCode(CodeGenContext & context);
  
  //get kids
  List<ref_ptr<FormalNode> > * getDeclarations(){ return myKids; }

 private:
  // list of kids
  List<ref_ptr<FormalNode> > *myKids;
};


// **********************************************************************
// Subclasses of Declnode
// **********************************************************************
class VarDeclNode: public DeclNode
{
 public:
  VarDeclNode(ref_ptr<TypeNode> type, ref_ptr<IdNode> id);
  void Unparse(int indent=0);
  
  //name analysis phase
  virtual void ProcessNames(ScopeList & list);
  
  //type check phase
  virtual SymbolType CheckTypes(FunctionTable & fnt);
  
  void setVarOffset(int offset){ myId->symbol()->offset = offset; }
  
  SymbolType getVariableType() const { return myType->getTypeSpecifier(); }

  //code gen phase
  virtual void GenerateCode(CodeGenContext & context);
 private:
  // 2 kids
  ref_ptr<TypeNode> myType;
  ref_ptr<IdNode> myId;
};

class FnDeclNode: public DeclNode
{
 public:
  FnDeclNode(ref_ptr<IdNode> id, ref_ptr<FormalsListNode> formalList, ref_ptr<FnBodyNode> body);
  void Unparse(int indent=0);
  
  //name analysis phase
  virtual void ProcessNames(ScopeList & list);
  
  //type check phase
  virtual SymbolType CheckTypes(FunctionTable & fnt);
  
  //code gen phase
  virtual void GenerateCode(CodeGenContext & context);

 private:
  // 3 kids
  ref_ptr<IdNode> myId;
  ref_ptr<FormalsListNode> myFormalsList;
  ref_ptr<FnBodyNode> myBody;
};

//priyananda's changes
class ProgramNode : public ASTnode
{
public:
	//constructor
	ProgramNode(ref_ptr<DeclListNode> declList);
	
	//name analysis phase
	virtual void ProcessNames(ScopeList & list);
	
	//name analysis pass
	bool AnalyzeNames();
	
	//type checking pass
	bool CheckTypes();
	
	//type checking phase
	virtual SymbolType CheckTypes(FunctionTable & fnt);
	
	//code gen phase
	bool GenerateCode(const string & filename);
	
	//code gen phase
    virtual void GenerateCode(CodeGenContext & context);
	
	virtual void Unparse(int indent = 0);
private:
	ref_ptr<DeclListNode> myDeclList;
};

// **********************************************************************
// GLOBAL variable: the root of the AST built by a (successful) parse)
// **********************************************************************
extern ref_ptr<ProgramNode> astRoot;

#endif
