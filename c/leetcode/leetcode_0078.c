/*
 * 题目：leetcode 78: 子集
 * 难度：中等
 * 技巧：递归
 * 时间：2020-04-27
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define LOCAL_DEBUG

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** subsets(int* nums, int numsSize, int* returnSize, int** returnColumnSizes){
    return NULL;
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
