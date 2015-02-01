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

string i2s(int i)
{
	static char bug[10];
	sprintf(bug,"%d",i);
	return bug;
}

//calfexecquery dbname.database [N]
int main(int argc, char * argv[])
{
	Database db(argv[1]);
	Engine engine(&db);
	engine.autoCommit = false;
	
	int N = 1000000;
	if(argc >= 3)
		N = atoi( argv[2] );
	
	for(map<string,Table *>::iterator iter = db.schema->tables.begin();
		iter != db.schema->tables.end();
		++iter)
	{
		Table * table = iter->second;
		string stmt = "insert " + table->name;
		int nc = table->getColumnCount();
		for(int i = 0 ; i < nc; ++i )
			stmt += " 1";
		InsertStmt * istmt = (InsertStmt *)QueryParser::parse(db.schema,stmt.c_str());
		for(int i = 0 ; i < N; ++i)
			engine.execute(istmt);
		delete istmt;
	}
	engine.commit();
	return 0;
}
