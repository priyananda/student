#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <sys/time.h>

template <class T>
int binSearch(T array[],int low,int high,T key){
	if ( low > high || array == 0) return -1;
	int mid = ( low + high )/2;
	if ( array[mid] == key ) return mid;
	return  ( array[mid] > key )?
		binSearch(array,low,mid-1,key):
		binSearch(array,mid+1,high,key);
}
template <class T>
void fillArray(T * array,int n){
	for (int i = 0;i < n;++i )array[i] = i;
}	
int main(){
	struct timeval start,end;			
	int * array,n,step = 100000;
	for ( n = 100000 ; n <= 1000000 ; n += step ){
			array = new int[n];
			fillArray<int>(array,n);
			gettimeofday(&start,0);
			for ( int i = 0 ; i < 100 ; ++i ){
				binSearch(array,0,n-1,n);
			}	
			gettimeofday(&end,0);
			std::cout << n << "\t\t:\t\t" 
				<< (end.tv_usec - start.tv_usec)/10.00 << std::endl;
	}		
	return 0;
}
