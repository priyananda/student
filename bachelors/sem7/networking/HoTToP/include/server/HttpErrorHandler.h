#ifndef HOTTOP_HTTP_ERROR_HANDLER_H
#define HOTTOP_HTTP_ERROR_HANDLER_H

#include <net/OutputStream.h>
#include <string>
#include <vector>
using std::string;
using std::vector;

#define HTTP_ERRORS_KNOWN 40

class HttpErrorHandler{
public:
	enum HttpError {
		_continue,
		switch_protocol,
		ok,
		created,
		accepted,
		non_authorative_information,
		no_content,
		reset_content,
		partial_content,
		multiple_choices,
		moved_permanently,
		found,
		see_other,
		not_modified,
		use_proxy,
		temporary_redirect,
		bad_request,
		unauthorised,
		payment_required,
		forbidden,
		not_found,
		method_not_allowed,
		not_acceptable,
		proxy_authenticatio_required,
		request_time_out,
		conflict,
		gone,
		length_required,
		precondition_failed,
		request_entity_too_large,
		unsupported_media_type,
		request_range_not_satified,
		expectation_failed,
		internal_server_error,
		not_implemented,
		bad_gateway,
		service_unavailable,
		gateway_time_out,
		version_not_supported
	};
	struct HttpErrorInfo{
		string no;
		string description;
	};
	static const HttpErrorInfo errInfo[];
private:
	vector<string> errFiles;
public:
	HttpErrorHandler();
	void setErrorFile(const string& no, const string& file);
	void sendError(const HttpError err, OutputStream& out) const;
	void reset();

	HttpError getError(const string& no) const ;
	string createResponseLine(const HttpError err) const ;
};

#endif
