#include "defs_itf.h"


/*
 * This function builds a decision tree.
 *
 * @param tbl is the table from which the decision tree should be built
 * @param tree is where the decision tree should be stored
 */

Tree *getTree(Table *tbl) {
//	printf("Now printing a table:\n");
//	tbl_print(tbl);
	if(tbl_column_count(tbl) == 0)
		return NULL;
	Tree *t = t_make();
	Node *n = (Node*)malloc(sizeof(Node)); // NODE ALLOCATED
	char *columnType = tbl_type(tbl);
	int columnCount = tbl_column_count(tbl); // count with the class included
	int random_count = (columnCount - 1) * 2 / 3;
	int isBase = 0;
	int baseIndex = -1;
	double *columnEntropy = (double *)malloc(sizeof(double) * random_count); // free columnEntropy TODO
	int *class = (int *) malloc(tbl_row_count(tbl) * sizeof(int));
	for(int i = 0; i < tbl_row_count(tbl); i++) {
		class[i] = (int)tbl_double_at(tbl_row_at(tbl,i), columnCount - 1);
//		printf("CLASS:%d\n", class[i]);
	}
	Column * column;
	int maxEntroIndex = 0;
	int *rindex = (int*) malloc(sizeof(int) * random_count);
	int random_index = 0;
	for(int i = 0; i < random_count; i++) {
		int flag = 1;
		int rcolumn;
		while(flag) {
			rcolumn = rand() % columnCount;
			if(random_index == 0) {
				flag = 0;
			}

			for(int j = 0; j < random_index; j++) {
				if(rindex[j] == rcolumn) {
					break;
				}
				if(j == random_index - 1) {
					flag = 0;
				}
			}
		}
//		printf("got one random columnCount!\n");
		rindex[random_index] = rcolumn;
		random_index++;
	}
//	printf("randoming numbers from %d:",random_count);
//	for(int i = 0 ; i < random_count; i++) {
//		printf("%d\t",rindex[i]);
//	}
//	printf("\n");

//	for(int i = 0; i < columnCount - 1; i++) { // getting the e /ntropy for every column
	for(int l = 0; l < random_count; l++) {
		int i = rindex[l];
		if(columnType[i] == 'S') {
			char **field = (char **)malloc(sizeof(char *) * tbl_row_count(tbl)); // free() FIELD TODO
			for(int j = 0; j < tbl_row_count(tbl); j++) {
				field[j] = (char *)malloc(strlen(tbl_string_at(tbl_row_at(tbl, j), i)) + 1);
				strcpy(field[j], tbl_string_at(tbl_row_at(tbl, j), i));
			}
			column = make_string_column(field, class, tbl_row_count(tbl));
			for(int k = 0; k < tbl_row_count(tbl); k++) {
				free(field[k]);
			}
			free(field); // field FREED
			if(is_impossible_split(column)) {
				free_column(column);
				free(columnEntropy);
				isBase = 1;
				baseIndex = i;
				break;
			}
			columnEntropy[l] = find_string_split_entropy(column);
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
			columnEntropy[l] = find_double_split_entropy(column);
			free_column(column);
		}
	}
	if(isBase) {
		n->leaf = 1;
		n->class = class[0];
//		printf("random_count:%d\n",random_count);
//		for(int i = 0; i < tbl_row_count(tbl); i++) {
	//	class[i] = (int)tbl_double_at(tbl_row_at(tbl,i), columnCount - 1);
//		printf("CLASS%d:%d\t\t",i, class[i]);
//		}
//		printf("GGGG:%d\tbase case:%d,%d\n", n->class, baseIndex,class[baseIndex]);  // problem
//		printf("class_count:%d\n",tbl_row_count(tbl));
		t_set_data(t ,n);
		t_set_left(t, NULL);
		t_set_right(t, NULL);
		return t;
	}
	for(int i = 1; i < random_count; i++) {
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
	if(tbl_row_count(rtbl) == 0 || tbl_row_count(ltbl) == 0) {
		n->leaf = 1;
		n->class = class[0];
//		printf("random_count:%d\n",random_count);
//		for(int i = 0; i < tbl_row_count(tbl); i++) {
	//	class[i] = (int)tbl_double_at(tbl_row_at(tbl,i), columnCount - 1);
//		printf("CLASS%d:%d\t\t",i, class[i]);
//		}
//		printf("GGGG:%d\tbasecase:%d\n", n->class, baseIndex);  // problem
		t_set_data(t ,n);
		t_set_left(t, NULL);
		t_set_right(t, NULL);
		return t;
	}
	n->field = f;
	n->column = maxEntroIndex;
	n->class = class[maxEntroIndex]; // CLASS TODO
			//printf("WWWW:%d\n", n->class);
	t_set_data(t, n);
	free(class);
	t_set_left(t, getTree(ltbl)); //tbl edit TODO
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
	printf("NAME=");
	if(((Node*)data)->type == 'S')
		printf("%s\n", ((Node*)data)->field.s);
	else
		printf("%.2f\n", ((Node*)data)->field.d);
}

char **colnames;
