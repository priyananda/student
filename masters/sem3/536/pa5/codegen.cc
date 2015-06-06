// CS 536 : PA5
// author: priyananda( shenoy@cs.wisc.edu )
// date: 22 Nov 2008
// random quote

#include "ast.h"
#include "codegen.h"
#include "generate.h"

#include <string>
using std::string;

using std::ofstream;
ofstream outFile;

bool ProgramNode::GenerateCode(const string & filename)
{
	CodeGenContext context;
	context.inCodeSection = false;
	context.currentFunctionExitLabel = "";

	outFile.open(filename.c_str());
	GenerateCode(context);
	outFile.close();

	return true;
}
void ProgramNode::GenerateCode(CodeGenContext & context)
{
	Generate(".globl main");
	CodeGenHelper::setSection(context,false);
	GenerateLabeled("_true",".asciiz","","\"true\"");
	GenerateLabeled("_false",".asciiz","","\"false\"");
	myDeclList->GenerateCode(context);
}

void DeclListNode::GenerateCode(CodeGenContext & context)
{
	myKids->Reset();
	while (!myKids->AtEnd()) {
		myKids->Current()->GenerateCode(context);
		myKids->Next();
	}
}

void VarDeclNode::GenerateCode(CodeGenContext & context)
{
	if(myId->symbol()->isGlobalVar()){
		CodeGenHelper::setSection(context,false);
		GenerateLabeled(
			CodeGenHelper::getGlobalVariableLabel(myId->symbol()),
			CodeGenHelper::getTypeLabel(myId->symbol()->type),
			"",
			CodeGenHelper::getInitValue(myId->symbol()->type)
		);
	}
}

void IntegerNode::GenerateCode(CodeGenContext & context)
{
}

void FloatNode::GenerateCode(CodeGenContext & context)
{
}

void BooleanNode::GenerateCode(CodeGenContext & context)
{
}

void StringNode::GenerateCode(CodeGenContext & context)
{
}

void IdNode::GenerateCode(CodeGenContext & context)
{
	switch(this->expressionType){
		case FloatType:
			if(symbol()->isGlobalVar())
				Generate("l.s",F0,CodeGenHelper::getGlobalVariableLabel(symbol()));
			else
				GenerateIndexed("l.s",F0,FP,symbol()->offset);
			GenerateFPush(F0);
			break;
		case IntType:
		case BoolType:
		case StringType:
			if(symbol()->isGlobalVar())
				Generate("lw",T0,CodeGenHelper::getGlobalVariableLabel(symbol()));
			else
				GenerateIndexed("lw",T0,FP,symbol()->offset);
			GeneratePush(T0);
			break;
		default:break;
	}
}

void FormalsListNode::GenerateCode(CodeGenContext & context)
{
	myKids->Reset();
  	while (!myKids->AtEnd()) {
		myKids->Current()->GenerateCode(context);
		myKids->Next();
 	}
}

void FnBodyNode::GenerateCode(CodeGenContext & context)
{
	myDeclList->GenerateCode(context);
	myStmtList->GenerateCode(context);
}

void StmtListNode::GenerateCode(CodeGenContext & context)
{
	myKids->Reset();
	while (!myKids->AtEnd()) {
		myKids->Current()->GenerateCode(context);
		myKids->Next();
	}
}

void ExpListNode::GenerateCode(CodeGenContext & context)
{
	//damnation, it's a singly linked list, flip it locally
	list< ref_ptr<ExpNode> > exps;
	for( myKids->Reset(); !myKids->AtEnd() ; myKids->Next() )
		exps.push_front(myKids->Current());
	for(list< ref_ptr<ExpNode> >::iterator iter = exps.begin(); iter != exps.end(); ++iter )
		(*iter)->GenerateCode(context);
}

