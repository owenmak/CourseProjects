#include "defs_itf.h"

ConfMatrix* cm_make(int  classes) {
	ConfMatrix *cm = malloc(sizeof(ConfMatrix));
	cm->matrix = (int **)calloc(classes+1, sizeof(int*));
	for(int i = 0; i <= classes; i++) {
		cm->matrix[i] = (int *)calloc(classes+1, sizeof(int));
	}
	for(int i = 0; i <= classes; i++) {
		for(int j = 0; j <= classes; j++) {
			cm->matrix[i][j] = 0;
		}
	}
	cm->count = classes;
	cm->total = 0;
	cm->error = 0;
	return cm;
}

void getClasses(ConfMatrix *cm, Table *tbl) {
    int *classes = (int*)malloc(tbl_row_count(tbl) * sizeof(int));
    int count = 1;
    int class;
	int temp;
    classes[0] = tbl_double_at(tbl_row_at(tbl, 0), tbl_column_count(tbl) - 1);
    for(int i = 1; i < tbl_row_count(tbl); i++) {
        class = tbl_double_at(tbl_row_at(tbl, i), tbl_column_count(tbl) - 1);
        for(int j = 0; j < count; j++) {
            if(class == classes[j])
                break;
            if(j == count - 1) {
                classes[count] = class;
                count++;
            }
        }
	}
	for(int i = 0; i <count; i++) {
		for(int j = i; j < count; j++) {
			if(classes[i] > classes[j]) {
				temp = classes[i];
				classes[i] = classes[j];
				classes[j] = temp;
			}
		}
	}
	for(int i = 1; i <= count; i++) {
		cm->matrix[0][i] = classes[i - 1];
		cm->matrix[i][0] = classes[i - 1];
	}
	cm->matrix[0][0] = -1;
	free(classes);
}


int getValue(Row *row, Tree *tree) {
	Node* n = (Node*)t_data(tree);
	if(n->leaf == 1) // base case
		return n->class;
	if(n->type == 'S') {
		if(strcmp(tbl_string_at(row, n->column), n->field.s) == 0)
			return getValue(row, t_left(tree));
		else
			return getValue(row, t_right(tree));
	}
	else {
		if(tbl_double_at(row, n->column) <= n->field.d)
			return getValue(row, t_left(tree));
		else
			return getValue(row, t_right(tree));
	}
}

void cm_free(ConfMatrix* cm) {
	for(int i = 0; i < cm->count; i++) {
		free(cm->matrix[i]);
	}
	free(cm->matrix);
	free(cm);
}

int voteValue(Row *row,Tree **tree, int tree_num) {
	int *value = (int*)malloc(sizeof(int) * tree_num);
	int *count = (int*)malloc(sizeof(int) * tree_num);
	int vote_index = 0;
	int vote_value;
	for(int i = 0; i < tree_num; i++) {
		value[i] = getValue(row, tree[i]);
		//printf("TEST%d:%d\n",i, value[i]);
		//t_print(tree[i], 0, dt_print);
	}
	for(int i = 0; i < tree_num; i++) {
		for(int j = 0; j < tree_num; j++) {
			if(value[j] == value[i]) {
				count[i]++;
			}
		}
	}
	//for(int  x = 0; x < tree_num; x++)
		//
	for(int i = 1; i < tree_num; i++) {
		if(count[vote_index] < count[i]) {
			vote_index = i;
		}
	}
	vote_value = value[vote_index];
	free(value);
	free(count);
	return vote_value;
}

void cm_validate(ConfMatrix *cm, Table *tbl, Tree **tree, int tree_num) {
	int realValue;
	int predValue;
	int xIndex;
	int yIndex;
	cm->total = tbl_row_count(tbl);
	cm->error = cm->total;
	getClasses(cm, tbl);
	for(int i = 0; i < tbl_row_count(tbl); i++) {
		Row *r = tbl_row_at(tbl, i);
		realValue = (int)tbl_double_at(r, tbl_column_count(tbl) - 1);
		predValue = voteValue(r, tree, tree_num);
		for(int i = 1; i <= cm->count; i++) {
			if(cm->matrix[0][i] == realValue)
				xIndex = i;
			if(cm->matrix[i][0] == predValue)
				yIndex = i;
		}
		cm->matrix[xIndex][yIndex]++;
	}
	for(int i = 1; i <= cm->count; i++) {
		cm->error -= cm->matrix[i][i];
	}
}

void cm_print(ConfMatrix* cm) {
	printf("Confusion matrix: total=%d, errors=%d \n", cm->total, cm->error);
	printf(" |");
	for(int i = 0; i < cm->count; i++) {	// prints the first line
		printf(" %d", cm->matrix[0][i+1]);
	}
	printf("\n");
	for(int i = 0; i < cm->count; i++) {
		printf("%d|", cm->matrix[i+1][0]);
		for(int j = 0; j < cm->count; j++) {
			printf("%d,", cm->matrix[i+1][j+1]);
		}
		printf("\n");
	}
}

int tbl_classes_count(Table * tbl) {
	int *classes = (int*)malloc(tbl_row_count(tbl) * sizeof(int));
	int count = 1;
	int class;
	classes[0] = tbl_double_at(tbl_row_at(tbl, 0), tbl_column_count(tbl) - 1);
	for(int i = 1; i < tbl_row_count(tbl); i++) {
		class = tbl_double_at(tbl_row_at(tbl, i), tbl_column_count(tbl) - 1);
		for(int j = 0; j < count; j++) {
			if(class == classes[j])
				break;
			if(j == count - 1) {
				classes[count] = class;
				count++;
			}
		}
	}
	free(classes);
	return count;
}
