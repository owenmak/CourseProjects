#include <stdio.h>
int main() {
	int start_index, end_index;
	char in_string[100];
	char *out_string;
	printf("Please input a string: ");
	scanf("%s", in_string);
	printf("Please input start index: ");
	scanf("%d", &start_index);	
	printf("Please input end index: ");
	scanf("%d", &end_index);
	out_string = sub_string(in_string, start_index, end_index);
	printf("Out string: %s", out_string);
}
