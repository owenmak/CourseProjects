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
	int status = 1;
	int hashNum = 0;
	int startSpace;
//	int wordStart = 1;
//	int wordEnd = 0;
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
	for( int i = 0; i < index; i++)
	{
		if(i + hashNum == 139)
		{
			if(isKeyWord(comp + i - spaceLength, spaceLength))
			{
				putchar('#');
				for(int j = i - spaceLength; i < i; j++)
					putchar(*(org + j));
				spaceLength = 0;
				break;
			}
			else
			{
				for(int j = i - spaceLength; j <= i; j++)
					putchar(*(org+j));
				spaceLength = 0;
				break;
			}
		}
		if(isSpace(*(org + i)))
		{
			if(isKeyWord(comp + i - spaceLength, spaceLength))
			{
				putchar('#');
				hashNum++;
			}
			for(int j = i - spaceLength; j <= i; j++)
				putchar(*(org+j));
			spaceLength = 0;
		}
		else
			spaceLength++;
	}
	if(spaceLength != 0)
	{
		printf("HERE WE ARE!");
		if(index - spaceLength + hashNum <=139)
		{
		//	printf("%d,%c", spaceLength, *(comp + index - spaceLength));
			if(isKeyWord(comp+index-spaceLength, spaceLength))
			{
				putchar('#');
				hashNum++;
			}
			for(int j = index- spaceLength; j < index; j++)
			{
				putchar(*(org + j));
				if(hashNum + j >= 139)
					break;
			}
		}
	}
	putchar('\n');
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
			if(i == 3)
				return 1;
		}
	}
	else
	{
		for(int i = 0; i < 11; i++)
		{
			if(*(c + i) != keyWord[1][i])
				break;
			if(i == 10)
				return 1;
		}
	}
	return 0;
}
int isSpace(char c) {
	if(c == ' ' || c == ',' || c == '.' || c == '\t')
		return 1;
	else 
		return 0;
}
