#include<stdio.h>
#include "defs_itf.h"

void printFind(char *handle, char *rating, Table *table)
{
	if(handle == NULL && rating == NULL)
	{	printf("double NULL");}
	else if(handle == NULL)
	{
		Row *temp;
		for(int i =0; i < tbl_row_count(table); i++)
		{
			temp = tbl_row_at( table, i);
			if(strcmp(rating, tbl_string_at(temp,3)) == 0)
			{	tbl_print_row(temp);}
		}
	}
	else if(rating == NULL)
    {
        Row *temp;
        for(int i =0; i < tbl_row_count(table); i++)
        {
            temp = tbl_row_at( table, i);
            if(strcmp(handle, tbl_string_at(temp,2)) == 0)
            {   tbl_print_row(temp);}
        }
    }
	else
	{  
        Row *temp;
        for(int i =0; i < tbl_row_count(table); i++)
        {
            temp = tbl_row_at( table, i);
            if(strcmp(rating, tbl_string_at(temp,3)) == 0)
			{
				if(strcmp(handle, tbl_string_at(temp,2)) == 0)
            	{   tbl_print_row(temp);}
			}
        }
    }
}

int main(int argc,char ** argv) {
	char ch;
	char *lineStart;
	int comma;
	int err;
	int lineSpace = 0;
	char *file;
	char *rating;
	char *handle;
	int line = 0;
	char buf[500];
	ca_init(argc,argv);
	if (ca_defined("file")) 
		file = ca_str_value("file");
	else
		return 0;
	if (ca_defined("find_rating"))
		rating = ca_str_value("find_rating");
	else
		rating = NULL;
	if (ca_defined("find_handle"))
		handle = ca_str_value("find_handle");
	else
		handle = NULL;
	Table *table = tbl_make();
	rd_open(file);
	while((ch = rd_getchar()) != EOF)
	{
		if(ch == '\n')
			{
				tbl_start_row(table, 5);
				lineStart = buf;
				comma = rd_field_length(lineStart,0,lineSpace - 1);
				tbl_add_double_to_row( table, rd_parse_number( lineStart, 0, comma, &err)); // first Number
				lineStart = lineStart + comma;
				comma = rd_field_length(lineStart + 1,0,lineSpace - 1);
				tbl_add_string_to_row( table, rd_parse_string(lineStart + 1, 0, comma)); // first String
				lineStart = lineStart + comma + 1;
				comma = rd_field_length(lineStart + 1,0,lineSpace - 1);
				tbl_add_string_to_row( table, rd_parse_string(lineStart + 1, 0, comma)); //second string
				lineStart = lineStart + comma + 1;
				comma = rd_field_length(lineStart + 1,0,lineSpace - 1);
				tbl_add_string_to_row( table, rd_parse_string(lineStart + 1, 0, comma)); // third string
				lineStart = lineStart + comma;
				tbl_add_double_to_row( table, rd_parse_number( lineStart + 2, 0, buf + lineSpace - lineStart - 2 , &err)); // last Number
				lineSpace = 0;
				lineStart = NULL;
				comma = 0;
				err = 1; 
			for(int i = 0; i < 500; i++)
				buf[i] = '\0';
			}
		else
		{
			buf[lineSpace] = ch;
			lineSpace++; 
		}
	}
	if(ch == EOF && lineSpace != 0)
	{
		tbl_start_row(table, 5);
		lineStart = buf;
		comma = rd_field_length(lineStart,0,lineSpace - 1);
		tbl_add_double_to_row( table, rd_parse_number( lineStart, 0, comma, &err)); // first Number
		lineStart = lineStart + comma;
		comma = rd_field_length(lineStart + 1,0,lineSpace - 1);
		tbl_add_string_to_row( table, rd_parse_string(lineStart + 1, 0, comma)); // first String
		lineStart = lineStart + comma + 1;
		comma = rd_field_length(lineStart + 1,0,lineSpace - 1);
		tbl_add_string_to_row( table, rd_parse_string(lineStart + 1, 0, comma)); //second string
		lineStart = lineStart + comma + 1;
		comma = rd_field_length(lineStart + 1,0,lineSpace - 1);
		tbl_add_string_to_row( table, rd_parse_string(lineStart + 1, 0, comma)); // third string
		lineStart = lineStart + comma;
		tbl_add_double_to_row( table, rd_parse_number( lineStart + 2, 0, buf + lineSpace - lineStart - 2 , &err)); // last Number
		lineSpace = 0;
		lineStart = NULL;
		comma = 0;
		err = 1; 
	}	
	table = tbl_done_building(table);
	printFind(handle,rating,table);
}
