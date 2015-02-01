// CS 764 : Project CALF
// author: satish@cs.wisc.edu,shenoy@cs.wisc.edu
// date: 1 Dec 2008

#include <string>
using std::string;

#include "Exec.h"
using namespace CALF::Exec;

#include "Meta.h"
using namespace CALF::Meta;

#include <iostream>
using std::cout;
using std::endl;

#include <cstdlib>
#include <cstdio>
#include <time.h>
#include <sys/time.h>

inline double tdiff(struct timeval & start,struct timeval & end)
{
	return (double)(
		end.tv_sec * 1000000 + end.tv_usec - (start.tv_sec * 1000000 + start.tv_usec)
	) / 1000.0;
}

//calfexecquery dbname [queryfile.query]+
int main(int argc, char * argv[])
{
	--argc;argv++;
	
	if(argc < 2){
		cout << "Argument missing. format is\n calfexecquery dbname [queryfile.query]+" << endl;
		exit(0);
	}

	Database db(string(argv[0]) + ".database");
	Engine engine(&db);
	
	struct timeval start,end;
	
	for(int i = 1; i < argc; ++i ){
		QueryFileParser parser(db.schema,argv[i]);
		int j = 1;
		for( list<Stmt*>::iterator iter = parser.statements.begin(); iter != parser.statements.end(); ++iter,++j ){
			gettimeofday(&start,NULL);
			engine.execute(*iter);
			gettimeofday(&end,NULL);
			printf("%s %lf\n",(*iter)->table->name.c_str(),tdiff(start,end));
		}
	}
	return 0;
}
