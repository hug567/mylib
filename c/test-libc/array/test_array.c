/*
 * 数组测试
 * 2020-07-30
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../test.h"

static int test_array_increment(void)
{
    int i;
    int array[10];

    for (i = 0; i < 10; i++) {
        array[i] = i;
        array[i]++;
        printf("%d ", array[i]);
    }
    printf("\n");

    return 0;
}

static void __test_arr_param(int **arr, int *size)
{
	int i;

	*size = 10;
	*arr = (int *)malloc(10 * sizeof(int));
	for (i = 0; i < 10; i++) {
		*arr[i] = i;
	}
}

/*
 * 一维数组作为函数输出参数
 */
static int test_arr_param(void)
{
	//int i;
	int size;
	int *arr = NULL;

	__test_arr_param(&arr, &size);
	mt_info("size = %d\n", size);

	return 0;
}

int test_array(void)
{
    test_array_increment();
    test_arr_param();
    return 0;
}
