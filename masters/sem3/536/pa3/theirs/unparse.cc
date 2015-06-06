#include "ast.h"
#include "list_T.h"
#include <iostream>
#include <string>

// **********************************************************************
// Unparse operations
//
// ***WARNING***
// Versions of the Unparse operation are provided for:
//      DeclListNode, VarDeclNode, IntegerNode, BooleanNode, StringNode,
//      IdNode
// These are not necessarily complete.
//
// Incomplete versions for the other kinds of ASTnode are provided so
// that the code will compile for you; you must replace all the other
// function bodies with the correct code.
//
// Notes:
//  1. Some versions of Unparse do not use their "indentation"
//     parameter; in these cases, have the list of formals include
//     only the type (int), not the name (indent); that way you won't
//     get a warning message from the compiler about an unused parameter.
// **********************************************************************

void DeclListNode::Unparse(int indent)
{
  myKids->Reset();
  while (!myKids->AtEnd()) {
    myKids->Current()->Unparse(indent);
    myKids->Next();
  }
}

void VarDeclNode::Unparse(int)
{
  myType->Unparse();
  myId->Unparse();
  std::cout << ";" << std::endl;
}

void IntegerNode::Unparse(int)
{ std::cout << "int "; }

void FloatNode::Unparse(int)
{ std::cout << "float "; }

void BooleanNode::Unparse(int)
{ std::cout << "bool "; }

void StringNode::Unparse(int)
{ std::cout << "String "; }

void IdNode::Unparse(int)
{ std::cout << *myStrVal; }

// EMPTY FUNCTION DEFINITIONS START HERE

void FormalsListNode::Unparse(int indent)
{
}

void FnBodyNode::Unparse(int indent)
{
}

void StmtListNode::Unparse(int indent)
{
}

void ExpListNode::Unparse(int indent)
{
}

void FnDeclNode::Unparse(int indent)
{
}

void FormalNode::Unparse(int indent)
{
}

void WriteStmtNode::Unparse(int indent)
{
}

void AssignStmtNode::Unparse(int indent)
{
}

void IfStmtNode::Unparse(int indent)
{
}

void IfElseStmtNode::Unparse(int indent)
{
}

void WhileStmtNode::Unparse(int indent)
{
}

void CallStmtNode::Unparse(int indent)
{
}

void ReturnStmtNode::Unparse(int indent)
{
}

void IntLitNode::Unparse(int indent)
{
}

void FloatLitNode::Unparse(int indent)
{
}

void StrLitNode::Unparse(int indent)
{
}

void TrueNode::Unparse(int indent)
{
}

void FalseNode::Unparse(int indent)
{
}

void UnaryMinusExpNode::Unparse(int indent)
{
}

void NotExpNode::Unparse(int indent)
{
}

void PlusExpNode::Unparse(int indent)
{
}

void MinusExpNode::Unparse(int indent)
{
}

void TimesExpNode::Unparse(int indent)
{
}

void DivideExpNode::Unparse(int indent)
{
}

void AndExpNode::Unparse(int indent)
{
}

void OrExpNode::Unparse(int indent)
{
}

void EqualsExpNode::Unparse(int indent)
{
}

void NotEqualsExpNode::Unparse(int indent)
{
}

void LessExpNode::Unparse(int indent)
{
}

void GreaterExpNode::Unparse(int indent)
{
}

void LessEqExpNode::Unparse(int indent)
{
}

void GreaterEqExpNode::Unparse(int indent)
{
}
