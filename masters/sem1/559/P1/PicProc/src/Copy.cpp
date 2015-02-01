// CS559 Project 1 : Picture Processor
// author: priyananda( shenoy@cs.wisc.edu )
// date: 15 sep 2007
// random quote: []
#include "Copy.h"
#include "Extractor.h"
#include "TargaImage.h"
#include "SymbolTable.h"

bool Copy::extract(const CommandLine & c)
{
	TargaImage * temp;
	if( Extractor::checkArguments(c,errorString,2) &&
		Extractor::extractVariable(c,0,errorString,srcImage) &&
		Extractor::extractVariable(c,1,errorString,temp,false))
	{
		destVarName = c[1][0];
		return true;
	}
	return false;
}

void Copy::execute()
{
	SymbolTable::setSymbol( destVarName, srcImage->clone());
}