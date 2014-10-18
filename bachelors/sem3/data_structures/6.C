#include <stdio.h>
#include <alloc.h>

struct nod{
	int job_id ;
	char job_name[20] , job_desc[20];
	struct nod *next;
};
typedef struct nod Node;
typedef Node * Nodeptr;
void linsert( Nodeptr *first ){
	Nodeptr p, current;
	p = (Nodeptr) malloc ( sizeof(struct nod) );
	puts("Enter the ID, name , description");
	scanf("%d %s %s",&(p->job_id) ,p->job_name , p->job_desc );
	current = *first;
	while( current != NULL ){
		if ( current->job_id == p->job_id ){
		   puts("The node already exists");
		   return;
		}
		current = current->next;
	}
	p->next = *first;
	*first = p;
}
void ldelete (  Nodeptr *first){
	Node * n, * p;
	int id;
	if(*first == NULL){
		puts("The List is Empty : Deletion Failed");
		return;
	}
	puts("Enter the job id to be deleted");
	scanf("%d",&id);
	if((*first)->job_id == id){
		 n = *first;
		printf("The deleted element is\nName:%s\nID:%d\nDEscription:%s\n",n->job_name,n->job_id,n->job_desc);
		n = *first;
		*first = n->next;
		free(n);
		return;
	}
	n = *first;
	while(n != NULL && n->job_id != id){
		p = n;
		n = n->next;
	}
	if(!n){
		puts("Element not found");
		return ;
	}
	printf("The deleted element is\nName:%s\nID:%d\nDEscription:%s\n",n->job_name,n->job_id,n->job_desc);
	p->next = n->next;
	free(n);

}


void lsearch(Nodeptr first){
	Nodeptr current = first;
	int key_id;
	puts("Enter the Job Id to be Searched :");
	scanf("%d",&key_id );
	while( current != NULL ){
		if ( current->job_id == key_id ){
			puts("The Node is found\nDetails of the found node are: ");
			printf("ID:%d\nName:%s\nDescription:%s\n",current->job_id ,current->job_name ,current->job_desc);
			return;
		}
		current = current->next;
	}
	puts("The Node is not found");
}

void ldisplay( Nodeptr first){
	Nodeptr current = first;
	int count = 1;
	if (first == NULL){
		puts("The list is Empty");
		return;
	}
	while ( current != NULL ){
		printf("Node%d :%d\t%s\t%s\n",count,current->job_id ,current->job_name ,current->job_desc);
		count++;
		current = current->next;
	}
}

int menu(){
	int ch;
	while(1){
		clrscr();
		puts("Menu:\nenter:\n1 for Insertion\n2 for deletion\n3 for search");
		printf("4 for display\n5 to quit\nYour choice:");
		scanf("%d",&ch);
		if ( ch > 0 && ch < 6 )
			return ch;
	}
}

int main(){
	Nodeptr first = NULL;
	int ch;
	while (1){
		ch = menu();
		switch(ch){
			case 1:linsert(&first);break;
			case 2:ldelete(&first);break;
			case 3:lsearch(first);break;
			case 4:ldisplay(first);break;
			case 5:exit();
		}
		printf("\nPress any key to continue");
		fflush(stdin);
		getch();
	}
}
