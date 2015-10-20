#ifndef _TREE_
#define _TREE_

//tree structure
typedef struct tree {
  void* data;
  struct tree* left;
  struct tree* right;
} Tree;

/*set the data on the tree node */
void  t_set_data(Tree* t, void* data) ;

/*let l be the left node of tree *t */
void  t_set_left(Tree* t, Tree* l);

/*let r be the left node of tree *t */
void  t_set_right(Tree* t, Tree* r);

/* simply return left node of the tree */
Tree* t_left(Tree* t);

/* simply return right node of the tree */
Tree* t_right(Tree* t);

/* simply return the data of the tree */
void* t_data(Tree* t);

/* make the node of the tree and allocate space for it*/
Tree* t_make();

/* 

print the whole tree in the following format

Root is printed with zero trailing spaces to the left
Every node/subtree is printed with one additional space
Below is an example for a tree with depth 2:
  Root
  <space>Left-Child
  <space><space>Left-Left-Child
  <space><space>Left-Right-Child
  <space>Right-Child 
  .... and so on ...

Use (void(* p))(function pointer) to print.

 */
void  t_print( Tree* t ,int space, void(* p)(void*) );

/* Find a node using compare function pointer p to navigate; d is the data
   to be found do f at the node. return d if found, otherwise return NULL
   f is a function pointer which returns a void pointer. 
   Hint: You could use it to print the node or perform other functions.
*/

void* t_navigate( Tree* t , void* d,  int(*p)(void*, void*), void*(*f)(void*));


/*
Frees the tree.  Uses free_function to free the data stored in a node.
*/
void t_free(Tree *t, void (*free_function)(void *));

#endif
