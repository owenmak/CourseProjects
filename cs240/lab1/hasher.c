#include <stdio.h>

int isKeyWord(char* c, int length);
int isSpace(const char c);
int main()
{
	char c;
	char comp[141];
	char org[141];
	int index = 0;
	int spaceLength = 0;
	int space[141];
	while((c = getchar())!=EOF && index < 141)
	{
		if( c >= 'A' && c <= 'Z') {
			org[index] = c;
			c = c + 32;
			comp[index] = c;
			index++;
		} else {
			org[index] = c;
			comp[index] = c;
			index++;
		}
	}
	for(int i = 0; i < index; i++) 
	{
		if(isSpace(*(org + i)))
		{
			if(isKeyWord(comp+i-spaceLength,spaceLength - 1))
			{
				putchar('#');
			}
			for(int j = i-spaceLength; j <= i; j++)
				putchar(*(org+j));
			spaceLength = 0;
		}
		else
			spaceLength++;
	}
	if(spaceLength != 0)
	{
		if(isKeyWord(comp+index-spaceLength + 1, spaceLength - 1))
		{
			putchar('#');
		}
		for(int j = index-spaceLength; j < index-1; j++)
		{
			putchar(*(org + j));
		}
	}
}
int isKeyWord(char *c, int length)
{
	if(length != 3 && length !=11 && length != 4)
		return 0;
	char keyWord[4][12] = {"cpp", "programming", "nba", "yolo"};
	if(length == 3) 
	{
		for(int i = 0; i < 3; i++)
		{
			if(*(c + i) != keyWord[0][i])
				break;
			if(i == 2)
				return 1;
		}
		for(int i = 0; i < 3; i++)
		{
			if(* (c + i) != keyWord[2][i])
				break;
			if(i == 2)
				return 1;
		}
	}
	else if(length == 4)
	{
		for(int i = 0; i < 4; i++)
		{
			if(* (c + i) != keyWord[3][i])
				break;
			if(i == 2)
				return 1;
		}
		return 0;
	}
	else
	{
		for(int i = 0; i < 11; i++)
		{
			if(*(c + i) != keyWord[1][i])
				break;
			if(i == 9)
				return 1;
		}
		return 0;
	}
}
int isSpace(char c) {
	if(c == ' ' || c == ',' || c == '.' || c == '\t')
		return 1;
	else 
		return 0;
}
