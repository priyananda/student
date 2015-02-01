// CS 764 : Project CALF
// author: satish@cs.wisc.edu,shenoy@cs.wisc.edu
// date: 10 Nov 2008

#ifndef CALF_META_H
#define CALF_META_H

#include <string>
using std::string;

#include <map>
using std::map;

#include <list>
using std::list;

namespace CALF
{
  namespace Meta
  {
  	//todo: all sql types
  	enum ColumnType
  	{
  		CTInteger = 21,
  		CTFloat = 22,
  		CTCharacter = 23
  	};

  	//should this be here?
  	enum PageLayout
  	{
  		SlottedLayout,
  		ColumnLayout,
  		GroupLayout
  	};

  	class Column
  	{
  	public:
  		//constructor
  		Column(const string & n, ColumnType type, int len):
  			name(n),dataType(type),length(len){}

  		string name;
  		ColumnType dataType;
  		int length;
  	};

  	class Group
  	{
  	public:
  		//constructor
  		Group(int numColumns);

  		//destructor
  		~Group();

  		//adds a column
  		void addColumn(const string &n, ColumnType type, int len);

  		//gets the total size of all columns in the group
  		int recordSize();

  		//array of columns
  		Column* *columns;

  		//number of columns
  		int columnCount;

  		//dont use this
  		void getAllColumns(list<Column *> & l);

  		//get column by name
		Column * getColumn(const string & name);

		//get column index by name
		int getColumnIndex(const string & name);

  	private:
  		int cIndex;
  	};

	class Table
	{
	public:
		//constructor
		Table(const string & tname, int numGroups);

		//destructor
		~Table();

		//adds a new group
		Group * addGroup(int numCols);

		//gets the size in bytes occupied by each record
		int recordSize();

		//get a flat list of all columns
		//todo: replace with iterator
		list<Column *> getAllColumns();

		//get column by name
		Column * getColumn(const string & name);

		//get the index of the column by name
		int getColumnIndex(const string & name);

		//get column by index
		Column * getColumn(int index);

		//get number of columns
		int  getColumnCount();

		//array of groups
		Group* *groups;

		//get list of groups which have atleast one column set to true
		//in either of the markers
		list<Group*> getGroups(bool * columnMarkers1, bool * columnMarkers2 = NULL);

		//table name
		string name;

		inline int getGroupCount(){ return gIndex; }
	private:
		int gIndex;
	};

	class Schema
	{
	public:
		//opens a metadata file
		Schema(const string & metadatafile);

		//cleaning up
		~Schema();

		//gets the metadata for a table with a given name
		Table * getTable(const string & tableName);

		map<string,Table *> tables;
	};

	class Database
	{
	public:
		//loads an exisiting DB from a given file
		Database(const string & filename);

		~Database();

		Schema * 	schema;
		PageLayout  pageLayout;
	};

	enum StmtType
	{
		InsertStmtType, DeleteStmtType, SelectStmtType, UpdateStmtType, ErrorStmtType = 100
	};

	class Stmt
	{
	public:
		virtual StmtType getStmtType() const = 0;
		Table  * table;
		virtual ~Stmt();
	};

	//insert statement
	class InsertStmt : public Stmt
	{
	public:
		InsertStmt(Schema *, const char * line);

		virtual ~InsertStmt();

		virtual StmtType getStmtType() const;

		string * values;
	};

	//delete statement
	class DeleteStmt : public Stmt
	{
	public:
		DeleteStmt(Schema *, const char * line);

		virtual ~DeleteStmt();

		virtual StmtType getStmtType() const;

		bool   * whereClauses;
		string * whereClauseValues;
		float selectivity;
	};

	//select statement
	class SelectStmt : public Stmt
	{
	public:
		SelectStmt(Schema *, const char * line);

		virtual ~SelectStmt();

		virtual StmtType getStmtType() const;

		bool   * selectClauses;
		bool   * whereClauses;
		string * whereClauseValues;

		float  selectivity;
	};

	class UpdateStmt : public Stmt
	{
	public:
		UpdateStmt(Schema *, const char * line);

		virtual ~UpdateStmt();

		virtual StmtType getStmtType() const;

		bool   * updateClauses;
		string * updateClauseValues;
		bool   * whereClauses;
		string * whereClauseValues;

		float  selectivity;
	};

	class QueryParser
	{
	public:
		static Stmt * parse(Schema *, const char * line);
	};

	class QueryFileParser
	{
	public:
		QueryFileParser(Schema *, const string & filename);

		~QueryFileParser();

		list<Stmt *> statements;
	};
  }
}
#endif
