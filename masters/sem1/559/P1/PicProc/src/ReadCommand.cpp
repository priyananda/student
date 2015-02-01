// CS559 Project 1 : Picture Processor
// author: priyananda( shenoy@cs.wisc.edu )
// date: 15 sep 2007
// random quote: [300] Leonidas: Give them nothing! But take from them everything! 
#include "ReadCommand.h"
#include "Extractor.h"
#include "TargaImage.h"
#include "SymbolTable.h"
#include "ImageHelpers.h"

bool ReadCommand::extract(const CommandLine & cl)
{
	if( Extractor::checkArguments(cl,errorString,2) &&
		Extractor::extractVariable(cl,0,errorString,image,false) &&
		Extractor::extractReadableFile(cl,1,errorString) ){
		this->varName  = cl[0][0];
		this->filePath = cl[1];
		return true;
	}
	return false;
}

static void unPreMultiply(Command * p,unsigned char * pixel)
{
	if( pixel[3] != 0 && pixel[3] != 255 ){
		pixel[0] = unsigned char( 255 * pixel[0] / pixel[3] );
		pixel[1] = unsigned char( 255 * pixel[1] / pixel[3] );
		pixel[2] = unsigned char( 255 * pixel[2] / pixel[3] );
	}
}

void ReadCommand::execute()
{
	image = TargaImage::readImage(this->filePath);
	if(image == NULL){
		REPORT_ERROR(errorString,1,"Is this a TGA file?");
		return;
	}
	//unpremultiply
	ImageHelpers::forEachPixel(this,image,unPreMultiply);
	SymbolTable::setSymbol(varName,image);
}

bool WriteCommand::extract(const CommandLine & c)
{
	if( Extractor::checkArguments(c,errorString,2) &&
		Extractor::extractVariable(c,0,errorString,image) &&
		Extractor::extractWritableFile(c,1,errorString)){
		filePath = c[1];
		return true;
	}
	return false; 
}

void WriteCommand::execute()
{
	image->write(filePath);
}