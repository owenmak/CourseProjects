/*
 * Opens a file identified by NULL-terminated string fn for reading.  Has
 * undefined behavior if called more than once or if the file can not be
 * openened.
 */
void rd_open(char *fn);

/*
 * Returns the next character in the input file or EOF. Has undefined
 * behavior if the file is not open.
 */
int rd_getchar();

/*
 * Parse the character array buf (from "from" index to "to" index, inclusive)
 * to extract a string discarding leading and trailing spaces and well-formed double quotes.
 * The format is:
 *   <space>*  '"' <not-quote> '"' <space>*  |
 *   <space>* <not-space-quote> ( <not-quote>* <not-space-quote> )? <space>*
 * where <space> is a space character, <not-quote> is any ASCII character
 * other than comma or a double quote, <not-space-quote> excludes spaces,
 * commas, and double quotes. A \C{*} means zero or more occurences, \C{?}
 * means zero or one.  If the string does not conform to this format return
 * NULL. The string returned is a newly allocated that is zero terminated.
 */
char *rd_parse_string(char buf[], int from, int to);

/*
 * Parse the character array buf (from "from" index to "to" index, inclusive) 
 * to extract a double discarding leading and trailing spaces. 
 * The format for a number is:
 *  <space>* ('+' | '-')?  (<digit>* '.')? <digit>+ <space>*
 * where <space> is a space character, <digit> is a single digit.  If the
 * buf does not contain a number, err is set to 1 and the return value is
 * undefined. Otherwise, the value of the number is returned and err is set
 * to 0.
 */
double rd_parse_number(char buf[], int from, int to, int *err);

/*
 * Return the number of comma separated values in the array buf.  end has
 * the length of the buffer. Returns -1 if it cannot calculate due to
 * odd number of double quotes.
 */
int rd_num_fields(char buf[], int end );

/*
 * Scan a sequence of characters from cur to end in buf[] and return the
 * position in the array of the first comma encountered (or the null terminator). Return -1 if there is an uneven number of double quotes.
 */
int rd_field_length(char buf[], int cur, int end );
