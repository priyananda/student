#include <utils/StringUtils.h>
#include <utils/Exception.h>
#include <sstream>

#include <list>
using std::list;

const char StringUtils::pathSep = '/';

string StringUtils::normalize(const string& apath){
	// Absolute path only.
	if(apath[0] != pathSep)
		 throw Exception(string("Absolute path only: ") + apath);

	const char * path = apath.c_str();
	char * out = new char[apath.length() + 1];

	list<int> slashes;
	int rIndex = 0, wIndex = 0;

	while(path[rIndex]){
		if(path[rIndex] == pathSep){
			while(path[++rIndex] == pathSep);
			if(path[rIndex] == '.' && 
				(path[rIndex + 1] == pathSep || !path[rIndex + 1]) )++rIndex;
			else if(path[rIndex] == '.'
					&& path[rIndex + 1] == '.'
					&& (path[rIndex + 2] == pathSep || !path[rIndex + 2])){
				rIndex += 2;
				if(slashes.size() != 0){
					wIndex = slashes.back();
					slashes.pop_back();
				}
			}
			if(wIndex && out[wIndex - 1] == pathSep)continue;
			out[wIndex] = pathSep;
			slashes.push_back(wIndex++);
		}else
			out[wIndex++] = path[rIndex++];
	}

	out[wIndex++] = 0;
	string ret(out);
	delete [] out;
	return ret;
}

string StringUtils::baseName(const string& path){
	if(path[0] != pathSep)
		throw Exception(string("Absolute path only") + path);

	int index = path.length();

	if(index == 1)return path;	// Trivial "/"
	if(path[index - 1] == pathSep){
		index = path.rfind(pathSep, index - 2);
		return path.substr(index + 1, path.length() - 2 - index);
	}
	index = path.rfind(pathSep);
	return path.substr(index + 1);
}

string StringUtils::dirName(const string& path){
	if(path[0] != pathSep)
		throw Exception(string("Absolute path only") + path);

	int index = path.length();

	if(index == 1)return path;	// Trivial "/"
	if(path[index - 1] == pathSep)
		index = path.rfind(pathSep, index - 2);
	else
		index = path.rfind(pathSep);
	if(index == 0)return string("/");
	return path.substr(0,index);
}

static char hex2char(const char ch){
	if(ch >= '0' && ch <= '9')return ch - '0';
	if(ch >= 'a' && ch <= 'f')return ch - 'a' + 10;
	if(ch >= 'A' && ch <= 'F')return ch - 'A' + 10;
	return 0;
}

string StringUtils::unescape(const string& str){
	char ch;
	const char * s = str.c_str();
	std::ostringstream o;
	o.unsetf(std::ios::skipws);
	while(*s){
		switch(*s){
			case '+':ch = ' ';break;
			case '%':
				ch = hex2char(*++s);
				ch = (ch << 4) | hex2char(*++s);
				break;
			default:
				ch = *s;
		}
		++s;
		o<<ch;
	}
	return string(o.str());
}
