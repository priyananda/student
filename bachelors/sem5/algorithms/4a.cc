#include <iostream>

typedef int** Array2D;
void make2DArray(Array2D &arr,int n){
	arr = new int*[n];	
	for(int i=0;i < n;++i ){
		arr[i] = new int[n];	
		for(int j=0;j < n ; ++j)arr[i][j]=0;
	}	
}
class Graph{
public:
	Array2D edges,trans;
	int nVert;
	void get();
	void findTrans();
	void checkConnect();
};
void Graph::get(){
	int i,j;char ch;	
	cout << "Enter the number of vertices :: ";
	cin >> nVert;
	make2DArray(edges,nVert);
	while(true){
		cout << "Enter i j {y|n} :: ";
		cin >> i >> j >> ch;
		edges[i-1][j-1] = 1;
		if( ch == 'n' )return;
	}
}	
void Graph::findTrans(){
	make2DArray(trans,nVert);
	for(int i=0; i < nVert ; ++i )
		for(int j=0; j < nVert ; ++j )
			trans[i][j] = edges[i][j];
	for(int k=0; k <  nVert ; ++k )
		for ( int i = 0 ; i < nVert ; ++i )
			for (int j = 0 ; j < nVert ; ++j )
				trans[i][j] = trans[i][j] ||
						trans[i][k] && trans[k][j];
}
void Graph::checkConnect(){
	bool retval = true;	
	for(int i=0; i < nVert && retval; ++i )
		for(int j=0; j < nVert ; ++j )
			if ( i != j &&!trans[i][j] ){retval=false;break;}
	if(retval)
		cout <<endl<< "Graph is connected"<<endl;
	else
		cout <<endl<< "Graph is not connected"<<endl;
	cout << " Trans :: "<<endl;
	for(int i=0; i < nVert ; ++i ,cout << endl)
		for(int j=0; j < nVert ; ++j )
			cout << trans[i][j] << " ";
}
int main(){
	Graph grp;
	grp.get();
	grp.findTrans();
	grp.checkConnect();
	return 0;
}
