#include <utils/ConfigExtractor.h>
#include <utils/Exception.h>
#include <config.h>

#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/ContentHandler.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
using namespace xercesc;

#include <cstdlib>
#include <iostream>
using namespace std;

void ConfigExtractor::characters (const XMLCh *const chars, const unsigned int length){}

#define EQ(str) XMLString::equals(qname, XStr(str))

ConfigExtractor::ConfigExtractor(): state(init), pi(), re(), vars(){
}

string ConfigExtractor::getAttribute(const Attributes& a, const char * str) const {
	string val;
	int index = a.getIndex(XStr(str));
	if(index == -1)return val;
	StrX s(a.getValue(index));
	const char * value = s;

	while(*value){
		index = XMLString::indexOf(value, '$');
		if(index != -1){
			if(index){
				val += string(value, index);
				value += index;
			}
			if(value[1] == '$'){
				val += '$';
				value += 2;
			}else if(value[1] == '{'){
				int closeIndex = XMLString::indexOf(value, '}');
				if(closeIndex == -1)break;
				string key(value + 2, closeIndex - 2);
				try{
					val += vars[key];
				}catch(Exception e){
					cout<<"Invalid variable: "<<key<<endl;
				}
				value += closeIndex + 1;
			}else{
				val += '$';
				value++;
			}
		}else break;
	}

	if(*value)val += value;
	return val;
}

Types ConfigExtractor::getType(const Attributes& a) const {
	StrX s(a.getValue(XStr("type")));
	const char * type = s;
	if(XMLString::equals(type, "read"))return t_read;
	if(XMLString::equals(type, "exec"))return t_exec;
	if(XMLString::equals(type, "any"))return t_any;
	throw Exception("ConfigFile: Invalid type specified");
}

void ConfigExtractor::startElement (const XMLCh *const uri, const XMLCh *const localname, const XMLCh *const qname, const Attributes &attrs){
	StrX s = StrX(qname);
	const char * e = s;
	switch(state){
		case init:{
			if(EQ("variable")){
				string name = getAttribute(attrs, "name");
				string value = getAttribute(attrs, "value");
				cout<<"Adding variable: "<<name<<": "<<value<<endl;
				vars.set(name,value);
			}else if(EQ("ServerRoot"))ConfigManager::serverRoot = getAttribute(attrs,"value");
			else if(EQ("port"))ConfigManager::port = atoi(getAttribute(attrs,"value").c_str());
			else if(EQ("plugin")){
				state = plugin;
				ConfigManager::pInfo.push_back(PluginInfo());
				PluginInfo& last = ConfigManager::pInfo.back();
				last.setType(getType(attrs));
				string name = getAttribute(attrs, "name");
				last.setName(name);
				PluginInfo * ptr = &last;
				pi.set(name, ptr);
			}else if(EQ("handler")){
				ConfigManager::handlers.push_back(Handler());
				Handler& h = ConfigManager::handlers.back();
				h.setMatch(getAttribute(attrs, "match"));
				string name = getAttribute(attrs, "plugin");
				try{
					const PluginInfo * p = pi[name];
					h.setPluginInfo(p);
				}catch(Exception e){
					string s("Unknown plugin ");
					s += name;
					throw Exception(s);
				}
			}else if(EQ("VirtualDir")){
				state = vdir;
				ConfigManager::vDirs.push_back(VirtualDirectory());
				VirtualDirectory& v = ConfigManager::vDirs.back();
				v.setType(getType(attrs));
				v.setVPath(getAttribute(attrs,"vpath"));
				v.setRPath(getAttribute(attrs,"rpath"));
				string name = getAttribute(attrs, "realm");
				if(name == "")break;
				try{
					const Realm * r = re[name];
					v.setRealm(r);
				}catch(Exception e){
					string s("Unknown realm ");
					s += name;
					throw Exception(s);
				}
			}else if(EQ("Realm")){
				state = realm;
				ConfigManager::realms.push_back(Realm());
				Realm& r = ConfigManager::realms.back();
				string name = getAttribute(attrs, "name");
				r.setName(name);
				Realm * ptr = &r;
				re.set(name, ptr);
			}else if(EQ("error")){
				ConfigManager::errHandler.setErrorFile(getAttribute(attrs,"no"),
					getAttribute(attrs,"file"));
			}else if(EQ("index")){
				ConfigManager::indexFiles.push_back(getAttribute(attrs,"file"));
			}
			break;
		}case realm:{
			Realm& last = ConfigManager::realms.back();
			if(EQ("user"))
				last.addUser(getAttribute(attrs,"name"), getAttribute(attrs,"password"));
			break;
		}case vdir:{
			if(EQ("handler")){
				VirtualDirectory& last = ConfigManager::vDirs.back();
				Handler h;
				h.setMatch(getAttribute(attrs, "match"));
				string name = getAttribute(attrs, "plugin");
				try{
					const PluginInfo * p = pi[name];
					h.setPluginInfo(p);
				}catch(Exception e){
					string s("Unknown plugin ");
					s += name;
					throw Exception(s);
				}
				last.addHandler(h);
			}
			break;
		}case plugin:{
			PluginInfo& last = ConfigManager::pInfo.back();
			if(EQ("file"))last.setPath(getAttribute(attrs, "path"));
			else if(EQ("conf-file"))last.setConfig(getAttribute(attrs, "conf-file"));
			break;
		}
	}
}

void ConfigExtractor::endElement (const XMLCh *const uri, const XMLCh *const localname, const XMLCh *const qname){
	switch(state){
		case realm:
			if(XMLString::equals(qname, XStr("Realm"))) state = init;
			break;
		case vdir:
			if(XMLString::equals(qname, XStr("VirtualDir"))) state = init;
			break;
		case plugin:
			if(XMLString::equals(qname, XStr("plugin"))) state = init;
			break;
	}
}

void ConfigExtractor::extract(){
	cout<<VAR_HTTP_EXEC_DIR<<" "<<ConfigManager::server_dir<<endl;
	cout<<VAR_HTTP_CONFIG_DIR<<" "<<ConfigManager::config_dir<<endl;

	vars.set(string(VAR_HTTP_EXEC_DIR), ConfigManager::server_dir);
	vars.set(string(VAR_HTTP_CONFIG_DIR), ConfigManager::config_dir);
	SAX2XMLReader * reader;

	XMLPlatformUtils::Initialize();
	reader = XMLReaderFactory::createXMLReader();

	reader->setContentHandler(this);
	reader->setExitOnFirstFatalError(true);
	reader->setFeature(XMLUni::fgSAX2CoreValidation, false);

	string configFile = ConfigManager::config_dir + "config.xml";
	cout<<"Parsing file: "<<configFile<<endl;
	reader->parse(configFile.c_str());

	delete reader;
	XMLPlatformUtils::Terminate();

	ConfigManager::vDirs.sort();
}
