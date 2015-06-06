#include "Handlers.h"
using namespace CALF::Exec;

#include "Marshall.h"

#include <cstdio>

void SlottedRowHandler::onSelect(int groupid, unsigned char * data)
{
	int nc = selectStmt->table->getColumnCount();
	string * vals = new string [nc];
	Marshall::extract(data,selectStmt->table,vals);
	for(int i = 0 ; i < nc; ++i)
		;//printf("%d:%s | ", i, vals[i].c_str());
	//puts("");
	delete [] vals;
}
bool SlottedRowHandler::onDelete(int groupid, unsigned char * data)
{
	return false;
}
bool SlottedRowHandler::onUpdate(int groupid, unsigned char * data)
{
	return false;
}
int  SlottedRowHandler::getSize (int groupid)
{
	return selectStmt->table->recordSize();
}

void ColumnRowHandler::onSelect(int groupid, unsigned char * data)
{
	Column * col = selectStmt->table->getColumn(groupid);
	string val;
	Marshall::extract(data,selectStmt->table,col,val);
	//printf("%s:%s\n", col->name.c_str() , val.c_str() );
}
bool ColumnRowHandler::onDelete(int groupid, unsigned char * data)
{
	return false;
}
bool ColumnRowHandler::onUpdate(int groupid, unsigned char * data)
{
	return true;
}
int  ColumnRowHandler::getSize (int groupid)
{
	return 0;
}

void GroupRowHandler::onSelect(int groupid, unsigned char * data)
{
}
bool GroupRowHandler::onDelete(int groupid, unsigned char * data)
{
	return false;
}
bool GroupRowHandler::onUpdate(int groupid, unsigned char * data)
{
	return true;
}
int  GroupRowHandler::getSize (int groupid)
{
	return 0;
}