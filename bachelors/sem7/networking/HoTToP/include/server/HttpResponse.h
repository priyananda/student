#ifndef HOTTOP_HTTP_RESPONSE_H
#define HOTTOP_HTTP_RESPONSE_H

#include <server/HttpErrorHandler.h>
#include <utils/ConfigManager.h>
#include <utils/HashTable.h>

class HttpResponse{
	string status;
	HashTable<string> headers;
public:

	void setStatus(const string& s){ status = s; }
	const string& getStatus(){ return status; }

	string getResponseLine(){
		const HttpErrorHandler& e = ConfigManager::getErrorHandler();
		return e.createResponseLine(e.getError(status));
	}

	const string& getValue(const string& header)const;
	void setValue(const string& header, const string& value){
		string v = value;
		headers.set(header, v);
	}

	const HashTable<string>& getHeaders(){ return headers; }

};

#endif
