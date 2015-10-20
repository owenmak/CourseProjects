#include<stdio.h>
#include"tweet.h"
int main()
{
	char msg[140];
	int length = 0;
	while((msg[length]=getchar()) != EOF)
	{
		if(length == 140)
			break;
		else
			length++;
	}
	tweet(length, msg);
}
