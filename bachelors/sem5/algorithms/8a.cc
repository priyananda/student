#include <iostream>
#include <vector>
#include <iomanip>

struct Queen{
	int i,j;
	Queen(int ii=-1,int jj=-1):i(ii),j(jj){}
	bool collides(Queen & q);
};	
bool Queen::collides(Queen & q){
	return  ( q.i == i || q.j == j || abs(q.i-i)==abs(q.j-j) ) ;
}
class Board{
public:
	int n;
	Board(int _n):n(_n){}
	vector<Queen> qstack;
	bool collideAll(Queen&);
	void solveNQueen();
};
bool Board::collideAll(Queen & q){
	for ( int k = 0 ; k < qstack.size() ; ++k )
		if ( q.collides(qstack[k]) ) return true;
	return false;
}
void Board::solveNQueen(){
	Queen cq,oq;
	int prev=0;int flag=0;
	qstack.push_back(Queen(-1,-1));
	while ( qstack.size() != n + 1){
		if ( qstack.size() == 0 ) break;
		oq	= qstack.back();
		cq = Queen(oq.i+1,prev);
		flag = 0;
		for ( ; cq.j < n ; ++cq.j)
			if(!collideAll(cq)){
				flag=1;
				qstack.push_back(cq);prev=0;
				break;
			}
		if ( flag == 0 ){
			prev = oq.j + 1;
			qstack.pop_back();
		}
	}
	for ( int i = 1 ; i < n + 1 ; ++i )
		cout << qstack[i].i << "\t:\t" << qstack[i].j << endl;
	if ( qstack.size() == n+1)
		cout << "Soln exists"<<endl;
	else
		cout << "no Soln"<<endl;
}	
int main(){
	int n;
	cout << "Enter n :: ";
	cin >> n;
	Board brd(n);
	brd.solveNQueen();
	return 0;
}
