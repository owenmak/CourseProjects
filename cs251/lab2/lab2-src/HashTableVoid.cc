
//
// CS251
// Implementation of a HashTable that stores void *
//
#include "HashTableVoid.h"
#include "stdlib.h"

// Obtain the hash code of a key
int HashTableVoid::hash(const char * key)
{
	int hash = 0;
	for(int i = 0; i < strlen(key); i++) {
		hash += key[i];
	}
	return hash % TableSize;
}

// Constructor for hash table. Initializes hash table
HashTableVoid::HashTableVoid()
{
	_buckets = new HashTableVoidEntry *[TableSize];
	for(int i = 0; i < TableSize; i++) {
		_buckets[i] = NULL;
	}
}

// Add a record to the hash table. Returns true if key already exists.
// Substitute content if key already exists.
bool HashTableVoid::insertItem( const char * key, void * data)
{
	int h = hash(key);
	HashTableVoidEntry *e = _buckets[h];
	while(e!=NULL) {
		if(!strcmp(e->_key, key)) {
			e->_data = data;
			return true;
		}
		e = e->_next;
	}
	e = new HashTableVoidEntry;
	e->_key = strdup(key);
	e->_data = data;
	e->_next = _buckets[h];
	_buckets[h] = e;
	return false;
}

// Find a key in the dictionary and place in "data" the corresponding record
// Returns false if key is does not exist
bool HashTableVoid::find( const char * key, void ** data)
{
	int h = hash(key);
	HashTableVoidEntry *e = _buckets[h];
	while(e != NULL) {
		if(!strcmp(e->_key, key)) {
			*data = e->_data;
			return true;
		}
		e = e->_next;
	}
	return false;
}


// Removes an element in the hash table. Return false if key does not exist.
bool HashTableVoid::removeElement(const char * key)
{
	int h = hash(key);
	HashTableVoidEntry *e = _buckets[h];
	HashTableVoidEntry *p = e;
	if(e == NULL)
		return false;
	if(!strcmp(e->_key, key)) {
		_buckets[h] = _buckets[h]->_next;
		delete e;
		return true;
	}
	e = e->_next;
	while(e != NULL) {
		if(!strcmp(e->_key, key)) {
			p->_next = e->_next;
			delete e;
			return true;
		}
		p = e;
		e = e->_next;
	}
	return false;
}

// Creates an iterator object for this hash table
HashTableVoidIterator::HashTableVoidIterator(HashTableVoid * hashTable)
{
	_hashTable = hashTable;
	_currentEntry = _hashTable->_buckets[0];
	_currentBucket = 0;
}

// Returns true if there is a next element. Stores data value in data.
bool HashTableVoidIterator::next(const char * & key, void * & data)
{
	if(_currentEntry == NULL) {
		while(_hashTable->TableSize > _currentBucket){
			_currentBucket++;
			if(_hashTable->_buckets[_currentBucket] != NULL) {
				_currentEntry = _hashTable->_buckets[_currentBucket];
				break;
			}
		}
	}
	if(_currentBucket >= _hashTable->TableSize) 
		return false;
	key = strdup(_currentEntry->_key);
	data = _currentEntry->_data;
	_currentEntry = _currentEntry->_next;
	return true;

}

