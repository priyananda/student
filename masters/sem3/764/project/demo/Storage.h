// CS 764 : Project CALF
// author: satish@cs.wisc.edu,shenoy@cs.wisc.edu
// date: 5 Nov 2008

#ifndef CALF_STORAGE_H
#define CALF_STORAGE_H

#include <string>
using std::string;

#include <map>
using std::map;

namespace CALF
{
  namespace Storage
  {
  	//4k blocks
  	const int BLOCK_SIZE = 8 * 1024;
  
  	class File;
  	class BufferManager;
  
	class Buffer
	{
	public:
		Buffer(unsigned char * d);
	
		//makes the buffer dirty
		void setDirty();
	
		//the actual data
		unsigned char * data;
		
		friend class File;
	private:
		bool isDirty;
	};
	
	typedef Buffer * BufferPtr;
	
	class BufferManager
	{
	public:
		//gets the buffer if it is in cache
		BufferPtr getBlock(int blockid);
		
		//removes all *non-dirty* pages from cache
		void clear();
		
		friend class File;
	private:
		map<int,BufferPtr> buffers;
	};

	//represents a file.
	class File
	{
	public:
		//creates an empty file. overwrites an existing one
		void create(const string & filename);
	
		//opens the underlying file
		void open(const string & filename);
		
		//allocates a new block, and returns the blockid
		int allocateBlock(BufferPtr & ptrBuffer);
		
		//reads block corresponding to 'blockid' into memory and returns
		//the pointer to the buffer. NULL if there is any error
		BufferPtr getBlock(int blockid);
		
		//writes dirty buffer
		void flush(int blockid);
		
		//writes all dirty buffers to disk
		void flush();
		
		//closes the file
		void close();

		//total number of blocks in the file
		int getBlockCount(){ return blockCount; }
	private:
		BufferManager bufferManager;
		int fileDescriptor;
		int blockCount;
	};

	class FileScanner
	{
	
	};
  }
}

#endif
