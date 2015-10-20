#include"defs_itf.h"
extern int uniqueClass;
extern int intClass;
extern char *charClass;
extern int finalClass;

Table* rf_rows(Table *tbl) {
	Row ** rows = tbl_rows(tbl);
	Table *t = tbl_make();
	char *type = tbl_type(tbl);
	int r;
	int rowCount = tbl_row_count(tbl);
	int columnCount = tbl_column_count(tbl);
	for(int i = 0; i < rowCount; i++) {
		r = rand() % (rowCount - 1);
		tbl_start_row(t, columnCount);
		for(int j = 0; j < columnCount; j++) {
			if(type[j] == 'S') {
				tbl_add_string_to_row(t, tbl_string_at(rows[r], j));
				//printf("test: %s\n",  tbl_string_at(rows[r], j));
			}
			else {
				tbl_add_double_to_row(t, tbl_double_at(rows[r], j));
			}
		}
	}
	tbl_done_building(t);
	//tbl_print(t);
	return t;
}

Table* rf_cols(Table *tbl) {
	Table *t = tbl_make();
	int columnCount = tbl_column_count(tbl);
	int rowCount = tbl_row_count(tbl);
	int loopCount = (columnCount - 1) * 2 / 3;
	char *type = tbl_type(tbl);
	int *randomColumns = (int*)malloc(sizeof(int) * loopCount);
	int r;
	for(int i = 0 ; i < loopCount; i++) {
		int flag = 1;
		while(flag) {
			r = rand() % (columnCount - 2);
			if(i == 0) {
				flag = 0;
				break;
			}
			for(int j = 0; j < i; j++) {
				if(randomColumns[j] == r) {
					break;
				}
				if(j == i - 1) {
					flag = 0;
				}
			}
		}
		randomColumns[i] = r;
	}
	for(int i = 0 ; i < rowCount; i++) {
		tbl_start_row(t, loopCount);
		for(int j = 0; j < loopCount; j++) {
			if(type[randomColumns[j]] == 'S') {
				tbl_add_string_to_row(t, tbl_string_at(tbl_row_at(tbl, i), randomColumns[j]));
			}
			else {
				tbl_add_double_to_row(t, tbl_double_at(tbl_row_at(tbl, i), randomColumns[j]));
			}
		}
		if(type[columnCount - 1] == 'S') {
			tbl_add_string_to_row(t, tbl_string_at(tbl_row_at(tbl, i), columnCount - 1));
		}
		else {
			tbl_add_double_to_row(t, tbl_double_at(tbl_row_at(tbl, i), columnCount - 1));
		}
	}
	tbl_done_building(t); 
	free(randomColumns);
	return t;
}

Table** int_mapping(Table *traintbl, Table *validatetbl, int isPrint) {
	int *int_class;
	int class_count = 0;
	int column_count1 = tbl_column_count(traintbl);
	int column_count2 = tbl_column_count(validatetbl);
	int_class = (int*) malloc(sizeof(int) * tbl_row_count(traintbl));
	for(int i = 0; i < tbl_row_count(traintbl); i++) { // getting values from train
		int temp = (int)tbl_double_at(tbl_row_at(traintbl, i), column_count1 - 1);
		if(class_count == 0) {
			int_class[0] = temp;
			class_count++;
		}
		for(int j = 0; j < class_count; j++) {
			if(int_class[j] == temp)
				break;
			if(j == class_count - 1) {
				int_class[class_count] = temp;
				class_count++;
			}					
		}
	}
/*	for(int i = 0; i < tbl_row_count(validatetbl); i++) { // getting values from validate
		int temp = (int)tbl_double_at(tbl_row_at(validatetbl, i), column_count1 - 1);
		if(class_count == 0) {
			int_class[0] = temp;
			class_count++;
		}
		for(int j = 0; j < class_count; j++) {
			if(int_class[j] == temp)
				break;
			if(j == class_count - 1) {
				int_class[class_count] = temp;
				class_count++;
			}					
		}
	} */
	uniqueClass = class_count;
	for(int i = 0; i < class_count; i++) { // sorting
		for(int j = i; j < class_count; j++) {
			if(int_class[i] > int_class[j]) {
				int temp;
				temp = int_class[i];
				int_class[i] = int_class[j];
				int_class[j] = temp;
			}
		}
	}
	if(isPrint) {
		printf("Class mapping:\n");
		for(int i = 0; i < class_count; i++) {
			printf("%d = %d\n", i, int_class[i]);
		}
	}
	for(int i = 0; i < class_count; i++) {
		if(int_class[i] == intClass) {
			finalClass = i;
			break;
		}
	}
	Table **tbl = (Table **)malloc(sizeof(Table*) * 2);
	tbl[0] = tbl_make();
	tbl[1] = tbl_make();
	char* type = tbl_type(traintbl);
	for(int i = 0; i < tbl_row_count(traintbl); i++) {
		tbl_start_row(tbl[0], column_count1);
		for(int j = 0; j < column_count1 - 1; j++) {
			if(type[j] == 'S') {
				tbl_add_string_to_row(tbl[0], tbl_string_at(tbl_row_at(traintbl, i), j));
			}
			else {
				tbl_add_double_to_row(tbl[0], tbl_double_at(tbl_row_at(traintbl, i), j));
			}
		}
		for(int k = 0; k < class_count; k++) {
			if(tbl_double_at(tbl_row_at(traintbl, i), column_count1 - 1) == int_class[k]) {
				tbl_add_double_to_row(tbl[0], k);
				break;
			}
		}
	}
	tbl_done_building(tbl[0]);
	for(int i = 0; i < tbl_row_count(validatetbl); i++) {
		tbl_start_row(tbl[1], column_count2);
		for(int j = 0; j < column_count2 - 1; j++) {
			if(type[j] == 'S') {
				tbl_add_string_to_row(tbl[1], tbl_string_at(tbl_row_at(validatetbl, i), j));
			}
			else {
				tbl_add_double_to_row(tbl[1], tbl_double_at(tbl_row_at(validatetbl, i), j));
			}
		}
		for(int k = 0; k < class_count; k++) {
			if(tbl_double_at(tbl_row_at(validatetbl, i), column_count2 - 1) == int_class[k]) {
				tbl_add_double_to_row(tbl[1], k);
				break;
			}
		}
	}
	tbl_done_building(tbl[1]);
	free(int_class);
	return tbl;
}

