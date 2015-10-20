#ifndef _TABLE_
#define _TABLE_
/*
 * returns the type of the table.  Undefined if called before tbl_done_building()
 */
char *tbl_type(Table *t);

/* 
 * Return a newly allocated table or NULL if unsufficient memory.
 */
Table * tbl_make();

/*
 * Prepare the table for the addition of a row with num_field values.
 * Undefined behavior if tbl_done_building() has been called.
 */
void    tbl_start_row(Table* tbl, int num_fields);

/* 
 * Add a NULL-terminated string as a field of the current row.  Undefined
 * behavior if tbl_done_building() has been called or if the row is already
 * full.
 */
void    tbl_add_string_to_row(Table* tbl, char * str) ;

/* 
 * Add a double as a field of the current row.  Undefined behavior if
 * tbl_done_building() has been called or if the row is already full.
 */
void    tbl_add_double_to_row(Table* tbl, double d) ;

/* 
 * Ends construction of the table.
 */
Table * tbl_done_building(Table* tbl) ;

/* 
 * Return the number of columns. 
 */
int     tbl_column_count( Table * tbl );

/*
 * Return the Row at index at or NULL if at is out of bounds
 */
Row *   tbl_row_at( Table * tbl, int at );

/* 
 * Return the string value from the fields array at index at of row
 */
char *  tbl_string_at( Row * row, int at);

/*
 * Return the double value from the fields array at index at of row
 */
double  tbl_double_at( Row * row, int at);

/* 
 * Prints each field of r.
 * Strings are printed in quotes
 * Doubles are printed to 2 decimal places
 */
void    tbl_print_row( Row * row );

/*
 * Print the fields of each row belonging to tbl.
 */
void    tbl_print(Table* tbl);

/* 
 * Free all memory in a table.  In no case should it cause a 
 * segmentation fault, even it NULL is passed in.
 */
void    tbl_free(Table *tbl);

/* 
 * Return the type of a column, either S or D;
 */
char    tbl_row_type_at( Row * row , int column );

/* 
 * Return the number of rows in the table
 */
int     tbl_row_count( Table * tbl );

/*
 * Return an array with all rows of this table.
 */
Row ** tbl_rows(Table *);

#endif
