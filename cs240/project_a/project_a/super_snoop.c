#include<stdio.h>
#include "defs_itf.h"

char **columnName;
char *columnType;
int columnNum;

Table *buildTable(char* file) {
	char ch;
	char *lineStart;
	int comma = 0;
	int err;
	int lineSpace = 0;
	char buf[500];
	Table *table = tbl_make();
	rd_open(file);
	while((ch = rd_getchar()) != EOF) { // getting the first line of column names;
		if(ch == '\n')
		{
			buf[lineSpace] = '\0';
			lineStart = buf;
			columnNum = rd_num_fields(buf,lineSpace+1);
			columnName = (char**) malloc(sizeof(char*) * columnNum);
			columnType = (char*) malloc (sizeof(char) * (columnNum + 1));
			comma = rd_field_length(lineStart, 0, lineSpace - 1);
			columnName[0] = rd_parse_string(lineStart, 0, comma);
			for(int i = 1; i < columnNum - 1; i++) {
				lineStart = lineStart + comma + 1;
				comma = rd_field_length(lineStart, 0, lineSpace - 1 );
				columnName[i] = rd_parse_string(lineStart, 0, comma);
			}
			lineStart = lineStart + comma + 1;
			columnName[columnNum - 1] = rd_parse_string(lineStart, 0, buf + lineSpace - lineStart);
			lineSpace = 0;
			lineStart = NULL;
			comma = 0;
			err = 1;
			for(int i = 0; i < 500; i++)
				buf[i] = '\0';
			break;
		}
		else
		{
			buf[lineSpace] = ch;
			lineSpace++;
		}
	} 
	while((ch = rd_getchar()) != EOF) {
		if(ch == '\n')
		{
			tbl_start_row(table, columnNum);
			lineStart = buf;
			comma = rd_field_length(lineStart, 0, lineSpace -1);
			rd_parse_number(lineStart, 0, comma, &err);
			if(err == 1) { //  a string
				tbl_add_string_to_row(table , rd_parse_string(lineStart, 0, comma));
				columnType[0] = 'S';
			} else {
				tbl_add_double_to_row(table, rd_parse_number(lineStart, 0, comma, &err));
				columnType[0] = 'D';
			}
			for(int i = 1; i < columnNum - 1; i++) {
				lineStart = lineStart + comma + 1;
				comma = rd_field_length(lineStart, 0, lineSpace - 1);
				rd_parse_number(lineStart, 0, comma, &err);
				if(err == 1) {
					tbl_add_string_to_row(table , rd_parse_string(lineStart, 0, comma));
					columnType[i] = 'S';
				} else {
					tbl_add_double_to_row(table, rd_parse_number(lineStart, 0, comma, &err));
					columnType[i] = 'D';
				}
			}
			lineStart = lineStart + comma + 1;
			rd_parse_number(lineStart, 0, buf + lineSpace - lineStart, &err);
			if(err == 1) { // a string
				tbl_add_string_to_row(table , rd_parse_string(lineStart, 0, buf + lineSpace - lineStart));
				columnType[columnNum - 1] = 'S';
			} else {
				tbl_add_double_to_row(table , rd_parse_number(lineStart, 0, buf + lineSpace - lineStart, &err));
				columnType[columnNum - 1] = 'D';
			}
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
			tbl_start_row(table, columnNum);
			lineStart = buf;
			comma = rd_field_length(lineStart, 0, lineSpace -1);
			rd_parse_number(lineStart, 0, comma, &err);
			if(err == 1) //  a string
				tbl_add_string_to_row(table , rd_parse_string(lineStart, 0, comma));
			else
				tbl_add_double_to_row(table, rd_parse_number(lineStart, 0, comma, &err));
			for(int i = 1; i < columnNum - 1; i++) {
				lineStart = lineStart + comma + 1;
				comma = rd_field_length(lineStart, 0, lineSpace - 1);
				rd_parse_number(lineStart, 0, comma, &err);
				if(err == 1)
					tbl_add_string_to_row(table , rd_parse_string(lineStart, 0, comma));
				else
					tbl_add_double_to_row(table, rd_parse_number(lineStart, 0, comma, &err));
			}
			lineStart = lineStart + comma + 1;
			rd_parse_number(lineStart, 0, buf + lineSpace - lineStart, &err);
			if(err == 1) // a string
				tbl_add_string_to_row(table , rd_parse_string(lineStart, 0, buf + lineSpace - lineStart));
			else
				tbl_add_double_to_row(table , rd_parse_number(lineStart, 0, buf + lineSpace - lineStart, &err));
			lineSpace = 0;
			lineStart = NULL;
			comma = 0;
			err = 1;
			for(int i = 0; i < 500; i++)
				buf[i] = '\0';
	}
	*(columnType+columnNum) = '\0';
	table = tbl_done_building(table);
	//rd_close();
	return table;
}

int compareFunc(Row *row, Tree *t) {
	int type = q_get_type(t->data);
	if(type == 1)
		return compareFunc(row,t->left) && compareFunc(row,t->right);
	else if(type == 0)
		return compareFunc(row,t->left) || compareFunc(row,t->right);
	else {
		int index = q_get_col_index(t->data);
		if(columnType[index] == 'S') {
			int result = strcmp(tbl_string_at(row, index), q_get_str(t->data));
			if(result == 0) {
				if(type == 2 || type == 5 || type ==6)
					return 1;
				else
					return 0;
			}
			else if(result < 0) {
				if(type == 3 || type == 5)
					return 1;
				else
					return 0;
			}
			else {
				if(type == 4 || type ==6)
					return 1;
				else 
					return 0;
			}
		}
		else {
			double result = tbl_double_at(row, index) - q_get_double(t->data);
			if(abs(result) < 0.001) {
				if(type == 2 || type == 5 || type ==6)
					return 1;
				else
					return 0;
			}
			else if(result < 0) {
				if(type == 3 || type == 5)
					return 1;
				else
					return 0;
			}
			else {
				if(type == 4 || type ==6)
					return 1;
				else 
					return 0;
			}
		}
			
	}
}

void doQuery(Table *table, Tree *t) {
	for(int i = 0; i < tbl_row_count(table); i++) {
		if(compareFunc(tbl_row_at(table,i), t) == 1)
			tbl_print_row(tbl_row_at(table,i));
	}
}

int main(int argc,char ** argv) {
	char *file;
	char *query;
	ca_init(argc,argv);
	if (ca_defined("file")) 
		file = ca_str_value("file");
	else
		return 0;
	if (ca_defined("query"))
		query = ca_str_value("query");
	else		
		query = NULL;
	Table *table = buildTable(file);
	Tree *t = q_parse(query,columnName,columnType,columnNum);
	doQuery(table,t);
	for(int i = 0; i < columnNum; i++)
		free(columnName[i]);
	tbl_free(table);
	q_free(t);
	ca_free();
	free(columnName);
	free(columnType);
}
