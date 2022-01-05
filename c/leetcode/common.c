/*
 * C语言做leetcode题需了解的场景
 * 2021-1-5
 */
#include "common.h"

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

int main(void)
{
    TestCase1();
    return 0;
}