#include <stdio.h>
#include <conio.h>

void partition ( int x[20] , int low ,int high , int * p){
	int a,down, temp,up;
	a = x[low];
	up = high;
	down = low;
	while ( down < up ){
		while ( x[down] <= a && down < high ) down++;
		while (x[up] > a)up--;
		if ( down < up ){
			temp = x[down];
			x[down] = x[up];
			x[up] = temp;
		}
	}
	x[low] = x[up];
	x[up] = a;
	*p = up;
}
 void quickSort ( int array[20] , int low,int high)
{
	int j;
	if ( low >= high ) return;
	partition(array,low,high,&j);
	quickSort(array,low,j-1);
	quickSort(array,j+1,high);
}

void main(){
	int a[20] ,n,i;
	clrscr();
	puts("Enter the size of the array<20");
	scanf("%d",&n);
	puts("Enter the numbers");
	for ( i=0;i<n;i++)
		scanf("%d",&a[i]);
	quickSort(a,0,n-1);
	puts("Sorted array is:");
	for ( i=0;i<n;i++)
		printf(" %d ",a[i]);
	getch();
}
