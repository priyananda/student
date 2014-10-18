#include <stdio.h>
#define TRUE 1
#define FALSE 0
typedef struct
{
	char elements[100];
	int top;
} stack;
void pop ( stack *s , char *popElement , int *empty ){
	if ( s->top == -1 )
		*empty = TRUE ;
	else{
		*empty = FALSE ;
		*popElement = s->elements[ s->top-- ];
	}
}

void push( stack *s ,char pushElement ){
	s->elements[++s->top] = pushElement ;
}

int precedence ( char op1 , char op2 ){
	if ( op1 == '(') return FALSE ;
	if ( op1 == ')'){
		puts( "Error : Invalid Expression ");
		exit();
	}
	if ( op2 == '(') return FALSE ;
	if ( op2 == ')') return TRUE;
	if ( op1 == op2 ){
		if ( op1 == '^')
			return FALSE ;
		return TRUE;
	}
	if ( op1 == '^' ) return TRUE;
	if (( op1 == '*' || op1 == '/') && (op2 == '+' || op2 == '-'))
		return TRUE ;
	return FALSE ;
}
int isOperand ( char c ){
	if ( (c >= 'a' && c <= 'z')  || (c >= 'A' && c <= 'Z'))
		return TRUE;
	return FALSE;
}

void toSuffix ( char *infix , char *suffix ){
	int i ,empty, j=0 ;
	char ch , t= '+ ';
	stack opStack ;
	opStack.top = -1;
	for ( i=0 ; ( ch = infix[i] ) != '\0' ; i++ ){
		if ( isOperand (ch) )
			suffix[j++] = ch ;
		else{
			pop ( &opStack , &t , &empty );
			while( !empty && precedence( t,ch ) ){
				suffix[j++] = t;
				pop( &opStack , &t ,&empty );
			}
			if ( !empty )
				push ( &opStack , t );
			if ( empty ||  ( ch != ')' ) )
				push ( &opStack , ch );
			else
				pop ( &opStack , &t , &empty );
		}
	}
	while ( opStack.top != -1 ){
		pop( &opStack , &ch , &empty );
		suffix[j++] = ch ;
	}
	suffix[j] = '\0';
}
main()
{
	char infix[100] ,suffix[100] ;
	clrscr();
	puts ( "Enter the Valid Infix Expression : Use A ... Z for operands\n and + - * / ^ operators ");
	gets(infix);
	toSuffix(infix,suffix );
	puts("The suffix expression is " );
	puts(suffix);
	getch();
}






