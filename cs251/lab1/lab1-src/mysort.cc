#include "mysort.h"
#include <alloca.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
//
// Sort an array of element of any type
// it uses "compFunc" to sort the elements.
// The elements are sorted such as:
//
// if ascending != 0
//   compFunc( array[ i ], array[ i+1 ] ) <= 0
// else
//   compFunc( array[ i ], array[ i+1 ] ) >= 0
//
// See test_sort to see how to use mysort.
//
void mysort( int n,                      // Number of elements
	     int elementSize,            // Size of each element
	     void * array,               // Pointer to an array
	     int ascending,              // 0 -> descending; 1 -> ascending
	     CompareFunction compFunc )  // Comparison function.
{
	void *temp;
	temp = (void*) malloc(elementSize);
	for(int i = 0; i < n; i++) {
		for(int j = i; j < n; j++) {
			if(ascending) {
				if(compFunc((void*)((char*)array + i*elementSize), (void*)((char*)array + j*elementSize)) > 0) {
					memcpy(temp, (void*)((char*)array +i*elementSize), elementSize);
					memcpy((void*)((char*)array +i*elementSize), (void*)((char*)array +j*elementSize), elementSize);
					memcpy((void*)((char*)array +j*elementSize), temp, elementSize);

				}
			}	else {
				if(compFunc((void*)((char*)array + i*elementSize), (void*)((char*)array + j*elementSize)) < 0) {
					memcpy(temp, (void*)((char*)array +i*elementSize), elementSize);
					memcpy((void*)((char*)array +i*elementSize), (void*)((char*)array +j*elementSize), elementSize);
					memcpy((void*)((char*)array +j*elementSize), temp, elementSize);
				}
			}
		}
	}
}

