#include<stdio.h>
int main()
{
	char c[] = "123 , Eagle has landed, JackRyan, Top Secret, 11\n";
	char *lineStart = c;
	int lineSpace = 0;
	while(*lineStart != '\n')
	{
		lineStart++;
		lineSpace++;
	}
	putchar(*(lineStart-lineSpace));
}
