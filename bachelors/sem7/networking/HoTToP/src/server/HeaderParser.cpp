#include <server/HeaderParser.h>
#include <sstream>
#include <cstring>
#include <cctype>

HeaderParser::HeaderParser(InputStream& i): is(i) {
}

string HeaderParser::readLine(){
	using std::ostringstream;
	using std::ios;
	ostringstream line;
	char ch;

	line.unsetf(ios::skipws);
	while(is.read(&ch,sizeof(ch)) != -1 ){
		if(ch == '\n')break;
		if(ch != '\r')line<<ch;
	}

	return string(line.str());
}

int HeaderParser::parseRequestLine(HttpRequest& req){
	string line = readLine();
	const char * r = line.c_str();

	switch(toupper(r[0])){
		case 'G':
			if(strncasecmp(r, "GET", 3) == 0){
				req.setMethod(HttpRequest::GET);
				r += 3;
				while(isspace(*r))++r;
			}else return EMETHOD;
			break;
		case 'P':
			if(strncasecmp(r, "POST", 4) == 0){
				req.setMethod(HttpRequest::POST);
				r += 4;
				while(isspace(*r))++r;
			}else return EMETHOD;
			break;
		default:
			return EMETHOD;
	}

	string res;
	while(!isspace(*r))res += *r++;
	while(isspace(*r))++r;

	req.setRequest(res);

	if(strncasecmp(r, "HTTP/1.", 7) == 0){
		r += 7;
		if(strcmp(r, "0") == 0)req.setVersion(HttpRequest::V10);
		else if(strcmp(r, "1") == 0)req.setVersion(HttpRequest::V11);
		else return EVERSION;
	}else return EVERSION;

	return SUCCESS;
}

bool HeaderParser::parseRequest(HttpRequest& req){
	string line;
	string key, value;

	while( (line = readLine()) != ""){
		if(split(line, key, value) == false)return false;
		req.setValue(key, value);
	}

	return true;
}

bool HeaderParser::parseResponse(HttpResponse& res){
	string line;
	string key, value;

	while( (line = readLine()) != ""){
		if(split(line, key, value) == false)return false;
		res.setValue(key, value);
	}

	return true;
}

bool HeaderParser::split(const string& line, string& key, string& value){
	const char * l = line.c_str();
	if(!isspace(*l)){
		int index = line.find(':');
		if(index == -1)return false;
		value = "";
		key = line.substr(0,index);
		l += index + 1;
	}else value += ' ';
	while(isspace(*l))++l;
	value += l;
	return true;
}
