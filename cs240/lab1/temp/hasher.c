#include <stdio.h>

int isKeyWord(char* c, int length);
int isSpace(const char c);
int main()
{
	char c;
	char comp[141];
	char org[141];
	char output[140];
	int outIndex = 0;
	int index = 0;
	int spaceLength = 0;
	int status = 1;
	int hashNum = 0;
	int startSpace;
	int count = 0;
//	int wordStart = 1;
//	int wordEnd = 0;
	while((c = getchar())!=EOF && index < 140)
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
		if(i + hashNum == 140)
		{
//			printf("HAHAHA %d", i);
//			printf("%d",spaceLength);
			if(isKeyWord(comp + i - spaceLength, spaceLength))
			{
				output[outIndex] = '#';
				outIndex++;
				for(int j = i - spaceLength; j < i - 1; j++)
				{	output[outIndex] = *(org + j); outIndex++;}
//				spaceLength = 0;
//				break;
			}
			else
			{
				for(int j = i - spaceLength; j < i; j++)
				{	output[outIndex] = *(org+j); outIndex++;}
//				spaceLength = 0;
//				break;
			}
			spaceLength = 0;
			break;
		}
		if(isSpace(*(org + i)))
		{
//			printf("hehe, %d", i);
			if(isKeyWord(comp + i - spaceLength, spaceLength))
			{
				output[outIndex] = '#';
				outIndex++;
				hashNum++;
			}
			for(int j = i - spaceLength; j <= i; j++)
			{	output[outIndex] = *(org+j);outIndex++;}
			spaceLength = 0;
		}
		else
		{
//			printf("haha");
			spaceLength++;
		}
	}
	if(spaceLength != 0)
	{
//		printf("%d", spaceLength);
		if(index - spaceLength + hashNum <=138)
		{
		//	printf("%d,%c", spaceLength, *(comp + index - spaceLength));
			if(isKeyWord(comp+index-spaceLength, spaceLength))
			{
				output[outIndex] = '#';
				hashNum++;
				outIndex++;
			}
			for(int j = index- spaceLength; j < index; j++)
			{
				output[outIndex] = *(org + j);
				outIndex++;
				if(hashNum + j >= 139)
					break;
			}
		}
	}
	if(outIndex >= 140)
		outIndex = 140;
	for(int i = 0; i < outIndex; i++)
	{
		putchar(*(output + i));
	}
	putchar('\n');
//	printf("%d",count);
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
