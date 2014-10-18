#include <iostream>
#include <iomanip>
typedef int ** Array2D;

void make2dArray(Array2D & arr,int n){
	arr = new int*[n];
	for(int i = 0; i < n ; ++i ){
		arr[i] = new int[n];
		for ( int j = 0 ; j < n ; ++ j) arr[i][j] = 0;
	}
}

class Graph{
public:
	int ** edges,nVert;
	void get();
	void findApsp(Array2D &);
};
void Graph::get(){
	cout << "Enter no of vertices :: ";
	cin >> nVert;
	make2dArray(edges,nVert);
	int i,j,w;
	while(true){
		cout << "Enter i j w : ";
		cin >> i >> j >> w;
		if ( i == 0 ) break;
		edges[i-1][j-1] = w;
	}
}
void Graph::findApsp(Array2D & cost){
	make2dArray(cost,nVert);
	for(int i = 0; i < nVert ; ++i )
		for ( int j = 0 ; j < nVert ; ++ j)
			cost[i][j] = edges[i][j];
	for(int i = 0; i < nVert ; ++i )
		for ( int j = 0 ; j < nVert ; ++j)
			for ( int k = 0 ; k < nVert ; ++k ){
				int t1 = cost[i][k] , t2=cost[k][j],t3=cost[i][j];
				if ( t1 && t2 && ( !t3 || t3 > t1 + t2 ))
					cost[i][j] = t1 + t2;
			}	
}
int main(){
	Array2D cost;
	Graph grp;
	grp.get();
	grp.findApsp(cost);
	for(int i = 0; i < grp.nVert ; ++i,cout << endl )
		for ( int j = 0 ; j < grp.nVert ; ++j)
			cout << setw(5) << cost[i][j];
	return 0;
}
