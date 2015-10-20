#include "defs_imp.h"

Table *tbl_make() {
	Table *mytbl = (Table*)malloc(sizeof(Table));
	mytbl->firstRow = NULL;
	mytbl->lastRow = NULL;
	mytbl->rows = NULL;
	mytbl->fieldCount = 0;
	mytbl->rowCount = 0;
	return mytbl;
}

void tbl_start_row(Table *tbl, int num_fields) {
	tbl->rowCount++;
	Row *r = (Row *)malloc(sizeof(Row));
	r->fields = (data *)malloc(num_fields * sizeof(data));
	r->type = (char*)calloc(num_fields,sizeof(char));
	r->field_length = 0;
	r->next = NULL;
	if(tbl->lastRow == NULL) {
		tbl->firstRow = r;
		tbl->lastRow = r;
	} else {
		tbl->lastRow->next = r;
		tbl->lastRow = r;
	}
}

void tbl_add_string_to_row(Table *tbl, char *str) {
	*(tbl->lastRow->type + tbl->lastRow->field_length) = 'S';
	(tbl->lastRow->fields + tbl->lastRow->field_length)->str = (char *)malloc((strlen(str) + 1) * sizeof(char));
	strcpy((tbl->lastRow->fields + tbl->lastRow->field_length)->str,str);
	tbl->lastRow->field_length++;
}

void tbl_add_double_to_row(Table *tbl, double d) {
	*(tbl->lastRow->type + tbl->lastRow->field_length) = 'D';
	(tbl->lastRow->fields + tbl->lastRow->field_length)->db = d;
	tbl->lastRow->field_length++;
}

Table *tbl_done_building(Table *tbl) {
/*	Row *tt;
	tt = tbl->firstRow;
	for(int i = 0; i < tbl->rowCount; i++) {
		tbl_print_row(tt);
		tt = tt->next; 
	} */
//	fprintf(stderr,"Reached");
    char *temp;
	Row *row1;
	Row *row2;
	int count = 0;
	int status = 0;
	row1 = tbl->firstRow;
	for(int i = 0; i < tbl->rowCount; i++) {
		row2 = row1;
		for(int j = i + 1; j < tbl->rowCount; j++) {
			row2 = row2->next;
			if(row1->type != NULL && row2->type != NULL) {
				if(strcmp(row1->type,row2->type) == 0) {
					temp = malloc((row2->field_length+1) * sizeof(char));
					strcpy(temp,row2->type);
					tbl->fieldCount = strlen(temp);
					status = 1;
//					printf("line:%d and line:%d, type: %s\n",i,j,temp);
					break;
				}
			}
		}
		if(status)
			break;
		row1 = row1->next;
	}
	row1 = tbl->firstRow;
	for(int i = 0; i < tbl->rowCount; i++) {
		if(strcmp(row1->type,temp) == 0) {
			count++;
		} else {
//			printf("line:%d freed\n",i);
			free(row1->type);
			row1->type = NULL;
			free(row1->fields);
			row1->fields = NULL;
		}
		row1 = row1->next;
	}
//	printf("count:%d\n",count);
	tbl->rows = (Row**)calloc(count,sizeof(Row));
	row1 = tbl->firstRow;
	for(int i = 0; i < count; i++) {
		while(row1->next != NULL) {
			if(row1->type != NULL) {
//				printf("line %s copied\n",row1->type);
				tbl->rows[i] = row1;
				row1 = row1->next;
				break;
			} else {
				row1 = row1->next;
			}
		}
	}
//	printf("lastRow: %s\n", tbl->lastRow->type);
	if(tbl->lastRow->type != NULL) {
//		printf("HERE WE GO\n");
		tbl->rows[count-1] = tbl->lastRow;
	}
	tbl->rowCount = count;
	return tbl;
}

int tbl_column_count(Table *tbl) {
	return tbl->fieldCount;
}

Row *tbl_row_at(Table *tbl, int at) {
	int index = 0;
	Row *temp =  (Row *)malloc(sizeof(Row));
	temp = tbl->firstRow;
	while(index < at) {
		temp = temp->next;
	}
	return temp;
}

char *tbl_string_at(Row *row, int at) {
	return (row->fields + at)->str;
}

double tbl_double_at(Row *row, int at) {
	return (row->fields + at)->db;
}

void tbl_print_row(Row *row) {
	for(int i = 0; i < row->field_length - 1; i++) {
		if(*(row->type+i) == 'S') {
			printf("\"%s\",",(row->fields+i)->str);
		}
		else if(*(row->type+i) == 'D') {
			printf("%.1f,",(row->fields+i)->db);
		}
	}
	if(*(row->type+row->field_length-1) == 'S') {
		printf("\"%s\"\n",(row->fields + row->field_length-1)->str);
	}
	else if(*(row->type + row->field_length-1) == 'D') {
		printf("%.1f\n",(row->fields+ row->field_length-1)->db);
	}
}
void tbl_print(Table *tbl) {
	for(int i = 0; i < tbl->rowCount; i++) {
		tbl_print_row(tbl->rows[i]);
	}
/*  int index = 0;
    Row *temp = (Row *)malloc(sizeof(Row));
    temp = tbl->firstRow;
    while(temp->next != NULL) {
		tbl_print_row(temp);
        temp = temp->next;
    } */
}

char tbl_row_type_at(Row *row, int column) {
	return row->type[column];
}

int tbl_row_count(Table *tbl) {
	return tbl->rowCount;
}

Row **tbl_rows(Table *tbl) {
	return tbl->rows;
}
