#// CS 764 : Project CALF
// author: satish@cs.wisc.edu,shenoy@cs.wisc.edu
// date: 8 Dec 2008

#ifndef CALF_MARSHALL_H
#define CALF_MARSHALL_H

namespace CALF
{
  namespace Storage
  {
	//marshalls data to and from raw byte stream
	class Marshall
	{
	public:
		//interpret a single column
		static void format(unsigned char * dest, Table * table, Column * column, const string & value);

		//interpret all columns
		static void format(unsigned char * dest, Table * table, const string * values);

		//interpret a group
		static void format(unsigned char * dest, Table * table, Group * group, const string * values);

		//extract a single column
		static void extract(unsigned char * src, Table * table, Column * column, string & output);
		
		//extract all columns
		static void extract(unsigned char * src, Table * table, string * output);
		
		//extract a group
		static void extract(unsigned char * src, Table * table, Group * group, string * output);
	};
  }
}

#endif