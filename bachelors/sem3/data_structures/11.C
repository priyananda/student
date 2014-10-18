#include <stdio.h>
#include <alloc.h>
#include <conio.h>
struct nod {
	int info;
	struct nod * left;
	struct nod * right;
};

typedef struct nod * Nodeptr;
Nodeptr newNode ( int x){
	Nodeptr p;
	p = (Nodeptr) malloc( sizeof(struct nod));
	p->info = x;
	p->left = p->right = NULL;
	return p;
}
void pqMinDelete( Nodeptr *tree){
	Nodeptr p,q;
	p = q = *tree;
	if (p == NULL ){
		puts("Deletion Failed:Tree is Empty");
		return;
	}
	if ( p->left == NULL && p->right == NULL ){
		printf("Deleted element is %d\n",p->info);
		*tree = NULL;
		return;
	}
	if ( p->left == NULL ){
		printf("Deleted element is %d\n",p->info);
		*tree = (*tree)->right;
		return;
	}
	while( p->left != NULL ){
		q = p;
		p = p->left;
	}
	q->left = p->right;
	printf("Deleted element is %d\n",p->info);
	free(p);
}
void preorder( Nodeptr tree ){
	if ( tree != NULL ){
		printf("  %d ",tree->info);
		preorder( tree->left);
		preorder( tree->right);
	}
}
void inorder( Nodeptr tree ){
	if ( tree != NULL ){
		inorder( tree->left);
		printf("  %d ",tree->info);
		inorder( tree->right);
	}
}
void postorder( Nodeptr tree ){
	if ( tree != NULL ){
		postorder( tree->left);
		postorder( tree->right);
		printf("  %d ",tree->info);
	}
}
void setRight( Nodeptr node , int e){
	Nodeptr p;
	p = newNode( e);
	if ( node == NULL   || (node->left != NULL ))return;
	node->left = p;
}
void setLeft( Nodeptr node , int e){
	Nodeptr p;
	p = newNode( e);
	if ( node == NULL   || (node->right != NULL ))return;
	node->right = p;
} /*
void pqInsert ( Nodeptr *tree,int e ){

	Nodeptr p,q;
	if ( *tree == NULL ){
		p = newNode(e) ;
		*tree = p;
		return;
	}
	p = q = *tree;
	while ( 1 ){
		if ( p->info
		if (e  < p->info )
			q = p->left ;
		else
			q = p->right;
	}
	if ( p->info == e ){
		puts("Duplicate Element");
		return;
	}
	q = newNode(e);
	if ( e < p->info )
		setLeft(p,e);
	else
		setRight(p,e);
}*/

void pqInsert(Nodeptr * t,int data){
	Nodeptr n = newNode(data),p = *t;

	if(*t == NULL){
		*t = n;
		return ;
	}
	while(1){
		if(p->info > data)
				if(p->left == NULL){
					p->left = n;
					return ;
				}
				else p = p->left;
		else if(p->info < data)
					if(p->right == NULL){
						p->right = n;
						return ;
					}
					else p = p->right;
			 else{
				free(n);
				printf("\nDuplicate node");
				return ;
			 }
	}
}
int menu(){
	int choice;
	while(1){
		clrscr();
		puts("Enter \n1 PQ Insert\n2 PQ Min Delete\n3 Preorder\n4 Inorder");
		printf("5 PostOrder\n6 Quit\nYour Choice:");
		scanf("%d",&choice);
		if ( choice >= 1 && choice <= 6)
			return choice;
	}
}
void main(){
	int ch, e;
	Nodeptr root = NULL ;
	while(1){
		ch = menu();
		switch( ch){
			case 1: puts("Enter element to be inserted");
					scanf("%d",&e);
					pqInsert(&root ,e);
					break;
			case 2: pqMinDelete(&root);break;
			case 3: preorder(root);break;
			case 4: inorder(root);break;
			case 5: postorder(root);break;
			case 6: exit(0);
		}
		puts("press any key for menu");
		getch();
	}
}




