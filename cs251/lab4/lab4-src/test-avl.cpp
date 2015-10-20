
#include "avl-dictionary.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>

int
main( int argc, char **argv)
{
	printf("-----------------------------------\n");
	printf("Running test-avl\n");
	AVLDictionary * dict= new AVLDictionary();

	int max = 10000;
	int i;
	for ( i = 0; i < max; i++) {
		char key[20];
		long k = i%79;
		sprintf(key, "k%ld", k);
		dict->addRecord(key, (void*) k);
	}

	for ( i = 0; i < max; i++) {
		char key[20];
		int k = i%79;
		if (k%2==0) {
			// Remove even keys
			sprintf(key, "k%d", k);
			dict->removeElement(key);
		}
	}

	for ( i = 0; i < max; i++) {
		char key[20];
		int k = i%79;
		sprintf(key, "k%d", k);
		void * data = dict->findRecord(key);
		if (k%2==0) {
			// Entry should not be there
			assert(data==NULL);
		}
		else {
			assert ((long)data == k);
		}
	}

dict->print();
	dict->check();

	printf(">>> test-avl passed\n\n");

}
