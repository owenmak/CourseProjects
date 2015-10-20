/*
 * Query API
 */

/**
 * q_parse
 * This makes the query tree based on the queryText.
 * If the queryText does not conform to the grammar, return NULL.
 *
 * char *queryText - The actual text of the query
 * char **columnNames - The names of the columns in the table
 * char *column_types - the type of the table
 * int numColumns - The number of column names
 */
Tree *q_parse(char *query_text, char **column_names, char *column_types,  int num_columns);

/**
 * q_free
 * Free the given query tree
 */
void q_free(Tree *query);

/**
 * Print the Query Tree
 * Format:
 * OR
 *  big=6
 *  abc<7
 *
 * If connective, print the connective type in all caps
 * Otherwise print the field
 */
void q_print(Tree *data);

//Connective and conditional types.  Used to interpret the int that q_get_type() returns
#define OR_TYPE 0
#define AND_TYPE 1
#define EQUALS_TYPE 2
#define LESS_TYPE 3
#define GREATER_TYPE 4
#define LESS_EQUALS_TYPE 5
#define GREATER_EQUALS_TYPE 6

/**
 * Return the type of the data as per the above defines
 */
int q_get_type(void *query_data);

/**
 * Return the column index
 */
int q_get_col_index(void *query_data);

/**
 * Return the value in the data as a double
 */
double q_get_double(void *query_data);

/**
 * Return the value in the data as a string
 */
char *q_get_str(void *query_data);