void FnDeclNode::GenerateCode(CodeGenContext & context)
{
	CodeGenHelper::setSection(context,true);
	
	string entryLabel = CodeGenHelper::getFunctionLabel(myId->symbol());
	context.currentFunctionExitLabel = ::NextLabel();
	
	//function entry
	GenerateWithComment("","entry code for " + entryLabel);
	GenerateLabel(entryLabel);
	GeneratePush(RA);
	GeneratePush(FP);
	Generate("addu",FP,SP,WORD_SIZE);
	if(myId->symbol()->numberOfLocals > 0)
		Generate("subu",SP,SP,WORD_SIZE * myId->symbol()->numberOfLocals);
	Generate("");

	//function body
	myBody->GenerateCode(context);

	//function exit
	GenerateLabel(context.currentFunctionExitLabel, "exit code for " + entryLabel);
	Generate("addu",SP,FP,0);//move FP to SP
	GenerateIndexed("lw",FP,FP,0);
	GeneratePop(RA);
}

void FormalNode::GenerateCode(CodeGenContext & context)
{
}

void WriteStmtNode::GenerateCode(CodeGenContext & context)
{
	GenerateWithComment("","Write statement");

	string sysCallLabel;
	myExp->GenerateCode(context);
	switch(myExp->expressionType)
	{
		case IntType:
			Generate("li",V0,"1");
			GeneratePop(A0);
			break;
		case FloatType:
			Generate("li",V0,"2");
			GenerateFPop(F12);
			break;
		case StringType:
			Generate("li",V0,"4");
			GeneratePop(A0);
			break;
		case BoolType:
			Generate("li",V0,"4");
			Generate("la",A0,"_false");
			GeneratePop(T0);
			Generate("beqz",T0,sysCallLabel = ::NextLabel());
			Generate("la",A0,"_true");
			GenerateLabel(sysCallLabel);
			break;
		default:
			break;
	}
	Generate("syscall");
	Generate("");
}

void AssignStmtNode::GenerateCode(CodeGenContext & context)
{
	GenerateWithComment("","Assign statement");

	myExp->GenerateCode(context);
	//the answer is now on the stack
	if(myExp->expressionType == FloatType){
		GenerateFPop(F0);
		CodeGenHelper::genSaveF0(myId->symbol());
	}else{
		GeneratePop(T0);
		CodeGenHelper::genSaveT0(myId->symbol());
	}
	Generate("");
}

void IfStmtNode::GenerateCode(CodeGenContext & context)
{
	string ifEndLabel = ::NextLabel();
	myExp->GenerateCode(context);
	//top of the stack is -1(true) or false(0)
	GeneratePop(T0);
	Generate("beqz",T0,ifEndLabel);
		myStmtList->GenerateCode(context);
	GenerateLabel(ifEndLabel);
}

void IfElseStmtNode::GenerateCode(CodeGenContext & context)
{
	string ifEndLabel = ::NextLabel();
	string elseEndLabel = ::NextLabel();

	myExp->GenerateCode(context);
	//top of stack is true or false
	
	GeneratePop(T0);
	Generate("beqz",T0,ifEndLabel);
		myThenStmtList->GenerateCode(context);
	Generate("b",T0,elseEndLabel);
	GenerateLabel(ifEndLabel);
		myElseStmtList->GenerateCode(context);
	GenerateLabel(elseEndLabel);
}

void WhileStmtNode::GenerateCode(CodeGenContext & context)
{
	string beginLabel = ::NextLabel();
	string endLabel   = ::NextLabel();
	
	GenerateLabel(beginLabel);
		myExp->GenerateCode(context);
	GeneratePop(T0);
	Generate("beqz",T0,endLabel);
		myStmtList->GenerateCode(context);
	Generate("b",beginLabel);
	GenerateLabel(endLabel);
}

void CallStmtNode::GenerateCode(CodeGenContext & context)
{
	//this will evaluate expressions in right-to-left order
	myExpList->GenerateCode(context);
	Generate("jal", CodeGenHelper::getFunctionLabel(myId->symbol()) );
	//pop the arguments off the stack
	Generate("addi",SP,SP, "" + (4 * myId->symbol()->numberOfParameters) );
	Generate("");
}

void ReturnStmtNode::GenerateCode(CodeGenContext & context)
{
	Generate("b",context.currentFunctionExitLabel);
}

void IntLitNode::GenerateCode(CodeGenContext & context)
{
	string temp = ::NextLabel();

	CodeGenHelper::setSection(context,false);
	GenerateLabeled(temp, ".word" ,"", "" + myIntVal);
	CodeGenHelper::setSection(context,true);
	Generate("lw",T0,temp);
	GeneratePush(T0);
}

