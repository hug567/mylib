/*
 * 题目：leetcode 90: 子集 II
 * 难度：中等
 * 技巧：
 * 时间：2020-05-06
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define LOCAL_DEBUG

int compare(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}

void dfs(int *nums, int n, int numsSize, int *arr, int ind, int **sub, int *returnSize, int **returnColumnSizes)
{
    ret
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** subsetsWithDup(int* nums, int numsSize, int* returnSize, int** returnColumnSizes){
    int **sub = NULL;
    int *arr = NULL;

    qsort(nums, numsSize, sizeof(int), compare);
    *returnSize = (int)pow(2, numsSize);
    sub = (int **)malloc(*returnSize * sizeof(int *));
    (*returnColumnSizes) = (int *)malloc((*returnSize) * sizeof(int));
    arr = (int *)malloc(numsSize * sizeof(int));
    dfs();
    return sub;
}

int main(int argc, char *argv[])
{
    int i, j;
    int nums[] = {2, 1, 2};
    int numsSize = sizeof(nums) / sizeof(int);
    int returnSize;
    int **returnColumnSize = (int **)malloc(sizeof(int *));
    int **sub = subsetsWithDup(nums, numsSize, &returnSize, returnColumnSize);
/*
    for (i = 0; i < returnSize; i++) {
        for (j = 0; j < returnColumnSize[0][i]; j++) {
            printf("%d ", sub[i][j]);
        }
        printf("\n");
    }
*/
    return 0;
}