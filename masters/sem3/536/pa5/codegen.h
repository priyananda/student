// CS 536 : PA5
// author: priyananda( shenoy@cs.wisc.edu )
// date: 22 Nov 2008
// random quote:

#ifndef CS536_PA5_CODEGEN_H
#define CS536_PA5_CODEGEN_H

#include <string>
using std::string;

const int WORD_SIZE = 4;

class CodeGenContext
{
public:
	//label of current function's exit snippet. useful for return
	string currentFunctionExitLabel;
	//are we right now in code section? or data section?
	bool inCodeSection;
};


class CodeGenHelper
{
public:
	//hopefully AR structure depends only on these calculations
	
	//calculates byte offset from FP for parameters.
	static int calculateParameterOffset(int pindex)
	{
		//4 bytes for RA, right-to-left ordering
		return (pindex + 2) * WORD_SIZE;
	}
	
	//calculate byte offset from FP for local variables.
	static int calculateLocalVariableOffset(int vindex)
	{
		return -4 * (vindex + 1);
	}
	
	//global vars are prefixed by '_'
	static string getGlobalVariableLabel(const SymbolPtr p)
	{
		return "_" + p->symbolName;
	}
	
	//function names are prefixed by "_" apart from main
	static string getFunctionLabel(const SymbolPtr p)
	{
		if(p->symbolName == "main")
			return p->symbolName;
		return "_" + p->symbolName;
	}

	static string getTypeLabel(SymbolType type)
	{
		switch(type){
			case IntType:
			case BoolType:
			case StringType:
				return ".word";
			case FloatType:
				return ".float";
			default:break;
		}
		return "";
	}
	static string getInitValue(SymbolType type)
	{
		switch(type){
			case IntType:
			case BoolType:
			case StringType:
				return "0";
			case FloatType:
				return "0.0";
			default:break;
		}
		return "";
	}

	static void genSaveT0(SymbolPtr ptr);

	static void genSaveF0(SymbolPtr ptr);

	static void setSection(CodeGenContext & ctx, bool codeSection);
};

#endif