void FloatLitNode::GenerateCode(CodeGenContext & context)
{
	char fstr[25];
	::sprintf(fstr,"%f",myFloatVal);
	string temp = ::NextLabel();

	CodeGenHelper::setSection(context,false);
	GenerateLabeled(temp, ".float" ,"",temp);
	CodeGenHelper::setSection(context,true);
	Generate("l.s",F0,temp);
	GenerateFPush(F0);
}

void StrLitNode::GenerateCode(CodeGenContext & context)
{
	string temp = ::NextLabel();

	CodeGenHelper::setSection(context,false);
	GenerateLabeled(temp, ".asciiz" ,"", *myStrVal);
	CodeGenHelper::setSection(context,true);
	Generate("la",T0,temp);
	GeneratePush(T0);
}

void TrueNode::GenerateCode(CodeGenContext & context)
{
	Generate("li",T0,TRUE);
	GeneratePush(T0);
}

void FalseNode::GenerateCode(CodeGenContext & context)
{
	Generate("li",T0,FALSE);
	GeneratePush(T0);
}

void UnaryMinusExpNode::GenerateCode(CodeGenContext & context)
{
	myExp->GenerateCode(context);
	
	if(myExp->expressionType == FloatType){
		GenerateFPop(F0);
		Generate("neg.d",F0,F0);
		GenerateFPush(F0);
	}else{
		GeneratePop(T0);
		Generate("neg",T0,T0);
		GeneratePush(T0);
	}
}

void NotExpNode::GenerateCode(CodeGenContext & context)
{
	myExp->GenerateCode(context);
	
	GeneratePop(T0);
	Generate("not",T0,T0);
	GeneratePush(T0);
}

void PlusExpNode::GenerateCode(CodeGenContext & context)
{
	myExp1->GenerateCode(context);
	myExp2->GenerateCode(context);

	if(expressionType == FloatType){
		GenerateFPop(F2);
		GenerateFPop(F0);
		Generate("add.s",F0,F0,F2);
		GenerateFPush(F0);
	}else{
		GeneratePop(T1);
		GeneratePop(T0);
		Generate("addu",T0,T0,T1);
		GeneratePush(T0);
	}
}

void MinusExpNode::GenerateCode(CodeGenContext & context)
{
	myExp1->GenerateCode(context);
	myExp2->GenerateCode(context);

	if(expressionType == FloatType){
		GenerateFPop(F2);
		GenerateFPop(F0);
		Generate("sub.s",F0,F0,F2);
		GenerateFPush(F0);
	}else{
		GeneratePop(T1);
		GeneratePop(T0);
		Generate("subu",T0,T0,T1);
		GeneratePush(T0);
	}
}

void TimesExpNode::GenerateCode(CodeGenContext & context)
{
	myExp1->GenerateCode(context);
	myExp2->GenerateCode(context);

	if(expressionType == FloatType){
		GenerateFPop(F2);
		GenerateFPop(F0);
		Generate("mul.s",F0,F0,F2);
		GenerateFPush(F0);
	}else{
		GeneratePop(T1);
		GeneratePop(T0);
		Generate("mul",T0,T0,T1);
		GeneratePush(T0);
	}
}

void DivideExpNode::GenerateCode(CodeGenContext & context)
{
	myExp1->GenerateCode(context);
	myExp2->GenerateCode(context);

	if(expressionType == FloatType){
		GenerateFPop(F2);
		GenerateFPop(F0);
		Generate("div.s",F0,F0,F2);
		GenerateFPush(F0);
	}else{
		GeneratePop(T1);
		GeneratePop(T0);
		Generate("div",T0,T0,T1);
		GeneratePush(T0);
	}
}

void AndExpNode::GenerateCode(CodeGenContext & context)
{
	string exp2Label = ::NextLabel();
	string endLabel = ::NextLabel();

	//short circuit
	myExp1->GenerateCode(context);
	GeneratePop(T0);
	Generate("bneqz",T0,exp2Label); //if not false, go to second part
	//exp1 was false, so push result back and finish
	GeneratePush(T0);
	Generate("b", endLabel);
	GenerateLabel(exp2Label);
	myExp2->GenerateCode(context);
	//nothing to do, the correct value already on stack
	GenerateLabel(endLabel);
}

