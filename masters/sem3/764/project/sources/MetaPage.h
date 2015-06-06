/*
 * MetaPage.h
 *
 *  Created on: Nov 22, 2008
 *      Author: satish
 */

#ifndef METAPAGE_H_
#define METAPAGE_H_

#include<climits>
#include <cassert>
#include <cstring>
#include<cstdlib>
#include<list>
using namespace std;

namespace CALF {
	namespace Page {
		class MetaPage {
		public:
			MetaPage(unsigned char *data)
			{
				mData = data;
			}

			virtual ~MetaPage() {}

			static bool isMetaPage(unsigned char *data)
			{
				unsigned short q = 9999;
				if (!memcmp(data, &q, sizeof(unsigned short))) {
					return true;
				}
				return false;
			}

			void getBlocks(int groupId, list<int> & blocks);
			void initialize();
			void open();
			unsigned char *getTuple(int groupId);
            unsigned free() const;
            bool isSpace(const short sz) const;
            void clear();
            bool isValid(const int sid) const;
            bool allocSlot(char *addr[], const short var_sz);
            void freeTupleSlot(int grp_num, int blk_id);
            int tupleCount() const;
            void* offsetAddress(unsigned short offset) const;

            void advanceHeapPtr(const short sz);
            void recedeHeapPtr(const short sz);
            void increaseFreeSpace(const short sz);
            void decreaseFreeSpace(const short sz);
            void markRecord(char *addr[],
							const short offset,
							const short sz);

            char *getAddress(int groupId, int blockId);

		private:
            struct SlotPageRep
            {
                SlotPageRep() {}
                unsigned short header;
                unsigned short heap_bot_offset;  ///< offset of bottom of heap
                unsigned short heap_top_offset;  ///< offset of top of heap
                unsigned short free;             ///< current free space available
                int slot_cnt;            ///< number of slot entries
                int att_cnt;
            };
            SlotPageRep* mpSlotPageRep;
			unsigned char *mData;
			const static unsigned short HEADER = 9999;
		};

		inline void* MetaPage::offsetAddress(unsigned short offset) const
		{
	        return static_cast<void*>(static_cast<char*>(static_cast<void *>(mData)) + offset);
		}
	}
}
#endif /* METAPAGE_H_ */
