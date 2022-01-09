/*
 * C语言做leetcode题需了解的场景
 * 2021-1-5
 */
#include "common.h"

/******************************************************************************/
/*
 * 一维数组作为输出参数
 * 返回二维数组
 */
int **test_alloc_array(int *retSize, int **retColSize)
{
    int i, j;
    int row = 5, col = 10;
    int **ret = NULL;

    *retSize = row; /* 行 */
    *retColSize = malloc(*retSize * sizeof(int));
    ret = malloc(*retSize * sizeof(int *)); /* 每行首指针 */
    for (i = 0; i < *retSize; i++) {
        *(*retColSize + i) = col;
        *(ret + i) = malloc(col * sizeof(int)); /* 列 */
    }
    for (i = 0; i < *retSize; i++) {
        for (j = 0; j < *(*retColSize + i); j++) {
            *(*(ret + i) + j) = i + j; /* 访问arr[i][j] */
        }
    }
    return ret;
}

void TestCase1(void)
{
    int i, j;
    int retSize;
    int *retColSize = NULL;
    int **ret = NULL;

    ret = test_alloc_array(&retSize, &retColSize);
    Log("array:\n");
    for (i = 0; i < retSize; i++) {
        for (j = 0; j < retColSize[i]; j++) {
            printf("%2d ", *(*(ret + i) + j)); /* 访问arr[i][j] */
        }
        printf("\n");
    }
}

/******************************************************************************/
/*
 * 二维数组作为函数参数, 传入二级指针
 */
void print_array(int **array, int row, int col)
{
    int i, j;

    int (*arr)[col] = (int (*)[col])array;
    Log("array:\n");
    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }

    int *arr2 = (int *)array;
    Log("array:\n");
    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            printf("%d ", *(arr2 + i * col + j));
        }
        printf("\n");
    }
}

/*
 * 二维数组作为函数参数, 传入指定列宽的二维数组指针
 */
void print_array2(int (*arr)[5], int row, int col)
{
    int i, j;

    Log("array:\n");
    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
}

void TestCase2(void)
{
    int arr[][5] = {
        { 1, 2, 3, 4, 5 },
        { 6, 7, 8, 9, 0 },
    };
    print_array((int **)arr, 2, 5);
    print_array2(arr, 2, 5);
}

/******************************************************************************/
int main(void)
{
    TestCase1();
    TestCase2();
    return 0;
}
