#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"vulnerable.h"

char* name = "abc";

void secret(){
  printf("Secret!\n");
  exit(0);
}

void wrong() {
  char buf[4];
  strcpy(buf,name);
}

void fence_secret(){
  printf("fence\n");
}

int main(){
    init();
    fence_secret();
    wrong();
    return 0;
}


