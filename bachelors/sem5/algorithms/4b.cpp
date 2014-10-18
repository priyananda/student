#include <iostream>
#include <iomanip>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;
// branch and bound TSP
const int g_inf = 100000;

void copy( int * dst , int * src , int n){
	for ( int i = 1 ; i <= n ; ++i )dst[i] = src[i];
}

class Node{
public:
	int cost ,path[20],n;
	Node ( int c,int ns,int * p):cost(c),n(ns){
		copy (path,p,n);
	}
	bool operator < ( Node & n){
		return cost > n.cost;
	}
	int getlast(){ return path[n];}
	bool visited(int i);
	void disp(){
		cout << "cost: "<< cost << " path: ";
		for ( int i = 1 ; i <= n ; ++i )cout <<setw(3)<< path[i];
		cout << endl; 
	}
	Node():cost(0),n(1){}
};

class Heap{
public:
	vector<Node> nodes;
	void ins(Node &);
	Node del();
	bool empty(){ return nodes.empty();}
};

class Graph{
public:
	int ** edges,nVert,start,minpath[20],mincost;
	void get();
	void findMinPath();
	void disp();
};

bool Node::visited(int v){
	for ( int i = 1 ; i <= n ; ++i ) if ( path[i] == v ) return true;
	return false;
}
void Heap::ins(Node & x){
	nodes.push_back(x);
	pop_heap(nodes.begin(),nodes.end());
}

Node Heap::del(){
	pop_heap(nodes.begin(),nodes.end());
	Node re = nodes.back();
	nodes.pop_back();
	return re;
}

void Graph::get(){
	cout << "Enter no of vertices :: ";
	cin >> nVert;
	int i,j,w;
	edges = new int*[nVert+1];
	for ( i = 0 ; i <= nVert ; ++i ){
		edges[i] = new int[nVert+1];
		for ( j = 0 ; j <= nVert ; ++j )edges[i][j] = g_inf;
	}
	while(true){
		cout << "Enter i j w : " ;
		cin >> i >> j >> w;
		if ( i == 0 ) break;
		edges[i][j] = w;
	}
}

void Graph::findMinPath(){
	int path[20];path[1] = 1;
	Heap hp;
	Node x= Node(0,1,path);
	hp.ins(x);
	mincost = g_inf;
	while(!hp.empty()){
		x = hp.del();
		if ( x.cost > mincost ) break;
		if ( x.n == nVert && 
			x.cost + edges[x.getlast()][1] < mincost ){
			mincost = x.cost + edges[x.getlast()][1] ;
			copy ( minpath,x.path,x.n);
			continue;
		}
		for ( int i = 1 ; i <= nVert ; ++ i ){
			if ( !x.visited(i) && edges[x.getlast()][i] != g_inf ){
				Node y = x;
				y.cost += edges[y.getlast()][i];
				y.path[++y.n] = i;
				hp.ins(y);
			}
		}
	}
}

void Graph::disp(){
	if ( mincost == g_inf )
		cout << "No Solution" << endl;
	else{
		cout << "Min Cost :: " <<mincost << endl;
		cout << "The path is :: "<<endl;
		for ( int i = 1 ; i <= nVert ; ++i )
			cout << setw(10) << minpath[i];
		cout << endl;
	}
}
int main(){

	Graph grp;
	grp.get();
	grp.findMinPath();
	grp.disp();
	return 0;

}
