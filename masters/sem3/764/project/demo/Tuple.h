/*
 * Tuple.h
 *
 *  Created on: Nov 21, 2008
 *      Author: satish
 */

#ifndef TUPLE_H_
#define TUPLE_H_

#include <climits>
#include <cassert>
#include <vector>
#include <cstdlib>
#include <cstring>

#include"Meta.h"
#include"Storage.h"
using namespace std;
using namespace CALF::Meta;

namespace CALF
{
  namespace Storage
  {
	class Tuple
	{
	public:
		Tuple(unsigned char *data, list<Column *> *columns)
		{
			//mOffsets = new vector<int>();
			//mLengths = new vector<int>();
			mColumns = columns;
			mData = static_cast<char *>(static_cast<void *>(data));
			int size = 0;
			for (list<Column *>::const_iterator ci = columns->begin(); ci != columns->end(); ++ci) {
				mOffsets.push_back(size);
				size += (*ci)->length;
				mLengths.push_back((*ci)->length);
			}
		}

		virtual ~Tuple()
		{
		}

		unsigned char *getData(int sindex)
		{
			int offset = mOffsets.at(sindex);
			int size = mLengths.at(sindex);
			char *temp = mData + offset;
			unsigned char *dest = (unsigned char *) malloc(size * sizeof(unsigned char));
			memcpy(dest, temp, size);
			return dest;
		}

	private:
		char *mData;
		list<Column *> *mColumns;
		vector<int> mOffsets;
		vector<int> mLengths;
	};
  }
}

#endif /* TUPLE_H_ */
