#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <math.h>

/*
 * A Field is a column in a Row; It contains either a double or a char*
 */
typedef union {
  double  v;
  char*   s;
} Field;

/* 
 * A Row is an entry in a table that stores column data
 */
typedef struct row {
  int          field_count; // number of columns
  Field*       fields;      // column array
  char*        type;        // A pattern that depicts the the order of column types; Each character corresponds to the type of column at the same position
  struct row*  next;        // Pointer to the next Row
} Row;

/*
 * A Table is a data structure that stores data in Rows
 */
typedef struct table {
  char* type;               // Overall column pattern that all Rows follow
  int   row_count;          // Number of Rows
  int   field_count;        // Number of columns in each Row
  Row*  first_row;          // Pointer to the head of a linked list of Rows; Used to build array
  Row*  last_row;           // Pointer to the tail of a linked list of Rows; Used to build array
  Row** rows;               // Pointer to an array of Rows
} Table;

