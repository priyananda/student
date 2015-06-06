/*
 * SlottedPage.h
 *
 *  Created on: Nov 13, 2008
 *      Author: shenoy, satish
 */

#ifndef SLOTTEDPAGE_H_
#define SLOTTEDPAGE_H_
#include <climits>
#include <cassert>
#include <cstring>
#include "Page.h"

namespace CALF {
	namespace Page {
		class SlottedPage : public Page
		{
			public:
				SlottedPage(unsigned char *data)
					:Page(data),mpSlotPageRep(0),mpSlotTable(0) {}

				virtual ~SlottedPage() {}

				void initialize();
				void open();
				virtual unsigned char *getTuple(int index);
	            unsigned free() const;
	            virtual bool isSpace(const short sz) const;
	            void clear();
	            bool isValid(const int sid) const;
	            bool allocSlot(unsigned* id, const short var_sz);
	            int getAddress(char* addr[], const unsigned sid) const;
	            virtual void freeTupleSlot(const unsigned id);
	            virtual int tupleCount() const;
	            void* offsetAddress(unsigned short offset) const;
	            void setTuple(int index, unsigned char *data);

			private:
	            struct SlotPageRep
	            {
	                SlotPageRep();
	                unsigned short heap_bot_offset;  ///< offset of bottom of heap
	                unsigned short heap_top_offset;  ///< offset of top of heap
	                unsigned short free;             ///< current free space available
	                int slot_cnt;            ///< number of slot entries
	                int att_cnt;
	            };
	            SlotPageRep* mpSlotPageRep; ///< The page's metadata
	            struct Prid
	            {
	                unsigned short var;
	                unsigned short size;
	            };
	            Prid* mpSlotTable;

	            void advanceHeapPtr(const short sz);
	            void recedeHeapPtr(const short sz);
	            void increaseFreeSpace(const short sz);
	            void decreaseFreeSpace(const short sz);
	            void markRecord(unsigned* index,
								const short offset,
								const short sz);

		};

		inline void* SlottedPage::offsetAddress(unsigned short offset) const
		{
/*
			unsigned char *temp = mData;
			temp += offset;
			T *value;
			memcpy(value, temp, sizeof(T));
*/
	        return static_cast<void*>(static_cast<char*>(SlottedPage::getData()) + offset);
		}

		inline bool SlottedPage::isValid(const int sid) const
	    {
			return (mpSlotTable[-sid].size != USHRT_MAX);
		}
	}
}

#endif /* SLOTTEDPAGE_H_ */
