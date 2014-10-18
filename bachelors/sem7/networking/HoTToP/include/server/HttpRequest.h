#ifndef HOTTOP_HTTP_REQUEST_H
#define HOTTOP_HTTP_REQUEST_H

#include <utils/HashTable.h>
#include <server/VirtualDirectory.h>

class HttpRequest{
public:
	enum RequestMethod {GET = 1, POST, TRACE, PUT, DELETE, HEAD, OPTIONS };
	enum HttpVersion { V10 = 1, V11 };
private:
	RequestMethod method;
	HttpVersion version;
	HashTable<string> headers;

	string request;		// Complete request string.
	string path;		// Request Path after vDir resolving.
	string filePath;	// Path of the file accessed.
	string pathInfo;	// Path Info [optional]
	string query;		// Query String [optional]

	const VirtualDirectory * vDir;
public:
	HttpRequest() : vDir(0) {}

	RequestMethod getMethod() const { return method; }
	void setMethod(RequestMethod m){ method = m; }

	HttpVersion getVersion() const{ return version; }
	void setVersion(HttpVersion v){ version = v; }

	void setRequest(const string& req){ request = req; }
	const string& getRequest() const { return request; }

	void setPath(const string& p){ path = p; }
	const string& getPath() const { return path; }

	void setFilePath(const string& pf){ filePath = pf; }
	const string& getFilePath() const { return filePath; }

	void setPathInfo(const string& pi){ pathInfo = pi; }
	const string& getPathInfo() const { return pathInfo; }

	void setQueryString(const string& q){ query = q; }
	const string& getQueryString() const { return query;}

	void setVirtualDirectory(const VirtualDirectory * v){ vDir = v; }
	const VirtualDirectory * getVirtualDirectory() const { return vDir; }

	const string& getValue(const string& header)const;
	void setValue(const string& header, const string& value){
		string v = value;
		headers.set(header, v);
	}

	const HashTable<string>& getHeaders(){ return headers; }
};

#endif
