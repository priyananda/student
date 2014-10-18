#include <types.h>
#include <string.h>
/**
 * @document : string.c
 * @author : shenoy
 * @date :5/14/03
 * @comments :  Code adapted from JiJos OS Code . tested on 5/14/03
 **/

/**
 *  strcpy - string copy from src to dest
 **/
char * strcpy(char * dest,  char *src){
    int d0, d1, d2;
    __asm__ __volatile__(
	    "cld\n"
	    "1:\tlodsb\n\t"
	    "stosb\n\t"
	    "testb %%al,%%al\n\t"
	    "jne 1b"
	    : "=&S" (d0), "=&D" (d1), "=&a" (d2)
	    :"0" (src),"1" (dest) : "memory"
    );
    return dest;
}

/**
 *  strncpy - string copy from src to dest , with count
 **/
char * strncpy(char * dest,char *src,s32  count){
    int d0, d1, d2, d3;
    __asm__ __volatile__(
        "cld\n"
        "1:\tdecl %2\n\t"
        "js 2f\n\t"
        "lodsb\n\t"
        "stosb\n\t"
        "testb %%al,%%al\n\t"
        "jne 1b\n\t"
        "rep\n\t"
        "stosb\n"
        "2:"
        : "=&S" (d0), "=&D" (d1), "=&c" (d2), "=&a" (d3)
        :"0" (src),"1" (dest),"2" (count) : "memory"
    );
    return dest;
}
/**
 * strcat - string concatenation dest = dest + source
 **/
char * strcat(char * dest,char * src){
    int d0, d1, d2, d3;
    __asm__ __volatile__(
        "cld\n\t"
        "repne\n\t"
        "scasb\n\t"
        "decl %1\n"
        "1:\tlodsb\n\t"
        "stosb\n\t"
        "testb %%al,%%al\n\t"
        "jne 1b"
        : "=&S" (d0), "=&D" (d1), "=&a" (d2), "=&c" (d3)
        : "0" (src), "1" (dest), "2" (0), "3" (0xffffffff):"memory"
    );
    return dest;
}
/**
 * strncat - string concatenation with limiting count
 **/
char * strncat(char * dest,char * src,s32 count){
    int d0, d1, d2, d3;
    __asm__ __volatile__(
        "cld\n\t"
        "repne\n\t"
        "scasb\n\t"
        "decl %1\n\t"
        "movl %8,%3\n"
        "1:\tdecl %3\n\t"
        "js 2f\n\t"
        "lodsb\n\t"
        "stosb\n\t"
        "testb %%al,%%al\n\t"
        "jne 1b\n"
        "2:\txorl %2,%2\n\t"
        "stosb"
        : "=&S" (d0), "=&D" (d1), "=&a" (d2), "=&c" (d3)
        : "0" (src),"1" (dest),"2" (0),"3" (0xffffffff), "g" (count)
        : "memory");
    return dest;
}
/**
 *  strcmp-string compare
 **/

s32 strcmp(char * cs,char * ct){
    int d0, d1;
    register int __res;
    __asm__ __volatile__(
        "cld\n"
        "1:\tlodsb\n\t"
        "scasb\n\t"
        "jne 2f\n\t"
        "testb %%al,%%al\n\t"
        "jne 1b\n\t"
        "xorl %%eax,%%eax\n\t"
        "jmp 3f\n"
        "2:\tsbbl %%eax,%%eax\n\t"
        "orb $1,%%al\n"
        "3:"
        :"=a" (__res), "=&S" (d0), "=&D" (d1)
                 :"1" (cs),"2" (ct));
    return __res;
}
/**
 * strncmp - string compare with count
 **/
int strncmp(char * cs,char * ct,s32 count){
    register int __res;
    int d0, d1, d2;
    __asm__ __volatile__(
        "cld\n"
        "1:\tdecl %3\n\t"
        "js 2f\n\t"
        "lodsb\n\t"
        "scasb\n\t"
        "jne 3f\n\t"
        "testb %%al,%%al\n\t"
        "jne 1b\n"
        "2:\txorl %%eax,%%eax\n\t"
        "jmp 4f\n"
        "3:\tsbbl %%eax,%%eax\n\t"
        "orb $1,%%al\n"
        "4:"
        :"=a" (__res), "=&S" (d0), "=&D" (d1), "=&c" (d2)
        :"1" (cs),"2" (ct),"3" (count)
    );
    return __res;
}

/**
 * strlen -string length
 **/
s32 strlen(  char * s) {
    int d0;
    register int __res;
    __asm__ __volatile__(
        "cld\n\t"
        "repne\n\t"
        "scasb\n\t"
        "notl %0\n\t"
        "decl %0"
        :"=c" (__res), "=&D" (d0) :"1" (s),"a" (0), "0" (0xffffffff));
    return __res;
}

/**
 *
 **/

void * memcpy(void * to,   void * from, s32 n){
    int d0, d1, d2;
    __asm__ __volatile__(
        "cld\n\t"
        "rep ; movsl\n\t"
        "testb $2,%b4\n\t"
        "je 1f\n\t"
        "movsw\n"
        "1:\ttestb $1,%b4\n\t"
        "je 2f\n\t"
        "movsb\n"
        "2:"
        : "=&c" (d0), "=&D" (d1), "=&S" (d2)
        :"0" (n/4), "q" (n),"1" ((long) to),"2" ((long) from)
        : "memory"
    );
    return (to);
}

