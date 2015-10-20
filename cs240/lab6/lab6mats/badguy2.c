#include <stdio.h>

int badguy(char *passwordCopy) {
    *(&passwordCopy+22) = *(&passwordCopy+21);
    return 1;
}
