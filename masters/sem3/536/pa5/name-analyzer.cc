// CS 536 : PA4
// author: priyananda( shenoy@cs.wisc.edu )
// date: 2 Nov 2008
// random quote:

#include "ast.h"

#include <string>
using std::string;

#include "helper.h"

#include <iostream>
using namespace std;

bool ProgramNode::AnalyzeNames()
{
	ScopeList scopes;
	this->ProcessNames(scopes);
	SymbolPtr mainSymbol = scopes.Lookup("main",false);
	if(mainSymbol == NULL || mainSymbol->type != FnType)
		NameAnalyzerHelper::errorNoMain();
	return NameAnalyzerHelper::getErrorCount() == 0;
}

void ProgramNode::ProcessNames(ScopeList & scopes)
{
	myDeclList->ProcessNames(scopes);
}

void DeclListNode::ProcessNames(ScopeList & scopes)
{
	myKids->Reset();
	while (!myKids->AtEnd()) {
		myKids->Current()->ProcessNames(scopes);
		myKids->Next();
	}
}

void VarDeclNode::ProcessNames(ScopeList & scopes)
{
	const string & idName = myId->strVal();
	if( scopes.Lookup(idName,true) != NULL){
		//duplicate decl
		  int line,col;
		  myId->getLineColNumber(line,col);
		  NameAnalyzerHelper::errorRedeclaration(line,col);
	}else
		scopes.Insert(idName, myType->getTypeSpecifier());

	myId->ProcessNames(scopes);
}

void IntegerNode::ProcessNames(ScopeList & scopes)
{
}

void FloatNode::ProcessNames(ScopeList & scopes)
{
}

void BooleanNode::ProcessNames(ScopeList & scopes)
{
}

void StringNode::ProcessNames(ScopeList & scopes)
{
}

void IdNode::ProcessNames(ScopeList & scopes)
{
	this->mySymbol = scopes.Lookup(*myStrVal,false);
	if(this->mySymbol == NULL)
		NameAnalyzerHelper::errorUndeclared(myLineNum,myColNum);
}

void FormalsListNode::ProcessNames(ScopeList & scopes)
{
	myKids->Reset();
  	while (!myKids->AtEnd()) {
		myKids->Current()->ProcessNames(scopes);
		myKids->Next();
 	}
}

void FnBodyNode::ProcessNames(ScopeList & scopes)
{
	myDeclList->ProcessNames(scopes);
	myStmtList->ProcessNames(scopes);
}

void StmtListNode::ProcessNames(ScopeList & scopes)
{
	myKids->Reset();
	while (!myKids->AtEnd()) {
		myKids->Current()->ProcessNames(scopes);
		myKids->Next();
	}
}

void ExpListNode::ProcessNames(ScopeList & scopes)
{
	myKids->Reset();
  	while (!myKids->AtEnd()) {
		myKids->Current()->ProcessNames(scopes);
		myKids->Next();
	}	
}

void FnDeclNode::ProcessNames(ScopeList & scopes)
{
	//todo
	const string & idName = myId->strVal();
	if( scopes.Lookup(idName,true) != NULL){
		//duplicate decl
		int line,col;
		myId->getLineColNumber(line,col);
		NameAnalyzerHelper::errorRedeclaration(line,col);
	}else
		scopes.Insert(idName, FnType);
	
	myId->ProcessNames(scopes);
	
	scopes.BeginScope();
	
	myFormalsList->ProcessNames(scopes);
	myBody->ProcessNames(scopes);
	
	scopes.EndScope();
}

void FormalNode::ProcessNames(ScopeList & scopes)
{
	const string & idName = myId->strVal();
	if( scopes.Lookup(idName,true) != NULL){
		//duplicate decl
		int line,col;
		myId->getLineColNumber(line,col);
		NameAnalyzerHelper::errorRedeclaration(line,col);
	}else
		scopes.Insert(idName, myType->getTypeSpecifier());

	myId->ProcessNames(scopes);
}

void WriteStmtNode::ProcessNames(ScopeList & scopes)
{
	myExp->ProcessNames(scopes);
}

void AssignStmtNode::ProcessNames(ScopeList & scopes)
{
	myId->ProcessNames(scopes);
	myExp->ProcessNames(scopes);
}

void IfStmtNode::ProcessNames(ScopeList & scopes)
{
	myExp->ProcessNames(scopes);
	myStmtList->ProcessNames(scopes);
}

void IfElseStmtNode::ProcessNames(ScopeList & scopes)
{
	myExp->ProcessNames(scopes);
	myThenStmtList->ProcessNames(scopes);
	myElseStmtList->ProcessNames(scopes);
}

void WhileStmtNode::ProcessNames(ScopeList & scopes)
{
	myExp->ProcessNames(scopes);
	myStmtList->ProcessNames(scopes);
}

void CallStmtNode::ProcessNames(ScopeList & scopes)
{
	myId->ProcessNames(scopes);
	myExpList->ProcessNames(scopes);
}

void ReturnStmtNode::ProcessNames(ScopeList & scopes)
{
}

void IntLitNode::ProcessNames(ScopeList & scopes)
{
}

void FloatLitNode::ProcessNames(ScopeList & scopes)
{
}

void StrLitNode::ProcessNames(ScopeList & scopes)
{
}

void TrueNode::ProcessNames(ScopeList & scopes)
{
}

void FalseNode::ProcessNames(ScopeList & scopes)
{
}

void UnaryMinusExpNode::ProcessNames(ScopeList & scopes)
{
	myExp->ProcessNames(scopes);
}

void NotExpNode::ProcessNames(ScopeList & scopes)
{
	myExp->ProcessNames(scopes);
}

void PlusExpNode::ProcessNames(ScopeList & scopes)
{
	myExp1->ProcessNames(scopes);
	myExp2->ProcessNames(scopes);
}

void MinusExpNode::ProcessNames(ScopeList & scopes)
{
	myExp1->ProcessNames(scopes);
	myExp2->ProcessNames(scopes);
}

void TimesExpNode::ProcessNames(ScopeList & scopes)
{
	myExp1->ProcessNames(scopes);
	myExp2->ProcessNames(scopes);
}

void DivideExpNode::ProcessNames(ScopeList & scopes)
{
	myExp1->ProcessNames(scopes);
	myExp2->ProcessNames(scopes);
}

void AndExpNode::ProcessNames(ScopeList & scopes)
{
	myExp1->ProcessNames(scopes);
	myExp2->ProcessNames(scopes);
}

void OrExpNode::ProcessNames(ScopeList & scopes)
{
	myExp1->ProcessNames(scopes);
	myExp2->ProcessNames(scopes);
}

void EqualsExpNode::ProcessNames(ScopeList & scopes)
{
	myExp1->ProcessNames(scopes);
	myExp2->ProcessNames(scopes);
}

void NotEqualsExpNode::ProcessNames(ScopeList & scopes)
{
	myExp1->ProcessNames(scopes);
	myExp2->ProcessNames(scopes);
}

void LessExpNode::ProcessNames(ScopeList & scopes)
{
	myExp1->ProcessNames(scopes);
	myExp2->ProcessNames(scopes);
}

void GreaterExpNode::ProcessNames(ScopeList & scopes)
{
	myExp1->ProcessNames(scopes);
	myExp2->ProcessNames(scopes);
}

void LessEqExpNode::ProcessNames(ScopeList & scopes)
{
	myExp1->ProcessNames(scopes);
	myExp2->ProcessNames(scopes);
}

void GreaterEqExpNode::ProcessNames(ScopeList & scopes)
{
	myExp1->ProcessNames(scopes);
	myExp2->ProcessNames(scopes);
}
