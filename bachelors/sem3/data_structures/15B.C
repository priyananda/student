#include <stdio.h>
#include <conio.h>
int count =0;
void towers(int n, char from,char to,char aux){
	count++;
	if ( n==1 ){
		printf("\nMove disk 1 from peg %c to peg %c",from,to);
		return;
	}
	towers(n-1,from,aux,to);
	printf("\nMove disk %d from peg %c to peg %c",n,from,to);
	towers(n-1,aux,to,from);
//	printf("\nMove disk %d from peg %c to peg %c",n,from,to);
}
void main(){
	int n;
	clrscr();
	puts("Enter the number of disks");
	scanf("%d",&n);
	towers(n,'A','B','C');
	printf("\nThe number of transfers is %d",count);
	getch();
}