void OrExpNode::GenerateCode(CodeGenContext & context)
{
	string exp2Label = ::NextLabel();
	string endLabel = ::NextLabel();

	//short circuit
	myExp1->GenerateCode(context);
	GeneratePop(T0);
	Generate("beqz",T0,exp2Label); //if false, go to second part
	//exp1 was true, so push result back and finish
	GeneratePush(T0);
	Generate("b", endLabel);
	GenerateLabel(exp2Label);
	myExp2->GenerateCode(context);
	//nothing to do, the correct value already on stack
	GenerateLabel(endLabel);
}

//all the bool exp nodes do the same thing, other than the comparison op codes
static inline void generateBoolExpNode(SymbolType expressionType, const string & copcode, const string & bfopcode, const string & biopcode)
{
	string eqLabel = ::NextLabel();
	string endLabel = ::NextLabel();

	if(expressionType == FloatType){
		GenerateFPop(F2);
		GenerateFPop(F0);
		Generate(copcode,F0,F2);
		Generate(bfopcode,eqLabel);
	}else{
		GeneratePop(T1);
		GeneratePop(T0);
		Generate(biopcode,T0,T1,eqLabel);
	}
	Generate("li",T0,FALSE);
	Generate("b", endLabel);
	GenerateLabel(eqLabel);
	Generate("li",T0,TRUE);
	GenerateLabel(endLabel);
	GeneratePush(T0);
}

void EqualsExpNode::GenerateCode(CodeGenContext & context)
{
	myExp1->GenerateCode(context);
	myExp2->GenerateCode(context);
	
	::generateBoolExpNode(
		this->expressionType,
		"c.eq.s",
		"bczt",
		"beq"
	);
}

void NotEqualsExpNode::GenerateCode(CodeGenContext & context)
{
	myExp1->GenerateCode(context);
	myExp2->GenerateCode(context);

	::generateBoolExpNode(
		this->expressionType,
		"c.eq.s",
		"bczf",
		"bneq"
	);
}

void LessExpNode::GenerateCode(CodeGenContext & context)
{
	myExp1->GenerateCode(context);
	myExp2->GenerateCode(context);
	
	::generateBoolExpNode(
		this->expressionType,
		"c.lt.s",
		"bczt",
		"blt"
	);
}

void GreaterExpNode::GenerateCode(CodeGenContext & context)
{
	myExp1->GenerateCode(context);
	myExp2->GenerateCode(context);

	::generateBoolExpNode(
		this->expressionType,
		"c.gt.s",
		"bczt",
		"bgt"
	);
}

void LessEqExpNode::GenerateCode(CodeGenContext & context)
{
	myExp1->GenerateCode(context);
	myExp2->GenerateCode(context);

	::generateBoolExpNode(
		this->expressionType,
		"c.le.s",
		"bczt",
		"ble"
	);
}

void GreaterEqExpNode::GenerateCode(CodeGenContext & context)
{
	myExp1->GenerateCode(context);
	myExp2->GenerateCode(context);

	::generateBoolExpNode(
		this->expressionType,
		"c.ge.s",
		"bczt",
		"bge"
	);
}

void CodeGenHelper::genSaveT0(SymbolPtr ptr)
{
	if(ptr->isGlobalVar())
		Generate("sw",T0,getGlobalVariableLabel(ptr));
	else
		GenerateIndexed("sw",T0,FP,ptr->offset);
}

void CodeGenHelper::genSaveF0(SymbolPtr ptr)
{
	if(ptr->isGlobalVar())
		Generate("s.s",F0,getGlobalVariableLabel(ptr));
	else
		GenerateIndexed("s.s",F0,FP,ptr->offset);
}

void CodeGenHelper::setSection(CodeGenContext & ctx, bool codeSection)
{
	if(codeSection == ctx.inCodeSection) return;
	Generate( (ctx.inCodeSection = codeSection) ? ".text" : ".data");
}