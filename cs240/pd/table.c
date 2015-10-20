#include"defs_imp.h"
/*
 * returns the type of the table.  Undefined if called before tbl_done_building()
 */
char *tbl_type(Table *t) {
	return t->firstRow->type;
}

/* 
 * Return a newly allocated table or NULL if unsufficient memory.
 */
Table * tbl_make() {
	Table *t = (Table *) malloc(sizeof(Table));
	t->row_count = 0;
	t->column_count = 0;
	return t;
}

/*
 * Prepare the table for the addition of a row with num_field values.
 * Undefined behavior if tbl_done_building() has been called.
 */
void    tbl_start_row(Table* tbl, int num_fields) {
	Row *r = (Row *) malloc(sizeof(Row));
	r->type = (char *) malloc(sizeof(char) * num_fields);
	r->fields = (data *) malloc(sizeof(data) * num_fields);
	r->num_field = 0;
	r->next = NULL;
	if(tbl->column_count == 0) { // initial
		tbl->column_count = num_fields;
		tbl->firstRow = r;
		tbl->lastRow = r;
	}
	else {
		tbl->lastRow->next = r;
		tbl->lastRow = r;
	}
	tbl->row_count++;
}

/* 
 * Add a NULL-terminated string as a field of the current row.  Undefined
 * behavior if tbl_done_building() has been called or if the row is already
 * full.
 */
void    tbl_add_string_to_row(Table* tbl, char * str) {
	if(tbl->lastRow->num_field >= tbl->column_count)
		return;
	int index = tbl->lastRow->num_field;
	tbl->lastRow->type[index] = 'S';
	tbl->lastRow->fields[index].str = (char *)malloc(sizeof(char) * (strlen(str) + 1));
	strcpy(tbl->lastRow->fields[index].str, str);
	tbl->lastRow->num_field++;
}

/* 
 * Add a double as a field of the current row.  Undefined behavior if
 * tbl_done_building() has been called or if the row is already full.
 */
void    tbl_add_double_to_row(Table* tbl, double d) {
	int index = tbl->lastRow->num_field;
	tbl->lastRow->type[index] = 'D';
	tbl->lastRow->fields[index].db = d;
	tbl->lastRow->num_field++;
}

/* 
 * Ends construction of the table.
 */
Table * tbl_done_building(Table* tbl) {
	int index;
	int new_count = 0;
	int *new_index = (int*) malloc(sizeof(int) * tbl_row_count(tbl));
	for(int i = 0; i < tbl_row_count(tbl); i++) {
		for(int j = i; j < tbl_row_count(tbl); j++) {
			if(strcmp(tbl_row_at(tbl,i)->type, tbl_row_at(tbl,j)->type)== 0 && (i!=j)) {
				index = i;	
				break;
			}
		}
	}
	for(int i = 0; i < tbl_row; i++) {
		if(strcmp(tbl_row_at(tbl,i)->type, tbl_row_at(tbl,index)->type) == 0) {
			new_index[new_count] = i;
			new_count++;
		}
	}
	Table *t = tbl_make();
	t->column_count = tbl_column_count(tbl);
	t->row_count = new_count;
	t->rows = (Row **) malloc(sizeof(Row*) * new_count);
	Row *r1 = tbl->firstRow;
	Row *r2 = tbl->firstRow;
	for(int i = 0; i < tbl_row_count(tbl); i++) {
		for(int j = 0; j < new_count; i++) {
			if(new_index[j] == i) {
				t->rows[j] = r1;
				r1 = r1->next;
				break;
			}
			if(j == new_count - 1) {
				r2 = r1;
				r1 = r1->next;
				row_free(r2);
			}
		}
	}



/*	for(int i = 0; i < new_count; i++) {
		Row *r = tbl_row_at(tbl, new_index[i]);
		t->rows[i]->num_field = r->num_field;
		t->rows[i]->type = (char*) malloc(sizeof(char) * (strlen(r->type) + 1));
		t->rows[i]->fields = (data*) malloc(sizeof(data) * r->num_field);
		strcpy(t->rows[i]->type, r->type);
		for(int j = 0; j < r->num_field; j++) {
			if(r->type[j] == 'S') {
				t->rows[i]->fields[j].str = (char*) malloc (sizeof(char) * strlen(r->fields[j].str + 1));
				strcpy(t->rows[i]->fields[j]->str, r->fields[j]->str);
			}
			else {
				t->rows[i]->fields[j]->db = r->fields[j]->db;
			}
		}
	} */
	for(int i = 0; i < new_count - 1; i++) {
		rows[i]->next = rows[i+1];
	}
	rows[new_count - 1]->next = NULL;
	t->firstRow = rows[0];
	t->lastRow = rows[new_count - 1];
	return t;
}

/* 
 * Return the number of columns. 
 */
int     tbl_column_count( Table * tbl ) {
	return tbl->column_count;
}

/*
 * Return the Row at index at or NULL if at is out of bounds
 */
Row *   tbl_row_at( Table * tbl, int at ) {
	int index = 0;
	Row *r = tbl->firstRow;
	while(index < at) {
		r = r->next;
		index++;
	}
	return r;
}

/* 
 * Return the string value from the fields array at index at of row
 */
char *  tbl_string_at( Row * row, int at) {
	return row->fields[at]->str;
}

/*
 * Return the double value from the fields array at index at of row
 */
double  tbl_double_at( Row * row, int at) {
	return row->fields[at]->db;
}

/* 
 * Prints each field of r.
 * Strings are printed in quotes
 * Doubles are printed to 2 decimal places
 */
void    tbl_print_row( Row * row ) {
	for(int i = 0; i < row->num_field - 1; i++) {
		if(row->type[i] == 'S')
			printf("\"%s\",", row->fields[i]->str);
		else
			printf("%.2f,", row->fields[i]->db);
	}
	if(*(row->type[row->num_field-1]) == 'S') {
		printf("\"%s\"\n", row->fields[row->field_length-1]->str;
	}
	else {
		printf("%.2f\n", row->fields[row->field_length-1]->db);
	}
}

/*
 * Print the fields of each row belonging to tbl.
 */
void    tbl_print(Table* tbl) {
	for(int i = 0; i < tbl->row_count; i++)
		tbl_print_row(tbl->rows[i]);
}

/* 
 * Free all memory in a table.  In no case should it cause a 
 * segmentation fault, even it NULL is passed in.
 */

void	row_free(Row *row) {
	for(int i = 0; i < row->num_field; i++) {
		if(type[i] == 'S') {
			free(row->fields[i]->str);
		}
	}
	free(row->type);
	free(row->fields);
	if(row->next == NULL)
		return;
	else
		row_free(row->next);
}

void    tbl_free(Table *tbl) { //TODO
	row_free(tbl->firstRow);
	
}

/* 
 * Return the type of a column, either S or D;
 */
char    tbl_row_type_at( Row * row , int column ) {
	return row->type[column];
}

/* 
 * Return the number of rows in the table
 */
int     tbl_row_count( Table * tbl ) {
	return tbl->row_count;
}

/*
 * Return an array with all rows of this table.
 */
Row ** tbl_rows(Table *tbl) {
	return tbl->rows;
}

