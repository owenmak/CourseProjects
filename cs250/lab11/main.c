#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ROWS 5000
#define MAX_COLUMNS 5000

struct array_info
{
		int	rows;
		int	columns;
		int order;
		char *base_pointer; /* pointer to array of bytes. In this array, float numbers will be stored (4 bytes each) */
};

struct array_info* init(int, int, int);
void store(struct array_info*, int, int, float);
float fetch(struct array_info*, int, int);
double calc_time_to_read(struct array_info*);

int main()
{
 int n_rows, n_columns, order, row_index, column_index;
 float out_value, in_value;
 int in;
 struct array_info *matrix;
 printf("Enter the total number of rows: \t");
 scanf("%d", &n_rows);
 printf("Enter the total number of columns: \t");
 scanf("%d", &n_columns);
 printf("Select the order (0-Row major order, 1-Column major order): \t");
 scanf("%d", &order);
 matrix = init(n_rows, n_columns, order);
 if(matrix == NULL)
 {
     printf("\n Error Creating the Array\n");
     return 0;
 }
 printf("\n 2-D Array has been initialized\n");
 while(1)
 {
     printf("\n 1 - Store a value \n 2 - Fetch a value \n 3 - Calculate time to read the entire array  \n 4 - Exit\n Enter your choice:\t");
     scanf("%d", &in);
     switch(in)
     {
     case 1:
        printf("Enter row number, column number and a value with spaces between them:\t");
        scanf("%d %d %f", &row_index, &column_index, &in_value);
        store(matrix, row_index, column_index, in_value);
        printf("Value stored successfully\n");
        break;
     case 2:
        printf("Enter row number and column number with spaces between them:\t");
        scanf("%d %d", &row_index, &column_index);
        out_value=fetch(matrix, row_index, column_index);
        printf("Fetched value at (%d, %d)= %f\n", row_index, column_index, out_value);
        break;
    case 3:
        printf("Time to read the entire array is %f secs\n", calc_time_to_read(matrix));
        break;
     case 4:
     default:
        return 0;
     }
 }
}


struct array_info* init(int rows, int columns, int order)
{
	if(rows > MAX_ROWS || rows < 1 || columns < 1 || columns > MAX_COLUMNS)
		return NULL;
	struct array_info* e;
	e = (struct array_info*)malloc(sizeof(struct array_info));
	e->rows = rows;
	e->columns = columns;
	e->order = order;
	e->base_pointer = calloc(columns * rows, sizeof(float));
	return e;
	
  /* Allocate the required memory for the 2D array to store float values (Ex: 1.45) with "rows" and "columns" */
  /* Make sure the size is within 1 to MAX_ROWS and 1 to MAX_COLUMNS specified in main.c. If not return null pointer */
  /* Initialize the 2D array to the all zeroes (0.0) */
  /* Assign suitable values to all the elements of the structure and return the struct pointer */
}

void store(struct array_info *array, int row_index, int column_index, float value)
{
	int index;	
	if(array->order == 0) {
		index = row_index * array->columns + column_index;
		memcpy(array->base_pointer + index, &value, sizeof(float));
	}
	else {
		unsigned char p[sizeof(float)];
		memcpy(p, &value, sizeof(float));	
		index = column_index * array->rows + row_index;
		int dif = array->rows;
		*(array->base_pointer + index) = p[0];
		*(array->base_pointer + index + array->rows) = p[1];
		*(array->base_pointer + index + array->rows * 2) = p[2];
		*(array->base_pointer + index + array->rows * 3) = p[3];
	}

//	memcpy(array->base_pointer + index, &value, sizeof(float));
//	for(int i = 0; i < 4; i++) {
//		*(array->base_pointer + index + i) = p[i];
//		printf("%d:%d,%d\n",i, *(array->base_pointer + index + i), p[i]);
//	}
//		printf("%d:%d\n", i, *(array->base_pointer + index));
   /* Store the "value" to the location (row_index, column_index) of the array whose details are in struct pointer *array */
   /* Assume row-major order if "order"=0 and column-major order if "order"=1 */
}

float fetch(struct array_info *array, int row_index, int column_index)
{
	float num;
	int index;
	if(array->order == 0) {
		index = row_index * array->columns + column_index;
		memcpy(&num, (array->base_pointer+index), sizeof(float));
	}
	else {
		index = column_index * array->rows + row_index;
		char p[4];
		for(int i = 0; i < 4; i++) {
			p[i] = *(array->base_pointer + index + i * array->rows);
		}
		memcpy(&num, p, sizeof(float));
	}
/*	unsigned char p[sizeof(float)];
	float num;
	int index;
	if(array->order = 0)
		index = row_index * array->columns + column_index;
	else
		index = column_index * array->rows + row_index;

	for(int i = 0; i < 4; i++) {
		p[i] = (unsigned char) *(array->base_pointer + index + i);
//		printf("%d:%d,%d\n",i, *(array->base_pointer + index + i), p[i]);
	}
	memcpy(&num, p, sizeof(float));*/
	return num;	
    /* Fetch the value from the location (row_index, column_index) of the array whose details are in struct pointer *array */
    /* Assume row-major order if "order"=0 and column-major order if "order"=1 */
    /* Return the fetched value */
}

double calc_time_to_read(struct array_info* array)
{
	clock_t begin, end;
	long int i,j;
	float value;
	begin = clock();
	for(i = 0; i < array->rows; i++) {
		for(j = 0; j < array->columns; j++) {
			fetch(array, i, j);
		}
	}
     /* Fetch back the whole array in the order 10, 20, 30, 40, 50, 60 assuming the 2x3 array given above irrespective of the order */
     /* Do not print the values, just fetch them and keep discarding. */
     /* We just need to evaluate the time to read from memory, not verifying the correctness of the content */
     end = clock();
     return (double)(end - begin)/CLOCKS_PER_SEC;
}
