#include <server/HttpErrorHandler.h>
#include <utils/Exception.h>
#include <unistd.h>
#include <fcntl.h>
#include <sstream>

const HttpErrorHandler::HttpErrorInfo HttpErrorHandler::errInfo [] = {
	{"100", "Continue"},
	{"101", "Switching Protocols"},
	{"200", "Ok" },
	{"201", "Created"},
	{"202", "Accepted"},
	{"203", "Non-Authorative Information"},
	{"204", "No Content"},
	{"205", "Reset Content"},
	{"206", "Partial Content"},
	{"300", "Multiple Choices"},
	{"301", "Moved Permanently"},
	{"302", "Found"},
	{"303", "See Other"},
	{"304", "Not Modified"},
	{"305", "Use Proxy"},
	{"307", "Temporary Redirect"},
	{"400", "Bad Request"},
	{"401", "Unauthorised"},
	{"402", "Payment Required"},
	{"403", "Forbidden"},
	{"404", "Not Found"},
	{"405", "Method Not Allowed"},
	{"406", "Not Acceptable"},
	{"407", "Proxy Authentication required"},
	{"408", "Request Time-out"},
	{"409", "Conflict"},
	{"410", "Gone"},
	{"411", "Length Required"},
	{"412", "Precondition Failed"},
	{"413", "Request Entity too Large"},
	{"414", "Request-URI too Large"},
	{"415", "Unsupported Media Type"},
	{"416", "Requested range not satisfiable"},
	{"417", "Expectation Failed"},
	{"500", "Internal Server Error"},
	{"501", "Not Implemented"},
	{"502", "Bad Gateway"},
	{"503", "Service Unavailable"},
	{"504", "Gateway Time-out"},
	{"505", "HTTP Version not supported"},
};

HttpErrorHandler::HttpErrorHandler(): errFiles(HTTP_ERRORS_KNOWN){}

void HttpErrorHandler::setErrorFile(const string& no, const string& file){
	HttpError error = getError(no);
	errFiles[int(error)] = file;
}

HttpErrorHandler::HttpError HttpErrorHandler::getError(const string& no) const{
	for(int i = 0;i < HTTP_ERRORS_KNOWN;i++)
		if(errInfo[i].no == no) return HttpError(i);
	throw Exception(string("Invalid err no: ") + no);
}

void HttpErrorHandler::reset(){
	for(int i = 0;i < HTTP_ERRORS_KNOWN;i++)
		errFiles[i] = "";
}

string HttpErrorHandler::createResponseLine(const HttpError errNo) const {
	return string("HTTP/1.1 ") + 
		errInfo[int(errNo)].no + 
		" "  + 
		errInfo[int(errNo)].description;
}

void HttpErrorHandler::sendError(const HttpError err, OutputStream& os) const {
	std::ostringstream out;
	out<<createResponseLine(err).c_str()<<"\nConnection: close\n";
	int fd;
	if((fd = open(errFiles[int(err)].c_str(),O_RDONLY)) >= 0){
		out<<"Content-type: text/html\nContent-length: "<<lseek(fd, 0,SEEK_END)<<"\n";
		lseek(fd,0,SEEK_SET);
	}
	if(true){
		out<<std::endl;
		string head = out.str();
		os.write(head.c_str(), head.length());
	}
	if(fd >= 0){
		char buff[512];
		int len;
		while( (len = read(fd, buff, 512)) > 0)
			os.write(buff,len);
		close(fd);
	}
}
