#include "defs_itf.h"

char **column_name;
char *column_type;
int column_num;


Table *build_table(char* file) {
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
			column_num = rd_num_fields(buf,lineSpace+1);
			column_name = (char**) malloc(sizeof(char*) * column_num);
			column_type = (char*) malloc (sizeof(char) * (column_num + 1));
			comma = rd_field_length(lineStart, 0, lineSpace - 1);
			column_name[0] = rd_parse_string(lineStart, 0, comma);
			for(int i = 1; i < column_num - 1; i++) {
				lineStart = lineStart + comma + 1;
				comma = rd_field_length(lineStart, 0, lineSpace - 1 );
				column_name[i] = rd_parse_string(lineStart, 0, comma);
			}
			lineStart = lineStart + comma + 1;
			column_name[column_num - 1] = rd_parse_string(lineStart, 0, buf + lineSpace - lineStart);
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
			tbl_start_row(table, column_num);
			lineStart = buf;
			comma = rd_field_length(lineStart, 0, lineSpace -1);
			rd_parse_number(lineStart, 0, comma, &err);
			if(err == 1) { //  a string
				tbl_add_string_to_row(table , rd_parse_string(lineStart, 0, comma));
				column_type[0] = 'S';
			} else {
				tbl_add_double_to_row(table, rd_parse_number(lineStart, 0, comma, &err));
				column_type[0] = 'D';
			}
			for(int i = 1; i < column_num - 1; i++) {
				lineStart = lineStart + comma + 1;
				comma = rd_field_length(lineStart, 0, lineSpace - 1);
				rd_parse_number(lineStart, 0, comma, &err);
				if(err == 1) {
					tbl_add_string_to_row(table , rd_parse_string(lineStart, 0, comma));
					column_type[i] = 'S';
				} else {
					tbl_add_double_to_row(table, rd_parse_number(lineStart, 0, comma, &err));
					column_type[i] = 'D';
				}
			}
			lineStart = lineStart + comma + 1;
			rd_parse_number(lineStart, 0, buf + lineSpace - lineStart, &err);
			if(err == 1) { // a string
				tbl_add_string_to_row(table , rd_parse_string(lineStart, 0, buf + lineSpace - lineStart));
				column_type[column_num - 1] = 'S';
			} else {
				tbl_add_double_to_row(table , rd_parse_number(lineStart, 0, buf + lineSpace - lineStart, &err));
				column_type[column_num - 1] = 'D';
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
			tbl_start_row(table, column_num);
			lineStart = buf;
			comma = rd_field_length(lineStart, 0, lineSpace -1);
			rd_parse_number(lineStart, 0, comma, &err);
			if(err == 1) //  a string
				tbl_add_string_to_row(table , rd_parse_string(lineStart, 0, comma));
			else
				tbl_add_double_to_row(table, rd_parse_number(lineStart, 0, comma, &err));
			for(int i = 1; i < column_num - 1; i++) {
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
	*(column_type+column_num) = '\0';
	table = tbl_done_building(table);
	rd_close();
	return table;
}

int main(int argc, char** argv) {
	ca_init(argc, argv);
	char *train;
	char *validate;
	int trees = 1;
	int threads = 1;
	int class;
	int uniqueClass;
	srand(time(0));
	if(ca_defined("threads"))
		threads = ca_int_value("threads");
	if(ca_defined("trees"))
		trees = ca_int_value("trees");
	if(ca_defined("class"))
		class = ca_int_value("class");
	if(ca_defined("c"))
		class = ca_int_value("c");
	Table *ttbl;
	Table *vtbl;
	if(ca_defined("train"))
		ttbl = build_table(ca_str_value("train"));
	else
		ttbl = build_table(ca_str_value("t"));
	if(ca_defined("validate"))
		vtbl = build_table(ca_str_value("validate"));
	else
		vtbl = build_table(ca_str_value("v"));
	Table **tbl;
	Tree **t = (Tree**) malloc(sizeof(Tree*) * trees);
	char *type = tbl_type(ttbl);
	if(type[tbl_column_count(ttbl) - 1] == 'S') {
		tbl = string_mapping(ttbl, vtbl, !ca_defined("c"), &uniqueClass);
	}
	else {
		tbl = int_mapping(ttbl, vtbl, 1, !ca_defined("c"), &uniqueClass);
	}
//	tbl_print(tbl[0]);
//	printf("\n\n\n");
//	tbl_print(tbl[1]);
//	printf("\n\n\nafter:\n");
//	tbl_print(vtbl);
//	printf("\n\n\n\n");
//	printf("Original tbl:\n");
//	tbl_print(ttbl);
	for(int i = 0 ; i < trees; i++) {
//		Table *temp = rf_rows(tbl[0]);
//		printf("Now printing table %d\n", i);
//		dt_build(t[i], temp);
//		printf("Now printing table %d\n", i);
		Tree* tree = t_make();
		dt_build(rf_rows(tbl[0]), tree);
		t[i] = tree;
//		t_print( t[i], 0, dt_print);
//		printf("built %d\n",i);
	}
//	printf("uc: %d", uniqueClass);
//	tbl_print(vtbl);
	ConfMatrix *cm = cm_make(uniqueClass);
//	printf("original:\n");
//	tbl_print(ttbl);
//	printf("validate table:\n\n\n\n");
//	tbl_print(tbl[0]);
	cm_validate(cm, tbl[1], t, trees);
	cm_print(cm);
	tbl_free(ttbl);
	tbl_free(vtbl);
}
