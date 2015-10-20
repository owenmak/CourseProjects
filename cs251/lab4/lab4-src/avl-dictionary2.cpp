
// Implementation of a dictionary using an AVL tree
// AVL Trees are balanced binary trees 
//
// The code in here is used for testing and debugging purposes. 
// Read it and understand it but you do not neet to modify it.

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>

#include "avl-dictionary.h"

//
// Goes over the nodes in the tree to verify that the height and keys 
// of the AVL tree are correct. It prints a message and exits if it is not a
// valid AVL tree.
//
void
AVLDictionary::check()
{
	checkRecursive(root);
}

void
AVLDictionary::checkRecursive(AVLNode * node) {
	if (node == NULL) {
		return;
	}

	if (node->left!=NULL) {
		// Make sure that it is sorted
		if ( strcmp(node->key, node->left->key) <= 0) {
			fprintf(stderr,
				"*** NOT SORTED: parent->key=\"%s\" <= left->key=\"%s\"\n",
			       node->key, node->left->key);
			assert(0);
		}
	}

	if (node->right!=NULL) {
		// Make sure that it is sorted
		if ( strcmp(node->key, node->right->key) >= 0) {
			fprintf(stderr,
				"*** NOT SORTED: parent->key=\"%s\" >= right->key=\"%s\"\n",
				node->key, node->right->key);
			assert(0);
		}
	}

	checkRecursive(node->left);
	checkRecursive(node->right);

	// Check height
	int lHeight = 0;
	if (node->left!=0) {
		lHeight = node->left->height;
	}

	int rHeight = 0;
	if (node->right!=0) {
		rHeight = node->right->height;
	}

	int diff = lHeight - rHeight;
	if (diff<0) {
		diff = - diff;
	}

	if (diff>1) {
		fprintf(stderr,
			"*** HEIGHT DIFFERENCE > 1: key=\"%s\" lheight=%d rheight=%d\n",
			node->key, lHeight, rHeight);
		assert(0);
	}

	// Compute height
	int maxHeight = lHeight;
	if (maxHeight<rHeight) {
		maxHeight = rHeight;
	}

	if (node->height != maxHeight + 1) {
		fprintf(stderr,
			"*** WRONGH HEIGHT: key=\"%s\" height=%d should be %d\n",
			node->key, node->height, maxHeight + 1);
		assert(0);
	}
}

void
AVLDictionary::printNode(const char * s, AVLNode * node, int depth) {
	AVLNode *current = root;

	for (int i = 0; i < depth; i++) {
		printf(" ");
	}

	if (node==NULL) {
		printf("%s:NULL\n", s);
		return;
	}

	printf("%s:key=\"%s\" data=%ld height=%d\n",
	       s, node->key, (long) node->data, node->height);
	printNode("L", node->left, depth+2);
	printNode("R", node->right, depth+2);
}

void
AVLDictionary::print()
{
	printNode("ROOT", root, 0);
}

