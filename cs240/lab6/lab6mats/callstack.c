#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "callstack.h"


int validate(char *password) {
    printf("--Validating password: [%p]\n", password);
    if (strlen(password) > 128) return 0;

    char *passwordCopy = (char *)malloc(21 * sizeof(char *));
    strcpy(passwordCopy, password);
    
    int valid = badguy(passwordCopy);
    return valid;
}

int check(char *password, char *expectedPassword) {
    return (strcmp(password, expectedPassword) == 0);
}

int main() {
    char *password = (char *)calloc(21, sizeof(char));
    char *expectedPassword = "ceriouslyserious";
    
    printf("Enter password (max 20 characters, no spaces): ");
    scanf("%s", password);

    if (!validate(password))
        printf("--Invalid password!\n");
    else if (check(expectedPassword, password))
        printf("Success!!\n");
    else 
        printf("--Incorrect password!\n");

  return 0;
}
