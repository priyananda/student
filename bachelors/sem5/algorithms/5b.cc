#include <iostream>
#include <list>
#include <iomanip> 

class Graph{
public:		
	int ** edges,nVert,start;
	void get();
	void BFSearch();
};
void Graph::get(){
	cout << "Enter the no of vertices :: ";	
	cin >> nVert;
	edges = new int*[nVert];
	for (int i=0; i < nVert ; ++i){
		edges[i] = new int[nVert];
		for(int j = 0; j < nVert ; ++j ) edges[i][j] = 0;
	}
	int i,j;char ch;
	while(true){
		cout << "Enter i j :: " ;
		cin >> i >> j;
		if ( i == 0 ) break;
		edges[i-1][j-1] =1;
	}
	cout << "Enter the starting vertex ::";
	cin >> start;--start;
}
void Graph::BFSearch(){
	int visited[nVert];
	for(int j = 0; j < nVert ; ++j ) visited[j]=0;
	list<int> queue;
	queue.push_back(start);
	visited[start] =1;
	cout << setw(10) << start+1 ;
	while (!queue.empty()){
		int cvert = queue.front();
		queue.pop_front();
		for ( int i = 0 ; i < nVert ; ++i )
			if (!visited[i] && edges[cvert][i]){
				cout << setw(10) << i+1 ;
				visited[i] = 1;
				queue.push_back(i);
			}
	}
	cout << endl;
}
int main(){
	Graph grp;
	grp.get();
	grp.BFSearch();
	return 0;
}
