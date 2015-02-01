// CS 764 : Project CALF
// author: satish@cs.wisc.edu,shenoy@cs.wisc.edu
// date: 17 Nov 2008

#include "Meta.h"
#include <strings.h>
#include <fstream>
#include <vector>
#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace CALF::Meta;
using namespace std;

static vector<string> split(const char * s)
{
	vector<string> ret;
	char * word = NULL;
	char * p = const_cast<char *>(s);
	while(*p){
		while (*p && *p <= ' ') p++;
		if (! (*p) || *p == '#')
			break;
		word = p;
		int len = 1;
		while(*p > ' '){ ++p;++len; }
		ret.push_back(string(word,len-1));
	}
	return ret;
}
static pair<string,string> split(const string & val, char delim='=')
{
	int index = val.find(delim);
	return pair<string,string>(string(val,0,index),string(val,index+1));
}

Database::Database(const string & filename)
{
	ifstream input(filename.c_str());
	if(!input.good())
		//todo: error handling
		return;
	char buffer[256];
	bool found = false;

	string schemaFile;
	string layout;

	while(!input.eof()){
		input.getline(buffer,255);
		if(::strlen(buffer) == 0 || buffer[0] == '#')
			continue;
		if(!found){
			schemaFile = buffer;
			found = true;
		}else{
			layout = buffer;
			break;
		}
	}
	input.close();

	this->schema = new Schema(schemaFile);
	if( ::strcasecmp(layout.c_str(), "SLOTTED") == 0){
		this->pageLayout = SlottedLayout;
	}else if( ::strcasecmp(layout.c_str(), "COLUMN") == 0){
		this->pageLayout = ColumnLayout;
	}else if( ::strcasecmp(layout.c_str(), "GROUP") == 0){
		this->pageLayout = GroupLayout;
	}
}

Database::~Database()
{
	delete schema;
}

static inline ColumnType string2ctype(char * ctype)
{
	if(strcasecmp(ctype,"int") == 0 )
		return CTInteger;
	if(strcasecmp(ctype,"float") == 0)
		return CTFloat;
	if(strcasecmp(ctype,"char") == 0)
		return CTCharacter;
	return CTInteger;
}

Schema::Schema(const string & filename)
{
	ifstream input(filename.c_str());
	if(!input.good()){
		//todo: error handling
		cout << "schema file not found" << endl;
		return;
	}
	char buffer[256];

	Table * currentTable = NULL;
	Group * currentGroup = NULL;

	while(input){
		input.getline(buffer,255);
		if(::strlen(buffer) == 0 || buffer[0] == '#')
			continue;

		if(::strncasecmp(buffer,"table",5) == 0){
			char tname[50];
			int numGroups = 0;
			::sscanf(buffer + 5, "%s %d", tname,&numGroups);
			tables[string(tname)] = currentTable = new Table(tname,numGroups);
		}else if(::strncasecmp(buffer,"group",5) == 0){
			int numCols = atoi(buffer+6);
			currentGroup = currentTable->addGroup(numCols);
		}else if(::strncasecmp(buffer,"column",6) == 0){
			char cname[50];
			char ctype[50];
			int  len = 0;
			::sscanf(buffer + 7, "%s %s %d", cname,ctype,&len);
			currentGroup->addColumn(cname,string2ctype(ctype),len);
		}
	}

	input.close();
}

Table* Schema::getTable(const string & tname)
{
	return tables[tname];
}

Schema::~Schema()
{
 	for(map<string,Table *>::iterator iter = tables.begin(); iter != tables.end(); ++iter)
		delete iter->second;
}

Table::Table(const string & tname, int ng):gIndex(0)
{
	this->name = tname;
	this->groups = new Group*[ng];
}

Group * Table::addGroup(int nc)
{
	Group * grp = new Group(nc);
	this->groups[gIndex++] = grp;
	return grp;
}

int Table::recordSize()
{
	int sz = 0;
	for(int i = 0 ; i < gIndex; ++i)
		sz += this->groups[i]->recordSize();
	return sz;
}

list<Column *> Table::getAllColumns()
{
	list<Column *> lst;
	for(int i = 0 ; i < gIndex; ++i)
		this->groups[i]->getAllColumns(lst);
	return lst;
}

