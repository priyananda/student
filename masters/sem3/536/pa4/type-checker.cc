// CS 536 : PA4
// author: priyananda( shenoy@cs.wisc.edu )
// date: 2 Nov 2008
// random quote:

#include <string>
using std::string;

#include <iostream>
using std::cout;
using std::endl;

#include "ast.h"
#include "helper.h"

bool ProgramNode::CheckTypes()
{
	FunctionTable table;
	this->CheckTypes(table);
	return TypeCheckerHelper::getErrorCount() == 0;
}

SymbolType ProgramNode::CheckTypes(FunctionTable & fnt) const
{
	myDeclList->CheckTypes(fnt);
	return NoType;
}

SymbolType  DeclListNode::CheckTypes(FunctionTable & fnt) const
{
	myKids->Reset();
	while (!myKids->AtEnd()) {
		myKids->Current()->CheckTypes(fnt);
		myKids->Next();
	}
	return NoType;
}

SymbolType  VarDeclNode::CheckTypes(FunctionTable & fnt) const
{
	myType->CheckTypes(fnt);
	myId->CheckTypes(fnt);
	return NoType;
}

SymbolType  IntegerNode::CheckTypes(FunctionTable & fnt) const
{
	return NoType;
}

SymbolType  FloatNode::CheckTypes(FunctionTable & fnt) const
{
	return NoType;
}

SymbolType  BooleanNode::CheckTypes(FunctionTable & fnt) const
{
	return NoType;
}

SymbolType  StringNode::CheckTypes(FunctionTable & fnt) const
{
	return NoType;
}

SymbolType  IdNode::CheckTypes(FunctionTable & fnt) const
{
	return mySymbol->type;
}

SymbolType  FormalsListNode::CheckTypes(FunctionTable & fnt) const
{
	myKids->Reset();
  	while (!myKids->AtEnd()) {
		myKids->Current()->CheckTypes(fnt);
		myKids->Next();
 	}
 	return NoType;
}

SymbolType  FnBodyNode::CheckTypes(FunctionTable & fnt) const
{
	myDeclList->CheckTypes(fnt);
	myStmtList->CheckTypes(fnt);
	return NoType;
}

SymbolType  StmtListNode::CheckTypes(FunctionTable & fnt) const
{
	myKids->Reset();
	while (!myKids->AtEnd()) {
		myKids->Current()->CheckTypes(fnt);
		myKids->Next();
	}
	return NoType;
}

SymbolType  ExpListNode::CheckTypes(FunctionTable & fnt) const
{
	myKids->Reset();
  	while (!myKids->AtEnd()) {
		myKids->Current()->CheckTypes(fnt);
		myKids->Next();
	}
	return NoType;
}

SymbolType  FnDeclNode::CheckTypes(FunctionTable & fnt) const
{
	//add function signature to table
	string fnName = myId->strVal();
	FunctionSignature sig;
	
	for(myFormalsList->getDeclarations()->Reset(); !myFormalsList->getDeclarations()->AtEnd(); myFormalsList->getDeclarations()->Next())
		sig.arguments.push_back( myFormalsList->getDeclarations()->Current()->getArgumentType() );
	
	fnt.addSignature(fnName,sig);
	
	myBody->CheckTypes(fnt);
	return NoType;
}

SymbolType  FormalNode::CheckTypes(FunctionTable & fnt) const
{
	myType->CheckTypes(fnt);
	myId->CheckTypes(fnt);
	return NoType;
}

SymbolType  WriteStmtNode::CheckTypes(FunctionTable & fnt) const
{
	SymbolType expType = myExp->CheckTypes(fnt);
	//already some error has occured, so dont print anything
	if( expType == ErrorType ) return ErrorType;
	if( expType == FnType ){
		IdNode * idnode = static_cast<IdNode *>(myExp.get_ptr());
		int line,col;
		idnode->getLineColNumber(line,col);
		TypeCheckerHelper::errorWriteFn(line,col);
	}
	return NoType;
}

