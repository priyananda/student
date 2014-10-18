#include <utils/DynamicLoader.h>
#include <utils/Exception.h>

#include <dlfcn.h>

DynamicLoader::DynamicLoader(const string& str){
	dlHandle = dlopen(str.c_str(), RTLD_LAZY);
	if(dlHandle == NULL)throw Exception(dlerror());
}

void * DynamicLoader::getSymbol(const string& str){
	return dlsym(dlHandle, str.c_str());
}

void DynamicLoader::close(){
	dlclose(dlHandle);
}

DynamicLoader::~DynamicLoader(){
	close();
}
