#include <stdio.h>
#include "Stack.h"

/*Stack::Stack() {
	_head = NULL;
}

Stack::~Stack() {
	ListNode *l;
	while(_head != NULL) {
		l = _head;
		while(l->_next != NULL) {
			l = l->_next;
		}
		delete(l);
	}
}*/

int Stack::pop() {
	if(_head == NULL) {
		printf("Nothing in stack!\n");
		return 0;
	}
	int value = _head->_value;
	ListNode *l = _head;
	_head = _head->_next;
	delete l;
	return value;
}

void Stack::push(int value) {
	ListNode *l = new ListNode;
	l->_next = _head;
	l->_value = value;
	_head = l;
}
