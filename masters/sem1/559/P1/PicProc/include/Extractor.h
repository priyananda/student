// CS559 Project 1 : Picture Processor
// author: priyananda( shenoy@cs.wisc.edu )
// date: 13 sep 2007
// random quote: [Fight Club] Tyler Durden: Our Great War's a spiritual war... our Great Depression is our lives.

//forward definitions
class CommandLine;
class TargaImage;

//this class is used to parse induvidual arguments
//and validate them. The "correct" thing to do is
//implement each as a different class. In this case
//I'm doing the "easy" thing: one big class.
class Extractor
{
public:
	//get a valid integer
	static bool extractInt(const CommandLine & c,int argno,char * errorBuffer, int & out);
	//get a valid boolean
	static bool extractBoolean(const CommandLine & c,int argno,char * errorBuffer, bool & out);
	//get a positive integer >= 0
	static bool extractPositiveInt(const CommandLine & c,int argno,char * errorBuffer, int & out);
	//get a valid integer within an (inclusive) range
	static bool extractRangedInt(const CommandLine & c,int argno,char * errorBuffer, int startRange, int endRange, int & out);
	//checks if the file exists and has read permissions
	static bool extractReadableFile(const CommandLine & c,int argno,char * errorBuffer);
	//checks if the file has write permissions
	static bool extractWritableFile(const CommandLine & c,int argno,char * errorBuffer);
	//gets a valid float value
	static bool extractFloat(const CommandLine & c,int argno,char * errorBuffer, float & out);
	//gets a valid float value within an inclusive range
	static bool extractRangedFloat(const CommandLine & c,int argno,char * errorBuffer, float startRange, float endRange, float & out);
	//gets an image from the symbol table. 
	static bool extractVariable(const CommandLine & c,int argno,char * errorBuffer,TargaImage * & out,bool checkForImage = true );
	//check for number of args
	static bool checkArguments(const CommandLine & c,char * buffer,int expectedCount);
};

//macros for reporting various errors
#define REPORT_ERROR(buffer,argno,err)			sprintf_s(buffer,255,"Argument %d is invalid: %s",argno,err)
#define REPORT_MISSING_ARG(buffer,argno)		REPORT_ERROR(buffer,argno,"Required Argument is missing")
#define REPORT_INT(buffer,argno)				REPORT_ERROR(buffer,argno,"Not a valid integer")
#define REPORT_RANGED_INT(buffer,argno,sr,er)	sprintf_s(buffer,255,"Argument %d is invalid: Not in range (%d,%d)",argno,sr,er)
#define REPORT_FLOAT(buffer,argno)				REPORT_ERROR(buffer,argno,"Not a valid floating point number")
#define REPORT_RANGED_FLOAT(buffer,argno,sr,er) sprintf_s(buffer,255,"Argument %d is invalid: Not in range (%f,%f)",argno,sr,er)
#define REPORT_READ_FILE(buffer,argno)			REPORT_ERROR(buffer,argno,"Can't read file. Does it exist?")
#define REPORT_WRITE_FILE(buffer,argno)			REPORT_ERROR(buffer,argno,"Can't write to file. No permissions?")
#define TEST_FOR_NULL(buffer,argno,c)			if(c[argno] == NULL){ REPORT_MISSING_ARG(buffer,argno); return false;}