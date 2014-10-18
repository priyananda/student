#include <iostream>
#include <list>
#include <iomanip>
class Graph{
public:
	int ** edges,nVert,*visited;
	void get();
	void DFSearch(int);
};
void Graph::get(){
	int i,j;
	cout << "Enter the no of vertices :: " ;
	cin >> nVert;
	edges = new int*[nVert];
	for ( int i = 0 ; i < nVert ; ++i){
		edges[i] = new int[nVert];
		for ( int j = 0 ; j < nVert ; ++j)edges[i][j] =0;
	}
	while(true){
		cout << "Enter i j : " ;
		cin >> i >> j;
		if ( i == 0 ) break;
		edges[i-1][j-1]=1;
	}
	visited = new int[nVert];
	for ( int i = 0 ; i < nVert ; ++i ) visited[i] =0;
}
void Graph::DFSearch(int vertex){
	if(visited[vertex])return;
	visited[vertex] = 1;
	cout << setw(10) << vertex + 1 ;
	for ( int i = 0 ; i < nVert ; ++i )
		if (!visited[i] && edges[vertex][i] ) DFSearch(i);
}	
int main(){
	Graph grp;int start;
	grp.get();
	cout << "Enter the starting vertex :: " ;
	cin >> start;
	grp.DFSearch(start-1);
	return 0;
}
