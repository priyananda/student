#include <stdio.h>
#include <conio.h>
#define FALSE 0
#define TRUE  1
#define MAX_SIZE 3
typedef int type;
struct stak
{
	type element[MAX_SIZE];
	int top ;
};
typedef struct stak stack ;

int isEmpty( stack * s){
	if ( s->top == -1 )
		return TRUE;
	else
		return FALSE;
}

int isFull( stack *s ){
	if ( s->top == MAX_SIZE - 1 )
		return TRUE ;
	else
		return FALSE ;
}

void pop( stack *s , type *poppedElement ){
	if ( isEmpty(s) )
		puts("Stack Underflow : Pop Operation cannot be carried out ");
	else
		*poppedElement = s->element[s->top--];
}

void push( stack *s , type pushedElement ){
	if ( isFull(s) )
		puts("Stack Overflow : Push Operation cannot be carried out ");
	else
		s->element[++s->top] = pushedElement;
}

void display ( stack *s ){
	int i;
	if ( isEmpty(s) ){
		puts("The Stack is Empty ");
		puts("\n--------Press any key for menu ---------------");
		return;
	}
	if ( isFull(s) )
		puts("The Stack is Full");
	puts("The Elements of the Stack are:");
	for ( i = s->top ; i >= 0 ;i--){
		if ( i == s->top )
			printf("%4d%cTOP\n",s->element[i],27);
		else if ( i == 0 )
				printf("%4d%cBASE\n",s->element[i],27);
			 else
				printf("%4d\n",s->element[i]);
	}
	puts("-----------Press any key for menu---------------");
}

int menu(){
	int choice;
	clrscr();
	puts("---------------------   MENU  --------------------");
	puts("Enter:\n1 for Pop Operation\n2 for Push Operation\n3 for Display Operation\n4 for Exit");
	printf("Your Choice : ");
	scanf("%d",&choice );
	return choice;
}
main()
{
	stack st;
	int p;
	type x;
	st.top = -1;
	while(1){
		p = menu();
		switch(p){
			case 1: pop (&st,&x);
					if ( !isEmpty(&st) )
						 printf("The Element popped is %d\n",x);
					 break;
			case 2:  if ( !isFull(&st) )
						printf("Enter the Element to be pushed :");
					 scanf("%d",&x);
					 push(&st,x);
					 break;
			case 3: break;
			case 4: exit();
			default: puts("Illegal Operation");
		}
		display(&st);
		getch();

	}
}






