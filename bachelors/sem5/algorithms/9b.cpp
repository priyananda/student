#include <iostream>
#include <iomanip>
#include <set>
#include <list>

using namespace std;
const int g_inf = 100000;

inline int min(int x,int y){ return x < y ? x : y ; }
class Graph{
	int minTour(int vertex,set<int> & s, list<int> & l);
public:
	int edges[20][20],nVert;
	int minCost;
	list<int> minPath;
	set<int> cities;
	void get();
	void solve();
	void disp();
};

void Graph::get(){
	int z;
	cout << "Enter no of cities  : ";
	cin >> nVert;
	cout << "Enter cost matrix : "<<endl;
	for ( int i = 1 ; i <= nVert ; ++i ){
		for ( int j = 1 ; j <= nVert ; ++j){
			cin >> z;
			edges[i][j] = (z != 0) ? z : g_inf;
			if ( i==j ) edges[i][j] = 0;
		}
	}
	for (  i = 2 ; i <= nVert ; ++i)
		cities.insert(i);
}
int Graph::minTour(int vertex,set<int> & s, list<int> & path ){
	if ( s.empty()){
		path.push_back(1);
		return edges[vertex][1];
	}
	int mintemp=g_inf,m=0;
	list<int> * tempPaths = new list<int>[s.size()];
	for ( set<int>::iterator iter = s.begin(); iter  != s.end() ; ++iter,++m ){
		int cvert = *iter;
		set<int> stemp = s;
		stemp.erase(stemp.find(cvert));
		int oldmin = mintemp;
		int rest = minTour(cvert,stemp,tempPaths[m]);
		mintemp = min(mintemp , rest + edges[vertex][cvert]);
		if ( oldmin != mintemp ){
			path = tempPaths[m];
			path.push_back(cvert);
		}
	}
	return mintemp;
}

void Graph::solve(){
	minCost = minTour(1,cities,minPath);
}

void Graph::disp(){
	cout << "Min Cost :: " << minCost <<endl;
	cout << "Min Path :: " <<endl;
	for ( list<int>::iterator iter = minPath.begin(); iter != minPath.end();++iter)
		cout << setw(10) << *iter;
	cout << endl;
}
int main(){
	Graph grp;
	grp.get();
	cout << "Size :: "<< grp.cities.size() << endl;
	grp.solve();
	grp.disp();
	return 0;
}