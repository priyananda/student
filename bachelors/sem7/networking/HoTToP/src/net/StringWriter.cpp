#include <net/StringWriter.h>

void StringWriter::write(const char * str){
	myOut.write(str,strlen(str)+1);
}
void StringWriter::write(const char str[] , int n){
	myOut.write(str,n);
}
void StringWriter::write( const string & str){
	myOut.write(str.c_str(),str.length()+1);
}
void StringWriter::write(const char ch){
	myOut.write(&ch,1);
}
/** 
 * 	very IMPORTANT note. `write` writes '\0' as well. This makes reading
 * 	on the other side easier. `writeLine` on the other hand , doesnot write
 * 	'\0' rather writes str followed by '\r\n' . No null terminated string
 */ 	
void StringWriter::writeLine( const char * str ){
	myOut.write(str,strlen(str));
	myOut.write("\r\n" , 2 );
}
