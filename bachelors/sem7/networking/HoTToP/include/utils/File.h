#ifndef HOTTOP_FILE_H
#define HOTTOP_FILE_H

#include <string>
using std::string;

class File{
public:
	static bool exists(const string& path);
	static bool isDir(const string& path);
};

#endif
