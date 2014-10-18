#include <iostream>
#include <iomanip>

static int * g_temp;

template <class T>
void merge(T array[],int low,int mid,int high){
	if (low >= high)return;	
	cout << "mg(" << low <<","<< mid << ","<<high<<")"<<endl;
	int i = low,j = mid+1, k=low;	
	while( i <= mid && j <= high )
		g_temp[k++]=(array[i]>array[j])?array[j++]:array[i++];	
	while( i <= mid ) g_temp[k++] = array[i++];
	while( j <= high ) g_temp[k++] = array[j++];
	for(i=low;i<=high;++i) array[i] = g_temp[i];
}	
				
template<class T>
void mergeSort(T array[],int low,int high){
	cout << "ms(" << low <<","<<high<<")"<<endl;
	if(low >= high ) return;
	int mid = ( low + high ) / 2;
	mergeSort<T>(array,low,mid);
	mergeSort<T>(array,mid+1,high);
	merge<T>(array,low,mid,high);
}
int main(){
	int n;
	cout << "Enter size:: ";
	cin >> n;
	int array[n];
	g_temp = new int[n];
	for(int i = 0 ; i < n; ++i )cin >> array[i];
	mergeSort<int>(array,0,n-1);
	for(int i = 0 ; i < n; ++i )cout << setw(10) << array[i];
	return 0;
}
