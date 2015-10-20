#include <sys/types.h>
#include <stdlib.h>

/*
 * Implement the following string procedures.
 *
 * Type "man strstr" to find what each of the functions should do.
 *
 * For example, mystrcpy should do the same as strcpy.
 *
 * IMPORTANT: DO NOT use predefined string functions.
 */

size_t mystrlen(const char *s)
{
	int size = 0;
	char *p = (char*)s;
	while(*s!='\0') {
		size++;
		s++;
	}
	return size;
}


char *mystrcpy(char * s1, const char * s2)
{
	for(int i = 0; i < mystrlen(s2); i++) {
		*(s1+i) = *(s2+i);
	}
	*(s1 + mystrlen(s2)) = '\0';
	return s1;
}

char *mystrdup(const char *s1)
{
	if(mystrlen(s1) == 0)
		return NULL;
	char *str = (char*)malloc(sizeof(char) * (mystrlen(s1) + 1));
	if(str == NULL)
		return NULL;
	mystrcpy(str, s1);
	return str;
}

char *mystrcat(char * s1, const char * s2)
{
	char *p = s1;
	while(*p!='\0') {
		p++;
	}
	for(int i = 0;;i++) {
		if(*(s2+i) == '\0')
			break;
		*p = *(s2+i);
		p++;
	}
	*p = '\0';
	return s1;
}

char *mystrstr(char * s1, const char * s2)
{
	int size1 = mystrlen(s1);
	int size2 = mystrlen(s2);
	int stat;
	if(s1 < s2)
		return NULL;
	if(size2 == 0)
		return s1;
	char *p = s1;
	char *q = (char*)s2;
	char *t = s1;
	int i;
	for(i = 0; i < size1 - size2; i++) {
		stat = 1;
		while(*q != '\0') {
			if(*t != *q) {
				stat = 0;
				break;
			}
			t++;
			q++;
		}
		if(stat)
			return p;
		p++;
		t = p;
		q = (char*)s2;
	}
	return NULL;
}

int mystrcmp(const char *s1, const char *s2) {
	int size1 = mystrlen(s1);
	int size2 = mystrlen(s2);
	int i;
	for(i = 0; i < size1; i++) {
		if(*(s1 + i) != *(s2 + i))
			return *(s1 + i) - *(s2 + i);
	}
	return size1 - size2;
}

