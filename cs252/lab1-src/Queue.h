#include "List.h"
class Queue: public List {
public:
	int current;

	void enqueue( int );
	int dequeue();
};
