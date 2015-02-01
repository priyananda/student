/*
 * PageManager.cpp
 *
 *  Created on: Nov 13, 2008
 *      Author: shenoy & satish
 */

#include "MetaPage.h"
#include "PageManager.h"

#include "Meta.h"
using namespace CALF::Meta;

#include "Storage.h"
using namespace CALF::Storage;

#include "SlottedPage.h"
using namespace CALF::Page;

#include<iostream>

PageManager * PageManager::mPm = 0;

#include "MersenneTwister.h"

static double _rand()
{
	static MTRand rng;
	return rng.rand();
}

void PageManager::initializeFile(File &file)
{
	//idempotent
	if (file.getBlockCount() == 0){
		BufferPtr ptr;
		for (int i = 0; i < MAX_META_BLOCKS; i++) {
			file.allocateBlock(ptr);
			MetaPage page(ptr->data);
			page.open();
			page.initialize();
		}
	}
}

PageManager::~PageManager()
{
}

inline bool shouldReadBlock(double selectivity)
{
	if( selectivity == 1.0) return true;
	return _rand() > selectivity;
}

void PageManager::selectRows(File& file, int groupId, RowHandler * handler, double selectivity)
{
	list<int> blocks;
	getBlockNumbers(file, groupId,blocks);

	for (list<int>::const_iterator li = blocks.begin(); li != blocks.end(); ++li){
		if(!shouldReadBlock(selectivity))
			continue;
		
		BufferPtr ptr = file.getBlock(*li);
		SlottedPage page(ptr->data);
		page.open();
		int tc = page.tupleCount();
		for (int j = 0; j < tc; j++) {
			unsigned char *data = page.getTuple(j);
			handler->onSelect(groupId, data);
		}
	}
}

void PageManager::insertRow(File& file, int groupid, int size, unsigned char * data)
{
	int blockid = getLastBlock(file,groupid);
	bool shouldAllocPage = blockid < 0;
	BufferPtr pageBuffer;
	
	if(!shouldAllocPage){
		SlottedPage page(file.getBlock(blockid)->data);
		page.open();
		if(!page.isSpace(size))
			shouldAllocPage = true;
	}
	
	if(shouldAllocPage){
		//allocate a new block if there were no blocks for this group or the last block was full
		blockid = file.allocateBlock(pageBuffer);
		//update the meta
		int metablock = getFreeMetaBlock(file, groupid, blockid);
		if (metablock < 0){
			cout << "meta blocks are full!" << endl;
			return;
		}
		
		BufferPtr metaPtr = file.getBlock(metablock);
		MetaPage metaPage(metaPtr->data);
		metaPage.open();

		//add a new slot for this group
		int isize = sizeof(int);
		char *metaaddr[1];
		metaPage.allocSlot(metaaddr, 2 * isize);
		memset(metaaddr[0], 0, isize);
		memcpy(metaaddr[0], &groupid, isize);
		memcpy(metaaddr[0] + isize, &blockid, isize);
		
		metaPtr->setDirty();
	}
	pageBuffer = file.getBlock(blockid);
	SlottedPage page(pageBuffer->data);
	page.open();
	if(shouldAllocPage)
		//this page was newly allocated, so initialize
		page.initialize();
		
	//put data in page slot
	unsigned int id = 0;
	char * addr;
	
	page.allocSlot(&id, size);
	page.getAddress(&addr, id);
	memcpy(addr, data, size);
	pageBuffer->setDirty();
}

void PageManager::updateRows(File& file, int groupId, RowHandler * handler,double selectivity)
{
	list<int> blocks;
	getBlockNumbers(file,groupId,blocks);

	for (list<int>::const_iterator li = blocks.begin(); li != blocks.end(); ++li) {
		if(!shouldReadBlock(selectivity))
			continue;
		
		BufferPtr ptr = file.getBlock(*li);
		SlottedPage page(ptr->data);
		page.open();
		for (int j = 0; j < page.tupleCount(); j++) {
			unsigned char *record = page.getTuple(j);
			if (handler->onUpdate(groupId,record)){
				page.setTuple(j, record);
				ptr->setDirty();
			}
		}
	}
}

void PageManager::deleteRows(File& file, int groupId, RowHandler * handler,double selectivity)
{
	list<int> blocks;
	getBlockNumbers(file, groupId, blocks);

	for (list<int>::const_iterator li = blocks.begin(); li != blocks.end(); ++li) {
		if(!shouldReadBlock(selectivity))
			continue;

		BufferPtr ptr = file.getBlock(*li);
		SlottedPage page(ptr->data);
		page.open();
		
		list<int> toRemove;
		for (int j = 0; j < page.tupleCount(); j++) {
			unsigned char *record = page.getTuple(j);
			if (handler->onDelete(groupId, record))
				toRemove.push_back(j); //?is it j?
		}

		for (list<int>::reverse_iterator ri = toRemove.rbegin(); ri != toRemove.rend(); ++ri) {
			page.freeTupleSlot(*ri);
			ptr->setDirty();
		}
	}
	// TODO: Optimization: if thr r no records in block, remove block from meta;
}

int PageManager::getLastBlock(File& file, int groupId)
{
	//todo: optimize
	list<int> blocks;
	getBlockNumbers(file,groupId,blocks);
	if(blocks.size() == 0) 
		return -1;
	return blocks.back();
}

void PageManager::getBlockNumbers(File& file, int groupId, list<int> & blocks)
{
	for (int i = 0; i < MAX_META_BLOCKS; i++) {
		BufferPtr ptr = file.getBlock(i);
		
		if (!MetaPage::isMetaPage(ptr->data))
			assert(false);
		
		MetaPage p(ptr->data);
		p.open();
		p.getBlocks(groupId, blocks);
	}
}


int PageManager::getFreeMetaBlock(File& file, int groupId, int blockId)
{
	for (int i = 0; i < MAX_META_BLOCKS; i++) {
		BufferPtr ptr = file.getBlock(i);
		
		if (!MetaPage::isMetaPage(ptr->data))
			assert(false);

		MetaPage p(ptr->data);
		p.open();
		if (p.getAddress(groupId, blockId))
			return -1;

		if (p.isSpace(2 * sizeof(int)))
			return i;
	}
	return -1;
}