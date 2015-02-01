#include "Meta.h"
using namespace CALF::Meta;

#include "Marshall.h"
using namespace CALF::Storage;

#include <cstdlib>
#include <cstring>

#include <iostream>
using namespace std;

void Marshall::format(unsigned char * dest, Table * table, Column * column, const string & value)
{
	switch(column->dataType)
	{
		case CTInteger:{
			int intval = atoi(value.c_str());
			unsigned char * src = reinterpret_cast<unsigned char *>(&intval);
			for(int i = 0 ; i < column->length; ++i)
				dest[i] = src[i];
			break;
		}
		case CTFloat:{
			float floatval = atof(value.c_str());
			unsigned char * src = reinterpret_cast<unsigned char *>(&floatval);
			for(int i = 0 ; i < column->length; ++i)
				dest[i] = src[i];
			break;
		}
		case CTCharacter:
			strncpy((char *)dest,value.c_str(),value.length());
			memset(dest + value.length(),0, column->length - value.length());
			break;
		default:
			break;
	};
}

//interpret all columns
void Marshall::format(unsigned char * dest, Table * table, const string * values)
{
	int nc = table->getColumnCount();
	for(int i = 0 ; i < nc; ++i){
		Column * col = table->getColumn(i);
		format(dest,table,col,values[i]);
		dest += col->length;
	}
}

//interpret a group
void Marshall::format(unsigned char * dest, Table * table, Group * group, const string * values)
{
	int nc = group->columnCount;
	for(int i = 0 ; i < nc; ++i){
		Column * col = group->columns[i];
		format(dest,table,col,values[ table->getColumnIndex(col->name) ]);
		dest += col->length;
	}
}

//extract a single column
void Marshall::extract(unsigned char * src, Table * table, Column * column, string & output)
{
	char buffer[25];
	switch(column->dataType)
	{
		case CTInteger:{
			int intval = 0;
			unsigned char * dst = reinterpret_cast<unsigned char *>(&intval);
			for(int i = 0 ; i < column->length; ++i)
				dst[i] = src[i];
			sprintf(buffer,"%d",intval);
			output = string(buffer);
			break;
		}
		case CTFloat:{
			float floatval = 0;
			unsigned char * dest = reinterpret_cast<unsigned char *>(&floatval);
			for(int i = 0 ; i < column->length; ++i)
				dest[i] = src[i];
			sprintf(buffer,"%f",floatval);
			output = string(buffer);
			break;
		}
		case CTCharacter:
			output = string((char *)src);//might be buggy
			break;
		default:
			break;
	};
}

void Marshall::extract(unsigned char * src, Table * table, string * output)
{
	int nc = table->getColumnCount();
	for(int i = 0 ; i < nc; ++i){
		Column * col = table->getColumn(i);
		extract(src,table,col,output[i]);
		src += col->length;
	}
}

void Marshall::extract(unsigned char * src, Table * table,Group * group, string * output)
{
	int nc = group->columnCount;
	for(int i = 0 ; i < nc; ++i){
		Column * col = table->getColumn(i);
		extract(src,table,col,output[i]);
		src += col->length;
	}
}