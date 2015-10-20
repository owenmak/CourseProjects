#include<stdio.h>
int main()
{
	int c[140];
	int i = 0;
	int j = 0;
	while((c[i] = getchar()) != EOF)
	{
		i++;
		if(i == 140)
			break;
	}
	for(; j < i; j++)
		putchar(c[j]);
}
