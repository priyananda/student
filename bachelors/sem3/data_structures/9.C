#include <stdio.h>
#include <alloc.h>
#include <conio.h>

typedef struct nod{
	int info;
	struct nod * next;
}Node;
typedef struct nod * Nodeptr;

Nodeptr newNode(){
	return (Nodeptr) malloc(sizeof(struct nod));
}
void insertFront( Nodeptr first,int e){
	Nodeptr p;
	p = newNode();
	p->info = e;
	p->next = (first)->next;
	(first)->next = p;
}
Nodeptr createList(){
	char ch;
	int i = 0;
	char string[80];
	Nodeptr header;
	header = newNode();
	header->next = header;
	fflush(stdin);
	gets (string);
	while ((ch = string[i++]) != '\0')
		insertFront(header , (int) (ch-'0'));
	return header;
}
Nodeptr add( Nodeptr ha,Nodeptr hb){
	Nodeptr hs,curra,currb;
	int carry=0,sum ,number;
	curra = ha->next;
	currb = hb->next;
	hs = newNode();
	hs->next = hs;
	while( curra != ha && currb != hb){
		sum = curra->info + currb->info + carry;
		number = sum % 10;
		carry = sum / 10;
		insertFront(hs,number);
		curra = curra->next;
		currb = currb->next;
	}
	while(curra != ha){
		sum = curra->info + carry;
		number = sum % 10;
		carry = sum / 10;
		insertFront(hs,number);
		curra = curra->next;
	}
	while(currb != hb){
		sum = currb->info + carry;
		number = sum % 10;
		carry = sum / 10;
		insertFront(hs,number);
		currb = currb->next;
	}
	if (carry == 1)
		insertFront(hs,1);
	return hs;
}

void display(Nodeptr header){
	Nodeptr curr = header->next;
	while(curr != header) {
		printf("%d",curr->info);
		curr = curr->next;
	}
}


int main(){
	Nodeptr a,b,sum;
	clrscr();
	puts("Enter the first number to be added");
	a = createList();
	//display(a);
	puts("Enter the second number to be added");
	b = createList();
	//display(b);
	puts("The sum is:");
	sum = add( a,b);
	display(sum);
	getch();
	return 1;
}







