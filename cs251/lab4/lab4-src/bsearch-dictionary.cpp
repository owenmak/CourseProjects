
// Implementation of a dictionary using an array and binary search
// It will inherit from the ArrayDictionary

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "bsearch-dictionary.h"
#include "Heap.h"

// Constructor
BinarySearchDictionary::BinarySearchDictionary()
{
	sorted = false;
}

bool
BinarySearchDictionary::addRecord( KeyType key, DataType record) {
	sorted = false;
	return ArrayDictionary::addRecord(key, record);
}

// Find a key in the dictionary and return corresponding record or NULL
DataType
BinarySearchDictionary::findRecord( KeyType key)
{
//	printf("Trying to find: %s\n", key);
	if (!sorted) {
		sort();
		sorted = true;
	}
	int start_num = 0;
	int end_num = currentNumber;
//	printf("currentNumber is: %d\n", currentNumber);
	while(start_num <= end_num) {
		int comp = strcmp(array[(start_num + end_num) / 2]->key, key);
		if(comp == 0) {
//			printf("found it: %d\n", (start_num + end_num)/2);
			return array[(start_num + end_num) / 2]->data;
		}
		else if(comp > 0) {
			end_num = (start_num + end_num) / 2 - 1;
		}
		else
			start_num = (start_num + end_num) / 2 + 1;
	}
//	printf("returning NULL\n");
	return NULL;
}


// Sort array using heap sort
void
BinarySearchDictionary::sort()
{
/*	printf("Before\n");
	for (int i = 0; i < currentNumber; i++) {
		printf("%s : %d\n", array[i]->key, (long)array[i]->data);
	}*/
	Heap h(maxNumber);
	for(int i = 0; i < currentNumber; i++) {
		h.insert(array[i]);
	}
	for(int i = 0; i < currentNumber; i++) {
		array[i] = h.removeMin();
	}
	
/*	printf("After\n");
	for (int i = 0; i < currentNumber; i++) {
		printf("%s : %d\n", array[i]->key, (long)array[i]->data);
	}*/
}




