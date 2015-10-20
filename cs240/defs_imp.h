#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <math.h>
#include "reader.h"
#include "cargs.h"

typedef union Data {
	double db;
	char * str;
} data;
typedef struct row {
	data * fields;
	char * type;
	struct row *next;
	int num_field;
	} Row;
typedef struct table {
	Row * firstRow;
	Row * lastRow;
	Row ** rows;
	int row_count;
	int column_count;
	} Table;
Table *r_read(FILE *in);
