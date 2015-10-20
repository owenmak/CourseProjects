//
// Implement the List class
//

#include <stdio.h>
#include "List.h"

//
// Inserts a new element with value "val" in
// ascending order.
//
void
List::insertSorted( int val )
{
	ListNode *l;
	l = new ListNode();
	ListNode *p = _head;
	l->_value = val;
	if(p == NULL || p->_value > val) {
		_head = l;
		l->_next = p;
	}
	else {
		while(1) {
			if(p->_next == NULL) {
				p->_next = l;
				break;
			}
			if(val < p->_next->_value) {
				l->_next = p->_next;
				p->_next = l;
				break;
			}
			p = p->_next;
		}
	}
}

//
// Inserts a new element with value "val" at
// the end of the list.
//
void
List::append( int val )
{
	ListNode *l;
	l  = new ListNode();
	l->_value = val;
	ListNode *p = _head;
	while(p != NULL) {
		p = p->_next;
	}
	p->_next = l;
}

//
// Inserts a new element with value "val" at
// the beginning of the list.
//
void
List::prepend( int val )
{
	ListNode *l;
	l  = new ListNode();
	l->_value = val;
	l->_next = _head;
	_head = l;
}

// Removes an element with value "val" from List
// Returns 0 if succeeds or -1 if it fails
int 
List:: remove( int val )
{
	ListNode *l = _head;
	ListNode *p;
	while(l != NULL) {
		if(l->_value == val) {
			p->_next = l->_next;
			delete(l);
			return 0;
		}
		p = l;
		l = l->_next;
	}
	return -1;
}

// Prints The elements in the list. 
void
List::print()
{
	ListNode *l = _head;
	while(l != NULL) {
		printf("%d\n", l->_value);
		l = l->_next;
	}
}

//
// Returns 0 if "value" is in the list or -1 otherwise.
//
int
List::lookup(int val)
{
	ListNode *l = _head;
	while(l != NULL) {
		if(l->_value == val)
			return 0;
		l = l->_next;
	}
	return -1;
}

//
// List constructor
//
List::List()
{
	_head = NULL;
}

//
// List destructor: delete all list elements, if any.
//
List::~List()
{
	ListNode *l;
	while(_head != NULL) {
		l = _head;
		while(l->_next != NULL) {
			l = l->_next;
		}
		delete(l);
	}
}

