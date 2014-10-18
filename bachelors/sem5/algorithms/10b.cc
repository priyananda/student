#include <iostream>
#include <iomanip>
class Graph{
public:
	int ** edges,nVert;
	void get();
	int getIndegree(int);
	void findSequence();
};
void Graph::get(){
	cout << "Enter the number of jobs :: ";
	cin >> nVert;
	edges = new int*[nVert];
	for ( int i = 0 ; i < nVert ; ++i ){
		edges[i] = new int[nVert];
		for ( int j = 0 ; j < nVert ; ++j )edges[i][j] = 0;
	}
	while(true){
		int i , j;
		cout << "Enter i j : ";cin >> i >> j;
		if ( i == 0 ) break;
		edges[i-1][j-1] = 1;
	}
}
int Graph::getIndegree(int vertex){
	int count=0;
	for ( int i=0;i < nVert ; ++i )
		if ( edges[i][vertex] ) count++;
	return count;
}
void Graph::findSequence(){
	int seq[nVert],indeg[nVert],visited[nVert],j=0;
	for ( int i = 0 ; i < nVert ; ++i )
		{ indeg[i] = getIndegree(i);visited[i] = 0;}
	int count=0;bool flag;
	while(true){
		flag = false;
		for ( int i = 0  ; i < nVert ; ++i )
			if ( indeg[i] == 0 && ! visited[i] ){
				visited[i] = 1;count++;
				cout << setw(10)<<i+1;flag=true;
				for ( int j = 0 ; j < nVert ; ++j )
					if(edges[i][j] && indeg[j] > 0 ) indeg[j]--;
			}
		if ( flag == false ) break;
	}
	if( count == nVert )
		cout << "Solution exists"<<endl;
	else
		cout << "Solution doesnot exists"<<endl;
}

int main(){
	Graph grp;
	grp.get();
	grp.findSequence();
	return 0;
}
