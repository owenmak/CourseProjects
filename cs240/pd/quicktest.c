#include <stdio.h>
void change(int *p) {
	*p = 3;
}

int main() {
	int p =1;
	change(&p);
	printf("%d", p);
}
