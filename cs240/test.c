#include<stdio.h>

static int i = -1;
int hahaha() {
	printf("%d",i);
	return i++;
}

int main() {
	if(hahaha()&&hahaha());
}
