// CS 764 : Project CALF
// author: satish@cs.wisc.edu,shenoy@cs.wisc.edu
// date: 23 Nov 2008

#include "Exec.h"
using namespace CALF::Exec;
using namespace CALF::Meta;

#include "Marshall.h"
using namespace CALF::Storage;

#include "PageManager.h"
using namespace CALF::Page;

#include "Handlers.h"

#include <iostream>
#include <cmath>
using namespace std;

void Engine::execute(const string & s)
{
	Stmt * stmt = QueryParser::parse(database->schema,s.c_str());
	execute(stmt);
	delete stmt;
}

void Engine::executeFile(const string & filename)
{
	QueryFileParser parser(database->schema,filename);
	for( list<Stmt*>::iterator iter = parser.statements.begin(); iter != parser.statements.end(); ++iter )
		execute(*iter);
}

void Engine::commit()
{
	for( map<string,File *>::iterator iter = files.begin(); iter != files.end(); ++iter )
		(*iter).second->flush();
}

void Engine::execute(const Stmt * statement)
{
	switch(statement->getStmtType()){
		case InsertStmtType:
			executeInsert(static_cast<const InsertStmt*>(statement) );
			break;
		case DeleteStmtType:
			executeDelete(static_cast<const DeleteStmt*>(statement) );
			break;
		case SelectStmtType:
			executeSelect(static_cast<const SelectStmt*>(statement) );
			break;
		case UpdateStmtType:
			executeUpdate(static_cast<const UpdateStmt*>(statement) );
			break;
		default:
			return;
	}
	if(autoCommit)
		commit();//auto commit after executing
}

File * Engine::getFileForTable(const string & tname)
{
	if(files.find(tname) == files.end()){
		string filename = tname;
		switch(database->pageLayout){
			case SlottedLayout: filename += ".Slotted.data"; break;
			case GroupLayout: 	filename += ".Group.data"; break;
			case ColumnLayout: 	filename += ".Column.data"; break;
		}
		(files[tname] = new File())->open(filename);
	}
	return files[tname];
}

//I hate global variables
static unsigned char buffer[512]; 

void Engine::executeInsert(const InsertStmt * stmt)
{
	PageManager * pageManager = PageManager::getInstance();
	File * file = getFileForTable(stmt->table->name);
	pageManager->initializeFile(*file);

	switch(database->pageLayout){
		case SlottedLayout:
			//only one group
			Marshall::format(buffer, stmt->table, stmt->values);
			pageManager->insertRow(*file,0,stmt->table->recordSize(), buffer);
			break;
		case ColumnLayout:{
			//num groups = num columns	
			int numCols = stmt->table->getColumnCount();
			for(int i = 0 ; i < numCols; ++i ){
				Column * col = stmt->table->getColumn(i);
				Marshall::format(buffer, stmt->table, col, stmt->values[i]);
				pageManager->insertRow(*file,i,col->length,buffer);
			}
			break;
		}
		case GroupLayout:{
			//use group count from meta
			int numGroups = stmt->table->getGroupCount();
			for(int i = 0 ; i < numGroups; ++i ){
				Group * group = stmt->table->groups[i];
				Marshall::format(buffer, stmt->table,group, stmt->values);
				pageManager->insertRow(*file,i,group->recordSize(),buffer);
			}
			break;
		}
	}
}

static bool intersects(Group * group, Table * table, bool * values)
{
	for(int i = 0 ; i < group->columnCount; ++i)
		if( values[ table->getColumnIndex( group->columns[i]->name ) ])
			return true;
	return false;
}

static inline int rpp(int x)
{
	return (int)ceil( double(PAGE_SZ)/ x);
}

static inline double effectiveSel(double sel, int s)
{
	return (1.0 - pow(1.0 - sel,rpp(s)));
} 

