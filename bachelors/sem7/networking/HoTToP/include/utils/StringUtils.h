#ifndef HOTTOP_STRING_UTILS_H
#define HOTTOP_STRING_UTILS_H

#include <string>
using std::string;

class StringUtils{
public:
	static const char pathSep;
	static string baseName(const string& path);
	static string dirName(const string& path);
	static string normalize(const string& absPath);
	static string unescape(const string& p);
};

#endif
