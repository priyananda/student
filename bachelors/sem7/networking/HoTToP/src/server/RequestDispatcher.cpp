#include <server/RequestDispatcher.h>
#include <server/HeaderParser.h>
#include <server/Plugin.h>

#include <utils/StringUtils.h>
#include <utils/ConfigManager.h>
#include <utils/File.h>

#include <list>
using std::list;

/*
	TODO:
	1) Replace all returns with appropriate HttpError.
	2) Send appropriate error page.
	3) Close the connection appropriately.
*/


bool RequestDispatcher::prepareRequest(){
	if(close)return false;
	clean();
	hr = new HttpRequest();
	HeaderParser parser(soc.getInputStream());

	if( parser.parseRequestLine(*hr) != 0){
		return false;
	}
	if(!parser.parseRequest(*hr)){
		return false;
	}
	return true;
}

const VirtualDirectory * RequestDispatcher::findVDir(const string& path){
	using std::list;
	const list<VirtualDirectory>& vDirs = ConfigManager::getVDirs();
	for(list<VirtualDirectory>::const_iterator i = vDirs.begin(); i != vDirs.end(); ++i){
		const string & vp = i->getVPath();
		if(path.compare(0, vp.length(), vp) == 0)
			return &(*i);
	}
	return 0;
}

int RequestDispatcher::splitPath(){
	const string& req = hr->getRequest();
	int index = req.find('?');
	string path;
	if(index != -1){
		hr->setQueryString(req.substr(index + 1));
		path = req.substr(0,index);
	}else
		path = req;
	path = StringUtils::unescape(path);
	const VirtualDirectory * vDir = findVDir(path);
	if(vDir == 0)return ENOPAGE;
	hr->setVirtualDirectory(vDir);
	path = path.replace(0,vDir->getVPath().length(), vDir->getRPath());
	hr->setPath(path);
	return 0;
}

#include <iostream>
using namespace std;

int RequestDispatcher::findFile(){
	const string& path = hr->getPath();
	bool found = false;
	string p;
	if(File::exists(path) == true){
		found = true;
		p = path;
	}else 
		p = StringUtils::dirName(path);
	for(;found == false && p != "/"; p = StringUtils::dirName(p)){
		if(File::exists(p)){
			hr->setPathInfo(path.substr(p.length()));
			found = true;
			break;
		}
	}
	if(found == false)return ENOPAGE;
	if(File::isDir(p)){
		const list<string>& index = ConfigManager::getIndexFiles();
		for(list<string>::const_iterator iter = index.begin();iter != index.end();iter++){
			string p2 = p + StringUtils::pathSep + *iter;
			if(File::exists(p2)){
				p = p2;
				break;
			}
		}
	}
	hr->setFilePath(StringUtils::normalize(p));
	return 0;
}

const Handler * RequestDispatcher::findHandler(){
	const string& file = hr->getFilePath();
	const vector<Handler>& vh = hr->getVirtualDirectory()->getHandlers();
	for(vector<Handler>::const_reverse_iterator i = vh.rbegin();i != vh.rend(); ++i)
		if(i->check(file))
			return &*i;
	const list<Handler>& h = ConfigManager::getHandlers();
	for(list<Handler>::const_reverse_iterator i = h.rbegin(); i != h.rend(); ++i)
		if(i->check(file))
			return &*i;
	return 0;
}

bool RequestDispatcher::dispatchRequest(){
	splitPath();
	findFile();
	const Handler * h = findHandler();
	if(h == 0)
		cout<<"Handler not found\n";
	else{
		const PluginInfo * pi = h->getPluginInfo();
		cout<<"Plugin: "<<pi->getName()<<endl;
		HttpResponse response;
		DynamicLoader dl(pi->getPath());
		Plugin * p = Plugin::loadPlugin(dl, *hr, response, soc);
		if(p){
			p->exec();
			delete p;
		}else
			cout<<"Load failed"<<endl;
	}
	return true;
}