SymbolType AssignStmtNode::CheckTypes(FunctionTable & fnt) const
{
	SymbolType idtype = myId->CheckTypes(fnt);
	SymbolType exptype = myExp->CheckTypes(fnt);
	
	if(idtype == FnType || exptype == FnType){
		if(idtype == FnType){
			IdNode * idnode = static_cast<IdNode *>(myId.get_ptr());
			int line,col;
		    idnode->getLineColNumber(line,col);
			TypeCheckerHelper::errorAssignToFn(line,col);
		}
		if(exptype == FnType){
			IdNode * idnode = static_cast<IdNode *>(myExp.get_ptr());
			int line,col;
		    idnode->getLineColNumber(line,col);
			TypeCheckerHelper::errorAssignFromFn(line,col);
		}
		return ErrorType;
	}
	if(exptype != ErrorType)
		if( idtype != exptype ){
			int line,col;
		    myExp->getLineColNumber(line,col);
			TypeCheckerHelper::errorTypeMismatch(line,col);
		}
	return NoType;
}

SymbolType  IfStmtNode::CheckTypes(FunctionTable & fnt) const
{
	SymbolType condType = myExp->CheckTypes(fnt);
	if( condType != ErrorType && condType != BoolType ){
		int line,col;
		myExp->getLineColNumber(line,col);
		TypeCheckerHelper::errorBoolIf(line,col);
	}

	myStmtList->CheckTypes(fnt);
	return NoType;
}

SymbolType  IfElseStmtNode::CheckTypes(FunctionTable & fnt) const
{
	SymbolType condType = myExp->CheckTypes(fnt);
	if( condType != ErrorType && condType != BoolType ){
		int line,col;
		myExp->getLineColNumber(line,col);
		TypeCheckerHelper::errorBoolIf(line,col);
	}
	myThenStmtList->CheckTypes(fnt);
	myElseStmtList->CheckTypes(fnt);
	return NoType;
}

SymbolType  WhileStmtNode::CheckTypes(FunctionTable & fnt) const
{
	SymbolType condType = myExp->CheckTypes(fnt);
	if( condType != ErrorType && condType != BoolType ){
		int line,col;
		myExp->getLineColNumber(line,col);
		TypeCheckerHelper::errorNonBoolWhile(line,col);
	}
	myStmtList->CheckTypes(fnt);
	return NoType;
}

SymbolType  CallStmtNode::CheckTypes(FunctionTable & fnt) const
{
	if(myId->CheckTypes(fnt) != FnType){
		int line,col;
		myId->getLineColNumber(line,col);
		TypeCheckerHelper::errorCallNonFn(line,col);
		return ErrorType;
	}
	string fname = string(myId->strVal());
	FunctionSignature & sig = fnt.getSignature(fname);
	
	if(myExpList->kidsCount() != int(sig.arguments.size()) ){
		int line,col;
		myId->getLineColNumber(line,col);
		TypeCheckerHelper::errorFnArgCount(line,col);
		return ErrorType;
	}
	
	myExpList->matchTypes(fnt,sig);
	return NoType;
}

void ExpListNode::matchTypes(FunctionTable & fnt, FunctionSignature & sig)
{
	myKids->Reset();
	list<SymbolType>::iterator sigiter = sig.arguments.begin();
  	while (!myKids->AtEnd()) {
		SymbolType expType = myKids->Current()->CheckTypes(fnt);
		if(expType != *sigiter ){
			int line,col;
		    myKids->Current()->getLineColNumber(line,col);
			TypeCheckerHelper::errorFnArgType(line,col);
		}
		myKids->Next();
		++sigiter;
	}
}

SymbolType  ReturnStmtNode::CheckTypes(FunctionTable & fnt) const
{
	return NoType;
}

SymbolType  IntLitNode::CheckTypes(FunctionTable & fnt) const
{
	return IntType;
}

SymbolType  FloatLitNode::CheckTypes(FunctionTable & fnt) const
{
	return FloatType;
}

SymbolType  StrLitNode::CheckTypes(FunctionTable & fnt) const
{
	return StringType;
}

SymbolType  TrueNode::CheckTypes(FunctionTable & fnt) const
{
	return BoolType;
}

SymbolType  FalseNode::CheckTypes(FunctionTable & fnt) const
{
	return BoolType;
}

SymbolType  UnaryMinusExpNode::CheckTypes(FunctionTable & fnt) const
{
	SymbolType type = myExp->CheckTypes(fnt);
	if(type == ErrorType || type == IntType || type == FloatType) return type;
	int line,col;
	myExp->getLineColNumber(line,col);
	TypeCheckerHelper::errorTypeMismatch(line,col);
	return ErrorType;
}

