#include <iostream>
#include <iomanip>
#include <sys/time.h>
template <class T>
int linSearch(T array[],int low,int high,T key){
		if(high < low)return -1;
		return ( array[high] == key )?
				high:linSearch(array,low,high-1,key);
}	
template <class T>
void fillArray(T * array,int n){
	array = new T[n];
	for(int i = 0 ; i < n ; ++i) array[i] = i;
}	
int main(){
	int n,step=5000,*array;
	struct timeval start,end;
	cout << "+" <<setfill('-')<<setw(48)<<"+"<<endl;
	cout << "|\tSize\t\t|\tTime(microsec)\t|"<<endl;
	cout << "+" <<setfill('-')<<setw(48)<<"+"<<endl;
	for(n=10000;n < 100000;n+=step){
		fillArray<int>(array,n);
		gettimeofday(&start,0);
		linSearch(array,0,n-1,n);
		gettimeofday(&end,0);
		cout << "|\t"<< n 
				<< "\t\t|\t\t" << end.tv_usec - start.tv_usec
				<< "\t|" <<endl;
		delete [] array;
	}	
	cout << "+" <<setfill('-')<<setw(48)<<"+"<<endl;
	return 0;
}
