/*
 * BufferManager.h
 *
 *  Created on: Nov 13, 2008
 *      Author: shenoy & satish
 */

#ifndef PAGEMANAGER_H_
#define PAGEMANAGER_H_
#include<map>
#include"Page.h"
#include"MetaPage.h"
#include"SlottedPage.h"
#include "Storage.h"
#include "Meta.h"
#include<list>
using namespace CALF::Meta;
using namespace CALF::Storage;

namespace CALF
{
	namespace Page
	{
		//actually should be three separate interfaces
		class RowHandler
		{
		public:
			//method called for each record during select
			//expected behavior: execute where clause, add to result set
			virtual void onSelect(int groupid, unsigned char * data) = 0;
			
			//method called for each record during delete
			//expected behavior: execute where clause, return true if is to be deleted
			virtual bool onDelete(int groupid, unsigned char * data) = 0;
			
			//method called for each record during update
			//expected behavior: execute where clause, return true if record has changed and update data in pointer
			virtual bool onUpdate(int groupid, unsigned char * data) = 0;

			//size of a "group". depending on page layout, con be column/group/tuple size
			virtual int  getSize (int groupid) = 0;

			virtual ~RowHandler() {}
		};

		class PageManager
		{
		public:
			const static int MAX_META_BLOCKS = 10;
			
			static PageManager * getInstance()
			{
				if (!mPm)
					mPm = new PageManager();
				return mPm;
			}

			virtual ~PageManager();

			//allocates meta blocks
			void initializeFile(File &file);

			void insertRow (File& file, int groupId, int dataSize, unsigned char * data);
			
			void selectRows(File& file, int groupId, RowHandler * handler, double selectivity = 1.0);
			
			void deleteRows(File& file, int groupId, RowHandler * handler, double selectivity = 1.0);
			
			void updateRows(File& file, int groupId, RowHandler * handler, double selectivity = 1.0);
		private:
			PageManager(){}
			
			int  getLastBlock(File& file, int groupId);
			
			void getBlockNumbers(File& file, int groupId, list<int> & out);
			
			int  getFreeMetaBlock(File& file, int groupId, int blockId);

			//singleton base
			static PageManager * mPm;
		};
	}
}

#endif /* PAGEMANAGER_H_ */