//get column by name
Column * Table::getColumn(const string & name)
{
	Column * ret = NULL;
	for(int i = 0 ; i < gIndex; ++i)
		if( (ret = this->groups[i]->getColumn(name)) != NULL)
			return ret;
	return NULL;
}

//get column index by name
int Table::getColumnIndex(const string & name)
{
	int ret = 0, iret = 0;
	for(int i = 0 ; i < gIndex; ++i){
		if( (iret = this->groups[i]->getColumnIndex(name)) != -1)
			return ret + iret;
		ret += this->groups[i]->columnCount;
	}
	return ret;
}

//get column by index
Column * Table::getColumn(int index)
{
	for(int i = 0 ; i < gIndex; ++i){
		if(index < this->groups[i]->columnCount )
			return this->groups[i]->columns[index];
		index -= this->groups[i]->columnCount;
	}
	return NULL;
}

//get number of columns
int  Table::getColumnCount()
{
	int sz = 0;
	for(int i = 0 ; i < gIndex; ++i)
		sz += this->groups[i]->columnCount;
	return sz;
}

list<Group*> Table::getGroups(bool * columnMarkers1,bool * columnMarkers2)
{
	list<Group *> grp;
	int ci = 0;
	for(int i = 0 ; i < gIndex; ++i){
		for(int j = 0 ; j < this->groups[i]->columnCount; ++j)
			if(columnMarkers1[ci + j] || ( columnMarkers2 != NULL && columnMarkers2[ci + j] ) ){
				grp.push_back(this->groups[i]);
				break;
			}
		ci += this->groups[i]->columnCount;
	}
	return grp;
}

Table::~Table()
{
	for(int i = 0 ; i < gIndex; ++i)
		delete groups[i];
	delete [] groups;
}


Group::Group(int nc):cIndex(0)
{
	columns = new Column* [columnCount = nc];
}

Group::~Group()
{
	for(int i = 0; i < cIndex; ++i)
		delete columns[i];
	delete [] columns;
}

void Group::addColumn(const string &n, ColumnType type, int len)
{
	Column * col = new Column(n,type,len);
	this->columns[cIndex++] = col;
}

int Group::recordSize()
{
	int sz = 0;
	for(int i = 0 ; i < cIndex; ++i)
		sz += this->columns[i]->length;
	return sz;
}

Column * Group::getColumn(const string & name)
{
	for(int i = 0 ; i < cIndex; ++i)
		if( this->columns[i]->name == name)
			return this->columns[i];
	return NULL;
}

int Group::getColumnIndex(const string & name)
{
	for(int i = 0 ; i < cIndex; ++i)
		if( this->columns[i]->name == name)
			return i;
	return -1;
}

void Group::getAllColumns(list<Column *> & l)
{
	for(int i = 0 ; i < cIndex; ++i)
		l.push_back(columns[i]);
}

QueryFileParser::QueryFileParser(Schema * schema, const string & filename)
{
	ifstream input(filename.c_str());
	if(!input.good())
		//todo: error handling
		return;
	char buffer[256];
	while(!input.eof()){
		input.getline(buffer,255);
		if(::strlen(buffer) == 0 || buffer[0] == '#')
			continue;
		Stmt * ptr = QueryParser::parse(schema,buffer);
		if(ptr != NULL)
			statements.push_back(ptr);
	}
}

QueryFileParser::~QueryFileParser()
{
	for(list<Stmt *>::iterator iter = statements.begin(); iter != statements.end(); ++iter)
		delete *iter;
}

Stmt * QueryParser::parse(Schema * schema,const char * line)
{
	if(::strncasecmp(line,"insert",6) == 0)
		return new InsertStmt(schema,line);
	if(::strncasecmp(line,"delete",6) == 0)
		return new DeleteStmt(schema,line);
	if(::strncasecmp(line,"select",6) == 0)
		return new SelectStmt(schema,line);
	if(::strncasecmp(line,"update",6) == 0)
		return new UpdateStmt(schema,line);
	return NULL;
}

Stmt::~Stmt()
{
}

