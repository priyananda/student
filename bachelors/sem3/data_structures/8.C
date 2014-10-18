#include <stdio.h>
#include <alloc.h>
#include <conio.h>
typedef struct nod{
	int info;
	struct nod * next;
} Node;
typedef Node * Nodeptr;
Nodeptr newNode(){
	return (Nodeptr) malloc(sizeof(Node));
}

void olinsert(Nodeptr *first,int e){
	Nodeptr p,curr,prev;
	p = newNode();
	p->info = e;
	prev = NULL;
	curr = *first;
	if ( curr == NULL ){
		*first = p;
		p->next = NULL;
		return;
	}
	if (  e < curr->info){
		p->next =  (*first);
		*first = p;
		return;
	}

	for ( ;curr != NULL && e > curr->info ; curr = curr->next)
		prev = curr;
	p->next = prev->next;
	prev->next = p;
}


Nodeptr createList(){
	Nodeptr list=NULL;
	char ch = 'Y';
	int e;

	do{
		printf("\nEnter the element to be inserted: ");
		scanf("%d",&e);
		olinsert(&list,e);
		printf("Want to insert another element?(y/n)");
		ch = getche();
	}while( ch == 'Y' || ch == 'y');
	return list;
}

void insert( Nodeptr *list, int e){
	Nodeptr curr,p;
	p = newNode();
	p->info = e;
	curr = *list;
	if (curr == NULL ){
		*list = p;
		p->next = NULL;
	}
	while(curr->next != NULL)
		curr = curr->next;
	curr->next = p;
	p->next = NULL;
}
void mergeList(Nodeptr  l1,Nodeptr l2,Nodeptr * dest){
	Nodeptr last;
	if(l1->info < l2->info){
		*dest = l1;
		l1 = l1->next;
		last = *dest;
	}else{
		*dest = l2;
		l2 = l2->next;
		last = *dest;
	}
	while(l1 && l2){
		if(l1->info < l2->info){
			last->next = l1;
			last = last->next;
			l1 = last->next;
		}else{
			last->next = l2;
			last = last->next;
			l2 = last->next;
		}
	}
	if(l1)
		last->next = l1;
	else
		last->next = l2;
}

void display( Nodeptr list){
	Nodeptr curr = list;
	if (curr == NULL ){
		puts("list is Empty");
		return;
	}
	printf("Start->");
	while(curr != NULL ){
		printf("  %d  ",curr->info);
		curr = curr->next;
	}
	printf("<-End");
}

int main(){
	Nodeptr list1,list2,mlist;
	list1 = list2 = mlist = NULL;
	clrscr();
	puts("Creating First list ....");
	list1 = createList();
	//display(list1);
	//getch();
	clrscr();
	puts("Creating Second list ....");
	list2 = createList();
	//display(list2);
	//getch();
	clrscr();
	puts("The merged list is:");
	mergeList(list1,list2,&mlist);
	display(mlist);
	getch();
	return 1;
}

