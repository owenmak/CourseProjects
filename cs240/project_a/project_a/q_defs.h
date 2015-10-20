typedef union Data{
	char* str;
	double db;
} data;

typedef struct Info{
	char* colName;
	char valueType;
	char* conditional;	
	data* value;
} info;

#include "defs_itf.h"
