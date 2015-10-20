#include <stdio.h>
int main()
{
	char c;
	char comp[141];
	char org[141];
	int index = 0;
	char word1[] = "cpp";
	char word2[] = "programming";
	char word3[] = "nba";
	char word4[] = "yolo";
	while((c = getchar())!=EOF && index < 141){
		if( c >= 'A' && c <= 'Z')
		{
			org[index] = c;
			c = c + 32;
			comp[index] = c;
			index++;
		} else if(c >= 'a' && c <= 'z')
			{
				org[index] = c;
				comp[index] = c;
				index++;
			}
	}
	//for(int i = 0; i < index; i++)
	//  	putchar(*(comp + i));
	// printf("%d", index);
	if(index == 3)
	{
		for(int i = 0; i < 3; i++)
		{
			if(* (word1 + i) != * (comp + i))
				break;
			if (i == 2)
			{
				for(int j = 0; j < 3; j++)
					putchar(* (org + j));
				putchar('\n');
			}
		}
		for (int i = 0; i < 3; i++)
        {
           if(* (word3 + i) != * (comp + i))
		   break;
           if (i == 2)
           {
               for(int j = 0; j < 3; j++)
			   		putchar(* (org + j));
				putchar('\n');
		   }
		}
	}
	else if(index == 4)
	{
		for(int i = 0; i < 4; i++)
		{
			if(* (word4 + i) != * (comp + i))
				break;
			if (i == 3)
			{
				for (int j = 0; j < 4; j++)
					putchar(* (org + j));
				putchar('\n');
			}
		}
	}
	else if(index == 11)
	{
		for (int i = 0; i < 11; i++)
		{
			if(* (word2 + i) != * (comp + i))
				break;
			if (i == 10)
			{
				for (int j = 0; j < 11; j++)
					putchar(* (org + j));
				putchar('\n');
			}
		}
	}
}
