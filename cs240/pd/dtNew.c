
/*
 * This function builds a decision tree.
 *
 * @param tbl is the table from which the decision tree should be built
 * @param tree is where the decision tree should be stored
 */

Tree* dt_build(Table *tbl) {
	Tree* t;
	t = t_make();
	Node *n = (Node*) malloc(sizeof(Node));
	Column *col;
	char *type = tbl_type(tbl);
	int column_count = tbl_column_count(tbl);
	int row_count = tbl_row_count(tbl);
	int isBase = 0;
	int* class = (int*)malloc(sizeof(int) * row_count);
	for(int i = 0; i < row_count; i++)
		class[i] = tbl_double_at(tbl_row_at(tbl, i), column_count - 1);
	int random_count = column_count * 2 / 3;
	double column_entropy = (int*)malloc(sizeof(int) * random_count);
	int entropy_count = 0;
	int* rindex = (int*)malloc(sizeof(int) * random_count);
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
	}

	for(int i = 0; i < random_count; i++) {
		int index = rindex[i];
		if(type[index] == 'S') { // this is a string column
			char **fields = (char**)malloc(sizeof(char*) * row_count);
			for(int j = 0; j < row_count; j++) { // copying the values into fields
				fields[j] = tbl_string_at(tbl_row_at(tbl, j), index));
			}
			col = make_string_column(fields, class, row_count);
			if(is_impossible_split(col)) {
				free(fields);
				free_column(col);
				isBase = 1;
				break;
			}
			column_entropy[i] = calc_entropy(col);
			entropy_count++;
			free(fields);
			free_column(col);
		}
		else {
			double *fields = (double*)malloc(sizeof(double) * row_count);
			for(int j = 0; j < row_count; j++) {
				fields[j] = tbl_double_at(tbl_row_at(tbl,j), index);
			}
			col = make_double_column(fields, class, row_count);
			column_entropy[i] = calc_entropy(col);
			entropy_count++;
			free(fields);
			free_column(col);
		}
	}


}

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
