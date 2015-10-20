#include "table.c"

int main() {
	Table *table;
	table = tbl_make();
//	fprintf(stderr,"ck0");
	tbl_start_row(table, 4);
//  fprintf(stderr,"ck1");
	char str1[] = "line1";
	char str2[] = "line2";
	char str3[] = "line3";
	char str4[] = "line4";
	tbl_add_double_to_row(table,1.0);
	tbl_add_string_to_row(table,str1);
	tbl_add_string_to_row(table,str1);
	tbl_add_double_to_row(table,1.1);
    tbl_start_row(table,3);
    tbl_add_string_to_row(table,str2);
    tbl_add_double_to_row(table,2.0);
	tbl_add_string_to_row(table,str2);
    tbl_start_row(table,4);
	tbl_add_double_to_row(table,3.0);
    tbl_add_string_to_row(table,str3);
	tbl_add_string_to_row(table,str3);
    tbl_add_double_to_row(table,3.1);
	tbl_start_row(table,4);
	tbl_add_double_to_row(table,4.0);
	tbl_add_string_to_row(table,str4);
	tbl_add_string_to_row(table,str4);
	tbl_add_double_to_row(table,4.1);
	table = tbl_done_building(table);
	tbl_print(table);
	printf("rowCount: %d\n",tbl_row_count(table));
//	printf("columnCount: %d\n", tbl_column_count(table));
}
