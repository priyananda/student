#ifndef HOTTOP_HEADERPARSER_H
#define HOTTOP_HEADERPARSER_H

#include <net/InputStream.h>
#include <server/HttpRequest.h>
#include <server/HttpResponse.h>

#include <string>
using std::string;

#define SUCCESS  0
#define EVERSION 1
#define EMETHOD  2

class HeaderParser{
	InputStream& is;

	string readLine();
	bool split(const string& line, string& key, string& value);

public:
	HeaderParser(InputStream& is);
	int parseRequestLine(HttpRequest& hr);
	bool parseRequest(HttpRequest& hr);
	bool parseResponse(HttpResponse& hr);
};

#endif
