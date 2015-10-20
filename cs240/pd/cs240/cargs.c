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
		if(keys[i] != NULL) {
			if(strncmp(key, keys[i], len) == 0)
				return 1;
		}
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
		if(keys[i] != NULL) {
			if(strcmp(key, keys[i]) == 0)
				return values[i];
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
	if(string == NULL || string[0] != '-' || string[len - 1] == '=' || string[1] == '=')
		return;
	int keyIndex = -1;
	for(int i = 0; i < len; i++)
	{
		if(string[i] == '=')
		{
			keyIndex = i;
			break;
		}
	}
	char *key;
	char *value;
	key = (char*)(malloc)(sizeof(char) * (len+10));
	value = (char*)(malloc)(sizeof(char) * (len+10));
	if(keyIndex == -1) {
//		key = (char*)(malloc)(sizeof(char) * (len)); // malloc here
		for(int i = 0; i < len - 1; i++)
			key[i] = string[i+1];
		key[len-1] = '\0';
		value = NULL;
	}
	else {
//		key = (char*)(malloc)(sizeof(char) * keyIndex); // malloc here
		for(int i = 0; i < keyIndex - 1; i++)
			key[i] = string[i+1];
		key[keyIndex-1] = '\0';
//		value = (char*)(malloc)(sizeof(char) * (len - keyIndex)); // malloc here
		for(int i = 0; i < len-keyIndex - 1 ; i++)
			value[i] = string[keyIndex+1+i];
		value[len-keyIndex-1] = '\0';
	}
	if(ca_defined(key))
	{
		int i = 0;
		if(keyIndex == -1)
		{
			for(; i < pos; i++)
			{
				if(strcmp(key, *(keys + i)) == 0)
				{
					free(values[i]);
					break;
				}
			}
			values[i] = NULL;
		}
		else
		{
			for(i = 0; i < pos; i++)
			{
				if(strcmp(*(keys + i),key) == 0)
				{
					if(values[i] != NULL) {
						free(values[i]);
					}
					break;
				}
			}
			values[pos] = (char*)malloc(sizeof(char)* (len - keyIndex)); // malloc here
			strcpy(*(values+pos), value);
		}
		free(key);
		free(value);
		return;
	}
	else {
		if(keyIndex == -1)
			{
				keys[pos] = (char*)(malloc)(sizeof(char)* len); // malloc here
				strcpy(keys[pos], key);
				*(values+pos) = NULL;
			}
		else
			{
				keys[pos] = (char*)malloc(sizeof(char)* (len)); // malloc here
				values[pos] = (char*)malloc(sizeof(char)* (len)); // malloc here
				strcpy(*(keys+pos), key);
				strcpy(*(values+pos), value);
			}
		free(key);
		free(value);
		pos++;
	}
}

/**
 * Read and parse command line arguments. argv is an array of argc strings.
 * The format is "-key" or "-key=val" where "key" and "val" are sequences of
 * alpha-numeric characters. All other string are silently discarded.  For
 * any key, only its last definition is retained.  "-key" has a NULL value.
 */
/* NO NEED TO MODIFY. */
void ca_free() {
	for(int i = 0; i < pos; i++) {
		free(keys[pos]);
		if(values[pos]!=NULL) {
			free(values[pos]);
		}
	}
	free(keys);
	free(values);
}
void ca_init(int argc, char **argv) {
	if (argc == 0 || argv == NULL) return;
	keys = (char**)malloc(sizeof(char*)*argc);
	values = (char**)malloc(sizeof(char*)*argc);
	for (int i = 1; i < argc; i++)
		process_string(strlen(argv[i]), argv[i]);
} /*
int main(int argc, char **argv) {
	ca_init(argc,argv);
	for(int i = 0; i < pos; i++) 
		printf("Key: %s\t Value:%s\n", *(keys+i),*(values+i));
	ca_free();
} */
