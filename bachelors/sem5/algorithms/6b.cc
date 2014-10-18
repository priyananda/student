#include <iostream>
#include <iomanip>
template <class T>
int partition(T array[],int low,int high){
	if ( low >= high ) return low;
	int up = high , down = low ;
	T pivot = array[low];
	while ( true ){
		while ( array[down] <= pivot && down < high )down ++;
		while ( array[up] > pivot ) up --;
		if ( down >= up ) break;
		T temp = array[down];
		array[down] = array[up];
		array[up] = temp;
	}
	array[low] = array[up];
	array[up] = pivot;
	return up;
}
template <class T>
void quickSort(T array[],int low,int high){
	if ( low >= high ) return ;
	int j = partition<T>(array,low,high);
	quickSort<T>(array,low,j-1);
	quickSort<T>(array,j+1,high);
}
int main(){
	int n;
	cout << "Enter the size of array :: ";
	cin >> n;
	cout << n <<endl;
	int array[n];
	for ( int i = 0 ; i < n ; ++i ) cin >> array[i];
	quickSort<int>(array,0,n-1);
	for ( int i = 0 ; i < n ; ++i ) cout << setw(10) << array[i];
	cout << endl;
	return 0;
}
