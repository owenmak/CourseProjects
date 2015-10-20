
// Implementation of a dictionary using an AVL tree
// AVL Trees are balanced binary trees 

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>

#include "avl-dictionary.h"

bool debug = false;

// Constructor
AVLDictionary::AVLDictionary()
{
	root = NULL;
	nElements = 0;
}

// Add a record to the dictionary. Returns false if key already exists
bool
AVLDictionary::addRecord( KeyType key, DataType record)
{
	if ( debug) {
		printf("------------------------------------\n");
		printf("addRecord(\"%s\",%ld)\n",  key, (long) record);
		printf("---------- Before -----------------\n");
		printNode("", root, 0);
	}
	
	// Add your implementation here
/*	if(root = NULL) {
		AVLNode *n = new AVLNode;
		n->key = strdup(key);
		n->data = record;
		n->parent = NULL;
		n->left = NULL;
		n->right = NULL;
		n->height = 1;
		return true;
	}*/
    AVLNode* current = root;
    AVLNode* previous = NULL;
    while(current != NULL) {
        previous = current;
        int comp = strcmp(key, current->key);
        if(comp == 0) {
            current->data = record;
			return false;
		}
        else if(comp > 0) {
            current = current->right;
        }
        else
            current = current->left;
    }
	AVLNode *n = new AVLNode;
	n->key = strdup(key);
	n->data = record;
	n->left = NULL;
	n->right = NULL;
	n->height = 1;
	n->parent = previous;
	if(previous == NULL) {
		root = n;
		return true;
	}
	if(strcmp(previous->key, key) > 0) 
		previous->left = n;
	else
		previous->right = n;
	AVLNode *m = n->parent;
	while(m != NULL) {
		int maxheight = 0;
		if(m->left != NULL)
			maxheight = m->left->height;
		if(m->right != NULL && m->right->height > maxheight)
			maxheight = m->right->height;
		m->height = 1 + maxheight;
		m = m->parent;
	}
	restructure(n);
	
	//Find node to insert into 
	//Node does not exist. Create it.
	//Height might not be valid anymore.
	//We need to restructure .

	if ( debug) {
		printf("---------- Before Restructure -----------------\n");
		printNode("", root, 0);
	}
	
	// Call restructure

	if (debug) {
		checkRecursive(root);
		
		printf("---------- After Restructure -----------------\n");
		printNode("", root, 0);
	}
		
	return true;
}

void
AVLDictionary::restructure(AVLNode * n) {
	AVLNode *z = n->parent;
	while(z != NULL) {
		int hleft = 0;
		if(z->left != NULL) {
			hleft = z->left->height;
		}
		int hright = 0;
		if(z->right != NULL) {
			hright = z->right->height;
		}
		int hdiff = hleft - hright;
		if(hdiff < 0)
			hdiff = -1 * hdiff;
		if(hleft > hright) 
			z->height = 1 + hleft;
		else
			z->height = 1 + hright;
		if(hdiff <= 1) {
			z = z->parent;
			continue;
		}
		AVLNode *y = NULL;
		int maxh = 0;
		if(z->left != NULL) {
			y = z->left;
			maxh = y->height;
		}
		if(z->right != NULL && (z->right->height > maxh)) {
			y = z->right;
			maxh = y->height;
		}
		assert(y != NULL);
		AVLNode *x = NULL;
		maxh = 0;
		if(y->left != NULL) {
			x = y->left;
			maxh = x->height;
		}
		if(y->right != NULL && (y->right->height > maxh)) {
			x = y->right;
			maxh = x->height;
		}
		assert(x != NULL);
		AVLNode *t0,*t1,*t2,*t3;
		AVLNode *a, *b, *c;
		if(z->right == y) {
			if(y->right == x) {
				a = z;
				b = y;
				c = x;
				t0 = a->left;
				t1 = b->left;
				t2 = c->left;
				t3 = c->right;
			}
			else {
				a = z;
				b = x;
				c = y;
				t0 = a->left;
				t1 = b->left;
				t2 = b->right;
				t3 = c->right;
			}
		}
		else {
			if(y->left == x) {
				a = x;
				b = y;
				c = z;
				t0 = a->left;
				t1 = a->right;
				t2 = b->right;
				t3 = c->right;
			}
			else {
				a = y;
				b = x;
				c = z;
				t0 = a->left;
				t1 = b->left;
				t2 = b->right;
				t3 = c->right;
			}
		}
		AVLNode *p = z->parent;
		if(p == NULL)
			root = b;
		else {
			if(p->left == z)
				p->left = b;
			else
				p->right = b;
		}
		b->parent = p;
		b->left = a;
		b->right = c;
		a->parent = b;
		a->left = t0;
		a->right = t1;
		c->parent = b;
		c->left = t2;
		c->right = t3;
		if(t0 != NULL)
			t0->parent = a;
		if(t1 != NULL)
			t1->parent = a;
		if(t2 != NULL)
			t2->parent = c;
		if(t3 != NULL)
			t3->parent = c;
		maxh = 0;
		if(a->left != NULL)
			maxh = a->left->height;
		if(a->right != NULL && a->right->height > maxh)
			maxh = a->right->height;
		a->height = maxh + 1;
		maxh = 0;
		if(b->left != NULL)
			maxh = b->left->height;
		if(b->right != NULL && b->right->height > maxh)
			maxh = b->right->height;
		b->height = maxh + 1;
		maxh = 0;
		if(c->left != NULL)
			maxh = c->left->height;
		if(c->right != NULL && c->right->height > maxh)
			maxh = c->right->height;
		c->height = maxh + 1;
		
	}
	
	//Balance the tree starting at n 

	//Go upwards until root is found

        // See class notes

	// Add your implementation here
}

