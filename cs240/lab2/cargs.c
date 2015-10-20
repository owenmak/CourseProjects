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

//the key-value table, both should store NULL-terminated strings
char keys[ MAX_ARGS][KEY_LEN + 1];
char values[ MAX_ARGS][VAL_LEN + 1];

/**
 * a2p: transform char[] to char* No need to modify
*/
char *a2p(char c[]) { return c; }

/**
 *  Check if the null-terminated string key is defined. Answer 1 if either
 * "-key" or "-key=val" were passed at the command line, 0 otherwise.
 */
int ca_defined(char key[]) {
	if( key == NULL)
		return 0;
	for(int i = 0; i < pos; i++)
	{
		if(keys[i] != NULL)
		{
			if(strcmp(key,keys[i]) == 0)
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
		if(keys[i] != NULL)
		{
			if(strcmp(key, keys[i]) == 0)
				return a2p(values[i]);
		}
/*		for(int j = 0; j <= KEY_LEN; j++)
		{
			if(key[j] != keys[i][j])
				break;
			if(j == KEY_LEN)
			{
				if(values[i] == NULL)
					return NULL;
				else
					return a2p(values[i]);
				
			}
		} */
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
	int isNull = 1;
	int keyIndex = 0;
	if(string[0] != '-')
		return;
	for(int i = 1; i < len; i++)
	{
		if(string[i] == '=')
		{
			if((i == len - 1)||(i == 1))
				return;
			else
			{
				keyIndex = i;
				isNull = 0;
			}
		}
	}
	if(isNull)
		keyIndex = len;
	if(keyIndex > KEY_LEN || (len - keyIndex) - 1 > VAL_LEN)
		return;
	char temp[KEY_LEN];
	for(int i = 0; i < keyIndex - 1; i++)
	{
		temp[i] = string[i+1];
	}
	temp[keyIndex-1] = '\0';
	for(int i = 0; i < pos; i++)
	{
		for(int j = 0; j < keyIndex; j++)
		{
			if(keys[i][j] != temp[j])
				break;
			if(j == keyIndex - 1)
				{
					if(isNull)
					{
						for(int k = 0; k <= VAL_LEN; k++)
							values[i][k] = '\0';
					}
					else
					{
						for(int k = 0; k < len-keyIndex-1;k++)
						{
							values[i][k] = string[k+keyIndex+1];
						}
						for(int k = len-keyIndex-1; k <= VAL_LEN; k++)
							values[i][k] = '\0';
					}
					return;
				}
		}
	}
	for(int i = 0; i <= keyIndex; i++)
		keys[pos][i] = temp[i];
	if(isNull)
	{
		values[pos][0] = '\0';
	}
	else
	{
		for(int i = 0; i <= len - keyIndex - 1;i++)
			values[pos][i] = string[i+keyIndex+1];
	}
	pos++;
	for(int i = 0; i <= KEY_LEN; i++)
		temp[i] = '\0';
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
