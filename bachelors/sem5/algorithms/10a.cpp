#include <iostream>
#include <iomanip>
#include <list>
using namespace std;
const int g_inf = 10000;

class List{
public:
	list<int> rlist;
	int del(){ int _t = rlist.back() ; rlist.pop_back();return _t;}
	void add(int v){
		for ( list<int>::iterator iter = rlist.begin();iter != rlist.end();++iter)
			if ( *iter == v ) return;
		rlist.push_front(v);
	}
	bool empty(){  return rlist.empty();}
};

class Graph{
public:
	int ** edges,nVert,start,*distance;;
	void get();
	void findSSSP();
};

void Graph::get(){
	int i,j,w;
	cout << "Enter the no of vertices :: ";
	cin >> nVert;
	edges = new int*[nVert+1];
	for (i = 0 ; i <= nVert ; ++i){
		edges[i] = new int[nVert+1];
		for ( int j= 0 ; j <= nVert ; ++j)edges[i][j] = 0;
	}
	while(true){
		cout << "Enter i j w : ";
		cin >> i >> j >> w;
		if ( i == 0 ) break;
		edges[i][j] = w;
	}
	cout << "Enter start vertex :: ";
	cin >> start;
}

void Graph::findSSSP(){
	distance = new int[nVert+1];
	List queue;
	for ( int i = 1 ; i <= nVert ; ++i){
		distance[i] = edges[start][i];
		if ( edges[start][i] ) queue.add(i);
	}
	distance[start] = -1;
	while (!queue.empty()){
		int cvert = queue.del();
		for ( int i = 1 ; i <= nVert ; ++i){
			if (!edges[cvert][i])continue;
			if ( distance[i] == 0 || distance[i] > distance[cvert] + edges[cvert][i] ){
				queue.add(i);
				distance[i] = distance[cvert] + edges[cvert][i] ;
			}
		}
	}
}
int main(){
	Graph grp;
	grp.get();
	grp.findSSSP();
	for ( int i = 1 ; i <= grp.nVert ; ++i)
		cout << setw(5) << grp.distance[i];
	cout << endl;
	return 0;
}