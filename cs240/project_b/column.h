/* CS240s14 Project 2 column.h
 *
 * The following api is to be implemented by the student in column.c.
 * Passing null parameters must not produce segfaults, 
 * but can otherwise result in undefined behavior.
 */

//Represents a column. To be defined by the student.
typedef struct column Column;

/* Initializes a new column from the given data. fields and classes are arrays of size n, 
 * with the ith field corresponding to the ith class.
 */
Column *make_double_column(double *fields, unsigned int *classes, unsigned int n);

/* Initializes a new column from the given data. fields and classes are arrays of size n,
 * with the ith field corresponding to the ith class.
 */
Column *make_string_column(char **fields, unsigned int *classes, unsigned int n);

/* Frees all memory associated with the given column.
 */ 
void free_column(Column *column);

/* Determines if the rows contain only one unique field value. 
 * Returns false (0) if not--true otherwise.
 */ 
int has_single_value(Column *column);

/* Determines if the rows contain only one unique class.
 * Returns false (0) if not--true otherwise.
 */ 
int is_impossible_split(Column *column);

/* Calculates the entropy of the given column.
 * See the handout for the entropy formula.
 */ 
double calc_entropy(Column *column);

/* Returns the best field value to split the given column on. 
 * Assumes that the column can be split and has more than one field value.
 *
 * The best split-value will produce two columns with the least weighted sum of their entropies.
 * When splitting by double, the first column contains all rows with fields less than or equal to the split-value, 
 * and the second column contains the remaining fields.
 */ 
double find_double_split_value(Column *column);

/* Returns the best field value to split the given column on. 
 * Assumes that the column can be split and has more than one field value.
 *
 * The best split-value will produce two columns with the least weighted sum of their entropies.
 * When splitting by string, the first column contains all rows with fields equal to the split-value, 
 * and the second column contains the remaining fields.
 */ 
char *find_string_split_value(Column *column);
