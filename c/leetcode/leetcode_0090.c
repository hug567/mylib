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
#define dprintf(fmt, ...) printf("[%s:%d] " fmt, __func__, __LINE__, ##__VA_ARGS__)

int rsize = 0;

int compare(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}

void dfs(int **retarr, int itend, int *nums, int numsSize,
         int **returnColumnSizes, int *column, int *temp)
{
    int i;

    returnColumnSizes[0][rsize] = *column;
    memcpy(retarr[rsize], temp, (*column) * sizeof(int));
    rsize++;

    for (i = itend; i < numsSize; i++) {
        temp[*column] = nums[i];
        *column = *column + 1;
        dfs(retarr, i + 1, nums, numsSize, returnColumnSizes, column, temp);
        *column = *column - 1;
        temp[*column] = 0;
        while ((i + 1) < numsSize && nums[i] == nums[i + 1]) {
            i++;
        }
    }
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** subsetsWithDup(int* nums, int numsSize, int* returnSize,
                     int** returnColumnSizes)
{
    int i, j;
    int t = 1U << numsSize;
    int colCount = 0;
    int **retarr = NULL;
    int *temp = NULL;

    *returnSize = t;
    returnColumnSizes[0] = (int *)malloc(sizeof(int) * t);
    temp = (int *)malloc(sizeof(int) * t);
    memset(temp, 0, sizeof(int) * t);
    retarr = (int **)malloc(sizeof(int *) * t);
    if (numsSize == 1 && nums[0] == 0) {
        temp = (int *)malloc(sizeof(int));
        returnColumnSizes[0][0] = 0;
        returnColumnSizes[0][1] = 1;
        retarr[0] = NULL;
        retarr[1] = (int *)malloc(sizeof(int));
        retarr[1][0] = 0;
        return retarr;
    }

    for (i = 0; i < t; i++) {
        retarr[i] = (int *)malloc(sizeof(int) * t);
        memset(retarr[i], 0, sizeof(int) * t);
    }
    qsort(nums, numsSize, sizeof(int), compare);
    dfs(retarr, 0, nums, numsSize, returnColumnSizes, &colCount, temp);

    *returnSize = rsize;
    return retarr;
}

int main(int argc, char *argv[])
{
    int i, j;
    int nums[] = {1, 1};
    int numsSize = sizeof(nums) / sizeof(int);
    int returnSize;
    int **returnColumnSize = (int **)malloc(sizeof(int *));
    int **sub = subsetsWithDup(nums, numsSize, &returnSize, returnColumnSize);
    for (i = 0; i < returnSize; i++) {
        printf("[");
        for (j = 0; j < returnColumnSize[0][i]; j++) {
            printf("%d ", sub[i][j]);
        }
        printf("]\n");
    }

    return 0;
}
