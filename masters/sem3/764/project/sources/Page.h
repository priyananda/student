/*
 * Page.h
 *
 *  Created on: Nov 13, 2008
 *      Author: shenoy, satish
 */

#ifndef PAGE_H_
#define PAGE_H_
using namespace std;
namespace CALF {
	namespace Page{
		const unsigned short PAGE_SZ = 8 * 1024;
		class Page
		{
			public:
				Page(unsigned char *data) {mData = data;}
				virtual ~Page(){}

				virtual void open() = 0;
				virtual unsigned char *getTuple(int index) = 0;
				void *getData() const {return (void *) mData;}
				virtual void clear() = 0;
				virtual void initialize() = 0;
	            virtual bool isSpace(const short sz) const = 0;
				virtual int tupleCount() const = 0;
				virtual void freeTupleSlot(const unsigned id) = 0;
				virtual bool allocSlot(unsigned* id, const short var_sz) = 0;
				virtual int getAddress(char* addr[], const unsigned sid) const = 0;
	            virtual void setTuple(int index, unsigned char *data) = 0;
			private:
				unsigned char *mData;
		};
	}
}

#endif /* PAGE_H_ */
