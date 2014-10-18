#include <iostream>
#include <cstdio>
#include <list>
#include <vector>
struct  Edge{
	int i,j,w;
	bool visited;
	Edge(int x=0,int y=0,int z=0):i(x),j(y),w(z),visited(false){}
	bool operator <(Edge &x){ return w < x.w;}
};	

class Graph{
public:	
	list<Edge> edges;	
	int nVert,nEdge;
	Graph():nEdge(0),nVert(0){}
	void get();
	void add(Edge x){ edges.push_back(x);++nEdge;}
	Edge min();
};

class Tree:public Graph{
public:		
	Tree(){}	
	bool find(int i);
	void merge(Tree &t);
	void disp();
};	

void Graph::get(){
	int i,j,w;char ch;	
	cout << "Enter the number of vertices ::";
	cin >> 	nVert;
	nEdge=0;
	while(true){
		cout << "Enter	i j w {y|n} :: ";
		cin >> i >> j >> w >> ch;
		add(Edge(i-1,j-1,w));
		if ( ch == 'n' )break;
	}
	edges.sort();
}	
Edge Graph::min(){
	list<Edge>::terator iter;
	for ( iter = edges.begin();
			iter != edges.end() && iter->visited ; ++iter );
	if ( iter == edges.end() )
		return Edge(-1,-1,-1);
	else{	
		iter->visited = true; 
		return *iter;
	}		
}	
bool Tree::find(int i){
	for ( list<Edge>::iterator iter = edges.begin();
			iter != edges.end(); ++iter )
		if ( iter->i == i || iter->j == i )	return true;
	return false;
}	
void Tree::merge(Tree& t){
	edges.sort();t.edges.sort();	
	edges.merge(t.edges);	
	nEdge += t.nEdge;
}		
int search(vector<Tree> & vec ,int v){
	for(int i = 0 ; i < vec.size() ; ++i)
		if(vec[i].find(v))return i;	
	return -1;
}	
void Tree::disp(){
	int count = 0;	
	for(list<Edge>::iterator iter = edges.begin();
		iter != edges.end();
		++iter){
		cout << iter->i+1 << "\t" << iter->j+1 << "\t"
				<< iter->w << endl;count += iter->w;
	}
	cout << count<<endl;
}
int main(){
	Graph grp;
	grp.get();
	vector<Tree> trees;int sptree=-1;
	while(true){
		Edge x = grp.min();
		cout << "min::"<<x.i << "\t" << x.j << "\t" << x.w << endl;
		if ( x.i == -1 )break;
		cout << "Note breaked"<<endl;
		int t1 = search(trees,x.i);
		int t2 = search(trees,x.j);
		cout << "T1:t2\t" << t1 << "\t" << t2 <<endl;
		if ( t1 == -1 && t2 == -1 ){
			Tree tx;
			tx.add(x);
			trees.push_back(tx);
			continue;
		}
		if ( t1 == -1 ){
			trees[t2].add(x);
			if(trees[t2].nEdge == grp.nVert-1){sptree = t2;break;}
			continue;
		}
		if ( t2 == -1 ){
			trees[t1].add(x);
			if(trees[t1].nEdge == grp.nVert-1){sptree = t1;break;}
			continue;
		}
		if ( t1 == t2 ) continue;
		trees[t1].merge(trees[t2]);
		trees[t1].add(x);
		cout << "Size::" << trees[t1].nEdge<<endl;
		trees[t2] = Tree();
		if(trees[t1].nEdge == grp.nVert-1){sptree = t1;break;}
	}	
	if ( sptree == -1 )
			cout << "error"<<endl;
	else 
			trees[sptree].disp();
	return 0;
}
