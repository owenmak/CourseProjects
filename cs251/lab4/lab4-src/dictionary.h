
// Abstract class for a string dictionary

#if !defined DICTIONARY_H
#define DICTIONARY_H

// KeyType is a string
typedef const char * KeyType;

// DataType is void *
typedef void * DataType;

class Dictionary {
public:
    // Add a record to the dictionary. Returns false if key already exists
    virtual bool addRecord( KeyType key, DataType record) = 0;
    
    // Find a key in the dictionary and return corresponding record or NULL
    virtual DataType findRecord( KeyType key) = 0;

    // Removes one element from the table
    virtual bool removeElement(KeyType key) = 0;

    // Returns all the elements in the table as an array of strings.
    // *n is the size of the table and it is returned by reference
    virtual KeyType * keys(int * n)=0;
};

#endif

