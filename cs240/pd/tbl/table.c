#include "defs_imp.h"

char *tbl_type(Table *t) {
	return t->type;
}

Table * tbl_make() {
	Table* tbl = malloc(sizeof(Table));
	tbl->row_count = 0;
	tbl->type = NULL;
	return tbl;
}

void    tbl_start_row(Table* tbl, int num_fields) {
	int row_count = tbl->row_count;
	Row* new_row = malloc(sizeof(Row));
	new_row->field_count = num_fields;
	new_row->next = NULL;
	new_row->type = calloc(num_fields + 1 , 1);
	new_row->fields = malloc(num_fields * sizeof(Field));
	new_row->cur = 0;
	if (row_count == 0) {
		tbl->first_row = new_row;
		tbl->last_row = tbl->first_row;
	} else {
		tbl->last_row->next = new_row;
		tbl->last_row = new_row;
	}
	tbl->row_count++;
}

void    tbl_add_string_to_row(Table* tbl, char * str) {
	int cur = tbl->last_row->cur;
	tbl->last_row->fields[cur].s = str;
	tbl->last_row->type[cur] = 'S';
	tbl->last_row->cur++;
}

void    tbl_add_double_to_row(Table* tbl, double d) {
	int cur = tbl->last_row->cur;
	tbl->last_row->fields[cur].v = d;
	tbl->last_row->type[cur] = 'D';
	tbl->last_row->cur++;
}

void free_row(Row* r) {
	for (int i = 0; i < r->field_count; ++i) {
		if (r->type[i] == 'S')
			free(r->fields[i].s);
	}
	free(r->fields);
	free(r->type);
	free(r);
}

char *  tbl_string_at( Row * row, int at);
void tbl_print_row(Row* r);

Table * tbl_done_building(Table* tbl) {
	int check = 0;
	if(tbl->row_count < 2)
		check = 1;
	char* temp = NULL;
	Row* temp_r = tbl->first_row;
	while (temp_r != NULL && temp_r->next != NULL) {
		if (!strcmp(temp_r->type,temp_r->next->type)) {
			temp = temp_r->type;
			tbl->type = malloc(strlen(temp) + 1);
			strcpy(tbl->type, temp);
			break;
		}
		Row* temp_rr = temp_r->next;
		temp_r = temp_rr;
	}
	if (temp == NULL) {
		Row* temp_1 = tbl->first_row;
		while(temp_1 != NULL && temp_1->next != NULL) {
			tbl->first_row = temp_1->next;
			free_row(temp_1);
			temp_1 = tbl->first_row;
		} 
		free_row(temp_1);
		tbl->row_count = 0;
	} else {
		Row* temp_1 = tbl->first_row;
		while (strcmp(temp_1->type, temp)){
			if (temp_1->next != NULL) {
				tbl->first_row = temp_1->next;
				free_row(temp_1);
				temp_1 = tbl->first_row;
				tbl->row_count--;
			}  else {
				tbl->first_row = NULL;
				free_row(temp_1);
				tbl->row_count--;
				break;
			}
		}
		Row* temp_2 = temp_1->next;
		while (temp_2 != NULL) {
			if(strcmp(temp_2->type, temp)) {
				if (temp_2->next != NULL) {
					Row* t = temp_2->next;
					free_row(temp_2);
					temp_2 = t;
					tbl->row_count--;
				} else {
					temp_1->next = NULL;
					free_row(temp_2);
					temp_2 = NULL;
					tbl->row_count--;
				}
			} else {
				temp_1->next = temp_2;
				temp_1 = temp_1->next;
				temp_2 = temp_1->next;
			}
		}

		
	} 
	if(tbl->row_count != 0) {
		tbl->field_count = tbl->first_row->field_count;
		Row** r = malloc(sizeof(Row*) * (tbl->row_count));
		int i = 0;
		Row* temp = tbl->first_row;
		while(temp != NULL) {
			r[i++] = temp;
			temp = temp->next;
		}
		tbl->rows = r;
	}

	if(check) {
		for(int i = 0; i < tbl->row_count; i++)
			free_row(tbl->rows[i]);
		tbl->row_count = 0;
	}
	return tbl;
}

int     tbl_column_count( Table * tbl ) {
	return tbl->field_count;
}

Row *   tbl_row_at( Table * tbl, int at ) {
	return tbl->rows[at];
}

char *  tbl_string_at( Row * row, int at) {
	return row->fields[at].s;
}

double  tbl_double_at( Row * row, int at) {
	return row->fields[at].v;
}

int     tbl_row_count( Table * tbl ) {
	return tbl->row_count;
}

void    tbl_print_row( Row * row ) {
	for (int i = 0; i < row->field_count - 1; ++i) {
		if(row->type[i] == 'D') {
			printf("%.2f,", row->fields[i].v);
		} else
			printf("\"%s\",", row->fields[i].s);
	}
	if(row->type[row->field_count - 1] == 'D')
		printf("%.2f\n", row->fields[row->field_count - 1].v);
	else
		printf("\"%s\"\n", row->fields[row->field_count - 1].s);
}

void    tbl_print(Table* tbl) {
	if(tbl->rows == NULL) return;
	Row** r = tbl->rows;
	for(int i = 0; i < tbl_row_count(tbl); ++i) {
		tbl_print_row(r[i]);
	}
}

char    tbl_row_type_at( Row * row , int column ) {
	return row->type[column];
}

Row ** tbl_rows(Table* tbl) {
	return tbl->rows;
}


void    tbl_free(Table *tbl) {
	Row** r = tbl->rows;
	for (int i = 0; i < tbl_row_count(tbl); i++) {
		free_row(r[i]);
	}
	if (tbl->type != NULL)
		free(tbl->type);
	free(r);
	tbl->row_count = 0;
	free(tbl);
}

Table* modify_dbl_table(Table* tbl, double* temp, int total) {
	int class_count = tbl_classes_count(tbl);
	int col_count = tbl_column_count(tbl) - 1;
	int row_count = tbl_row_count(tbl);
	Row** r = tbl_rows(tbl);
	char* ttype = tbl->type;
	ttype[col_count - 1] = 'D';
	for (int i = 0; i < row_count; ++i) {
		for (int j = 0; j < class_count; ++j) {
			if (tbl_double_at(r[i], col_count) == temp[j]) {
				r[i]->fields[col_count].v = j;
				break;
			}
		}		
	}
	return tbl;
}

Table* modify_str_table(Table* tbl, char** temp, int total) {
	int col_count = tbl_column_count(tbl) - 1;
	int row_count = tbl_row_count(tbl);
	Row** r = tbl_rows(tbl);
	char* ttype = tbl->type;
	ttype[col_count] = 'D';
	for (int i = 0; i < row_count; ++i) {
		for (int j = 0; j < total; ++j) {
			if (!strcmp(tbl_string_at(r[i], col_count), temp[j])) {
				free(r[i]->fields[col_count].s);
				r[i]->fields[col_count].v =j;
				r[i]->type[r[i]->field_count - 1] = 'D';
				break;
			}
		}		
	}
	return tbl;
}
	


void set_table_column(Table* tbl, char* col) {
	tbl->col_type = malloc(strlen(col) + 1);
	strcpy(tbl->col_type, col);
}

char* get_table_column(Table* tbl) {
	return tbl->col_type;
}

void free_table_column(Table* tbl) {
	free(tbl->col_type);
}