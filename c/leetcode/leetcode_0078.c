/*
 * 题目：leetcode 78: 子集
 * 难度：中等
 * 技巧：1、递归，共2^n个子集
 *       2、用二进制的位表示，对于n个元素的集合，有2^n个子集，则从0~2^n，
 *          二进制数中为1的位置对应的数，组成的子集，即为所有的子集
 * 时间：2020-04-27
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define LOCAL_DEBUG

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** subsets(int* nums, int numsSize, int* returnSize, int** returnColumnSizes){
    int i, j, idx;
    int **sub = NULL;

    *returnSize = (int)pow(2, numsSize);
    returnColumnSize[0] = (int *)malloc(*returnSizr * sizeof(int));
    sub = (int **)malloc(*returnSize * sizeof(int *));
    for (i = 0; i < *returnSize; i++) {
        sub[i] = (int *)malloc(numsSize * sizeof(int));

        idx = 0;
        returnColumnSize[]



    }

    return sub;
}

int main(int argc, char *argv[])
{
    int i, j;
    int nums[] = {1, 2, 3};
    int numsSize = sizeof(nums) / sizeof(int);
    int returnSize;
    int *returnColumnSize;
    int **sub = subsets(nums, numsSize, &returnSize, &returnColumnSize);

    return 0;
}