// Find a key in the dictionary and return corresponding record or NULL
DataType
AVLDictionary::findRecord( KeyType key)
{
	AVLNode* current = root;
	AVLNode* previous = NULL;
	while(current != NULL) {
		previous = current;
		int comp = strcmp(key, current->key);
		if(comp == 0)
			return current->data;
		else if(comp > 0) {
			current = current->right;
		}
		else
			current = current->left;
	}
	return NULL;
}

// Removes one element from the dictionary
bool
AVLDictionary::removeElement(KeyType key)
{
	if (debug) {
		printf("------------------------------------\n");
		printf("removeElement(\"%s\")\n",  key);
		printf("---------- Before -----------------\n");
		printNode("", root, 0);
	}
    AVLNode* current = root;
    AVLNode* previous = NULL;
    while(current != NULL) {
        previous = current;
        int comp = strcmp(key, current->key);
        if(comp == 0) {
			AVLNode *m;
			if(current->left == NULL && current->right == NULL) { // a leaf
				if(current->parent == NULL) {
					root = NULL;
					return true;
				}
				else {
					if(current->parent->left == current)
						current->parent->left = NULL;
					else
						current->parent->right = NULL;
					m = current->parent;
				}
			}
			else if(current->left == NULL && current->right != NULL) { // has a right child
				if(current->parent == NULL) {
					root = current->right;
					current->right->parent = NULL;
					return true;
				}
				else {
					if(current->parent->left == current) {
						current->parent->left = current->right;
						current->right->parent = current->parent;
					}
					else {
						current->parent->right = current->right;
						current->right->parent = current->parent;
					}
					m = current->parent;
				}
			}
			else if(current->right == NULL && current->left != NULL) { // has a left child
				if(current->parent == NULL) {
					root = current->left;
					current->left->parent = NULL;
					return true;
				}
				else {
					if(current->parent->left == current) {
						current->parent->left = current->left;
						current->left->parent = current->parent;
					}
					else {
						current->parent->right = current->left;
						current->right->parent = current->parent;
					}
					m = current->parent;
				}
			}
			else { // has two children
				AVLNode* closeNode = current->right;
				while(closeNode->left != NULL)
					closeNode = closeNode->left;
				closeNode->left = current->left;
				m = closeNode->parent;
				closeNode->parent->left = NULL;
				closeNode->parent = current->parent;
				closeNode->right = current->right;
				if(current->parent->left == current)
					current->parent->left = closeNode;
				else
					current->parent->right = closeNode;
			}
//			AVLNode *m = current->parent;
			while(m != NULL) {
				int maxheight = 0;
				if(m->left != NULL)
					maxheight = m->left->height;
				if(m->right != NULL && m->right->height > maxheight)
					maxheight = m->right->height;
				m->height = 1 + maxheight;
				m = m->parent;
			}
			restructure(current->parent);
			delete(current);
            return true;

		}
        else if(comp > 0) {
            current = current->right;
        }
        else
            current = current->left;
    }
    return false;
	// Add your implementation here
	
	if (debug) {
		printf("---------- After -----------------\n");
		printNode("", root, 0);

		checkRecursive(root);
	}
	
	return true;
}

// Returns all the elements in the table as an array of strings.
// *n is the size of the table and it is returned by reference
KeyType *
AVLDictionary::keys(int * n)
{
	KeyType * a = (KeyType *) malloc(nElements * sizeof(KeyType));
	*n = 0;
	addKeysRecursive(root, a, n);

	return a;
}

// Add keys recursively
void
AVLDictionary::addKeysRecursive(AVLNode * node, KeyType * a, int * n) {
	if (node==NULL) {
		return;
	}
	
	a[*n] = node->key;
	(*n)++;
	addKeysRecursive(node->left, a, n);
	addKeysRecursive(node->right, a, n);
}

