#include "Storage.h"
#include "Meta.h"
#include "Page.h"
#include "MetaPage.h"
#include "SlottedPage.h"
#include "PageManager.h"
#include "Tuple.h"
#include <cstring>
#include <cstdlib>
#include <list>

using namespace CALF::Storage;
using namespace CALF::Meta;
using namespace CALF::Page;

using namespace std;
#include <iostream>

void testStorage()
{
	File dataFile;
	dataFile.create("Student.Slotted.data");
	BufferPtr buffer = NULL;
	dataFile.allocateBlock(buffer);
	memset(buffer->data,'1', BLOCK_SIZE);
	dataFile.flush();
	dataFile.close();

	File readItBack;
	readItBack.open("Student.Slotted.data");
	buffer = readItBack.getBlock(0);
	for(int i = 0 ; i < BLOCK_SIZE; ++i )
		cout << buffer->data[i];
	cout << endl;
	readItBack.close();
}

void testMeta()
{
	Database database("test.database");
	Table * table = database.schema->getTable("Student");

	cout << "Listing all columns" << endl;
	list<Column *> cols = table->getAllColumns();
	for( list<Column *>::iterator  iter = cols.begin(); iter != cols.end(); ++iter )
		cout << "\t" << (*iter)->name << "," << (*iter)->dataType << "," << (*iter)->length << endl;

	cout << "total record size = " << table->recordSize() << endl;

	cout << "iterating using index" << endl;
	int colCount = table->getColumnCount();
	for(int i = 0 ; i < colCount; ++i ){
		cout << "\t" << table->getColumn(i)->name << endl;
	}

	cout << "Looking for specific name(existing): " << table->getColumn("Major") << endl;
	cout << "Looking for specific name(nonexisting): " << table->getColumn("kajor") << endl;
}

void testSlotPage(int argc, char *argv[])
{
	//database argv[1];
	//queries file argv[2];
	//
	assert (argc > 3);
	File dataFile;
	dataFile.create("Student.Slotted.data");

	Database database(argv[1]);
	PageManager *p = PageManager::getInstance(dataFile);
	//(unsigned char *) malloc(sizeof (unsigned char) * database.schema->getTable("Student")->recordSize());
	const string student("Student");

	QueryFileParser parser(database.schema, string(argv[2]));
	for (list<Stmt *>::const_iterator query = parser.statements.begin(); query != parser.statements.end(); ++query) {
		if ((*query)->getStmtType() == InsertStmtType) {
			InsertStmt *is = (InsertStmt *) (*query);
			Table *t = is->table;
			unsigned char *grpData[t->ng];
			for (int i = 0; i < t->ng; i++) {
				list<Column *> cols;
				t->groups[i]->getAllColumns(cols);
				grpData[i] = (unsigned char *) malloc(sizeof(unsigned char) * t->groups[i]->recordSize());
				unsigned char *tGrpData = grpData[i];
				for (list<Column *>::const_iterator ci = cols.begin(); ci != cols.end(); ++ci) {
					int size = (*ci)->length;
					const char *temp = is->values[0].c_str();
					memcpy(tGrpData, temp, size);
					tGrpData += size;
				}
			}

			for (int i = 0; i < t->ng; i++) {
				p->insert(dataFile, database, student, grpData[i], i);
			}

		}
		else if ((*query)->getStmtType() == UpdateStmtType) {

		}
		else if ((*query)->getStmtType() == SelectStmtType) {
			SelectStmt *ss = (SelectStmt *) *query;
			Table *t = ss->table;
			for (int i = 0; i < t->ng; i++) {
				p->getTuples(dataFile, database, i);
			}
		}
	}

	for (int i = 2; i < argc; i++) {
		unsigned char *tuple = reinterpret_cast<unsigned char*>(argv[i]);
		p->insert(dataFile, database, student, tuple, 0);
	}

	dataFile.flush();
	dataFile.close();

	File dat;
	dat.open("Student.Slotted.data");
	BufferPtr buff = NULL;
	p = PageManager::getInstance(dat);
	unsigned char *tuple = reinterpret_cast<unsigned char*>(argv[2]);
	p->deleteRow(dat, database, student, tuple, 0);

	dat.flush();
	dat.close();


	File dat2;
	dat2.open("Student.Slotted.data");
	buff = NULL;
	p = PageManager::getInstance(dat2);
	tuple = reinterpret_cast<unsigned char*>(argv[2]);
	unsigned char *newTuple = reinterpret_cast<unsigned char*>(argv[3]);
	p->updateRow(dat2, database, student, tuple, newTuple, 0);

	dat2.flush();
	dat2.close();

	File readItBack;
	readItBack.open("Student.Slotted.data");
	buff = NULL;
	p = PageManager::getInstance(readItBack);
	list<unsigned char*> *data = p->getTuples(readItBack, database, 0);
	list<Column *> *cols = new list<Column *>();
	database.schema->getTable(student)->groups[0]->getAllColumns(*cols);
	for (list<unsigned char *>::const_iterator ci = data->begin(); ci != data->end(); ++ci) {
		cout << *ci << " ";
	}

	readItBack.close();
	cout << endl;
}

int main(int argc, char *argv[])
{
	//testStorage();
	//testMeta();
	testSlotPage(argc, argv);
/*	unsigned char *d = (unsigned char *) malloc(8 * sizeof(unsigned char));
	::memcpy(d, argv[1], 8);
	bool b = MetaPage::isMetaPage(d);
	cout << b << endl;*/
	return 0;
}
