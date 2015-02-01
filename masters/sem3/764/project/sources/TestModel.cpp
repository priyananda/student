#include<iostream>
#include<fstream>
#include<cstdlib>
#include<list>
#include<math.h>
#include<string.h>
#include"Meta.h"
#include"Storage.h"
#include<string>
using namespace std;
using namespace CALF::Meta;
using namespace CALF::Storage;

bool selectMatch(string query, string column) {
	size_t pos = query.find("where", 0);
	size_t pos1;
	if (pos == string::npos) {
		// NO WHERE CLAUSE
		pos1 = query.find(column, 0);
	} else {
		string select = query.substr(0, pos);
		pos1 = select.find(column, 0);
	}

	if (pos1 == string::npos) {
		return false;
	}

	return true;
}

bool whereMatch(string query, string column) {
	size_t pos = query.find("where", 0);
	if (pos == string::npos) {
		// NO WHERE CLAUSE
		return false;
	}
	size_t pos1 = query.find(column, pos);
	if (pos1 == string::npos) {
		return false;
	}

	return true;
}

int main(int argc, char *argv[]) {
	Database database(argv[2]);
	static int PG_SZ = 4096;
	const string tableName = "Student";
	Table *table = database.schema->getTable(tableName);
	list<Column *> cols = table->getAllColumns();
	int rpp[table->ng];
	ifstream input(argv[1]);
	if (!input.good()) {
		fprintf(stderr, "ERROR READING FILE!");
		return 0;
	}

	int i = 0;
	int totalSize = 0;

	double costr = 1;
	double costw = 10;
	double cost = 0;
	double sum = 0;
	double wsum = 0;
	int N = 2500;
	char buf[256];
	while (!input.eof()) {
		input.getline(buf, 255);
		if (::strlen(buf) == 0 || buf[0] == '#')
			continue;
		string qi(buf);
		if (qi.find("insert", 0) != string::npos) {
			cost += (costr + costw) * table->ng;
		}
		else if (qi.find("update", 0) != string::npos) {
			sum = 0;
			wsum = 0;
			for (i = 0; i < table->ng; i++) {
				Group *g = table->groups[i];
				cols.clear();
				g->getAllColumns(cols);
				totalSize = 0;
				bool match = false;
				bool wmatch = false;
				for (list<Column *>::const_iterator ci = cols.begin(); ci != cols.end(); ci++) {
					totalSize += (*ci)->length;
					if (!match && selectMatch(qi, (*ci)->name)) {
						match = true;
					}

					if (!wmatch && whereMatch(qi, (*ci)->name)) {
						wmatch = true;
					}
				}

				rpp[i] = PG_SZ / totalSize;
				if (match) {
					sum += ceil((double) N / (double) rpp[i]);
				}
				if (wmatch) {
					wsum += ceil((double) N / (double) rpp[i]);
				}
			}
			cost += costr * sum + costw * wsum;
		}
		else if (qi.find("select", 0) != string::npos) {
			for (i = 0; i < table->ng; i++) {
				Group *g = table->groups[i];
				cols.clear();
				g->getAllColumns(cols);
				totalSize = 0;
				bool match = false;
				for (list<Column *>::const_iterator ci = cols.begin(); ci != cols.end(); ci++) {
					totalSize += (*ci)->length;
					if (!match && (selectMatch(qi, (*ci)->name) || whereMatch(qi, (*ci)->name))) {
						match = true;
					}
				}
				rpp[i] = PG_SZ / totalSize;
				if (match) {
					sum += ceil((double) N / (double) rpp[i]);
				}
			}

			cost += costr * sum;
		}
	}

	cout << cost << endl;
}
