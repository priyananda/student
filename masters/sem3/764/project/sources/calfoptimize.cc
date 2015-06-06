// CS 764 : Project CALF
// author: satish@cs.wisc.edu,shenoy@cs.wisc.edu
// date: 1 Dec 2008

#include <string>
using std::string;

#include "Exec.h"
using namespace CALF::Exec;

#include "Meta.h"
using namespace CALF::Meta;

#include "partition.h"

#include <iostream>
using std::cout;
using std::endl;

#include <cstdlib>
#include <cmath>

typedef vector<int> MyGroup;

static QueryFileParser * qfp = NULL;

static double costr = 1, costw = 2;
static int N = 10000;

static int rpp(Table * table, MyGroup grp)
{
	int size = 0;
	for(int i = 0; i < int(grp.size()); ++i )
		size += table->getColumn(grp.at(i))->length;
	return (int)floor( (double) BLOCK_SIZE / size);
}

static inline int costprime(Table * table, MyGroup grp)
{
	return (int)ceil( (double)N / rpp(table,grp) );
}

static bool intersects(MyGroup grp, bool * cols)
{
	for(int i = 0 ; i < int(grp.size()); ++i)
		if(cols[ grp.at(i) ])
			return true;
	return false;
}

static inline double rowselfactor(double sel, Table * table, MyGroup & grp)
{
	return (1.0 - pow(1.0 - sel,rpp(table, grp)));
}

static double insertCost(vector<MyGroup> partition, InsertStmt * stmt)
{
	return (costr + costw) * partition.size();
}

static double updateCost(vector<MyGroup> partition, UpdateStmt * stmt)
{
	double ret = 0;
	for(int i = 0 ; i < int(partition.size()); ++i){
		if(intersects(partition.at(i), stmt->whereClauses))
			ret += costr * costprime(stmt->table, partition.at(i));
		if(intersects(partition.at(i), stmt->updateClauses))
			ret += costw * rowselfactor(stmt->selectivity,stmt->table, partition.at(i))
				* costprime(stmt->table,partition.at(i));
	}
	return ret;
}

static double deleteCost(vector<MyGroup> partition, DeleteStmt * stmt)
{
	double ret = 0;
	for(int i = 0 ; i < int(partition.size()); ++i){
		if(intersects(partition.at(i), stmt->whereClauses))
			ret += costr * costprime(stmt->table, partition.at(i));
		ret += costw * rowselfactor(stmt->selectivity,stmt->table, partition.at(i))
			* costprime(stmt->table,partition.at(i));
	}
	return ret;
}

static double selectCost(vector<MyGroup> partition, SelectStmt * stmt)
{
	double ret = 0;
	for(int i = 0 ; i < int(partition.size()); ++i){
		if(intersects(partition.at(i), stmt->whereClauses))
			ret += costprime(stmt->table, partition.at(i));
		else if(intersects(partition.at(i), stmt->selectClauses))
			ret += rowselfactor(stmt->selectivity,stmt->table, partition.at(i))
				* costprime(stmt->table,partition.at(i));
	}
	return ret * costr;
}

static double calculateGroupCost(Table * table, vector<MyGroup> pGroup)
{
	double cost = 0.0;
	for(list<Stmt *>::iterator iter = qfp->statements.begin();
		iter != qfp->statements.end();
		++iter){
		if((*iter)->table != table)//ayyo ayyo, pointer comparison
			continue;
		switch((*iter)->getStmtType()){
			case InsertStmtType: cost += insertCost(pGroup, (InsertStmt *)(*iter)); break;
			case UpdateStmtType: cost += updateCost(pGroup, (UpdateStmt *)(*iter)); break;
			case SelectStmtType: cost += selectCost(pGroup, (SelectStmt *)(*iter)); break;
			case DeleteStmtType: cost += deleteCost(pGroup, (DeleteStmt *)(*iter)); break;
			default: break;
		}
	}
	return cost;
}

static void printPartition(Table * table, vector<MyGroup> pGroup, ostream & cout)
{
	int numGroups = pGroup.size();
	cout << "table " << table->name << " " << numGroups << endl;
	
	for(int i = 0; i < numGroups; ++i){
		MyGroup & gp = pGroup.at(i);
		int numCols = gp.size();

		cout << "group " << numCols << endl;

		for(int j = 0; j < numCols; ++j){
			CALF::Meta::Column * c = table->getColumn(gp.at(j));
			cout << "column " << c->name << " " << c->dataType << " " << c->length << endl;
		}
	}
	cout << endl;
}

static void optimizeATable(Table * table)
{
	int cols = table->getColumnCount();
	vector<int> colIndices;

	double bestCost = 99999999999.0;
	vector<MyGroup> groups;
	MyGroup g0;
	g0.push_back(0);
	groups.push_back(g0);
	int numGrps = 1;
	int bestJ = 0;
	for(int i = 1 ; i < cols; ++i) {
		bestCost = 99999999999.0;
		for (int j = 0; j < numGrps; ++j) {
			groups.at(j).push_back(i);
			double cost = calculateGroupCost(table, groups);
			if (cost < bestCost) {
				bestCost = cost;
				bestJ = j;
			}
			groups.at(j).pop_back();
		}

		MyGroup agrp;
		agrp.push_back(i);
		groups.push_back(agrp);
		double cost = calculateGroupCost(table, groups);
		if (cost < bestCost) {
			numGrps++;
		}
		else {
			groups.pop_back();
			groups.at(bestJ).push_back(i);
		}
	}

	printPartition(table, groups, cout);
}

//calfoptimize schema.schema [queryfile.query]+
int main(int argc, char * argv[])
{
	--argc;argv++;

	if(argc < 2){
		cout << "Argument missing. format is\n calfoptimize <>.schema [queryfile.query]+" << endl;
		exit(0);
	}

	Schema schema(argv[0]);
	qfp = new QueryFileParser(&schema, string(argv[1]));
	for(map<string,Table *>::iterator iter = schema.tables.begin(); iter != schema.tables.end(); ++iter)
		optimizeATable( (*iter).second );

	return 0;
}