InsertStmt::InsertStmt(Schema * schema,const char * line)
{
	vector<string> parts = split(line);
	table = schema->getTable(parts[1]);
	int nc = table->getColumnCount();
	if(nc != int(parts.size()) - 2)
		;//error!
	values = new string[nc];
	for(int i = 0 ; i < nc; ++i )
		values[i] = parts[i+2];
}

StmtType InsertStmt::getStmtType() const { return InsertStmtType; }

InsertStmt::~InsertStmt()
{
	delete [] values;
}

DeleteStmt::DeleteStmt(Schema * schema,const char * line)
{
	vector<string> parts = split(line);
	table = schema->getTable(parts[1]);
	int nc = table->getColumnCount();

	this->whereClauses = new bool[nc];
	for(int i = 0 ; i < nc; ++i ) this->whereClauses[i] = false;
	this->whereClauseValues = new string[nc];
	this->selectivity = atof(parts[2].c_str());

	for(int i = 3 ; i < int(parts.size()); ++i){
		pair<string,string> nvp = split(parts[i]);
		int cindex = table->getColumnIndex(nvp.first);
		if(cindex > -1){
			this->whereClauseValues[cindex] = nvp.second;
			this->whereClauses[cindex] =  true;
		}
	}
}

StmtType DeleteStmt::getStmtType() const { return DeleteStmtType; }

DeleteStmt::~DeleteStmt()
{
	delete [] whereClauses;
	delete [] whereClauseValues;
}

SelectStmt::SelectStmt(Schema * schema,const char * line)
{
	vector<string> parts = split(line);
	table = schema->getTable(parts[1]);

	int nc = table->getColumnCount();

	this->selectClauses = new bool[nc];
	this->whereClauses = new bool[nc];
	for(int i = 0 ; i < nc; ++i ) this->selectClauses[i] = this->whereClauses[i] = false;
	this->whereClauseValues = new string[nc];
	this->selectivity = atof(parts[2].c_str());

	for(int i = 3 ; i < int(parts.size()); ++i){
		if(parts[i].find('=') != string::npos){
			pair<string,string> nvp = split(parts[i]);
			int cindex = table->getColumnIndex(nvp.first);
			if(cindex > -1){
				this->whereClauseValues[cindex] = nvp.second;
				this->whereClauses[cindex] =  true;
			}
		}else{
			int cindex = table->getColumnIndex(parts[i]);
			if(cindex > -1)
				this->selectClauses[cindex] = true;
		}
	}
}

StmtType SelectStmt::getStmtType() const { return SelectStmtType; }

SelectStmt::~SelectStmt()
{
	delete [] selectClauses;
	delete [] whereClauses;
	delete [] whereClauseValues;
}

UpdateStmt::UpdateStmt(Schema * schema,const char * line)
{
	vector<string> parts = split(line);
	table = schema->getTable(parts[1]);

	int nc = table->getColumnCount();

	this->updateClauses = new bool[nc];
	this->whereClauses = new bool[nc];
	for(int i = 0 ; i < nc; ++i )
		this->updateClauses[i] = this->whereClauses[i] = false;
	this->updateClauseValues = new string[nc];
	this->whereClauseValues = new string[nc];
	this->selectivity = atof(parts[2].c_str());

	for(int i = 3 ; i < int(parts.size()); ++i){
		if(parts[i].find('=') != string::npos){
			pair<string,string> nvp = split(parts[i]);
			int cindex = table->getColumnIndex(nvp.first);
			if(cindex > -1){
				this->whereClauseValues[cindex] = nvp.second;
				this->whereClauses[cindex] =  true;
			}
		}else{
			pair<string,string> nvp = split(parts[i],':');
			int cindex = table->getColumnIndex(nvp.first);
			if(cindex > -1){
				this->updateClauses[cindex] = true;
				this->updateClauseValues[cindex] = nvp.second;
			}
		}
	}
}

UpdateStmt::~UpdateStmt()
{
	delete [] updateClauses;
	delete [] updateClauseValues;
	delete [] whereClauses;
	delete [] whereClauseValues;

}

StmtType UpdateStmt::getStmtType() const { return UpdateStmtType;}