void Engine::executeSelect(const SelectStmt * stmt)
{
	PageManager * pageManager = PageManager::getInstance();
	File * file = getFileForTable(stmt->table->name);
	
	pageManager->initializeFile(*file);
 	
	switch(database->pageLayout){
		case SlottedLayout:{
			SlottedRowHandler handler;
			handler.selectStmt = stmt;
			pageManager->selectRows(*file,0,&handler);
			break;
		}
		case ColumnLayout:{
			ColumnRowHandler handler;
			handler.selectStmt = stmt;
			//num groups = num columns	
			int numCols = stmt->table->getColumnCount();
			for(int i = 0 ; i < numCols; ++i ){
				if(stmt->whereClauses[i]){
					handler.isWhereClause = true;
					pageManager->selectRows(*file,i,&handler);
				}else if(stmt->selectClauses[i]){
					handler.isWhereClause = false;
					pageManager->selectRows(*file,i,&handler,
						effectiveSel( stmt->selectivity , stmt->table->getColumn(i)->length )
					);
				}
			}
			break;
		}
		case GroupLayout:{
			GroupRowHandler handler;
			handler.selectStmt = stmt;
			//use group count from meta
			int numGroups = stmt->table->getGroupCount();
			for(int i = 0 ; i < numGroups; ++i ){
				Group * group = stmt->table->groups[i];
				if( intersects(group,stmt->table,stmt->whereClauses) ){
					handler.isWhereClause = true;
					pageManager->selectRows(*file,i,&handler);
				}else if( intersects(group,stmt->table,stmt->selectClauses) ){
					handler.isWhereClause = false;
					pageManager->selectRows(*file,i,&handler,
						effectiveSel( stmt->selectivity , group->recordSize() )
					);
				}
			}
			break;
		}
	}
}

void Engine::executeDelete(const DeleteStmt * stmt)
{
	PageManager * pageManager = PageManager::getInstance();
	File * file = getFileForTable(stmt->table->name);
	
	pageManager->initializeFile(*file);
 	
	switch(database->pageLayout){
		case SlottedLayout:{
			SlottedRowHandler handler;
			handler.deleteStmt = stmt;
			pageManager->deleteRows(*file,0,&handler);
			break;
		}
		case ColumnLayout:{
			ColumnRowHandler handler;
			handler.deleteStmt = stmt;
			//num groups = num columns	
			int numCols = stmt->table->getColumnCount();
			for(int i = 0 ; i < numCols; ++i ){
				if(stmt->whereClauses[i]){
					handler.isWhereClause = true;
					pageManager->deleteRows(*file,i,&handler);
				}else{
					handler.isWhereClause = false;
					pageManager->deleteRows(*file,i,&handler,
						effectiveSel( stmt->selectivity , stmt->table->getColumn(i)->length )
					);
				}
			}
			break;
		}
		case GroupLayout:{
			GroupRowHandler handler;
			handler.deleteStmt = stmt;
			//use group count from meta
			int numGroups = stmt->table->getGroupCount();
			for(int i = 0 ; i < numGroups; ++i ){
				Group * group = stmt->table->groups[i];
				if( intersects(group,stmt->table,stmt->whereClauses) ){
					handler.isWhereClause = true;
					pageManager->deleteRows(*file,i,&handler);
				}else{
					handler.isWhereClause = false;
					pageManager->deleteRows(*file,i,&handler,
						effectiveSel( stmt->selectivity , group->recordSize() )
					);
				}
			}
			break;
		}
	}
}

void Engine::executeUpdate(const UpdateStmt * stmt)
{
	PageManager * pageManager = PageManager::getInstance();
	File * file = getFileForTable(stmt->table->name);
	
	pageManager->initializeFile(*file);
 	
	switch(database->pageLayout){
		case SlottedLayout:{
			SlottedRowHandler handler;
			handler.updateStmt = stmt;
			pageManager->updateRows(*file,0,&handler);
			break;
		}
		case ColumnLayout:{
			ColumnRowHandler handler;
			handler.updateStmt = stmt;
			//num groups = num columns	
			int numCols = stmt->table->getColumnCount();
			for(int i = 0 ; i < numCols; ++i ){
				if(stmt->whereClauses[i]){
					handler.isWhereClause = true;
					pageManager->updateRows(*file,i,&handler);
				}else if(stmt->updateClauses[i]){
					handler.isWhereClause = false;
					pageManager->updateRows(*file,i,&handler,
						effectiveSel( stmt->selectivity , stmt->table->getColumn(i)->length )
					);
				}
			}
			break;
		}
		case GroupLayout:{
			GroupRowHandler handler;
			handler.updateStmt = stmt;
			//use group count from meta
			int numGroups = stmt->table->getGroupCount();
			for(int i = 0 ; i < numGroups; ++i ){
				Group * group = stmt->table->groups[i];
				if( intersects(group,stmt->table,stmt->whereClauses) ){
					handler.isWhereClause = true;
					pageManager->updateRows(*file,i,&handler);
				}else if(intersects(group,stmt->table,stmt->updateClauses)){
					handler.isWhereClause = false;
					pageManager->updateRows(*file,i,&handler,
						effectiveSel( stmt->selectivity , group->recordSize() )
					);
				}
			}
			break;
		}
	}
}