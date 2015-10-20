#include "defs_itf.h"

Tree* root;
int key;


Table *createTable(char *file) {
	char ch;
	char *lineStart;
	int comma;
	int err;
	int lineSpace = 0;
	int line = 0;
	char buf[500];
	Table *table = tbl_make();
	rd_open(file);
	while((ch = rd_getchar()) != EOF)
	{
		if(ch == '\n')
			{
				tbl_start_row(table, 5);
				lineStart = buf;
				comma = rd_field_length(lineStart,0,lineSpace - 1);
				tbl_add_string_to_row( table, rd_parse_string( lineStart, 0, comma)); // first String
				lineStart = lineStart + comma;
				comma = rd_field_length(lineStart + 1,0,lineSpace - 1);
				tbl_add_double_to_row( table, rd_parse_number(lineStart + 1, 0, comma, &err)); // first Double
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
		tbl_add_string_to_row( table, rd_parse_string( lineStart, 0, comma)); // first String
		lineStart = lineStart + comma;
		comma = rd_field_length(lineStart + 1,0,lineSpace - 1);
		tbl_add_double_to_row( table, rd_parse_number(lineStart + 1, 0, comma, &err)); // first Double
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

int compareDouble(const void *a, const void *b) {
	double d1 = tbl_double_at(((Tree *)a)->data, key);
	double d2 = tbl_double_at(((Tree *)b)->data, key);
	if(d1 > d2)
		return 1;
	else if(d1 == d2)
		return 0;
	else
		return -1;
}

int compareDb(void *a,void *b) {
     double d1 = *(double *)a;
     double d2 = tbl_double_at((Row* )b, key);
     if(d1 > d2)
         return 1;
     else if(d1 == d2)
         return 0;
     else
         return -1;
}

int compareStr(void *a,void *b) {
     char *str1 = (char *)a;
     char *str2 = tbl_string_at((Row *)b ,key);
     return strcmp(str1, str2);
}

int compareString(const void *a, const void *b) {
	char *str1 = tbl_string_at(((Tree *)a)->data, key);
	char *str2 = tbl_string_at(((Tree *)b)->data ,key);
	return strcmp(str1, str2);
}

Tree *insertValue(int startIndex, int endIndex, Table *table) {
	Tree *t = t_make();
	if(startIndex > endIndex)
		return NULL;
	t->data = tbl_row_at(table,(startIndex + endIndex) / 2);
	t->left = insertValue(startIndex, (startIndex + endIndex) / 2 - 1, table);
	t->right = insertValue((startIndex + endIndex) / 2 + 1, endIndex, table);
	return t;
}

Tree *createTree(Table *table, int key) {
	int count;
	if(key != 0)
		qsort(tbl_rows(table), tbl_row_count(table), sizeof(tbl_rows(table)), &compareDouble);
	else
		qsort(tbl_rows(table), tbl_row_count(table), sizeof(tbl_rows(table)), &compareString);
	count = tbl_row_count(table);
//	printf("count = %d\n", count);
	root = (Tree*)malloc(sizeof(Tree));
	root = insertValue(0,count-1,table);
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

void printRow(void *t) {
    if(t != NULL)
        printf("\"%s\",%.0f,%.1f\n", tbl_string_at(t,0), tbl_double_at(t,1),tbl_double_at(t,2));
}

void* printR(void *r) {
	if(r != NULL)
		printf("\"%s\",%.0f,%.1f\n", tbl_string_at(r,0), tbl_double_at(r,1),tbl_double_at(r,2));
	return r;
}

void findTree(char *find, int key) {
	Row *r;
	if(key == 0)
		r = t_navigate(root, find, &compareStr, &printR);
	else {
		double f = atof(find);
		r = t_navigate(root, &f, &compareDb, &printR);
	}
	if(r == NULL)
		printf("Not Found.\n");
} 

int findDepth(Tree* t) {
	if(t == NULL)
		return 0;
	int leftDepth = findDepth(t->left) + 1;
	int rightDepth = findDepth(t->right) + 1;
	return (leftDepth > rightDepth) ? leftDepth : rightDepth;
}


/*define helper functions here*/



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
		return 0;
	if(ca_defined("key"))
		key = ca_int_value("key");
	if(ca_defined("find"))
		find = ca_str_value("find");
	if(ca_defined("print"))
		print = 1;
	if(ca_defined("depth"))
		depth = 1;
	table = createTable(file);
	createTree(table,key);
//	tbl_print_row(root->left->data);
	if(ca_defined("find"))
		findTree(find,key);
	if(print)
		t_print(root, 0, &printRow);
	if(depth) 
		printf("%d\n",findDepth(root)-1);
    return 0;
}
