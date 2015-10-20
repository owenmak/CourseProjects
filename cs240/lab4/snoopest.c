#include<stdio.h>
#include "defs_imp.h"

int colSort = -1;
int descending = 1;
int compareDouble(const void * a, const void * b) {
	double d1 = tbl_double_at(*(Row **)a,colSort);
	double d2 = tbl_double_at(*(Row **)b,colSort);
	if(d1>d2)
		return 1 * descending;
	else if(d1 == d2)
		return 0;
	else
		return -1 * descending;
}


int compareString(const void *a, const void * b) {
	return strcmp(tbl_string_at(*(Row **)a),tbl_string_at(*(Row **)b)) * descending;
}

void printFind(char *handle, char *rating, Table *table)
{
	if(handle == NULL && rating == NULL)
	{	tbl_print(table); }//printf("double NULL");}
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
	int sort = -1;
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
	if(ca_defined("sort"))
		colSort = ca_int_value("sort");
	if(ca_defined("descending"))
		descending = -1;
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
	if(colSort != -1 && colSort <= tbl_column_count(table)) {
		printf("sorting\n\n\n\n\n\n\n\n\n\n");
		if(tbl_row_type_at(tbl_rows(table), colSort) == 'D')
			qsort(tbl_rows(table),tbl_row_count(table), sizeof(tbl_rows(table)), compareDouble);
		else
			qsort(tbl_rows(table),tbl_row_count(table), sizeof(tbl_rows(table)), compareString);
	}
	printf("%d\n\n",sort);
//	tbl_print(table);
	printFind(handle,rating,table);
}
