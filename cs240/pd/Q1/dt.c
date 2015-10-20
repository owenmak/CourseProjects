#include "defs_itf.h"


/*
 * This function builds a decision tree.
 *
 * @param tbl is the table from which the decision tree should be built
 * @param tree is where the decision tree should be stored
 */

Tree *getTree(Table *tbl) {
	Tree *t = t_make();
	Node *n = (Node*)malloc(sizeof(Node)); // NODE ALLOCATED
	char *columnType = tbl_type(tbl);
	int columnCount = tbl_column_count(tbl); // count with the class included
	int isBase = 0;
	int baseIndex = -1;
	double *columnEntropy = (double *)malloc(sizeof(double) * (columnCount - 1)); // free columnEntropy TODO
	int *class = (int *) malloc(tbl_row_count(tbl) * sizeof(int));
	for(int i = 0; i < tbl_row_count(tbl); i++) {
		class[i] = (int)tbl_double_at(tbl_row_at(tbl,i), columnCount - 1);
	}
	Column * column;
	int maxEntroIndex = 0;
	for(int i = 0; i < columnCount - 1; i++) { // getting the entropy for every column
		if(columnType[i] == 'S') {
			char **field = (char **)malloc(sizeof(char *) * tbl_row_count(tbl)); // free() FIELD TODO
			for(int j = 0; j < tbl_row_count(tbl); j++) {
				field[j] = (char *)malloc(strlen(tbl_string_at(tbl_row_at(tbl, j), i)) + 1);
				strcpy(field[j], tbl_string_at(tbl_row_at(tbl, j), i));
			}
			column = make_string_column(field, class, tbl_row_count(tbl));
			for(int i = 0; i < tbl_row_count(tbl); i++) {
				free(field[i]);
			}
			free(field); // field FREED
			if(is_impossible_split(column)) {
				free_column(column);
				free(columnEntropy);
				isBase = 1;
				baseIndex = i;
				break;
			}
			columnEntropy[i] = find_string_split_entropy(column);
			free_column(column);
		}
		else {
			double *field = (double *)malloc(sizeof(double) * tbl_row_count(tbl)); // free() FIELD TODO
			for(int j = 0; j < tbl_row_count(tbl); j++) {
				field[j] = tbl_double_at(tbl_row_at(tbl, j), i);
			}
			column = make_double_column(field, class, tbl_row_count(tbl)); 
			free(field); // field FREED
			if(is_impossible_split(column)) {
				free(columnEntropy);
				free_column(column);
				isBase = 1;
				baseIndex = i;
				break;
			}
			columnEntropy[i] = find_double_split_entropy(column);
			free_column(column);
		}
	}
	if(isBase) {
		n->leaf = 1;
		n->class = class[baseIndex];
		t_set_data(t ,n);
		t_set_left(t, NULL);
		t_set_right(t, NULL);
		return t;
	}
	for(int i = 1; i < columnCount - 1; i++) {
		if(columnEntropy[maxEntroIndex] > columnEntropy[i])
			maxEntroIndex = i;
	}
	n->leaf = 0;
	n->entropy = columnEntropy[maxEntroIndex];
	n->type = columnType[maxEntroIndex];
	Field f;
	Table *ltbl = tbl_make(); // left table
	Table *rtbl = tbl_make(); // right table
	if(n->type == 'S') {
		char **field = (char **)malloc(sizeof(char *) * tbl_row_count(tbl)); // free() FIELD TODO
		for(int i = 0; i < tbl_row_count(tbl); i++) {
			field[i] = (char *)malloc(strlen(tbl_string_at(tbl_row_at(tbl, i), maxEntroIndex)) + 1);
			strcpy(field[i], tbl_string_at(tbl_row_at(tbl, i), maxEntroIndex));
		}
		column = make_string_column(field, class, tbl_row_count(tbl));
		for(int i = 0; i < tbl_row_count(tbl); i++)
				free(field[i]);
		free(field);
		f.s = (char *)malloc((strlen(find_string_split_value(column)) + 1) * sizeof(char) );
		strcpy(f.s, find_string_split_value(column));
		for(int i = 0; i < tbl_row_count(tbl); i++) {
			if(strcmp(tbl_string_at(tbl_row_at(tbl, i), maxEntroIndex), f.s) == 0) {
				tbl_start_row(ltbl, columnCount);
				for(int j = 0; j < columnCount; j++) {
					if(columnType[j] == 'S') {
						tbl_add_string_to_row(ltbl, tbl_string_at(tbl_row_at(tbl, i), j));
					}
					else {
						tbl_add_double_to_row(ltbl, tbl_double_at(tbl_row_at(tbl, i), j));
					}
				}
			}
			else {
				tbl_start_row(rtbl, columnCount);
				for(int j = 0; j < columnCount; j++) {
					if(columnType[j] == 'S') {
						tbl_add_string_to_row(rtbl, tbl_string_at(tbl_row_at(tbl, i), j));
					}
					else {
						tbl_add_double_to_row(rtbl, tbl_double_at(tbl_row_at(tbl, i), j));
					}
				}
			}
		}
		tbl_done_building(ltbl);
		tbl_done_building(rtbl);
		free_column(column);
	}
	else if(n->type == 'D') {
		double *field = (double *)malloc(sizeof(double) * tbl_row_count(tbl)); // free() FIELD TODO
		for(int i = 0; i < tbl_row_count(tbl); i++) {
			field[i] = tbl_double_at(tbl_row_at(tbl, i), maxEntroIndex);
		}
		column = make_double_column(field, class, tbl_row_count(tbl)); 
		free(field); // field FREED
		f.d = find_double_split_value(column);
		for(int i = 0; i < tbl_row_count(tbl); i++) {
			if(tbl_double_at(tbl_row_at(tbl, i), maxEntroIndex) <= f.d) {
				tbl_start_row(ltbl, columnCount);
				for(int j = 0; j < columnCount; j++) {
					if(columnType[j] == 'S') {
						tbl_add_string_to_row(ltbl, tbl_string_at(tbl_row_at(tbl, i), j));
					}
					else {
						tbl_add_double_to_row(ltbl, tbl_double_at(tbl_row_at(tbl, i), j));
					}
				}
			}
			else {
				tbl_start_row(rtbl, columnCount);
				for(int j = 0; j < columnCount; j++) {
					if(columnType[j] == 'S') {
						tbl_add_string_to_row(rtbl, tbl_string_at(tbl_row_at(tbl, i), j));
					}
					else {
						tbl_add_double_to_row(rtbl, tbl_double_at(tbl_row_at(tbl, i), j));
					}
				}
			}
		}
		tbl_done_building(rtbl);
		tbl_done_building(ltbl);
		free_column(column);
	}
	n->field = f;
	n->column = maxEntroIndex;
	n->class = class[maxEntroIndex]; // CLASS TODO
	t_set_data(t, n);
	free(class);
	t_set_left(t, getTree( ltbl)); //tbl edit TODO
	t_set_right(t, getTree(rtbl)); // tbl edit TODO
//	if(ltbl != NULL)
//		tbl_free(ltbl);
//	if(rtbl != NULL)
//		tbl_free(rtbl);
	return t;
}

void dt_build(Table *tbl, Tree *tree) {
	*tree = *getTree(tbl);
}

/*
 * This function should be passed to t_free() with the decision tree
 * to free all the memory allocated for your decision tree.
 *
 * @param data is the data that will be freed
 */
void dt_free(void *data) {
	if(data == NULL) {
		return;
	}
	if(((Node*)data)->type == 'S') {
		free(((Node*)data)->field.s);
	}
	free(data);
}

/*
 * This function should be passed to t_print() to print your tree. The tree
 * should be printed as follows:
 * 
 * colname=value
 *  C:class
 *  etc..
 *
 * @param data is the data to be printed
 */
void dt_print(void *data) {
	if(data == NULL) {
		return;
	}
	if (((Node*)data)->leaf == 1) {
		printf("C:%d\n", ((Node*)data)->class);
		return;
	}
	printf("%s=", colnames[((Node*)data)->column]);
	if(((Node*)data)->type == 'S')
		printf("%s\n", ((Node*)data)->field.s);
	else
		printf("%.2f\n", ((Node*)data)->field.d);
}

char **colnames;
