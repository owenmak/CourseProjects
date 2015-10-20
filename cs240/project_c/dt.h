#ifndef _DT_HEADER_
#define _DT_HEADER_

/*
 * This function builds a decision tree.
 *
 * @param tbl is the table from which the decision tree should be built
 * @param tree is where the decision tree should be stored
 */
void dt_build(Table *tbl, Tree *tree);

/*
 * This function should be passed to t_free() with the decision tree
 * to free all the memory allocated for your decision tree.
 *
 * @param data is the data that will be freed
 */
void dt_free(void *data);

/*
 * This function should be passed to t_print() to print your tree. The tree
 * should be printed as follows:
 * 
 * colname=value
 *  C:class
 *  etc..
 *
 * @param data is the data to be printed
 */
void dt_print(void *data);

/* Holds the data in each field. */
typedef union field { char *s; double d; } Field;

/* This struct represents a node in the decision tree. A node can be either
 * a node internal to the tree or a leaf. An internal node will represent a
 * split value while a leaf will represent a class. 
 */
typedef struct node {
    double entropy;         // the entropy value of this node
    Field field;            // data for this node
    char type;              // type of data this node represents (S or D)
    short leaf;             // whether or not this node is a leaf
    unsigned int class;     // the class of node
    unsigned int column;    // the column index 
} Node;

/* You should expect the names of the columns to be on the first line of the file used
 * to bulid a table. These will be single-word, non-quote encased, 
 * comma separated values, just like the fields of the table.
 * Define this variable when you create a table during your development and use this in
 * your print function to print the name of a column.
 */
extern char **colnames;

#endif
