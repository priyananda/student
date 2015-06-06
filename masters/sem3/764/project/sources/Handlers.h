#ifndef CALF_HANDLERS_H
#define CALF_HANDLERS_H

#include "PageManager.h"
using namespace CALF::Page;

namespace CALF
{
  namespace Exec
  {
	class RowHandlerCommon : public RowHandler
	{
	public:
		RowHandlerCommon():selectStmt(0),updateStmt(0), deleteStmt(0){}

		const SelectStmt * selectStmt;
		const UpdateStmt * updateStmt;
		const DeleteStmt * deleteStmt;

		bool isWhereClause;
	};

	class SlottedRowHandler : public RowHandlerCommon
	{
	public:
		virtual void onSelect(int groupid, unsigned char * data);
		virtual bool onDelete(int groupid, unsigned char * data);
		virtual bool onUpdate(int groupid, unsigned char * data);
		virtual int  getSize (int groupid);
		virtual ~SlottedRowHandler() {}
	};

	class ColumnRowHandler : public RowHandlerCommon
	{
	public:
		virtual void onSelect(int groupid, unsigned char * data);
		virtual bool onDelete(int groupid, unsigned char * data);
		virtual bool onUpdate(int groupid, unsigned char * data);
		virtual int  getSize (int groupid);
		virtual ~ColumnRowHandler() {}
	};

	class GroupRowHandler : public RowHandlerCommon
	{
	public:
		virtual void onSelect(int groupid, unsigned char * data);
		virtual bool onDelete(int groupid, unsigned char * data);
		virtual bool onUpdate(int groupid, unsigned char * data);
		virtual int  getSize (int groupid);
		virtual ~GroupRowHandler() {}
	};
  }
}
#endif