Table** string_mapping(Table *traintbl, Table *validatetbl, int isPrint) { // do string mapping. return a table array tbl[0] for train, tbl[1] for validate.
	char **string_class;
	int class_count = 0;
	int column_count1 = tbl_column_count(traintbl);
	int column_count2 = tbl_column_count(validatetbl);
	string_class = (char**) malloc(sizeof(char*) * tbl_row_count(traintbl));
	for(int i = 0; i < tbl_row_count(traintbl); i++) {
		char *temp = tbl_string_at(tbl_row_at(traintbl, i), column_count1 - 1);
		if(class_count == 0) {
			string_class[0] = (char*) malloc(sizeof(char) * (strlen(temp) + 1));
			strcpy(string_class[0], temp);
			class_count++;
		}
		for(int j = 0; j < class_count; j++) {
			if(strcmp(temp, string_class[j]) == 0)
				break;
			if(j == class_count - 1) {
				string_class[class_count] = (char*) malloc(sizeof(char) * (strlen(temp) + 1));
				strcpy(string_class[class_count], temp);
				class_count++;
			}
		}
	}
	uniqueClass = class_count;
/*	for(int i = 0; i < tbl_row_count(validatetbl); i++) {
		char *temp = tbl_string_at(tbl_row_at(validatetbl, i), column_count1 - 1);
		if(class_count == 0) {
			string_class[0] = (char*) malloc(sizeof(char) * (strlen(temp) + 1));
			strcpy(string_class[0], temp);
			class_count++;
		}
		for(int j = 0; j < class_count; j++) {
			if(strcmp(temp, string_class[j]) == 0)
				break;
			if(j == class_count - 1) {
				string_class[class_count] = (char*) malloc(sizeof(char) * (strlen(temp) + 1));
				strcpy(string_class[class_count], temp);
				class_count++;
			}
		}
	} */
	for(int i = 0; i < class_count; i++) {
		for(int j = i; j < class_count; j++) {
			if(strcmp(string_class[i], string_class[j]) > 0) {
				char *temp;
				temp = (char*) malloc(sizeof(char) * (strlen(string_class[i]) + 1));
				strcpy(temp, string_class[i]);
				free(string_class[i]);
				string_class[i] =  (char*) malloc(sizeof(char) * (strlen(string_class[j]) + 1));
				strcpy(string_class[i], string_class[j]);
				free(string_class[j]);
				string_class[j] = (char*) malloc(sizeof(char) * (strlen(temp) + 1));
				strcpy(string_class[j], temp);
				free(temp);
			}
		}
	}
	if(isPrint) {
		printf("Class mapping:\n");
		for(int i = 0; i < class_count; i++) {
			printf("%d = %s\n", i, string_class[i]);
		}
	}
	if(!isPrint) {
		for(int i = 0; i < class_count; i++) {
			if(strcmp(string_class[i], charClass) == 0) {
				finalClass = i;
				break;
			}
		}
	}
	Table **tbl = (Table **)malloc(sizeof(Table*) * 2);
	tbl[0] = tbl_make();
	tbl[1] = tbl_make();
	char* type = tbl_type(traintbl);
	for(int i = 0; i < tbl_row_count(traintbl); i++) {
		tbl_start_row(tbl[0], column_count1);
		for(int j = 0; j < column_count1 - 1; j++) {
			if(type[j] == 'S') {
				tbl_add_string_to_row(tbl[0], tbl_string_at(tbl_row_at(traintbl, i), j));
			}
			else {
				tbl_add_double_to_row(tbl[0], tbl_double_at(tbl_row_at(traintbl, i), j));
			}
		}
		for(int k = 0; k < class_count; k++) {
			if(strcmp(tbl_string_at(tbl_row_at(traintbl, i), column_count1 - 1), string_class[k]) == 0 ) {
				tbl_add_double_to_row(tbl[0], k);
				break;
			}
		}
	}
	tbl_done_building(tbl[0]);

	for(int i = 0; i < tbl_row_count(validatetbl); i++) {
		tbl_start_row(tbl[1], column_count2);
		for(int j = 0; j < column_count2 - 1; j++) {
			if(type[j] == 'S') {
				tbl_add_string_to_row(tbl[1], tbl_string_at(tbl_row_at(validatetbl, i), j));
			}
			else {
				tbl_add_double_to_row(tbl[1], tbl_double_at(tbl_row_at(validatetbl, i), j));
			}
		}
		for(int k = 0; k < class_count; k++) {
			if(strcmp(tbl_string_at(tbl_row_at(validatetbl, i), column_count1 - 1), string_class[k]) == 0 ) {
				tbl_add_double_to_row(tbl[1], k);
				break;
			}
		}
	}
	tbl_done_building(tbl[1]);
	for(int i = 0; i < class_count; i++) {
		free(string_class[i]);
	}
	free(string_class);
	return tbl;
}
