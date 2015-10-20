#include "defs_itf.h"

//DO NOT MODIFY BELOW
#define MAX_ARGS 20
#define KEY_LEN 25
#define VAL_LEN 255
//DO NOT MODIFY ABOVE

/**
 * Definitions of Global Variables
 * DO NOT MODIFY THE VARIABLE NAMES
 * UPDATE THE VALUES CORRECTLY IN YOUR FUNCTIONS
 */

//the number of args in the table
int pos;
char **keys;
char **values;


/**
 *  Check if the null-terminated string key is defined. Answer 1 if either
 * "-key" or "-key=val" were passed at the command line, 0 otherwise.
 */
int ca_defined(char key[]) {
	if( key == NULL)
		return 0;
	int len = strlen(key);
	for(int i = 0; i < pos; i++)
	{
		if((*keys + i) !=NULL)
			if(strncmp(key, *(keys + i), len) == 0)
				return 1;
	}
	return 0;
}

/**
 * If "key" is associated to "val", returns "val". 
 * Undefined behavior, if "key" is not found.
 * You may need the helper function a2p.
 */
char *ca_str_value(char key[]) {
	for(int i = 0; i < pos; i++)
	{
		if((*keys + i) != NULL)
		{
			if(strcmp(key, *(keys +i)) == 0)
				return *(values + i);
		}
	}
	return NULL;
}

/**
 * If "key" is associated to "val", returns atoi(val). If "val" is NULL,
 * returns -1.  Undefined behavior, if "key" is not found.
 */
int ca_int_value(char key[]) {
	if(ca_str_value(key) == NULL)
		return -1;
	else
		return atoi(ca_str_value(key));
}

/**
 * Parse string with length len and add it to the key-values table.
 * The string should be of format "-key=value" or "-key" where key and value are
 * non-empty. If the format does not match, do nothing.
 *
 * Note: update pos correctly. It is the index of key-value table.
 */
void process_string(int len, char string[]) {
	fprintf(stderr,"ck0");
	if(string == NULL || *string != '-' || *(string + len - 1) == '=' || *(string+1) == '=')
		return;
	fprintf(stderr,"ck0.5");
	int keyIndex = -1;
	for(int i = 0; i < len; i++)
	{
		if(*(string+i) == '=')
		{
			keyIndex = i;
			break;
		}
	}
	char *key;
	char *value;
	if(keyIndex == -1) {
		key = (malloc)(sizeof(char) * len);
		for(int i = 0; i < len - 1; i++)
			key[i] = string[i+1];
		key[len-1] = '\0';
		value = NULL;
	}
	else {
		key = (malloc)(sizeof(char) * keyIndex);
		for(int i = 0; i < keyIndex - 1; i++)
			key[i] = string[i+1];
		key[keyIndex-1] = '\0';
		value = (malloc)(sizeof(char) * (len - keyIndex));
		for(int i = 0; i < len-keyIndex - 1 ; i++)
			value[i] = string[keyIndex+1+i];
		value[len-keyIndex-1] = '\0';
	}
	if(ca_defined(key))
	{
		fprintf(stderr,"ck1");
		int i = 0;
		if(keyIndex == -1)
		{
			for(; i < pos; i++)
			{
				if(strcmp(key, *(keys + i)) == 0)
				{
					free(*(values + i));
					break;
				}
			}
			*(values + i) = NULL;
		}
		else
		{
			fprintf(stderr,"ck1.5");
			for(i = 0; i < pos; i++)
			{
				if(strcmp(*(keys + i),key) == 0)
				{
					free(*(values + i));
					break;
				}
			}
			*(values+pos) = (malloc)(sizeof(char)* (len - keyIndex));
			strcpy(*(values+pos), value);
		}
		free(key);
		free(value);
		return;
	}
	if(keyIndex == -1)
		{
			*(keys+pos) = (malloc)(sizeof(char)* (keyIndex));
			strcpy(*(keys+pos), key);
			*(values+pos) = NULL;
		}
	else
		{
			*(keys+pos) = (malloc)(sizeof(char)* (keyIndex));
			*(values+pos) = (malloc)(sizeof(char)* (len - keyIndex));
			strcpy(*(keys+pos), key);
			strcpy(*(values+pos), value);
		}
	free(key);
	free(value);
	pos++;
}

/**
 * Read and parse command line arguments. argv is an array of argc strings.
 * The format is "-key" or "-key=val" where "key" and "val" are sequences of
 * alpha-numeric characters. All other string are silently discarded.  For
 * any key, only its last definition is retained.  "-key" has a NULL value.
 */
/* NO NEED TO MODIFY. */
void ca_init(int argc, char **argv) {
	if (argc == 0 || argv == NULL) return;
	for (int i = 1; i < argc; i++)
		process_string(strlen(argv[i]), argv[i]);
}
int main(int argc, char **argv) {
	ca_init(argc,argv);
	fprintf(stderr,"%d\n",pos);
	for(int i = 0; i < pos; i++) 
		printf("Key: %s\t Value:%s\n", *(keys+i),*(values+i));
}
