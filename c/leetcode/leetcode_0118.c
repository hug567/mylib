/*
 * leetcode 118: 杨辉三角 [简单]
 * 思路：动态规划，当前行的值可由上一行的值生成
 * 2021-1-9
 */
#include "common.h"

/***** 提交代码 ****************************************************************/
int** generate(int numRows, int* returnSize, int** returnColumnSizes)
{
    int i, j;
    int **arr = malloc(numRows * sizeof(int *));
    *returnColumnSizes = malloc(numRows * sizeof(int));
    for (i = 0; i < numRows; i++) {
        (*returnColumnSizes)[i] = i + 1;
        arr[i] = malloc((*returnColumnSizes)[i] * sizeof(int));
        (*(arr + i))[0] = 1;
        (*(arr + i))[(*returnColumnSizes)[i] - 1] = 1;
    }
    for (i = 2; i < numRows; i++) {
        for (j = 1; j < (*returnColumnSizes)[i] - 1; j++) {
            *(*(arr + i) + j) = *(*(arr + i - 1) + j) + *(*(arr + i - 1) + j - 1);
        }
    }
    *returnSize = numRows;
    return arr;
}

/***** 本地调试 ****************************************************************/
void TestCase1(void)
{
    int i, j;
    int **arr = NULL;
    int numRows = 5;
    int retSize;
    int *retColSize;
    arr = generate(numRows, &retSize, &retColSize);
    Log("array:\n");
    for (i = 0; i < retSize; i++) {
        for (j = 0; j < retColSize[i]; j++) {
            printf("%d ", *(*(arr + i) + j));
        }
        printf("\n");
    }
}

int main(void)
{
    TestCase1();
    return 0;
}