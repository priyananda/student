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
typedef auto_ptr< vector< MyGroup > > GroupsPtr;

static QueryFileParser * qfp = NULL;

static double costr = 1, costw = 2;
static int N = 100000;
static int k = 4; //bytes overhead per record.

static int rpp(Table * table,MyGroup & grp)
{
	int size = k;
	for(int i = 0; i < int(grp.size()); ++i )
		size += table->getColumn(grp[i])->length;
	return (int)floor( (double) BLOCK_SIZE / size);
}

static inline int costprime(Table * table, MyGroup & grp)
{
	return (int)ceil( (double)N / rpp(table,grp) );
}

static bool intersects(MyGroup & grp, bool * cols)
{
	for(int i = 0 ; i < int(grp.size()); ++i)
		if(cols[ grp[i] ])
			return true;
	return false;
}

static inline double rowselfactor(double sel, Table * table, MyGroup & grp)
{
	return (1.0 - pow(1.0 - sel,rpp(table,grp)));
}

static double insertCost(GroupsPtr & partition, InsertStmt * stmt)
{
	return (costr + costw) * partition->size();
}
static double updateCost(GroupsPtr & partition, UpdateStmt * stmt)
{
	double ret = 0;
	for(int i = 0 ; i < int(partition->size()); ++i){
		bool inWhere  = intersects((*partition)[i], stmt->whereClauses);
		bool inUpdate = intersects((*partition)[i], stmt->updateClauses);
		if(inWhere || inUpdate){
			double cdash = costprime(stmt->table,(*partition)[i]);
			if(inWhere && !inUpdate)
				ret += costr * cdash;
			else if(!inWhere && inUpdate)
				ret += rowselfactor(stmt->selectivity,stmt->table, (*partition)[i]) *
					(costr + costw) * cdash;
			else if(inWhere && inUpdate)
				ret += (costr + rowselfactor(stmt->selectivity,stmt->table, (*partition)[i]) * costw)
					* cdash;
		}
	}
	return ret;
}
static double deleteCost(GroupsPtr & partition, DeleteStmt * stmt)
{
	double ret = 0;
	for(int i = 0 ; i < int(partition->size()); ++i){
		if(intersects((*partition)[i], stmt->whereClauses))
			ret += costr * costprime(stmt->table,(*partition)[i]);
		ret += costw * rowselfactor(stmt->selectivity,stmt->table, (*partition)[i])
			* costprime(stmt->table,(*partition)[i]);
	}
	return ret;
}
static double selectCost(GroupsPtr & partition, SelectStmt * stmt)
{
	double ret = 0;
	for(int i = 0 ; i < int(partition->size()); ++i){
		if(intersects((*partition)[i], stmt->whereClauses))
			ret += costprime(stmt->table,(*partition)[i]);
		else if(intersects((*partition)[i], stmt->selectClauses))
			ret += rowselfactor(stmt->selectivity,stmt->table, (*partition)[i])
				* costprime(stmt->table,(*partition)[i]);
	}
	return ret * costr;
}

static double calculateGroupCost(Table * table, GroupsPtr & pGroup)
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

static void printPartition(Table * table, GroupsPtr & pGroup)
{
	int numGroups = int(pGroup->size());
	for(int i = 0; i < numGroups; ++i){
		cout << "{ ";
		MyGroup & gp = (*pGroup)[i];
		int numCols = int(gp.size());
		for(int j = 0; j < numCols; ++j)
			cout << table->getColumn(gp[j])->name << " ";
		cout << " }";
	}
	cout << endl;
}

static double __nm(Table * table)
{
	for(list<Stmt *>::iterator iter = qfp->statements.begin();
		iter != qfp->statements.end();
		++iter)
		if((*iter)->table == table)
			return ((UpdateStmt*)(*iter))->selectivity;
	return 0.0;
}


static void optimizeTable(Table * table)
{
	int cols = table->getColumnCount();
	vector<int> colIndices;
	for(int i = 0 ; i < cols; ++i)
		colIndices.push_back(i);
	double bestCost = -1, naryCost = -1, colsCost = -1;
	partition::iterator partIter(cols);
	while(true){
		GroupsPtr grp = partIter[colIndices];
		double cost = calculateGroupCost(table,grp);
		if(bestCost < 0.0 || cost < bestCost)
			bestCost = cost;
		if(naryCost < 0)
			naryCost = cost;
		//printPartition(table,grp);
		if(int(partIter.subsets()) == cols){
			colsCost = cost;
			break;
		}
		++partIter;
	}
	cout << __nm(table) << " " << naryCost << " " << colsCost << " " << bestCost << endl;
}

//calfoptimize schema.schema [queryfile.query]+
int main(int argc, char * argv[])
{
	--argc;argv++;

	if(argc < 2){
		cout << "Argument missing. format is\n calfoptimize <>.schema queryfile.query [N] [cost_ratio]" << endl;
		exit(0);
	}
	if(argc > 2)
		N = atoi(argv[2]);
	if(argc > 3)
		costw = atof(argv[3]);
	
	Schema schema(argv[0]);
	qfp = new QueryFileParser(&schema, string(argv[1]));

	//for(double rat = 0; rat <= 5.0; rat += 0.1){
		//costw = costr * rat;
		//cout << rat << " ";
		for(map<string,Table *>::iterator iter = schema.tables.begin(); iter != schema.tables.end(); ++iter)
			optimizeTable( (*iter).second );
	//}
	return 0;
}