#include<stdio.h>
#include "defs_itf.h"
int main() {
	char yeah[] = "HELLO HOW ARE YOU";
	char *str = yeah;
	if(strcmp(str, "HELLO HOW ARE YOU") == 0)
		printf("yes");
}
