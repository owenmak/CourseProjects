#include "column.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef union Data {
	double *db;
	char **str;
} data;

//implement the column, in type, 0 for double, 1 for string
typedef struct column {
	int count;
	int type;
	data *value;
	unsigned int* class;
} Column;

Column *make_double_column(double *fields, unsigned int* classes, unsigned int n) {
	Column *col;
	col = (Column*)malloc(sizeof(Column) * n);
	col->count = n;
	col->type = 0;
	col->value = (data*)malloc(sizeof(data));
	col->value->db = (double*)malloc(sizeof(double) * n);
	col->class = (int*)malloc(sizeof(int) * n);
	for(int i = 0; i < n; i++) {
		*(col->value->db + i) = *(fields + i);
		*(col->class + i) = *(classes + i);
	}
	return col;
}

Column *make_string_column(char **fields, unsigned int* classes, unsigned int n) {
    Column *col;
    col = (Column*)malloc(sizeof(Column) * n);
    col->count = n;
    col->type = 1;
	col->value = (data*)malloc(sizeof(data));
    col->value->str = (char**)malloc(sizeof(char*) * n);
    col->class = (int*)malloc(sizeof(int) * n);
    for(int i = 0; i < n; i++) {
		col->value->str[i] = (char*) malloc(sizeof(char) * (strlen(fields[i]) + 1));
        strcpy(col->value->str[i],fields[i]);
        *(col->class + i) = *(classes + i);
    }
    return col;
}

void free_column(Column *column) {
	free(column->class);
	if(column->type == 0) {
		free(column->value->db);
	}
	else {
		for(int i = 0; i < column->count; i++) {
			free(column->value->str[i]);
		}
		free(column->value->str);
	}
	free(column->value);
	free(column);
}

int has_single_value(Column *column) {
    if(column->count == 1)
		return 1;
	if(column->type == 0) {
		for(int i = 0; i < column->count; i++) {
			for(int j = 0; j < column->count; j++) {
				if(column->value->db[i] != column->value->db[j]) {
					return 0;
				}
			}
		}
	}
	else {
		for(int i = 0; i < column->count; i++) {
            for(int j = 0; j < column->count; j++) {
                if(strcmp(column->value->str[i], column->value->str[j]) != 0) {
					return 0;
				}
            }
        }
	}
	return 1;
}

int is_impossible_split(Column *column) {
	if(column->count == 1)
		return 1;
	for(int i = 0; i < column->count - 1; i++) {
		if(column->class[i] != column->class[i+1])
			return 0;
		else if(i == column->count - 2)
			return 1;
	}
}

double get_pi(Column *column, int class) {
	double num = 0.0;
	double pi;
	for(int i = 0; i < column->count; i++) {
		if(column->class[i] == class)
			num += 1.0;
	}
	if(num < 1.0)
		return 0;
	pi = num/column->count;
	return pi * log2(pi);
}

double calc_entropy(Column *column) {
	double entropy = 0.0;
	double pi;
	int m = 0;
	for(int i = 0; i < column->count; i++) {
		if(column->class[i] > m) {
			m = column->class[i];
		}
	}
	for(int i = 0; i <= m; i++) {
		entropy -= get_pi(column, i);
	}
	return entropy;
}


double find_double_split_value(Column *column) {
	int *class1;
	int *class2;
	int *validCol;
	double *entropy;
	double *field1;
	double *field2;
	Column *col1;
	Column *col2;
	int count1 = 0;
	int count2 = 0;
	int min;
	validCol = (int*)malloc(sizeof(int) * column->count);
	for(int i = 0; i < column->count; i++) {
		validCol[i] = 1;
	}
	entropy = (double*)malloc(sizeof(double) * column->count);
	for(int i = 0; i < column->count; i++) {
		field1 = (double *)malloc(sizeof(double) * column->count);
		field2 = (double *)malloc(sizeof(double) * column->count);
		class1 = (int *)malloc(sizeof(int) * column->count);
		class2 = (int *)malloc(sizeof(int) * column->count);
		for(int j = 0; j < column->count; j++) {
			if(column->value->db[j] <= column->value->db[i]) {
				field1[count1] = column->value->db[j];
				class1[count1] = column->class[j];
				count1++;
			}
			else {
				field2[count2] = column->value->db[j];
				class2[count2] = column->class[j];
				count2++;
			}
		}
		if(count1 == 0 || count2 == 0) {
			validCol[i] = 0;
			entropy[i] = 0;
			free(field1);
			free(field2);
			free(class1);
			free(class2);
			count1 = 0;
			count2 = 0;
			continue;
		}
		col1 = make_double_column(field1, class1, count1);
		col2 = make_double_column(field2, class2, count2);
		entropy[i] = calc_entropy(col1) * count1 + calc_entropy(col2) * count2;
		free(class1);
		free(class2);
		free(field1);
		free(field2);
		free_column(col1);
		free_column(col2);
		count1 = 0;
		count2 = 0;
	}
	for(int i = 0; i < column->count; i++) {
		if(validCol[i] != 0) {
			min=i;
			break;
		}
	}
	for(int i = min; i < column->count; i++) {
		if(validCol[i] == 0)
			continue;
		if(entropy[min] > entropy[i]) {
			min = i;
		}
	}
	free(entropy);
	free(validCol);
	return column->value->db[min];
}

char *find_string_split_value(Column *column) {
	int *class1;
	int *class2;
	double *entropy;
	char **field1;
	char **field2;
	Column *col1;
	Column *col2;
	int count1 = 0;
	int count2 = 0;
	int min;
	entropy = (double*)malloc(sizeof(double) * column->count);
	for(int i = 0; i < column->count; i++) {
		field1 = (char**)malloc(sizeof(char*) * column->count);
		field2 = (char**)malloc(sizeof(char*) * column->count);
		class1 = (int *)malloc(sizeof(int) * column->count);
		class2 = (int *)malloc(sizeof(int) * column->count);
		for(int j = 0; j < column->count; j++) {
			if(strcmp(column->value->str[j], column->value->str[i]) == 0) {
				field1[count1] = (char*)malloc(sizeof(char)*(strlen(column->value->str[j]) + 1));
				strcpy(field1[count1],column->value->str[j]);
				class1[count1] = column->class[j];
				count1++;
			}
			else {
				field2[count2] = (char*)malloc(sizeof(char)*(strlen(column->value->str[j]) + 1));
                strcpy(field2[count2],column->value->str[j]);
				class2[count2] = column->class[j];
				count2++;
			}
		}
		col1 = make_string_column(field1, class1, count1);
		col2 = make_string_column(field2, class2, count2);
		entropy[i] = calc_entropy(col1) * count1 + calc_entropy(col2) * count2;
		free(class1);
		free(class2);
		for(int i = 0; i < count1; i++)
			free(field1[i]);
		for(int i = 0; i < count2; i++)
			free(field2[i]);
		free(field1);
		free(field2);
		free_column(col1);
		free_column(col2);
		count1 = 0;
		count2 = 0;
	}
	min = 0;
	for(int i = 1; i < column->count; i++) {
		if(entropy[min] > entropy[i]) {
			min = i;
		}
	}
	free(entropy);
	return column->value->str[min];
}


