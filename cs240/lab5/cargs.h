/*
* @update Jan 18, 2014
*/

/*
* Read and parse command line arguments. argv is an array of argc strings.
* The format is "-key" or "-key=val" where "key" and "val" are sequences of
* alpha-numeric characters. All other string are silently discarded. For
* any key, only its last definition is retained. "-key" has a NULL value.
*/
void ca_init(int argc, char **argv);

/*
* Check is the null-terminated string key is defined. Answer true if either
* "-key" or "-key=val" were passed at the command line.
*/
int ca_defined(char *key);

/*
* If "key" is associated to "val", returns atoi(val). If "val" is NULL,
* returns -1. Undefined behavior, if "key" is not found.
*/
int ca_int_value(char *key);

/*
* If "key" is associated to "val", returns val. Undefined behavior, if
* "key" is not found.
*/
char *ca_str_value(char *key);


