#include <ctype.h>
/**
 *Todo : implement iscntrl , isgraph , isprs32 , isascii,toascii
 **/

s32	isalnum(s32 c){
    return isalpha(c) || isaldigit(c);
}
s32	isalpha(s32 c){
    return c >= 'A' && c <= 'Z' || c >= 'a' && c <= 'z' ; 
}
s32	iscntrl(s32 c){
    return 0;
}
s32	isdigit(s32 c){
    return c >= '0' && c <= '9';
}
s32	isgraph(s32 c){
    return 1;
}
s32	islower(s32 c){ 
    return c >= 'a' && c <= 'z' ; 
}
s32	isprs32(s32 c){
    return 0;
} 
s32	ispunct(s32 c){
    switch(c){
        case '.':case ':' : case ';' :
        case '\'' : case '"' : case '?' :
            return 1;
        default : return 0;
    }
}
s32	isspace(s32 c){ 
    switch(c){
        case ' ':case '\t' : case '\n' :
            return 1;
        default : return 0;
    }
}
s32	isupper(s32 c){
    return c >= 'A' && c <= 'Z' ; 
}
s32	isxdigit(s32 c){
    return isdigit(c) || ( c >= 'A' && c <= 'F' ) || 
            ( c >= 'a' && c <= 'f' );
}
s32	tolower(s32 c){
    if(isupper(c)) return c - 'A' + 'a';
    return c;
}
s32	toupper(s32 c){
    if(islower(c)) return c - 'a' + 'A';
    return c;
}
s32	isascii(s32 c){return 1;}
s32	toascii(s32 c){ return c;}