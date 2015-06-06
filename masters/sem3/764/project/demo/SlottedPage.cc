/*
 * SlottedPage.cc
 *
 *  Created on: Nov 13, 2008
 *  Author: shenoy, satish
 */
#include"Page.h"
#include"SlottedPage.h"
#include <climits>
#include <cassert>
#include <cstring>
#include <cstdlib>
using namespace CALF::Page;

#include <cstdio>

void SlottedPage::initialize()
{
    SlotPageRep& rep = *mpSlotPageRep;
    // place the slot table at the end of the page.
    rep.slot_cnt = 0;
    const unsigned off = PAGE_SZ - sizeof(Prid);
    mpSlotTable = static_cast<Prid*>(offsetAddress(off));

    // record the number of attributes in a record, and each attribute size
    short heap_bot = sizeof(SlotPageRep);
    //heap_bot += (heap_bot%PAGE_SZ)? PAGE_SZ - (heap_bot%PAGE_SZ): 0; //align with l2 cache size == page_size * n?
    rep.heap_bot_offset = heap_bot;
    rep.heap_top_offset = heap_bot;

    // record the free space available in the partition
    rep.free = PAGE_SZ - rep.slot_cnt*sizeof(Prid) - rep.heap_top_offset;
}

void SlottedPage::open()
{
    mpSlotPageRep = static_cast<SlotPageRep*>(offsetAddress(0));
    assert(mpSlotPageRep);
    const unsigned off = PAGE_SZ - sizeof(Prid);
    mpSlotTable = static_cast<Prid*>(offsetAddress(off));
}

/**
 * reset the heap pointer
 * re-write the slotted page metadata
 */
void SlottedPage::clear()
{
    SlotPageRep slot_rep = *mpSlotPageRep;
    slot_rep.free = PAGE_SZ - slot_rep.slot_cnt*sizeof(Prid) - slot_rep.heap_top_offset;
    slot_rep.heap_top_offset = slot_rep.heap_bot_offset;
    slot_rep.slot_cnt = 0;
    *mpSlotPageRep = slot_rep;
}


int SlottedPage::tupleCount() const
{
    assert(mpSlotPageRep);
    return mpSlotPageRep->slot_cnt;
}

unsigned SlottedPage::free() const
{
    assert(mpSlotPageRep);
    return mpSlotPageRep->free;
}

bool SlottedPage::allocSlot(unsigned* id, const short var_sz)
{
    assert(mpSlotPageRep);
    SlotPageRep& rep = *mpSlotPageRep;
    // make sure there is enough room
    if (!isSpace(var_sz))
    {
        return false; //throw exception?
    }

    // advance the top of the heap to point to the next free block.
    markRecord(id, rep.heap_top_offset, var_sz);
    advanceHeapPtr(var_sz);
    decreaseFreeSpace(var_sz);
    return true;
}

/*
 * Calculate address and length of record.  Shift all records by the deleted
 * record's size.  Update each slot's starting address, and mark the deleted
 * slot as being deleted.
 */
void SlottedPage::freeTupleSlot(const unsigned id)
{
	int sid = static_cast<int>(id);
    Prid& prid = mpSlotTable[-sid];
    char* end = static_cast<char*>(offsetAddress(prid.var));
    char* start = end + prid.size;
    unsigned sz = mpSlotPageRep->heap_top_offset - (prid.var + prid.size);
    memmove(end, start, sz);

    recedeHeapPtr(prid.size);
    increaseFreeSpace(prid.size);

    for (int i = sid + 1; i < tupleCount(); i++)
    {
        Prid& sid = mpSlotTable[-i];
        sid.var -= prid.size;
    }
    // shift back actual slot ids.

    for (int i = sid; i < tupleCount(); i++) {
    	mpSlotTable[-i] = mpSlotTable[-i - 1];
    }
    mpSlotPageRep->slot_cnt -= 1;
}

int SlottedPage::getAddress(char* addr[], const unsigned sid) const
{
    // negate the index because the slot table grows upwards in memory
	int id = static_cast<int>(sid);
    const Prid& prid = mpSlotTable[-id];
    addr[0] = static_cast<char*>(offsetAddress(prid.var));
    return 1;
}

bool SlottedPage::isSpace(const short sz) const
{
    return mpSlotPageRep->free >= sz + sizeof(Prid);
}

void SlottedPage::advanceHeapPtr(const short sz)
{
    mpSlotPageRep->heap_top_offset += sz;
}

void SlottedPage::recedeHeapPtr(const short sz)
{
    mpSlotPageRep->heap_top_offset -= sz;
}


void SlottedPage::decreaseFreeSpace(const short sz)
{
    mpSlotPageRep->free -= sz;
    // adjust the free space to provide a free slot entry.
    // if not enough room for a
    // slot entry, there is no free space on the page.
    if (mpSlotPageRep->free > static_cast<short>(sizeof(Prid)))
    {
        mpSlotPageRep->free -= sizeof(Prid);
    }
    else
    {
        mpSlotPageRep->free = 0;
    }
}

void SlottedPage::increaseFreeSpace(const short sz)
{
    mpSlotPageRep->free += sz;
}

void SlottedPage::markRecord(unsigned* index,
							 const short offset,
							 const short sz)
{
	assert(mpSlotPageRep);
    SlotPageRep& rep = *mpSlotPageRep;
    Prid& prid = mpSlotTable[-rep.slot_cnt];
    prid.var = offset;
    prid.size = sz;
    rep.slot_cnt += 1;
    *index = tupleCount() - 1;
}

unsigned char *SlottedPage::getTuple(int index)
{
	assert(index < tupleCount());
	Prid& prid = mpSlotTable[-index];
	unsigned char *start = static_cast<unsigned char *>(offsetAddress(prid.var));
	int len = prid.size;
	unsigned char *dest = (unsigned char *) malloc(len * sizeof(unsigned char));
	memcpy(dest, start, len); //break into columns?
	return dest;
}

void SlottedPage::setTuple(int index, unsigned char *data)
{
	assert(index < tupleCount());
	Prid& prid = mpSlotTable[-index];
	unsigned char *start = static_cast<unsigned char *>(offsetAddress(prid.var));
	int len = prid.size;
	memcpy(start, data, len);
}
