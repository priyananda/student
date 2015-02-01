#include "ast.h"
#include "ref_ptr_T.h"
#include "list_T.h"
#include <string>

// **********************************************************************
// Constructors for all of the subclasses of ASTnode that need one
// **********************************************************************

DeclListNode::DeclListNode(List<ref_ptr<DeclNode> > *L): myKids(L)
{}

FormalsListNode::FormalsListNode(List<ref_ptr<FormalNode> > *L): myKids(L)
{}

FnBodyNode::FnBodyNode(ref_ptr<DeclListNode> declList, ref_ptr<StmtListNode> stmtList):
   myDeclList(declList), myStmtList(stmtList)
{}

StmtListNode::StmtListNode(List<ref_ptr<StmtNode> > *L): myKids(L)
{}

ExpListNode::ExpListNode(List<ref_ptr<ExpNode> > *L): myKids(L)
{}

VarDeclNode::VarDeclNode(ref_ptr<TypeNode> type, ref_ptr<IdNode> id):
  myType(type), myId(id)
{}

FnDeclNode::FnDeclNode(ref_ptr<IdNode> id, ref_ptr<FormalsListNode> formalList,
		       ref_ptr<FnBodyNode> body):
   myId(id), myFormalsList(formalList), myBody(body)
{}

FormalNode::FormalNode(ref_ptr<TypeNode> type, ref_ptr<IdNode> id):
   myType(type), myId(id)
{}

IntegerNode::IntegerNode(int lineNum, int colNum):
  myLineNum(lineNum), myColNum(colNum)
{}

SymbolType IntegerNode::getTypeSpecifier()
{
   return IntType;
}

FloatNode::FloatNode(int lineNum, int colNum):
  myLineNum(lineNum), myColNum(colNum)
{}

SymbolType FloatNode::getTypeSpecifier()
{
	return FloatType;
}

BooleanNode::BooleanNode(int lineNum, int colNum):
  myLineNum(lineNum), myColNum(colNum)
{}

SymbolType BooleanNode::getTypeSpecifier()
{
	return BoolType;
}

StringNode::StringNode(int lineNum, int colNum):
  myLineNum(lineNum), myColNum(colNum)
{}

SymbolType StringNode::getTypeSpecifier()
{
	return StringType;
}

WriteStmtNode::WriteStmtNode(ref_ptr<ExpNode> exp): myExp(exp)
{}

AssignStmtNode::AssignStmtNode(ref_ptr<IdNode> id, ref_ptr<ExpNode> exp):
   myId(id), myExp(exp)
{}

IfStmtNode::IfStmtNode(ref_ptr<ExpNode> exp, ref_ptr<StmtListNode> stmtList):
   myExp(exp), myStmtList(stmtList)
{}

IfElseStmtNode::IfElseStmtNode(ref_ptr<ExpNode> exp,
                               ref_ptr<StmtListNode> thenStmtList,
                               ref_ptr<StmtListNode> elseStmtList):
   myExp(exp), myThenStmtList(thenStmtList), myElseStmtList(elseStmtList)
{}

WhileStmtNode::WhileStmtNode(ref_ptr<ExpNode> exp, ref_ptr<StmtListNode> stmtList):
   myExp(exp), myStmtList(stmtList)
{}

CallStmtNode::CallStmtNode(ref_ptr<IdNode> id, ref_ptr<ExpListNode> expList):
   myId(id), myExpList(expList)
{}

ReturnStmtNode::ReturnStmtNode(int lineNum, int colNum):
  myLineNum(lineNum), myColNum(colNum)
{}

IntLitNode::IntLitNode(int lineNum, int colNum, int intVal):
  myLineNum(lineNum), myColNum(colNum), myIntVal(intVal)
{}

FloatLitNode::FloatLitNode(int lineNum, int colNum, float floatVal):
  myLineNum(lineNum), myColNum(colNum), myFloatVal(floatVal)
{}

StrLitNode::StrLitNode(int lineNum, int colNum, std::string *strVal):
  myLineNum(lineNum), myColNum(colNum), myStrVal(strVal)
{}

TrueNode::TrueNode(int lineNum, int colNum):
  myLineNum(lineNum), myColNum(colNum)
{}

FalseNode::FalseNode(int lineNum, int colNum):
  myLineNum(lineNum), myColNum(colNum)
{}

IdNode::IdNode(int lineNum, int colNum, std::string *strVal):
  myLineNum(lineNum), myColNum(colNum), myStrVal(strVal), mySymbol(NULL)
{}

// Unary operators -----------------------------------
UnaryMinusExpNode::UnaryMinusExpNode(ref_ptr<ExpNode> exp):
  myExp(exp)
{}

NotExpNode::NotExpNode(ref_ptr<ExpNode> exp):
  myExp(exp)
{}