SymbolType NotExpNode::CheckTypes(FunctionTable & fnt) const
{
	SymbolType type = myExp->CheckTypes(fnt);
	if(type == ErrorType || type == BoolType) return type;
	int line,col;
	myExp->getLineColNumber(line,col);
	TypeCheckerHelper::errorNonBoolLogical(line,col);
	return ErrorType;
}

SymbolType  PlusExpNode::CheckTypes(FunctionTable & fnt) const
{
	SymbolType exp1type = myExp1->CheckTypes(fnt);
	SymbolType exp2type = myExp2->CheckTypes(fnt);
	if(exp1type == ErrorType || exp2type == ErrorType) return ErrorType;
	if( ( exp1type == IntType || exp1type == FloatType ) && ( exp2type == IntType || exp2type == FloatType ) ){
		if(exp1type == exp2type)
			return exp1type;
		int line,col;
		this->getLineColNumber(line,col);
		TypeCheckerHelper::errorTypeMismatch(line,col);
		return ErrorType;
	}
	if(exp1type != IntType && exp1type != FloatType){
		int line,col;
		myExp1->getLineColNumber(line,col);
		TypeCheckerHelper::errorNonNumArithmetic(line,col);
	}
	if(exp2type != IntType && exp2type != FloatType){
		int line,col;
		myExp2->getLineColNumber(line,col);
		TypeCheckerHelper::errorNonNumArithmetic(line,col);
	}
	return ErrorType;
}

SymbolType  MinusExpNode::CheckTypes(FunctionTable & fnt) const
{
	SymbolType exp1type = myExp1->CheckTypes(fnt);
	SymbolType exp2type = myExp2->CheckTypes(fnt);
	if(exp1type == ErrorType || exp2type == ErrorType) return ErrorType;
	if( ( exp1type == IntType || exp1type == FloatType ) && ( exp2type == IntType || exp2type == FloatType ) ){
		if(exp1type == exp2type)
			return exp1type;
		int line,col;
		this->getLineColNumber(line,col);
		TypeCheckerHelper::errorTypeMismatch(line,col);
		return ErrorType;
	}
	if(exp1type != IntType && exp1type != FloatType){
		int line,col;
		myExp1->getLineColNumber(line,col);
		TypeCheckerHelper::errorNonNumArithmetic(line,col);
	}
	if(exp2type != IntType && exp2type != FloatType){
		int line,col;
		myExp2->getLineColNumber(line,col);
		TypeCheckerHelper::errorNonNumArithmetic(line,col);
	}
	return ErrorType;
}

SymbolType  TimesExpNode::CheckTypes(FunctionTable & fnt) const
{
	SymbolType exp1type = myExp1->CheckTypes(fnt);
	SymbolType exp2type = myExp2->CheckTypes(fnt);
	if(exp1type == ErrorType || exp2type == ErrorType) return ErrorType;
	if( ( exp1type == IntType || exp1type == FloatType ) && ( exp2type == IntType || exp2type == FloatType ) ){
		if(exp1type == exp2type)
			return exp1type;
		int line,col;
		this->getLineColNumber(line,col);
		TypeCheckerHelper::errorTypeMismatch(line,col);
		return ErrorType;
	}
	if(exp1type != IntType && exp1type != FloatType){
		int line,col;
		myExp1->getLineColNumber(line,col);
		TypeCheckerHelper::errorNonNumArithmetic(line,col);
	}
	if(exp2type != IntType && exp2type != FloatType){
		int line,col;
		myExp2->getLineColNumber(line,col);
		TypeCheckerHelper::errorNonNumArithmetic(line,col);
	}
	return ErrorType;
}

SymbolType  DivideExpNode::CheckTypes(FunctionTable & fnt) const
{
	SymbolType exp1type = myExp1->CheckTypes(fnt);
	SymbolType exp2type = myExp2->CheckTypes(fnt);
	if(exp1type == ErrorType || exp2type == ErrorType) return ErrorType;
	if( ( exp1type == IntType || exp1type == FloatType ) && ( exp2type == IntType || exp2type == FloatType ) ){
		if(exp1type == exp2type)
			return exp1type;
		int line,col;
		this->getLineColNumber(line,col);
		TypeCheckerHelper::errorTypeMismatch(line,col);
		return ErrorType;
	}
	if(exp1type != IntType && exp1type != FloatType){
		int line,col;
		myExp1->getLineColNumber(line,col);
		TypeCheckerHelper::errorNonNumArithmetic(line,col);
	}
	if(exp2type != IntType && exp2type != FloatType){
		int line,col;
		myExp2->getLineColNumber(line,col);
		TypeCheckerHelper::errorNonNumArithmetic(line,col);
	}
	return ErrorType;
}

