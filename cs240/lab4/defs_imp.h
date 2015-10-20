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
	int field_length;
	} Row;
typedef struct table {
	Row * firstRow;
	Row * lastRow;
	Row ** rows;
	int rowCount;
	int fieldCount;
	} Table;
Table *r_read(FILE *in);
