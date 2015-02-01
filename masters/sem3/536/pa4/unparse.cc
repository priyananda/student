// CS 536 : PA4
// author: priyananda( shenoy@cs.wisc.edu )
// date: 2 Nov 2008
// random quote:

#include "ast.h"
#include "list_T.h"

#include <iostream>
using std::cout;
using std::endl;

#include <string>
using std::string;

static inline void doIndent(int x)
{
	while(x--)
		//four spaces
		cout << "    ";
}

void ProgramNode::Unparse(int indent)
{
	myDeclList->Unparse(indent);
}

void DeclListNode::Unparse(int indent)
{
	myKids->Reset();
	while (!myKids->AtEnd()) {
		myKids->Current()->Unparse(indent);
		myKids->Next();
	}
}

void VarDeclNode::Unparse(int indent)
{
	doIndent(indent);
	myType->Unparse(0);
	myId->Unparse(0);
	cout << ";" << endl;
}

void IntegerNode::Unparse(int)
{
	cout << "int ";
}

void FloatNode::Unparse(int)
{
	cout << "float ";
}

void BooleanNode::Unparse(int)
{
	cout << "bool ";
}

void StringNode::Unparse(int)
{
	cout << "String ";
}

void IdNode::Unparse(int)
{
	cout << *myStrVal;
}

void FormalsListNode::Unparse(int indent)
{
	myKids->Reset();
	bool first = true;
  	while (!myKids->AtEnd()) {
	  	if(first) first = false; else cout << ", ";
		myKids->Current()->Unparse(indent);
		myKids->Next();
 	}
}

void FnBodyNode::Unparse(int indent)
{
	myDeclList->Unparse(indent);
	myStmtList->Unparse(indent);
}

void StmtListNode::Unparse(int indent)
{
	myKids->Reset();
	while (!myKids->AtEnd()) {
		myKids->Current()->Unparse(indent);
		myKids->Next();
	}
}

void ExpListNode::Unparse(int indent)
{
	myKids->Reset();
	bool first = true;
  	while (!myKids->AtEnd()) {
	  	if(first) first = false; else cout << ", ";
		myKids->Current()->Unparse(indent);
		myKids->Next();
	}	
}

void FnDeclNode::Unparse(int indent)
{
	doIndent(indent); cout << "void "; myId->Unparse(0); cout << "("; myFormalsList->Unparse(0); cout << ") {" << endl;
	myBody->Unparse(indent+1);
	doIndent(indent); cout << "}" << endl;
}

void FormalNode::Unparse(int indent)
{
	myType->Unparse(0);
	cout << " ";
	myId->Unparse(0);
}

void WriteStmtNode::Unparse(int indent)
{
	doIndent(indent);
	cout << "write(";
	myExp->Unparse(0);
	cout << ");" << endl;
}

void AssignStmtNode::Unparse(int indent)
{
	doIndent(indent);
	myId->Unparse(0);
	cout << " = ";
	myExp->Unparse(0);
	cout << ";" << endl;
}

void IfStmtNode::Unparse(int indent)
{
	doIndent(indent); cout << "if("; myExp->Unparse(0); cout << ") {" << endl;
	myStmtList->Unparse(indent+1);
	doIndent(indent); cout << "}" << endl;
}

void IfElseStmtNode::Unparse(int indent)
{
	doIndent(indent); cout << "if("; myExp->Unparse(0); cout << ") {" << endl;
	myThenStmtList->Unparse(indent+1);
	doIndent(indent); cout << "}" << endl;
	doIndent(indent); cout << "else {" << endl;
	myElseStmtList->Unparse(indent+1);
	doIndent(indent); cout << "}" << endl;
}

void WhileStmtNode::Unparse(int indent)
{
	doIndent(indent); cout << "while("; myExp->Unparse(0); cout << ") {" << endl;
	myStmtList->Unparse(indent+1);
	doIndent(indent); cout << "}" << endl;
}

void CallStmtNode::Unparse(int indent)
{
	doIndent(indent);
	myId->Unparse(0); cout << "("; myExpList->Unparse(0); cout << ")";
	cout << ";" << endl;
}

void ReturnStmtNode::Unparse(int indent)
{
	doIndent(indent);
	cout << "return;" << endl;
}

void IntLitNode::Unparse(int)
{
	cout << myIntVal;
}

void FloatLitNode::Unparse(int)
{
	cout << myFloatVal;
}

void StrLitNode::Unparse(int)
{
	cout << *myStrVal;
}

void TrueNode::Unparse(int)
{
	cout << "true";
}

void FalseNode::Unparse(int)
{
	cout << "false";
}

void UnaryMinusExpNode::Unparse(int)
{
	cout << "-"; myExp->Unparse(0);
}

void NotExpNode::Unparse(int)
{
	cout << "!"; myExp->Unparse(0);
}

void PlusExpNode::Unparse(int indent)
{
	cout << "("; myExp1->Unparse(0); cout << " + "; myExp2->Unparse(0); cout << ")"; 
}

void MinusExpNode::Unparse(int indent)
{
	cout << "("; myExp1->Unparse(0); cout << " - "; myExp2->Unparse(0); cout << ")"; 
}

void TimesExpNode::Unparse(int indent)
{
	cout << "("; myExp1->Unparse(0); cout << " * "; myExp2->Unparse(0); cout << ")"; 
}

void DivideExpNode::Unparse(int indent)
{
	cout << "("; myExp1->Unparse(0); cout << " / "; myExp2->Unparse(0); cout << ")"; 
}

void AndExpNode::Unparse(int indent)
{
	cout << "("; myExp1->Unparse(0); cout << " && "; myExp2->Unparse(0); cout << ")"; 
}

void OrExpNode::Unparse(int indent)
{
	cout << "("; myExp1->Unparse(0); cout << " || "; myExp2->Unparse(0); cout << ")"; 
}

void EqualsExpNode::Unparse(int indent)
{
	cout << "("; myExp1->Unparse(0); cout << " == "; myExp2->Unparse(0); cout << ")"; 
}

void NotEqualsExpNode::Unparse(int indent)
{
	cout << "("; myExp1->Unparse(0); cout << " != "; myExp2->Unparse(0); cout << ")"; 
}

void LessExpNode::Unparse(int indent)
{
	cout << "("; myExp1->Unparse(0); cout << " < "; myExp2->Unparse(0); cout << ")"; 
}

void GreaterExpNode::Unparse(int indent)
{
	cout << "("; myExp1->Unparse(0); cout << " > "; myExp2->Unparse(0); cout << ")"; 
}

void LessEqExpNode::Unparse(int indent)
{
	cout << "("; myExp1->Unparse(0); cout << " <= "; myExp2->Unparse(0); cout << ")"; 
}

void GreaterEqExpNode::Unparse(int indent)
{
	cout << "("; myExp1->Unparse(0); cout << " >= "; myExp2->Unparse(0); cout << ")"; 
}
