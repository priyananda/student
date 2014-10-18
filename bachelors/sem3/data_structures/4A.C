#include <stdio.h>
#include <conio.h>
#define TRUE 1
#define FALSE 0
#define MAX_SIZE 3
#include "menu.c"


typedef struct
{
	int element [MAX_SIZE];
	int rear, front;
} queue ;

int isEmpty ( queue *q){
	return (q->rear < q->front) ? TRUE : FALSE ;
}

int isFull ( queue *q ){
	return ( q->rear == MAX_SIZE - 1) ? TRUE : FALSE ;
}

void qDelete ( queue *q , int *element){
	if (isEmpty(q))
		printf("Queue Underflow");
	else
		*element = q->element[ q->front++ ];
}


void qInsert ( queue *q ,int element ){
	if (isFull(q))
		puts("Queue OverFlow");
	else
		q->element[ ++q->rear ] = element;
}

void qDisplay ( queue *q ){
	int i;
	if ( isEmpty(q) ){
		puts("Queue is Empty");
		return;
	}
/*	if ( isFull(q) )
		puts("Queue is full");*/
	printf("F->  ");
	for ( i = q->front ; i <= q->rear ; i++)
		printf("%d  ", q->element[ i ] );
	printf("<-R\n\n");
}
/*
int menu(){
	int ch;
	while(1){
		clrscr();
		puts("*************************MENU***********************");
		printf("Enter:\n1 for insertion\n2 for Deletion\n3 for Display\n4 to exit\nYour Choice:");
		scanf("%d",&ch);
		if ( ch > 0 && ch <= 4 )
			return ch;
	}
}
*/

main()
{
	int element , ch ;
	queue q;
	char * mnu[] = {
					"Insertion",
					"Deletion",
					"Display",
					"Exit",

				   };
	q.rear = -1;
	q.front = 0;
	while(1){
		ch = menu(mnu,4,20,10,"****Choices****") ;
		switch(ch){
			case 1:puts("Enter the element to be inserted");
				   scanf("%d",&element);
				   qInsert( &q , element );
				   break;
			case 2:if (!isEmpty(&q) ){
						qDelete( &q , &element );
						printf("The deleted Element is %d\n ",element );
						}
				   else
						printf("Queue Under Flow ");
				   break;
			case 4:exit();
		}
		qDisplay(&q);
		puts("*************** Press any key to continue ********************** ");
		getch();
	}
}




