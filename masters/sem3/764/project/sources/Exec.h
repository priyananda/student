// CS 764 : Project CALF
// author: satish@cs.wisc.edu,shenoy@cs.wisc.edu
// date: 23 Nov 2008

#ifndef CALF_EXEC_H
#define CALF_EXEC_H

#include "Meta.h"
using CALF::Meta::Database;
using CALF::Meta::Stmt;
using CALF::Meta::InsertStmt;
using CALF::Meta::DeleteStmt;
using CALF::Meta::SelectStmt;
using CALF::Meta::UpdateStmt;

#include "Storage.h"
using CALF::Storage::File;

#include "PageManager.h"
using CALF::Page::PageManager;

namespace CALF
{
  namespace Exec
  {
	class Engine
	{
	public:
		Engine(Database * db):autoCommit(true),database(db){}
		
		//executes a single statement
		void execute(const string & statement);

		//executes all the statements in the file
		void executeFile(const string & filename);

		//commit changes to storage
		void commit();
	
		//internal executor
		void execute(const Stmt *);

		bool autoCommit;

	private:
		//loads it if it isn't already there
		File * getFileForTable(const string & tname);

		void executeInsert(const InsertStmt *);

		void executeSelect(const SelectStmt *);

		void executeDelete(const DeleteStmt *);

		void executeUpdate(const UpdateStmt *);

		//tablename to file map
		map<string, File *> files;

		//the underlying database
		Database * database;
	}; 
  }
}

#endif