SymbolType  AndExpNode::CheckTypes(FunctionTable & fnt) const
{
	SymbolType exp1type = myExp1->CheckTypes(fnt);
	SymbolType exp2type = myExp2->CheckTypes(fnt);
	if(exp1type == ErrorType || exp2type == ErrorType) return ErrorType;
	if( exp1type == BoolType && exp2type == BoolType )
		return BoolType;
	if(exp1type != BoolType){
		int line,col;
		myExp1->getLineColNumber(line,col);
		TypeCheckerHelper::errorNonBoolLogical(line,col);
	}
	if(exp2type != BoolType){
		int line,col;
		myExp2->getLineColNumber(line,col);
		TypeCheckerHelper::errorNonBoolLogical(line,col);
	}
	return ErrorType;
}

SymbolType  OrExpNode::CheckTypes(FunctionTable & fnt) const
{
	SymbolType exp1type = myExp1->CheckTypes(fnt);
	SymbolType exp2type = myExp2->CheckTypes(fnt);
	if(exp1type == ErrorType || exp2type == ErrorType) return ErrorType;
	if( exp1type == BoolType && exp2type == BoolType )
		return BoolType;
	if(exp1type != BoolType){
		int line,col;
		myExp1->getLineColNumber(line,col);
		TypeCheckerHelper::errorNonBoolLogical(line,col);
	}
	if(exp2type != BoolType){
		int line,col;
		myExp2->getLineColNumber(line,col);
		TypeCheckerHelper::errorNonBoolLogical(line,col);
	}
	return ErrorType;
}

SymbolType  EqualsExpNode::CheckTypes(FunctionTable & fnt) const
{
	SymbolType exp1type = myExp1->CheckTypes(fnt);
	SymbolType exp2type = myExp2->CheckTypes(fnt);
	if(exp1type == ErrorType || exp2type == ErrorType) return ErrorType;
	
	if(exp1type == FnType && exp2type == FnType){
		//todo
		int line,col;
		this->getLineColNumber(line,col);
		TypeCheckerHelper::errorCompareFn(line,col);
		return ErrorType;
	}
	if(exp1type == exp2type)
		return BoolType;
	
	int line,col;
	this->getLineColNumber(line,col);
	TypeCheckerHelper::errorTypeMismatch(line,col);
	return ErrorType;
}

SymbolType  NotEqualsExpNode::CheckTypes(FunctionTable & fnt) const
{
	SymbolType exp1type = myExp1->CheckTypes(fnt);
	SymbolType exp2type = myExp2->CheckTypes(fnt);
	if(exp1type == ErrorType || exp2type == ErrorType) return ErrorType;
	
	if(exp1type == FnType && exp2type == FnType){
		int line,col;
		this->getLineColNumber(line,col);
		TypeCheckerHelper::errorCompareFn(line,col);
		return ErrorType;
	}
	if(exp1type == exp2type)
		return BoolType;
	
	int line,col;
	this->getLineColNumber(line,col);
	TypeCheckerHelper::errorTypeMismatch(line,col);
	return ErrorType;
}

SymbolType  LessExpNode::CheckTypes(FunctionTable & fnt) const
{
	SymbolType exp1type = myExp1->CheckTypes(fnt);
	SymbolType exp2type = myExp2->CheckTypes(fnt);
	if(exp1type == ErrorType || exp2type == ErrorType) return ErrorType;
	
	if( ( exp1type == IntType || exp1type == FloatType ) && ( exp2type == IntType || exp2type == FloatType ) ){
		if(exp1type == exp2type)
			return BoolType;
		int line,col;
		this->getLineColNumber(line,col);
		TypeCheckerHelper::errorTypeMismatch(line,col);
		return ErrorType;
	}
	if(exp1type != IntType && exp1type != FloatType){
		int line,col;
		myExp1->getLineColNumber(line,col);
		TypeCheckerHelper::errorNonNumRelational(line,col);
	}
	if(exp2type != IntType && exp2type != FloatType){
		int line,col;
		myExp2->getLineColNumber(line,col);
		TypeCheckerHelper::errorNonNumRelational(line,col);
	}
	if(exp1type == FnType && exp2type == FnType){
		int line,col;
		this->getLineColNumber(line,col);
		TypeCheckerHelper::errorCompareFn(line,col);
	}
	return ErrorType;
}

