/*
 * MetaPage.cc
 *
 *  Created on: Nov 13, 2008
 *  Author: shenoy, satish
 */
#include"Page.h"
#include"MetaPage.h"
#include <climits>
#include <cassert>
#include <cstring>
#include<cstdlib>
#include<iostream>
using namespace CALF::Page;
using namespace std;

void MetaPage::initialize()
{
    SlotPageRep& rep = *mpSlotPageRep;
    rep.slot_cnt = 0;

    // record the number of attributes in a record, and each attribute size
    short heap_bot = sizeof(SlotPageRep);
    //heap_bot += (heap_bot%PAGE_SZ)? PAGE_SZ - (heap_bot%PAGE_SZ): 0; //align with l2 cache size == page_size * n?
    rep.heap_bot_offset = heap_bot;
    rep.heap_top_offset = heap_bot;
    rep.header = HEADER;
    // record the free space available in the partition
    rep.free = PAGE_SZ - rep.heap_top_offset;
}

void MetaPage::open()
{
    mpSlotPageRep = static_cast<SlotPageRep*>(offsetAddress(0));
    assert(mpSlotPageRep);
}

/**
 * reset the heap pointer
 * re-write the slotted page metadata
 */
void MetaPage::clear()
{
    SlotPageRep slot_rep = *mpSlotPageRep;
    slot_rep.free = PAGE_SZ - slot_rep.heap_top_offset;
    slot_rep.heap_top_offset = slot_rep.heap_bot_offset;
    slot_rep.slot_cnt = 0;
    *mpSlotPageRep = slot_rep;
}


int MetaPage::tupleCount() const
{
    assert(mpSlotPageRep);
    return mpSlotPageRep->slot_cnt;
}

unsigned MetaPage::free() const
{
    assert(mpSlotPageRep);
    return mpSlotPageRep->free;
}

bool MetaPage::allocSlot(char *addr[], const short var_sz)
{
    assert(mpSlotPageRep);
    SlotPageRep& rep = *mpSlotPageRep;
    // make sure there is enough room
    if (!isSpace(var_sz))
    {
        return false; //throw exception?
    }

    // advance the top of the heap to point to the next free block.
    markRecord(addr, rep.heap_top_offset, var_sz);
    advanceHeapPtr(var_sz);
    decreaseFreeSpace(var_sz);
    return true;
}

/*
 * Calculate address and length of record.  Shift all records by the deleted
 * record's size.  Update each slot's starting address, and mark the deleted
 * slot as being deleted.
 */
void MetaPage::freeTupleSlot(int grp_num, int blk_id)
{
	//TODO CHECK IF THIS IS CORRECT;
    char* end = getAddress(grp_num, blk_id);
    if (!end) {
    	return;
    }

    char* start = end + 2 * sizeof(int);
    unsigned sz = mpSlotPageRep->heap_top_offset;
    memmove(end, start, sz);

    recedeHeapPtr(sz);
    increaseFreeSpace(sz);
    mpSlotPageRep->slot_cnt--;
}

bool MetaPage::isSpace(const short sz) const
{
    return mpSlotPageRep->free >= sz;
}

void MetaPage::advanceHeapPtr(const short sz)
{
    mpSlotPageRep->heap_top_offset += sz;
}

void MetaPage::recedeHeapPtr(const short sz)
{
    mpSlotPageRep->heap_top_offset -= sz;
}


void MetaPage::decreaseFreeSpace(const short sz)
{
    mpSlotPageRep->free -= sz;
}

void MetaPage::increaseFreeSpace(const short sz)
{
    mpSlotPageRep->free += sz;
}

void MetaPage::markRecord(char *addr[],
						  const short offset,
						  const short sz)
{
	assert(mpSlotPageRep);
    SlotPageRep& rep = *mpSlotPageRep;
    rep.slot_cnt += 1;
    addr[0] = static_cast<char*>(offsetAddress(offset));
}

void MetaPage::getBlocks(int groupId, list<int> & blocks)
{
	char *temp = static_cast<char *>(offsetAddress(sizeof(SlotPageRep)));
	int blk = 0;
	int grp;
	for (int i = 0; i < mpSlotPageRep->slot_cnt; i++) {
		::memcpy(&grp, temp, sizeof(int));
		if (grp == groupId) {
			::memcpy(&blk, temp + sizeof(int), sizeof(int));
			blocks.push_back(blk);
		}
		temp += 2 * sizeof(int);
	}
}

char *MetaPage::getAddress(int groupId, int blockId)
{
	char *temp = static_cast<char *>(offsetAddress(sizeof(SlotPageRep)));
	int blk = 0;
	int grp;
	for (int i = 0; i < mpSlotPageRep->slot_cnt; i++) {
		::memcpy(&grp, temp, sizeof(int));
		if (grp == groupId) {
			::memcpy(&blk, temp + sizeof(int), sizeof(int));
			if (blk == blockId) {
				return temp;
			}
		}
		temp += 2 * sizeof(int);
	}

	return NULL;
}