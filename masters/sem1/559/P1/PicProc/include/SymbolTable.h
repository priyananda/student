// CS559 Project 1 : Picture Processor
// author: priyananda( shenoy@cs.wisc.edu )
// date: 13 sep 2007
// random quote: [Terminator] Terminator: I'll be back

//forward defn
class TargaImage;

//this basically maintains a name->image map.
//calling this a symbol table is a bit of an
//overkill, but the analogy is so apt.
class SymbolTable
{
public:
	//returns NULL if no such var exists
	static TargaImage * getSymbol(char varName);
	//sets a variable. should destroy existing image.
	static void setSymbol(char varname,TargaImage *p);
	
	//function pointer for enumerate
	typedef void (*EnumFunction) ( char varName, TargaImage * image );

	//enumerate all symbols
	static void enumerate(EnumFunction function);
};