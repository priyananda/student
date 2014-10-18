#include <server/Handler.h>
#include <utils/Exception.h>

Handler::Handler(): pInfo(0), compiled(false), match(""){
}

Handler::Handler(const Handler& h): compiled(0), pInfo(0){
	setMatch(h.getMatch());
	setPluginInfo(h.getPluginInfo());
}

bool Handler::check(const string& str) const {
	return regexec(&cp,str.c_str(),0,0,0) == 0;
}

void Handler::clean(){
	if(!compiled)return;
	regfree(&cp);
	match = "";
	compiled = false;
}

void Handler::setMatch(const string& str){
	clean();
	match = str;
	if(str == "")return;
	if(regcomp(&cp,str.c_str(),REG_EXTENDED))
		throw Exception("Invalid RE for handler");
	compiled = true;
}

Handler::~Handler(){
	clean();
}
