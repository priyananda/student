#include <iostream>
#include <iomanip>

template <class T>
int select(T array[],int low,int high,int pos){
	if ( low >= high ) return low;
	int down=low,up=high;
	T pivot = array[low];
	while(true){
		while(array[down] <= pivot && down < high ) down ++;
		while(array[up] > pivot ) up --;
		if ( down >= up ) break;
		T temp = array[down];
		array[down] = array[up];
		array[up] = temp;
	}
	if ( up-low == pos ) return pos;
	array[low] = array[up];
	array[up] = pivot;
	if ( pos < up - low )
		return select(array,low,up-1,pos);
	else
		return select(array,up+1,high,pos-up+low-1);
}
template <class T>
void sort(T array[],int n){ 
	for ( int i = 0 ; i < n ; ++i){
		int temp = select<T>(array,0,n-1,i);
		T _x = array[temp];
		array[temp] = array[i];
		array[i] = _x;
	}
}
int main(){
	int array[] = {1024,522,238,277,182,786};	
	sort<int>(array,6);
	for ( int i = 0 ; i < 6 ; ++i)cout << setw(10) << array[i];
	cout << endl;
	return 0;
}
