#include <server/Realm.h>

void cpy(const string& key, const string& value, void * data);

Realm::Realm(const Realm& r): users(10){
	name = r.name;
	r.users.hash_iterate(cpy, (void *)this);
}

void Realm::addUser(const string& user, const string& password){
	string p(password);
	users.set(user,p);
}

void cpy(const string& key, const string& value, void * data){
	((Realm*)(data))->addUser(key,value);
}
