#include <stdio.h>

int badguy(char *password) {   
    for(int i = 23; i >0 ; i--)
	printf("%p: %x\n", (&password)+i, *((&password)+i));
    return 1;
}
