/*
 * Array pointer as a function parameter
 * 2020-07-18
 */

#include <stdlib.h>
#include "../test.h"

#define ARR_ROW 10
#define ARR_COL 10

/*
 * pointer to pointer as function parameter
 */
static int __test_ptr_ptr(int **arr, int *row, int *col)
{
	int i, j;
	*row = ARR_ROW;
	*col = ARR_COL;

	for (i = 0; i < *row; i++) {
		arr[i] = (int *)malloc(*col * sizeof(int));
	}

	for (i = 0; i < *row; i++){
		for (j = 0; j < *col; j++) {
			arr[i][j] = i * 10 + j;
		}
	}
	return 0;
}

int test_func_param(void)
{
	int ret;
	int i, j;
	int row, col;
	int **arr = (int **)malloc(ARR_ROW * sizeof(int *));

	ret = __test_ptr_ptr(arr, &row, &col);
	if (ret < 0) {
		mt_error("pointer to pointer as function parameter failed\n");
		return ret;
	}

	mt_info("row = %d, col = %d\n", row, col);
	for (i = 0; i < row; i++) {
		printf("row[%d]: ", i);
		for (j = 0; j < col; j++) {
			printf("%3d ", arr[i][j]);
		}
		printf("\n");
	}

	return 0;
}
