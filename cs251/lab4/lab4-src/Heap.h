#include <assert.h>
#include <stdio.h>
#include "array-dictionary.h"
class Heap {
    // Assume that keys are int and no elements are stored with key.
    // This data structure can be modified to support elements.

    int maxSize; // Max size of the array.
    ArrayDictionaryNode ** heap;
    int last; // One after last element.

    public:
    Heap(int maxSize);
    
    inline int left(int p) {
      return 2*p+1;
    }

    inline int right(int p) {
      return 2*p+2;
    }

    inline int theParent(int c) {
      return (c-1)/2;
    }

    void insert(ArrayDictionaryNode* key);

    ArrayDictionaryNode* removeMin();

    ~Heap();
};

Heap::Heap(int maxSize) {
  this->maxSize = maxSize;
  heap = new ArrayDictionaryNode* [maxSize];
  last = 0;
}

void 
Heap::insert(ArrayDictionaryNode* key) {
  // Make sure there is space in the heap.
  assert(last < maxSize);
  
  heap[last] = key;
  last++;
  
  // Apply upheap.
  int child = last-1;
  int parent = theParent(child);
  while(child > 0) {  // while we don't reach the root
    if(strcmp(heap[child]->key, heap[parent]->key) >0) {
      // No swap needed
      break;
    }
    // Swap is needed. Swap parent and child.
    ArrayDictionaryNode* tmp = heap[child];
    heap[child]= heap[parent];
    heap[parent] = tmp;
    
    child = parent;
    parent = theParent(child);
  }
}

ArrayDictionaryNode* Heap::removeMin() {
  // Make sure there are elements in the heap.
  assert(last > 0);
  
  // Get minimum key from the root of the heap.
  ArrayDictionaryNode* minKey = heap[0];
  
  // Replace root with (last-1) element.
  heap[0] = heap[last-1];
  last--;
  
  // Apply downheap.
  int parent = 0;
  int ileft = left(parent);
  int iright = right(parent);
  
  // Downheap until we reach the bottom or swap not needed.
  while(ileft < last) {
    // Get minimum child.
    int minChild = ileft;
    
    // If right child exists and is less than the left,
    // make minChild the right child.
    if(iright < last && strcmp(heap[iright]->key, heap[ileft]->key) < 0) {
      minChild = iright;
    }
    
    // Check if swap is needed.
    if(strcmp(heap[parent]->key, heap[minChild]->key) < 0) {
      // No swap is needed.
      break;
    }
    // Swap is needed.
    ArrayDictionaryNode* tmp = heap[minChild];
    heap[minChild] = heap[parent];
    heap[parent] = tmp;
    
    // Update parent, ileft, and iright.
    parent = minChild;
    ileft = left(parent);
    iright = right(parent);
  }
  return minKey;
}

Heap::~Heap() {
  delete []heap;
}

