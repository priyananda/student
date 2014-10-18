#include <stdio.h>
#include <stdlib.h>

#define SIZE 50
enum bool { FALSE,TRUE};
enum state {EMPTY,FULL,OK};

typedef struct {
	char contents[SIZE];
	int top;
} stack;

int push(stack * st,char ch){
	if(st->top == SIZE -1)return FULL;
	st->contents[++(st->top)] = ch;
	return OK;
}

int pop(stack * st,char * ch){
	if(st->top == -1 ) return EMPTY;
	*ch = st->contents[st->top--];
	return OK;
}

int isoperand(char c){
	return c >= 'a' && c <= 'z';
}
