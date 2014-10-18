#include <iostream>
#include <list>
#include <iomanip>

struct Job{
	int p, d,id;
	bool operator < ( Job & x){
		if ( d > x.d ) return false;
		if ( d < x.d ) return true;
		return p > x.p ;
	}
	Job(int pp=0,int dd=0,int i=0):p(pp),d(dd),id(i){}
};
ostream & operator << ( ostream & cout, Job & j){
	return cout << "Job "<<  j.id <<"\t:\t"<< j.p 
		<< "\t:\t" << j.d <<endl;
}	
typedef list<Job>::iterator Iter;
class JobSet{
public:
	list<Job> jobs;
	void get();
	void findSequence();
};	
void JobSet::get(){
	int p,d,i=1;
	cout << "Enter jobs p w ::";
	while(true){
		cout << "Job " << i << " : " ;
		cin >> p >> d;
		if ( p == 0 ) break;
		jobs.push_back(Job(p,d,i++));
	}
	jobs.sort();
}
void JobSet::findSequence(){
	int curr = 0,profit =0;
	for ( Iter iter = jobs.begin() ; iter != jobs.end(); ++iter )
		if ( iter->d > curr ){
			cout << *iter;profit += iter->p;++curr;
		}	
	cout << "Total profit ::" << profit << endl;			
}
int main(){
	JobSet js;
	js.get();
	js.findSequence();
	return 0;
}
