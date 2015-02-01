#include <cstdio>
#include <cctype>
#include "SymbolTable.h"
#include "TargaImage.h"

//duh!
#define NUMBER_OF_LETTERS_IN_ENGLISH_ALPHABET 26
static TargaImage * table[NUMBER_OF_LETTERS_IN_ENGLISH_ALPHABET];
//have we been initialized?
static bool inited = false;

//get image for variable
TargaImage * SymbolTable::getSymbol(char var)
{
	if(!inited){
		inited = true;
		for(int i = 0 ; i < NUMBER_OF_LETTERS_IN_ENGLISH_ALPHABET; ++i )
			table[i] = NULL;
	}
	if(!isalpha(var))
		return NULL;
	return table[var >= 'a' ? var - 'a' : var - 'A'];
}

//set image for variable
void SymbolTable::setSymbol(char var,TargaImage * p)
{
	if(!isalpha(var))
		return;
	int index = var >= 'a' ? var - 'a' : var - 'A';
	if( table[index] != NULL )
		//destroy existing image
		delete table[index];
	table[index] = p;
}

//calls function for each non-null image
void SymbolTable::enumerate(SymbolTable::EnumFunction function)
{
	for(int i = 0 ; i < NUMBER_OF_LETTERS_IN_ENGLISH_ALPHABET; ++i )
		if(table[i] != NULL)
			function('a' + i,table[i]);
}