#ifndef HOTTOP_CONFIG_EXTRACTOR_H
#define HOTTOP_CONFIG_EXTRACTOR_H

#include <utils/ConfigManager.h>
#include <utils/HashTable.h>

#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/ContentHandler.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>

using namespace xercesc;

class ConfigExtractor: public ContentHandler {
public:
	enum parse_state {init, vdir, plugin, realm };
private:
	parse_state state;
	HashTable<string> vars;
	HashTable<PluginInfo *> pi;
	HashTable<Realm *> re;
public:
	ConfigExtractor();
	virtual void characters (const XMLCh *const chars, const unsigned int length);
	virtual void startDocument(){}
	virtual void endDocument(){}

	virtual void startElement (const XMLCh *const uri, const XMLCh *const localname, const XMLCh *const qname, const Attributes &attrs);
	virtual void endElement (const XMLCh *const uri, const XMLCh *const localname, const XMLCh *const qname);

	virtual void ignorableWhitespace(const XMLCh *const chars, const unsigned int length = 0){}
	virtual void processingInstruction(const XMLCh *const target, const XMLCh *const data){}

	virtual void setDocumentLocator(const Locator* const loc){}

	virtual void startPrefixMapping(const XMLCh *const prefix, const XMLCh *const uri){}
	virtual void endPrefixMapping(const XMLCh *const prefix){}

	virtual void skippedEntity(const XMLCh *const prefix){}

	string getAttribute(const Attributes& a,const char * str) const;
	Types getType(const Attributes& a) const;

	void extract();
};

class StrX {
	char* fLocalForm;
public :
	StrX(const XMLCh* const toTranscode){
		fLocalForm = XMLString::transcode(toTranscode);
	}

	~StrX(){
		XMLString::release(&fLocalForm);
	}

	operator const char *() const{
		return fLocalForm;
	}
};

class XStr{
	XMLCh * xForm;
public:
	XStr(const char * const str){
		xForm = XMLString::transcode(str);
	}

	~XStr(){
		XMLString::release(&xForm);
	}

	operator const XMLCh *() const{
		return xForm;
	}
};

#endif
