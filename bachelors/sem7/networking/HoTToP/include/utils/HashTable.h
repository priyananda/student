#ifndef HOTTOP_HASHTABLE_H
#define HOTTOP_HASHTABLE_H

#define DEFAULT_HASH_SIZE 20

#include <utils/Exception.h>
#include <string>
using std::string;

/*
	Implements a static hashtable of <string, T>
*/
template <class T> class HashTable{
	struct Link{
		Link * next;
		string key;
		T value;
	};
	int n;
	Link ** links;

	int hash(const string& str) const;
public:
	typedef void (*iter_func)(const string& key, T& value, void * data);
	typedef void (*const_iter_func)(const string& key, const T& value, void * data);

	/*
		Creates a HashTable with table size tableSize.
	*/
	HashTable(int tableSize = DEFAULT_HASH_SIZE);

	void set(const string& str, T& value);
	bool contains(const string& key) const;

	const T& operator[](const string& str ) const;
	T& operator[](const string& str);

	~HashTable();

	void hash_iterate(iter_func f, void * data);
	void hash_iterate(const_iter_func f, void * data)const;
};

template<class T>
int HashTable<T>::hash(const string& key) const {
	register unsigned int hashValue = 0, length = key.length();
	register const char * k = key.c_str();

	for(int i = 0; i < length; i++)
		hashValue += (k[i] >> 5) + (k[i] << 5) * i;

	return hashValue % n;
}

template<class T>
HashTable<T>::HashTable(int tableSize): n(tableSize){
	links = new Link*[n];
	if(!links)
		throw Exception("Out of memory");
	for(int i = 0;i < n;i++)links[i] = NULL;
}

template<class T>
void HashTable<T>::set(const string& key, T& value){
	int hVal = hash(key);
	Link *head = links[hVal], *prev = 0;

	while(head && head->key < key)head = (prev = head)->next;

	//Key already exists
	if(head && head->key == key){
		head->value = value;
		return;
	}

	Link * link = new Link();
	if(prev == 0){// Empty list or insert First
		links[hVal] = link;
	}else{// insert 2..N
		prev->next = link;
	}

	link->next = head;
	link->key = key;
	link->value = value;
}

template<class T>
bool HashTable<T>::contains(const string& key) const{
	Link *head = links[hash(key)];

	while(head && head->key < key) head = head->next;

	return head && head->key == key;
}

template<class T>
const T& HashTable<T>::operator [] (const string& key) const {
	Link *head = links[hash(key)];

	while(head && head->key < key) head = head->next;

	if(head && head->key == key)
		return head->value;
	throw Exception("HashTable: invalid key");
}

template<class T>
T& HashTable<T>::operator [] (const string& key){
	Link *head = links[hash(key)];

	while(head && head->key < key) head = head->next;

	if(head && head->key == key)
		return head->value;
	throw Exception("HashTable: invalid key");
}

template<class T>
HashTable<T>::~HashTable(){
	Link *head, *prev;
	for(int i = 0;i < n;i++){
		head = links[i];
		while(head){
			head = (prev = head)->next;
			delete prev;
		}
	}
	delete [] links;
}

template<class T>
void HashTable<T>::hash_iterate(iter_func func, void * data){
	Link * head;
	for(int i = 0;i < n;i++){
		for(head = links[i];head;head = head->next){
			func(head->key, head->value,data);
		}
	}
}

template<class T>
void HashTable<T>::hash_iterate(const_iter_func func, void * data) const {
	Link * head;
	for(int i = 0;i < n;i++){
		for(head = links[i];head;head = head->next){
			func(head->key, head->value,data);
		}
	}
}

//template<class T1,class T2>void hash_iterate(HashTable<T1>& h, T2 obj);
#endif
