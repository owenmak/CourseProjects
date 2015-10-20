#include "defs_itf.h"

void t_set_data(Tree* t, void* data) {
	t->data = data;
}

void t_set_left(Tree* t, Tree* l) {
	t->left = l;
}

void t_set_right(Tree* t, Tree* r) {
	t->right = r;
}

Tree* t_left(Tree* t) {
	return t->left;
}

Tree* t_right(Tree* t) {
	return t->right;
}

void* t_data(Tree* t) {
	return t->data;
}

Tree* t_make() {
	Tree *t = (Tree*)malloc(sizeof(Tree));
	t->data = NULL;
	t->left = NULL;
	t->right = NULL;
	return t;
}

void t_print( Tree* t, int space, void(* p)(void*)) {
	if(t == NULL)
		return;
	for(int i = 0; i < space; i++)
    	putchar(' ');
    p(t->data);	
	t_print(t->left,space + 1, p);
	t_print(t->right,space + 1, p);
}

void* t_navigate( Tree *t, void* d, int(*p)(void* , void*), void*(*f)(void*)) {
	if(t==NULL)
		return NULL;
	if(p(d, t->data) == 0) {
		return f(t->data);
	}
	else if(p(d, t->data) < 0)
		return t_navigate(t->left, d, p, f);
	else
		return t_navigate(t->right, d, p, f);
}

void t_free(Tree *t, void (*free_function)(void *)) {
	free_function(t->data);
	if(t->left != NULL)
		t_free(t->left, free_function);
	if(t->right != NULL)
		t_free(t->right, free_funtion);
	free(t);
}
