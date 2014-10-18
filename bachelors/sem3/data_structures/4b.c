#include <stdio.h>
#include <conio.h>
#define TRUE 1
#define FALSE 0
#define MAX_SIZE 3
#define NO_OF_Q 3
typedef struct
{
	int element [MAX_SIZE];
	int rear, front;
} queue ;

typedef struct
{
	queue que[NO_OF_Q];
} priorityQ ;

int isEmpty ( queue *q){
	return (q->rear < q->front) ? TRUE : FALSE ;
}

int isFull ( queue *q ){
	return ( q->rear == MAX_SIZE - 1) ? TRUE : FALSE ;
}

void qDelete ( queue *q , int *element){
	*element = q->element[ q->front++ ];
}


void qInsert ( queue *q ,int element ){
	q->element[ ++q->rear ] = element;
}

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
void initialize( priorityQ *pq ){
	int i;
	for ( i=0 ; i < NO_OF_Q ; i++ ){
		pq->que[i].rear = -1;
		pq->que[i].front = 0;
	}
}
void pqInsert ( priorityQ *pq , int p , int element ){
	if ( isFull( &(pq->que[p - 1]) ))
		puts("Insertion Failed : Queue is already full");
	else
		qInsert(&(pq->que[p-1]),element);
}

void pqDelete ( priorityQ *pq , int * element , int *flag ){
	int i;
	*flag = 0;
	for ( i=0 ; i < NO_OF_Q ; i++ )
		if ( isEmpty ( &(pq->que[i]) ) )
			continue;
		else{
			 qDelete( &(pq->que[i]) , element);
			 *flag = 1;
			 break;
		}
}
void pqDisplay( priorityQ *pq ){
	int i,j;
	puts("");
	for ( i = 0; i < NO_OF_Q ; i++ ){
		printf("queue %d:",i+1);
		if ( isEmpty ( &(pq->que[i]) ) )
			printf("Empty");
		else{
			printf("F-> ");
			for (j = pq->que[i].front;j <= pq->que[i].rear ;j++ )
				printf("%d   ",pq->que[i].element[j] );
			printf("<-R");
		}
		puts("");
	}
}
main()
{
	int element , ch , p ;
	priorityQ pq;
	initialize ( &pq );
	while(1){
		ch = menu() ;
		switch(ch){
			case 1:puts("\nEnter the element to be inserted");
				   scanf("%d",&element);
				   printf("Enter the priority:\n");
				   scanf("%d",&p);
				   pqInsert( &pq , p,element );
				   break;
			case 2:pqDelete( &pq , &element,&p );
				   if( p == 1 )
						printf("The deleted Element is %d\n ",element );
				   else
						printf("Queue Under Flow : All Q's are empty\n");
				   break;
			case 4:exit();
		}
		pqDisplay(&pq);
		puts("*************** Press any key to continue ********************** ");
		getch();
	}
}




