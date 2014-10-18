#include <iostream.h>
#include <iomanip>
#include <list>

class Graph{
public:
	int ** edges,nVert;
	Graph():edges(0),nVert(0){}
	void get();
	int min(int);
};	
struct Edge{
	int i,j,w;
	Edge(int x=0,int y=0,int z=0):i(x),j(y),w(z){}
};
class Tree{
public:		
	list<Edge> edges;
	int * visited;
	int nVert,nEdges;
	void min(int &,int&,Graph&);
	void findSpanTree(Graph &);
	void disp();
};

void Graph::get(){
	char ch;	
	int i,j,w;
	cout << "Enter number of vertices :: ";
	cin >> nVert;
	edges = new int*[nVert];
	for ( i = 0 ; i < nVert ; ++i ){
		edges[i] = new int[nVert];
		for ( j = 0 ; j < nVert ; ++j )edges[i][j] = -1;
	}	
	while(true){
		cout << "Enter i j w (y|n) ::";
		cin >> i >> j >> w >> ch;
		edges[i-1][j-1] = w;
		edges[j-1][i-1] = w;
		if ( ch == 'n' ) return;
	}	
}

int Graph::min(int vertex){
	int min = -1,minval = -1;	
	for ( int i = 0 ; i < nVert ; ++i ){
		if ( edges[vertex][i] != -1 && 
			(edges[vertex][i] < minval || minval == -1 )){
			min = i ; minval = edges[vertex][i];
		}		
	}	
	return min;
}	

void Tree::min(int & mini,int&minj ,Graph & g){
	mini = -1 ;
	minj = -1 ;
	int minval = -1 , temp;
	for ( int i = 0 ; i < nVert ; ++i )
		if (visited[i] && ((temp=g.min(i)) != -1 ))
			if( g.edges[i][temp] < minval || minval == -1)
				{mini = i ; minj = temp ;minval = g.edges[i][temp];}
}		

void Tree::findSpanTree(Graph &grp){
	int i,j;	
	nVert = grp.nVert;nEdges = 0;	
	visited = new int[nVert];
	for (i = 0 ; i < nVert ; ++i )
		visited[i] =0;
	visited[0] = 1;
	while ( nEdges < nVert - 1 ){
		min(i,j,grp);
		if ( i == -1 || j == -1 )break;
		if ( visited[j] ) continue;
		visited[j] = 1;
		edges.push_back(Edge(i,j,grp.edges[i][j]));
		grp.edges[i][j] = grp.edges[j][i] = -1;
		nEdges++;
	}
	if ( nEdges != nVert - 1){
			cout << "Error";
	}
}	

void Tree::disp(){
	int count=0;	
	for( list<Edge> :: iterator iter = edges.begin();
		iter != edges.end(); ++iter ){
		cout << iter->i+1<< "\t"<<iter->j+1<<"\t"<<iter->w<<endl;
		count += iter->w;
	}
	cout<< "Total Cost::" << count <<endl;
}	

int main(){
	Graph grp;	
	grp.get();
	Tree tree;
	tree.findSpanTree(grp);
	tree.disp();
	return 0;
}

