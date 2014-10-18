#include <iostream>
#include <iomanip>
#include <list>

struct Item{
	int p,w;
	Item(int _p=0,int _w=0):p(_p),w(_w){}
	bool operator < ( Item &i){
		return float(p)/w > float(i.p)/i.w;
	}
};
class KnapSack{
public:		
	list<Item> items;
	int capacity;
	void get();
	void fill();
};
void KnapSack::get(){
	int i,j;char ch;
	cout << "Enter capacity :: ";cin >> capacity;
	while(true){
		cout << "Enter the p w {y|n} :: ";
		cin >> i >> j >> ch;
		items.push_back(Item(i,j));
		if(ch == 'n')break;
	}
	items.sort();
}	
void KnapSack::fill(){
	float profit=0;
	list<Item> :: iterator iter = items.begin();
	for(;iter != items.end() ; ++iter ){
		if ( capacity < iter->w ) break;
		capacity -= iter->w;
		profit += iter->p;
		cout << "\t\t" << iter->p << "\t:\t"<< iter->w <<endl;
	}	
	if(iter != items.end()){
		float temp =  iter->p * float(capacity)/float(iter->w);	
		cout << "\t\t" << temp
				<< "\t:\t" << iter->w<<endl;
		profit += temp;
	}
	cout << "Total profit :: "<< profit<<endl;
}
int main(){
	KnapSack ks;
	ks.get();
	ks.fill();
	return 0;
}
