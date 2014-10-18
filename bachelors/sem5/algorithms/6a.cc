#include <iostream>

int max(int a,int b){
	return a > b ? a : b;
}
class KnapSack{
public:
	int * p,*w,nItems,capacity,*x,profit;
	void get();
	int f(int,int);
	void fill();
	void disp();
};
void KnapSack::get(){
	cout << "Enter the number of items :: ";
	cin >> nItems;
	cout << "Enter the capacity :: ";
	cin >> capacity;
	cout << "Enter the items p  w:: "<<endl;
	p = new int[nItems];w=new int[nItems];x = new int[nItems];
	for ( int i = 0 ; i < nItems ; ++i ){
		cout << "Item " << i + 1 << "  : ";
		cin >> p[i]>>w[i];x[i] =0;
	}
}	
int KnapSack::f(int i,int y){
	if ( i == nItems - 1)
		return y < w[i] ? 0 : p[i];
	if ( y < w[i] ) return f(i+1,y);
	return max(f(i+1,y) , f(i+1,y-w[i]) + p[i]);
}
void KnapSack::fill(){
	profit = 0;
	for ( int i = 0 ; i < nItems - 1 ; ++i )
		if ( f(i,capacity) == f(i+1,capacity) )
			x[i] = 0;
		else
			{x[i] = 1,capacity -= w[i];profit+=p[i];}
	x[nItems-1] = f(nItems-1,capacity)?1:0;
}
void KnapSack::disp(){
	for ( int i = 0 ; i < nItems ; ++ i )
		cout << "Item " << i + 1 << " :\t"
			<< p[i] << "\t:\t" << w[i] << "\t:\t" 
			<<  (x[i] ? "yes" : "no") <<endl;
	cout << "Total profit :: " << profit + x[nItems-1] * p[nItems-1];
}	
int main(){
	KnapSack ks;
	ks.get();
	ks.fill();
	ks.disp();
	return 0;
}
