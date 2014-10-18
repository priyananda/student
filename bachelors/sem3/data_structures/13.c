#include <stdio.h>
#include <alloc.h>
#define TRUE 1
#define FALSE 0
typedef struct node {
	char info;
	struct node *left;
	struct node *right;
} * Nodeptr;


typedef struct
{
	char elements[100];
	int top;
} stack;
char list[10];
float value[10];
int j = 0;
Nodeptr newNode ( char ch){
	Nodeptr p;
	p = malloc(sizeof(struct node));
	p->info = ch;
	return p;
}
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

Nodeptr toTree( char *suffix){

	Nodeptr stk[10],p;
	int i=0,j=0;
	char ch;
	while ( (ch = suffix[i++]) != '\0'){
		p = newNode (ch);
		if ( isOperand(ch) )    stk[j++] = p;
		else{
			p->right = stk[--j];
			p->left = stk[--j];
			stk[j++] = p;
		}
	 }	return stk[--j];
}
int isPresent(char ch){
	int i = 0;
	for (;i<j;i++)
		if ( ch == list[i] ) return TRUE;
		return FALSE;

}
float valueOf (char ch){
	int i = 0;
	while ( ch != list[i] ) i++;
	return value[i];
}
float evaluate( Nodeptr tree){
	float element,result;
	switch(tree->info){
		case '+':result = evaluate(tree->left) + evaluate(tree->right);break;
		case '-':result = evaluate(tree->left) - evaluate(tree->right);break;
		case '*':result = evaluate(tree->left) * evaluate(tree->right);break;
		case '/':result = evaluate(tree->left) / evaluate(tree->right);break;
		//case '^':result = evaluate(tree->left) ^ evaluate(tree->right);break;
		default : if ( isOperand( tree->info)){
					if ( !isPresent(tree->info) ){
					printf("Enter value of %c:",tree->info);
					scanf("%f",&element);
					list[j] = tree->info ;
					value[j++] = element;
					}
					else
						element = valueOf(tree->info);
					return element;
				  }
		}
		return result;
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
void main()
{
	char infix[100] ,suffix[100] ;
	float result;
	Nodeptr n;
	clrscr();
	puts ( "Enter the Valid Infix Expression : Use A ... Z for operands\n and + - * /  operators ");
	gets(infix);
	toSuffix(infix,suffix );
	puts("The suffix expression is " );
	puts(suffix);
	n = toTree ( suffix);
	result = evaluate(n);
	printf("%f",result);
	getch();
}






