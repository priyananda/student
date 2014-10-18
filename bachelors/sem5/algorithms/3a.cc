#include <iostream>
#include <cstdlib>

template <class T>
void minMax(T array[],int low,int high ,T & min,T &max){
	if ( low == high ){min=max=array[low]; return;}
	int mid = (high + low)/2;
	T min1,min2,max1,max2;
	minMax(array,low,mid,min1,max1);
	minMax(array,mid+1,high,min2,max2);
	min = min1 > min2 ? min2 :min1;
	max = max1 < max2 ? max2 :max1;
}		

int main(){
	int n,min,max;
	cout << "Enter size of array :: ";
	cin >> n;
	int array[n];
	cout << "Enter the array :: "<<endl;
	for(int i=0;i<n;++i)cin >> array[i];
	minMax<int>(array,0,n-1,min,max);
	cout << "Min:: "<<min <<endl<<"Max:: "<<max <<endl;
	return 0;
}
