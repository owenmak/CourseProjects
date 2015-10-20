#include "defs_itf.h"

Table *creatTable(char *file) {
	Table table = tbl_make();
	rd_open(file);
	while((ch = rd_getchar()) != EOF)
	{
		if(ch == '\n')
			{
				tbl_start_row(table, 5);
				lineStart = buf;
				comma = rd_field_length(lineStart,0,lineSpace - 1);
				tbl_add_double_to_row( table, rd_parse_string( lineStart, 0, comma)); // first String
				lineStart = lineStart + comma;
				comma = rd_field_length(lineStart + 1,0,lineSpace - 1);
				tbl_add_string_to_row( table, rd_parse_number(lineStart + 1, 0, comma, &err)); // first Double
				lineStart = lineStart + comma;
				tbl_add_double_to_row( table, rd_parse_number( lineStart + 2, 0, buf + lineSpace - lineStart - 2 , &err)); // last Double
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
		tbl_add_double_to_row( table, rd_parse_string( lineStart, 0, comma)); // first String
		lineStart = lineStart + comma;
		comma = rd_field_length(lineStart + 1,0,lineSpace - 1);
		tbl_add_string_to_row( table, rd_parse_double(lineStart + 1, 0, comma, &err)); // first Double
		lineStart = lineStart + comma;
		tbl_add_double_to_row( table, rd_parse_number( lineStart + 2, 0, buf + lineSpace - lineStart - 2 , &err)); // last Double
		lineSpace = 0;
		lineStart = NULL;
		comma = 0;
		err = 1; 
	}	
	table = tbl_done_building(table);
	return table;
}

int compareDouble(void *a, void *b) {
	double a = tbl_double_at((Tree *)a->data, key);
	double b = tbl_double_at((Tree *)b->data, key);
	if(a > b)
		return 1;
	else if(a == b)
		return 0;
	else
		return -1;
}
int compareString(void *a, void *b) {
	return strcmp(tbl_string_at(((Tree *)a)->data, key), stbl_string_at(((Tree *)b)->data ,key));
}

Tree *insertValue(int startIndex, int endIndex, Table *table) {
	Tree *t = (Tree*)malloc(sizeof(Tree));
	if(startIndex > endIndex)
		return NULL;
	t->data = tbl_row_at(table,(startIndex + endIndex) / 2);
	t->left = insertValue(startIndex, (startIndex + endIndex) / 2 - 1, table);
	t->right = insertValue((startIndex + endIndex) / 2 + 1, endIndex, table);
	return t;
}

Tree *createTree(Table *table, int key) {
	int count;
	if(tbl_row_type_at(tbl_row_at(table,0)) == 'D')
		qsort(tbl_rows(table), tbl_row_count(table), sizeof(tbl_rows(table)), &compareDouble);
	else
		qsort(tbl_rows(table), tbl_row_count(table), sizeof(tbl_rows(table)), &compareString);
	count = tbl_column_count(table);
	root = (Tree*)malloc(sizeof(Tree));
	root = inserValue(0,count-1,table);
}

/* Tree *findDoubleTree(Tree *t, int key, double value) {
	if(tbl_double_at(t->data,key) == value)
		return t;
	return findDoubleTree(t->left, key, value) || findDoubleTree(t->right, key, value);
} */

/* Tree *findStringTree(Tree *t, int key, char *value) {
	if(t == NULL)
		return NULL;
	if((strcmp(tbl_string_at(t->data,key),value) == 0)
		return t;
	return findStringTree(t->left, key, value) || findStringTree(t->right, key, value);
} */

void findTree(char *find, int key) {
	Tree *t;
	if(key == 0)
		t = t_navigate(root, find, &compareDouble, &printRow);
	else
		t = t_navigate(root, atof(find), &compareString, &printRow);
	if(t == NULL)
		printf("Not Found.\n");
	free(t);
	t = NULL;
}

int findDepth(Tree* t) {
	if(t == NULL)
		return 0;
	int leftDepth = findDepth(t->left) + 1;
	int rightDepth = findDepth(t->right) + 1;
	return (leftDepth > rightDepth) ? leftDepth : rightDepth;
}

void* printRow(void *t) {
	if(t != NULL)
		tbl_print_row(((Tree*)t)->data);
}

/*define helper functions here*/

Tree* root;
int key;

int main(int argc, char** argv)
{
	char *find;
	char *file;
	int print = 0;
	int depth = 0;
	Table *table;
	ca_init(argc,argv);
	if(ca_defined("file"))
		file = ca_str_value("file");
	else
		return;
	if(ca_defined("key"))
		key = ca_str_value("key");
	if(ca_defined("find"))
		find = ca_int_value("find");
	if(ca_defined("print"))
		print = 1;
	if(ca_defined("depth"))
		depth = 1;
	table = createTable(file);
	createTree(table,key);
	if(ca_defined("find"))
		findTree(find,key);
	if(print)
		t_print(root, 0, &printRow);
	if(depth) 
		findDepth(root);
    return 0;
}
