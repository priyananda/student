#include <stdio.h>
#include <conio.h>
#include <alloc.h>
typedef struct colnode{
	int info;
	int colno;
	struct colnode * next;
} ColNode;
typedef struct rownode{
	ColNode * colptr;
	int rowno;
	struct rownode * rownext;
} RowNode;
typedef RowNode * Matrix;

Matrix insert ( Matrix m,int n,int i,int j){
	Matrix curr , prev , newrow ;
	ColNode * newnode = NULL , *temp;
	newnode = (ColNode *) malloc(sizeof(ColNode));
	newnode->info = n;
	newnode->colno = j;
	newnode->next = NULL;
	if ( m== NULL){
		m = (Matrix ) malloc(sizeof(struct rownode));
		m->rowno = i;
		m->colptr = newnode;
		m->rownext = NULL;
		return m;
	}
	for ( prev = curr = m;curr->rowno <i && curr != NULL;) {prev = curr; curr= curr->rownext;}
	if ( curr->rowno == i){
		for (temp = curr->colptr;temp->next != NULL && temp->next->colno < j; temp = temp->next);
		if ( temp->next == NULL ) temp->next = newnode;
		else if ( (temp->next)->colno > j){
			newnode->next = temp->next;
			temp->next = newnode;
		}
	}
	else if ( curr->rowno > i || curr == NULL ){
			newrow = (Matrix) malloc(sizeof(RowNode));
			newrow->rowno = i;
			newrow->colptr = newnode;
			newrow->rownext = prev->rownext;
			prev->rownext = newrow;
	}
	return m;
}
int getvalue(Matrix m, int row,int col){
	Matrix curr;
	ColNode * colcurr;
	for(curr=m;curr != NULL && curr->rowno != row;curr = curr->rownext);
	if ( curr== NULL ) return 0;
	for ( colcurr = curr->colptr ;colcurr != NULL && colcurr->colno != col ; colcurr = colcurr->next);
	if ( colcurr == NULL ) return 0;
	return (colcurr->info);
}
Matrix addMatrix( Matrix m1 ,Matrix m2,int row,int col){
	Matrix msum = NULL;
	int sum , num1 ,num2,i,j;
	for(i=0;i<row;i++)
		for(j=0;j<col;j++){
			num1 = getvalue(m1,i,j);
			num2 = getvalue(m2,i,j);
			sum = num1 + num2;
			msum = insert (msum ,sum,i,j);
		}
	return msum;
}
void display( Matrix m,int r,int c){
	int i,j,num;
	for(i=0;i<r;i++){
		for(j=0;j<c;j++){
			num = getvalue(m,i,j);
			printf(" %d ",num);
		}
		puts("");
	}

}
void main(){
	Matrix m1 , m2 , msum;
	int m ,n , i,j,num;
	m1 = m2 = msum = NULL;
	clrscr();
	puts("Enter the size of matricesM N");
	scanf("%d %d",&m,&n);
	puts("Enter the elements of Matrix 1:");
	for ( i=0;i<m;i++)
		for(j=0;j<n;j++){
			scanf("%d",&num);
			if ( num != 0 )m1= insert(m1,num,i,j);
		}
	puts("Enter the elements of Matrix 2:");
	for ( i=0;i<m;i++)
		for(j=0;j<n;j++){
			scanf("%d",&num);
			if ( num != 0 ) m2 = insert(m2,num,i,j);
		}
	puts("The First matrix is:");
	display(m1,m,n);
	puts("The Second matrix is:");
	display(m2,m,n);
	msum = addMatrix(m1,m2,m,n);
	puts("The Sum matrix is:");
	display(msum,m,n);
	getch();
}