SymbolType  GreaterExpNode::CheckTypes(FunctionTable & fnt) const
{
	SymbolType exp1type = myExp1->CheckTypes(fnt);
	SymbolType exp2type = myExp2->CheckTypes(fnt);
	if(exp1type == ErrorType || exp2type == ErrorType) return ErrorType;
	
	if( ( exp1type == IntType || exp1type == FloatType ) && ( exp2type == IntType || exp2type == FloatType ) ){
		if(exp1type == exp2type)
			return BoolType;
		int line,col;
		this->getLineColNumber(line,col);
		TypeCheckerHelper::errorTypeMismatch(line,col);
		return ErrorType;
	}
	if(exp1type != IntType && exp1type != FloatType){
		int line,col;
		myExp1->getLineColNumber(line,col);
		TypeCheckerHelper::errorNonNumRelational(line,col);
	}
	if(exp2type != IntType && exp2type != FloatType){
		int line,col;
		myExp2->getLineColNumber(line,col);
		TypeCheckerHelper::errorNonNumRelational(line,col);
	}
	if(exp1type == FnType && exp2type == FnType){
		int line,col;
		this->getLineColNumber(line,col);
		TypeCheckerHelper::errorCompareFn(line,col);
	}
	return ErrorType;
}


SymbolType  LessEqExpNode::CheckTypes(FunctionTable & fnt) const
{
	SymbolType exp1type = myExp1->CheckTypes(fnt);
	SymbolType exp2type = myExp2->CheckTypes(fnt);
	
	if(exp1type == ErrorType || exp2type == ErrorType) return ErrorType;
	if( ( exp1type == IntType || exp1type == FloatType ) && ( exp2type == IntType || exp2type == FloatType ) ){
		if(exp1type == exp2type)
			return BoolType;
		int line,col;
		this->getLineColNumber(line,col);
		TypeCheckerHelper::errorTypeMismatch(line,col);
		return ErrorType;
	}
	if(exp1type != IntType && exp1type != FloatType){
		int line,col;
		myExp1->getLineColNumber(line,col);
		TypeCheckerHelper::errorNonNumRelational(line,col);
	}
	if(exp2type != IntType && exp2type != FloatType){
		int line,col;
		myExp2->getLineColNumber(line,col);
		TypeCheckerHelper::errorNonNumRelational(line,col);
	}
	if(exp1type == FnType && exp2type == FnType){
		int line,col;
		this->getLineColNumber(line,col);
		TypeCheckerHelper::errorCompareFn(line,col);
	}
	return ErrorType;
}

SymbolType  GreaterEqExpNode::CheckTypes(FunctionTable & fnt) const
{
	SymbolType exp1type = myExp1->CheckTypes(fnt);
	SymbolType exp2type = myExp2->CheckTypes(fnt);
	if(exp1type == ErrorType || exp2type == ErrorType) return ErrorType;
	
	if( ( exp1type == IntType || exp1type == FloatType ) && ( exp2type == IntType || exp2type == FloatType ) ){
		if(exp1type == exp2type)
			return BoolType;
		int line,col;
		this->getLineColNumber(line,col);
		TypeCheckerHelper::errorTypeMismatch(line,col);
		return ErrorType;
	}
	if(exp1type != IntType && exp1type != FloatType){
		int line,col;
		myExp1->getLineColNumber(line,col);
		TypeCheckerHelper::errorNonNumRelational(line,col);
	}
	if(exp2type != IntType && exp2type != FloatType){
		int line,col;
		myExp2->getLineColNumber(line,col);
		TypeCheckerHelper::errorNonNumRelational(line,col);
	}
	if(exp1type == FnType && exp2type == FnType){
		int line,col;
		this->getLineColNumber(line,col);
		TypeCheckerHelper::errorCompareFn(line,col);
	}
	return ErrorType;
}
