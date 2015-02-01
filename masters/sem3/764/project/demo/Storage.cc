// CS 764 : Project CALF
// author: satish@cs.wisc.edu,shenoy@cs.wisc.edu
// date: 12 Nov 2008

#include "Storage.h"
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <cstring>

using namespace CALF::Storage;
using namespace std;

#include <iostream>

Buffer::Buffer(unsigned char * d) : data(d),isDirty(false){}

void Buffer::setDirty()
{
	this->isDirty = true;
}

BufferPtr BufferManager::getBlock(int blockid)
{
	return buffers[blockid];
}

//todo: implement this
void BufferManager::clear()
{
}

void File::create(const string & filename)
{
	fileDescriptor = ::creat(filename.c_str(),0777);
	blockCount = 0;
}

void File::open(const string & filename)
{
	fileDescriptor = ::open(filename.c_str(), O_RDWR);

	if(fileDescriptor < 0)
		return create(filename);
		
	struct stat fileinfo;
	::fstat(fileDescriptor,&fileinfo);
	
	blockCount = fileinfo.st_size / BLOCK_SIZE;
}

int File::allocateBlock(BufferPtr & ptrBuffer)
{
	unsigned char * data = new unsigned char[BLOCK_SIZE];
	::memset(data,0,BLOCK_SIZE);
	ptrBuffer = new Buffer(data);
	ptrBuffer->setDirty();
	bufferManager.buffers[blockCount] = ptrBuffer;
	return blockCount++;
}

BufferPtr File::getBlock(int blockid)
{
	if(blockid < 0 || blockid >= blockCount) return NULL;
	
	if(bufferManager.buffers.find(blockid) != bufferManager.buffers.end())
		return bufferManager.buffers[blockid];
		
	int seekLoc = blockid * BLOCK_SIZE;
	::lseek(fileDescriptor, seekLoc, SEEK_SET);
	
	unsigned char * data = new unsigned char[BLOCK_SIZE];
	BufferPtr ptrBuffer = new Buffer(data);
	
	::read(fileDescriptor, data, BLOCK_SIZE);
	
	bufferManager.buffers[blockid] = ptrBuffer;
	
	return ptrBuffer;
}

void File::flush(int blockid)
{
	if(blockid < 0 || blockid >= blockCount) return;
	BufferPtr ptrBuffer = bufferManager.buffers[blockid];
	
	int seekLoc = blockid * BLOCK_SIZE;
	::lseek(fileDescriptor, seekLoc, SEEK_SET);
	
	::write(fileDescriptor, ptrBuffer->data, BLOCK_SIZE);
	
	ptrBuffer->isDirty = false;
}

//writes all dirty buffers to disk
void File::flush()
{
	for(map<int,BufferPtr>::iterator iter = bufferManager.buffers.begin();
		iter != bufferManager.buffers.end(); ++iter){
		if((*iter).second->isDirty)
			flush((*iter).first);
	}
}

void File::close()
{
	::close(fileDescriptor);
}
