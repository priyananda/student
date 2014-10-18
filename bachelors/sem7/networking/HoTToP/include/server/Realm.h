#ifndef HOTTOP_REALM_H
#define HOTTOP_REALM_H

#include <string>
#include <utils/HashTable.h>

/**
	Realm is a grouping used to perform authentication for accessing the content.
	A Realm has a name and list of users and their passwords.
*/
using std::string;
class Realm{
	string name;
	HashTable<string> users;
public:
	Realm(): users(10){}
	Realm(const Realm& r);

	void setName(const string& n){name = n;}
	const string& getName() const { return name;}

	void addUser(const string& user, const string& password);
	const string& getPassword(const string& user) const { return users[user]; }
};

#endif
