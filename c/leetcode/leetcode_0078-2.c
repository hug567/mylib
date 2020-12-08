/*
 * 题目：leetcode 78: 子集
 * 难度：中等
 * 技巧：1、空集是所有集合的子集
 *      2、在现有的所有子集上加上未使用的一个元素，构成一批新的子集，直到遍历完所有的元素
 *      3、子集个数是2^size
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

/***** 本地调试 ****************************************************************/
#define LOCAL_DEBUG
#define log_info(fmt, ...) printf("[%s:%d] " fmt, __func__, __LINE__, ##__VA_ARGS__)

void PrintSub(int **sub, int size, const int *colSize)
{
    int i, j;
    printf("sub:\ncolSize: ");
    for (i = 0; i < size; i++) {
        printf("%d ", colSize[i]);
    }
    printf("\n");
    for (i = 0; i < size; i++) {
        printf("[");
        for (j = 0; j < colSize[i]; j++) {
            printf("%d ", sub[i][j]);
        }
        printf("]\n");
    }
}
/******************************************************************************/

int UpdateSub(int **sub, int curNum, int *colSize, int elem)
{
    int i;
    int *tmp = NULL;

    /* 将当前已有子集复制一遍，并在复制出的每个子集末尾添加新的元素 */
    for (i = 0; i < curNum; i++) {
        memcpy(sub[curNum + i], sub[i], colSize[i] * sizeof(int));
        sub[curNum + i][colSize[i]] = elem;
        colSize[curNum + i] = colSize[i] + 1;
    }
    return 2 * curNum;
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** subsets(int* nums, int numsSize, int* returnSize, int** returnColumnSizes){
    int i, j;
    int num;
    int curNum;
    int **sub = NULL;

    *returnSize = (int)pow(2, numsSize); /* 子集总数：2^n */
    *returnColumnSizes = (int *)malloc(*returnSize * sizeof(int)); /* 每个子集的长度 */
    memset(*returnColumnSizes, 0, *returnSize * sizeof(int));

    sub = (int **)malloc(*returnSize * sizeof(int *));
    for (i = 0; i < *returnSize; i++) {
        sub[i] = (int *)malloc(numsSize * sizeof(int));
    }

    /* 初始集合是空集，空集是所有集合的子集 */
    (*returnColumnSizes)[0] = 0;
    curNum = 1;
    for (i = 0; i < numsSize; i++) {
        curNum = UpdateSub(sub, curNum, *returnColumnSizes, nums[i]);
    }

    return sub;
}

/***** 本地调试 ****************************************************************/
int main(int argc, char *argv[])
{
    int i, j;
    int nums[] = {1, 2, 3};
    int numsSize = sizeof(nums) / sizeof(int);
    int returnSize;
    int *returnColumnSize = NULL; /* 一维数组作为输出参数 */
    int **sub = subsets(nums, numsSize, &returnSize, &returnColumnSize);

    PrintSub(sub, returnSize, returnColumnSize);

    return 0;
}
/******************************************************************************/
