#include <stdio.h>
#include <alloc.h>
#include <conio.h>
#include <time.h>
//#include "menu.c"

typedef struct nod {
	int info;
	struct nod *prev;
	struct nod *next;
} Node;
typedef Node * Nodeptr;
Nodeptr newNode(){
	return  (Nodeptr) malloc ( sizeof(Node));
}

void insertFront ( Nodeptr  header,int element){
	Nodeptr p = newNode();
	p->info = element;
	if ( header->next == NULL ){
		header->next = p;
		p->next = NULL;
		p->prev = header;
		return;
	}
	p->next = header->next;
	header->next = p;
	p->next->prev = p;
}

void insertLeft( Nodeptr header , int key , int element){
	Nodeptr curr , p;
	p = newNode();
	p->info = element;
	curr = header->next;
	if ( curr == NULL ){
		puts("Element is not found");
		return;
	}
	while ( curr != NULL ){
		if ( curr->info == key ){
			curr->prev->next = p;
			p->prev = curr->prev;
			p->next = curr;
			curr->prev = p;
			return;
		}
		curr = curr->next;
	}
	puts("Element is not found");
}

int  delete(Nodeptr header ,Nodeptr element){
//	Nodeptr curr;
	if ( element == header ) return 0;
	if ( element == header->next) { header->next = element->next ; return 1;}
	if ( element->next == NULL ) { element->prev->next = NULL;return 1;}
	element->prev->next = element->next ;
	element->next->prev = element->prev;
	return 1;
}
int deleteAll ( Nodeptr header, int key){
	Nodeptr curr ,temp;
	int count = 0;
	if ( header->next  == NULL  ) return 0;
	curr = header->next;
	while( curr != NULL ){
		if ( curr->info == key ){
			temp = curr->next;
			count += delete ( header,curr );
			curr = temp;
		}
		else curr = curr->next;
	}
	return count;
}

int menu(){
	int ch;
	while(1){
		clrscr();
		puts("Menu:\nenter:\n1 for Insert Front\n2 for Insert Left\n3 for Delete");
		printf("4 for display\n5 to quit\nYour choice:");
		scanf("%d",&ch);
		if ( ch > 0 && ch < 6 )
			return ch;
	}
}

void display( Nodeptr header ){
	Nodeptr curr = header;
	if ( curr == NULL ){
		puts("List is Empty");
		return;
	}
	curr = header->next;
	printf("Start->");
	while( curr != NULL ){

		printf("  %d  ",curr->info);
		curr = curr->next;
	}
	printf("<-End");

}

int main(){
	Nodeptr header;
	int key, ch,element;
	char * str[] = { "Insert at front ","Insert Left" , "Delete","Display","Quit"};
	header = newNode();
	header->next = header->prev = NULL;
	while(1){
		ch = menu();//str,5,10,10,"Menu: Doubly Linked list");
		switch(ch){
			case 1:puts("Enter the element to be inserted");
				   scanf("%d",&key);
				   insertFront(header,key);
				   break;
			case 2:puts("Enter the key element ");


			scanf("%d",&key);
				   puts("Enter the element to be inserted");
				   scanf("%d",&element);
				   insertLeft(header,key,element);
				   break;
			case 3:puts("Enter the key element for deletion ");
				   scanf("%d",&key);
				   element = deleteAll(header,key);
				   if (element == 0)
						puts("Key is not Found");
				   else
						printf("\nNumber of nodes deleted : %d",element);
				   break;
			case 4:display ( header);
				   break;
			case 5:return 1;
		}
		puts("\n\n\nPress any key to continue");
		getch();
	}
}









