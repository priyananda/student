#include <net/StringReader.h>

int StringReader::read(){
	char ch;
	if ( myIn.read(&ch,1) < 0 )return -1;
	return ch;
}

string StringReader::readString(){
	char ch = 0;
	int _ret;
	string ret = "";
	while ( ( _ret = myIn.read(&ch,1) ) > 0){
		if(!ch)break;
		ret += char(ch);
	}
	if( _ret <= 0 ) throw EndOfFileException();
	return ret;
}

/**
 * See writeLine below. If a line with CRLF  is written with a '\0' 
 * The NUL char still stays in the stream. Use writeLine and readLine 
 * consistently 
 */ 
string StringReader::readLine(char delim){
	char ch = 0;
	string ret = "";
	int _ret;
	while ( ( _ret = myIn.read(&ch,1)) > 0){
		if(!ch || ch == delim )break;
		ret += char(ch);
	}
	if ( _ret <= 0 ) throw EndOfFileException();
	if ( ret[ ret.length() - 1 ] == '\r' )
		ret.erase(ret.length() - 1 , 1 ); 
	return ret;
}