// Binary operators -----------------------------------
PlusExpNode::PlusExpNode(ref_ptr<ExpNode> exp1, ref_ptr<ExpNode> exp2):
  myExp1(exp1), myExp2(exp2)
{}

MinusExpNode::MinusExpNode(ref_ptr<ExpNode> exp1, ref_ptr<ExpNode> exp2):
  myExp1(exp1), myExp2(exp2)
{}

TimesExpNode::TimesExpNode(ref_ptr<ExpNode> exp1, ref_ptr<ExpNode> exp2):
  myExp1(exp1), myExp2(exp2)
{}

DivideExpNode::DivideExpNode(ref_ptr<ExpNode> exp1, ref_ptr<ExpNode> exp2):
  myExp1(exp1), myExp2(exp2)
{}

AndExpNode::AndExpNode(ref_ptr<ExpNode> exp1, ref_ptr<ExpNode> exp2):
  myExp1(exp1), myExp2(exp2)
{}

OrExpNode::OrExpNode(ref_ptr<ExpNode> exp1, ref_ptr<ExpNode> exp2):
  myExp1(exp1), myExp2(exp2)
{}

EqualsExpNode::EqualsExpNode(ref_ptr<ExpNode> exp1, ref_ptr<ExpNode> exp2):
  myExp1(exp1), myExp2(exp2)
{}

NotEqualsExpNode::NotEqualsExpNode(ref_ptr<ExpNode> exp1, ref_ptr<ExpNode> exp2):
  myExp1(exp1), myExp2(exp2)
{}

LessExpNode::LessExpNode(ref_ptr<ExpNode> exp1, ref_ptr<ExpNode> exp2):
  myExp1(exp1), myExp2(exp2)
{}

GreaterExpNode::GreaterExpNode(ref_ptr<ExpNode> exp1, ref_ptr<ExpNode> exp2):
  myExp1(exp1), myExp2(exp2)
{}

LessEqExpNode::LessEqExpNode(ref_ptr<ExpNode> exp1, ref_ptr<ExpNode> exp2):
  myExp1(exp1), myExp2(exp2)
{}

GreaterEqExpNode::GreaterEqExpNode(ref_ptr<ExpNode> exp1, ref_ptr<ExpNode> exp2):
  myExp1(exp1), myExp2(exp2)
{}

ProgramNode::ProgramNode(ref_ptr<DeclListNode> declList)
:myDeclList(declList)
{}

//pps:getLineCols
void IntLitNode::getLineColNumber(int & line, int & col) const
{
  line = myLineNum;
  col  = myColNum;
}
void FloatLitNode::getLineColNumber(int & line, int & col) const
{
  line = myLineNum;
  col  = myColNum;
}
void StrLitNode::getLineColNumber(int & line, int & col) const
{
  line = myLineNum;
  col  = myColNum;
}
void TrueNode::getLineColNumber(int & line, int & col) const
{
  line = myLineNum;
  col  = myColNum;
}
void FalseNode::getLineColNumber(int & line, int & col) const
{
  line = myLineNum;
  col  = myColNum;
}
void IdNode::getLineColNumber(int & line, int & col) const
{
  line = myLineNum;
  col  = myColNum;
}
void UnaryMinusExpNode::getLineColNumber(int & line, int & col) const
{
  myExp->getLineColNumber(line,col);
}
void NotExpNode::getLineColNumber(int & line, int & col) const
{
  myExp->getLineColNumber(line,col);
}
void PlusExpNode::getLineColNumber(int & line, int & col) const
{
  myExp1->getLineColNumber(line,col);
}
void MinusExpNode::getLineColNumber(int & line, int & col) const
{
  myExp1->getLineColNumber(line,col);
}
void TimesExpNode::getLineColNumber(int & line, int & col) const
{
  myExp1->getLineColNumber(line,col);
}
void DivideExpNode::getLineColNumber(int & line, int & col) const
{
  myExp1->getLineColNumber(line,col);
}
void AndExpNode::getLineColNumber(int & line, int & col) const
{
  myExp1->getLineColNumber(line,col);
}
void OrExpNode::getLineColNumber(int & line, int & col) const
{
  myExp1->getLineColNumber(line,col);
}
void EqualsExpNode::getLineColNumber(int & line, int & col) const
{
  myExp1->getLineColNumber(line,col);
}
void NotEqualsExpNode::getLineColNumber(int & line, int & col) const
{
  myExp1->getLineColNumber(line,col);
}
void LessExpNode::getLineColNumber(int & line, int & col) const
{
  myExp1->getLineColNumber(line,col);
}
void GreaterExpNode::getLineColNumber(int & line, int & col) const
{
  myExp1->getLineColNumber(line,col);
}
void LessEqExpNode::getLineColNumber(int & line, int & col) const
{
  myExp1->getLineColNumber(line,col);
}
void GreaterEqExpNode::getLineColNumber(int & line, int & col) const
{
  myExp1->getLineColNumber(line,col);
}