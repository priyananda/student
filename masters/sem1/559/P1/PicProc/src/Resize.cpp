// CS559 Project 1 : Picture Processor
// author: priyananda( shenoy@cs.wisc.edu )
// date: 22 sep 2007
// random quote: [Grindhouse] Stuntman Mike: There are few things fetching as a bruised ego on a beautiful woman.

#include "Resize.h"
#include "Extractor.h"
#include "TargaImage.h"
#include "ImageHelpers.h"
#include "SymbolTable.h"

bool Resize::extract(const CommandLine & c)
{
	if( Extractor::checkArguments(c,errorString,3) &&
		Extractor::extractVariable(c,0,errorString,image) &&
		Extractor::extractPositiveInt(c,1,errorString,num) &&
		Extractor::extractPositiveInt(c,2,errorString,den)){
			varName = c[0][0];
			return true;
	}
	return false;
}

//resize to arbitrary ratio is same as applying
//two integral up- and down- scales. not very
//efficient but...:D
void Resize::execute()
{
	if( num == 0 || den == 0 )
		return;
	TargaImage * tempImage = ImageHelpers::upSample2D(image,num);
	TargaImage * newImage = ImageHelpers::downSample2D(tempImage,den);
	SymbolTable::setSymbol(varName,newImage);
}