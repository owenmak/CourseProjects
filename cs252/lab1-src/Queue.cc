#include <stdio.h>
#include "Queue.h"

/*Queue::Queue() {
	_head = NULL;
}

Queue::~Queue() {
	ListNode *l;
	while(_head != NULL) {
		l = _head;
		while(l->_next != NULL) {
			l = l->_next;
		}
		delete(l);
	}
}*/

int Queue::dequeue() {
	if(_head == 0) {
		printf("Nothing in Queue!\n");
		return 0;
	}
	ListNode *l = _head;
	int value = _head->_value;
	_head = _head->_next;
	delete l;
	return value;
}

void Queue::enqueue(int value) {
	ListNode *l = new ListNode;
	l->_next = NULL;
	l->_value = value;
	ListNode *p = _head;
	if(p == NULL) {
		_head = l;
		return;
	}
	while(p->_next != NULL) {
		p = p->_next;
	}
	p->_next = l;
}
