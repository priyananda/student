#include <alloc.h>
#include "menu.c"

typedef struct nod{
	int info;
	struct nod *next ;
} Node;
typedef Node * Nodeptr;
Nodeptr newNode (){
	return (Nodeptr) malloc( sizeof(Node) );
}

void insertLeft( Nodeptr *first){
	Nodeptr p;
	p = newNode();
	puts("Enter the data for node to be inserted:");
	scanf("%d",&(p->info) );
	p->next = *first;
	*first = p;
}

void remLeft( Nodeptr *first){
	if ( *first == NULL ){
		puts("Deletion Failed : list is empty\n");
		return;
	}
	printf("The deleted data is :%d\n", (*first)->info );
	*first = (*first)->next ;
}

void insertRight( Nodeptr *first ){
	Nodeptr current, p;
	p = newNode();
	puts("Enter the data to be inserted:");
	scanf("%d",&(p->info) );
	if ( *first == NULL ){
		*first = p;
		p->next = NULL;
		return;
	}
	current = *first;
	if (current->next == NULL){
		current->next = p;
		p->next = NULL;
		return;
	}
	while ((current->next)->next  != NULL )
	   current = current->next;
	(current->next)->next = p;
	p->next = NULL;
}
void remRight( Nodeptr *first){
	Nodeptr current;
	if ( *first == NULL ){
		puts("The list is empty");
		return;
	}
	current = *first;
	if (current->next == NULL ){
		printf("The deleted Element is: %d \n",current->info );
		*first = NULL;
		return;
	}
	while( (current->next)->next != NULL )
		current = current->next;
	printf("The deleted Element is: %d\n ",current->info );
	current->next = NULL;
}
void display(Nodeptr first){
	Nodeptr current;
	if ( first == NULL )  {
		puts("List is Empty");
		return;
	}
	current = first;
	printf("f-> ");
	while ( current != NULL ){
		printf("%d   ",current->info );
		current = current->next;
	}
	printf("<- r ");
}
int main(){
	Nodeptr first = NULL;
	int choice;

	char *items[] = { "Remove Left" ,"Remove Right", "Insert Left", "Insert Right","Display","Quit" };
	while(1){
		clrscr();
		choice = menu(items,6,20,10,"**********Menu***********" );
		switch( choice){
			case 1:remLeft(&first);break;
			case 2:remRight(&first);break;
			case 3:insertLeft(&first);break;
			case 4:insertRight(&first);break;
			case 5:display(first);break;
			case 6:exit();
		}
		gotoxy(30,28);
		puts("press any key to continue");
		getch();
	}
}

