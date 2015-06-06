// CS559 Project 1 : Picture Processor
// author: priyananda( shenoy@cs.wisc.edu )
// date: 16 sep 2007
// random quote: [Casablanca] Elsa: Play it again, Sam.

#include "Extractor.h"
#include "Command.h"
#include "SymbolTable.h"
#include <cstdlib>
#include <float.h>
#include <windows.h>

//todo: check for non-digit chars
bool Extractor::extractInt(const CommandLine & cl,int argno,char * buffer, int & out)
{
	TEST_FOR_NULL(buffer,argno,cl)
	char * input = cl[argno];
	out = ::atoi(input);
	return true;
}

bool Extractor::extractBoolean(const CommandLine & cl,int argno,char * buffer, bool & out)
{
	if( _stricmp(cl[argno],"true") == 0 || _stricmp(cl[argno],"1") == 0 ){
		out = true;
		return true;
	}
	if( _stricmp(cl[argno],"false") == 0 || _stricmp(cl[argno],"0") == 0 ){
		out = false;
		return true;
	}
	REPORT_ERROR(buffer,argno,"Invalid Boolean value");
	return false;
}

//an integer >= 0
bool Extractor::extractPositiveInt(const CommandLine & cl,int argno,char * buffer, int & out)
{
	int val = 0;
	if(!extractInt(cl,argno,buffer,out)) return false;
	if( val < 0 ){
		REPORT_ERROR(buffer,argno,"Positive Integer required");
		return false;
	}
	return true;
}
//range is inclusive
bool Extractor::extractRangedInt(const CommandLine & cl,int argno,char * buffer, int startRange, int endRange, int & out )
{
	TEST_FOR_NULL(buffer,argno,cl)
	char * input = cl[argno];
	out = ::atoi(input);
	if( out >= startRange && out <= endRange )
		return true;
	REPORT_RANGED_INT(buffer,argno,startRange,endRange);
	return false;
}
//todo: check for non-digits
bool Extractor::extractFloat(const CommandLine & cl,int argno,char * buffer, float &out)
{
	TEST_FOR_NULL(buffer,argno,cl)
	char * input = cl[argno];
	out = static_cast<float>(::atof(input));
	if(_isnan(out)){
		REPORT_FLOAT(buffer,argno);
		return false;
	}
	return true;
}
//range is inclusive
bool Extractor::extractRangedFloat(const CommandLine & cl,int argno,char * buffer, float startRange, float endRange, float & out)
{
	TEST_FOR_NULL(buffer,argno,cl)
	char * input = cl[argno];
	out = static_cast<float>(::atof(input));
	if( out >= startRange && out <= endRange )
		return true;
	REPORT_RANGED_FLOAT(buffer,argno,startRange,endRange);
	return false;
}
//are there other ways of checking for file exists?
//well, we can use POSIX stat.
bool Extractor::extractReadableFile(const CommandLine & cl,int argno,char * buffer)
{
	TEST_FOR_NULL(buffer,argno,cl)
	char * input = cl[argno];
	if(::GetFileAttributes(input) == INVALID_FILE_ATTRIBUTES){
		REPORT_READ_FILE(buffer,argno);
		return false;
	}
	return true;
}
//todo: implement this
bool Extractor::extractWritableFile(const CommandLine & cl,int argno,char * buffer)
{
	return true;
}
//get an image for a variable. The checkForImage flag ( with default true )
//controls what to do when there is no image yet for this variable. This
//happens in read/copy/blank commands. In such cases, we ignore it.
bool Extractor::extractVariable(const CommandLine & cl,int argno,char * buffer,TargaImage *&var,bool checkForImage)
{
	TEST_FOR_NULL(buffer,argno,cl)
	char * input = cl[argno];
	var = SymbolTable::getSymbol(input[0]);
	if( checkForImage && var == NULL ){
		sprintf_s(buffer,255,"No image exists for variable %c",input[0]);
		return false;
	}
	return true;
}

//you can have more arguments than the expectedCount, but not less.
bool Extractor::checkArguments(const CommandLine & c,char * buffer,int expectedCount)
{
	if(c.numberOfArguments() < expectedCount){
		sprintf_s(buffer,255,"Invalid number of arguments: expected %d, got %d",expectedCount,c.numberOfArguments());
		return false;
	}
	return true;
}