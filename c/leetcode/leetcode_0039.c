/*
 * leetcode 39: 组合总和
 * 方法：DFS + 回溯 + 剪枝
 * 2021-03-23
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>

/***** 本地调试代码 ************************************************************/
#define debug_log(fmt, ...) if (1) {printf("[%s:%d] " fmt, __func__, __LINE__, ##__VA_ARGS__);}

void PrintArray(int *arr, int size)
{
    int i;
    printf("array: ");
    for (i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}
/***** 提交代码 ****************************************************************/
void Dfs(int targetLeft)
{}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** combinationSum(int* candidates, int candidatesSize, int target,
                     int* returnSize, int** returnColumnSizes)
{
    *returnSize = 0;
    return NULL;
}
/***** 本地调试代码 ************************************************************/
int main(void)
{
    int i;
    int cands[] = { 2, 3, 6, 7 };
    int cSize = sizeof(cands) / sizeof(cands[0]);
    int target = 7;
    int retSize;
    int *retColSizes = NULL;
    int **combs = NULL;

    combs = combinationSum(cands, cSize, target, &retSize, &retColSizes);
    for (i = 0; i < retSize; i++) {
        PrintArray(combs[i], retColSizes[i]);
    }

    return 0;
}
