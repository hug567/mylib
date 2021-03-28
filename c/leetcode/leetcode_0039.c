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
#define MAX_SIZE 1001
int **g_combs = NULL;
int g_count = 0;
int *g_colSize = NULL;

/* 保存符合条件的组合 */
void CreateAns(int *comb, int size)
{
    g_combs[g_count] = (int *)malloc(size * sizeof(int));
    memcpy(g_combs[g_count], comb, size * sizeof(int));
    g_colSize[g_count] = size;
    g_count++;
}

void Dfs(int *cand, int candSize, int candIdx, int *comb, int combCurSize, int targetLeft)
{
    /* 目标剩余值为0，找到一个有效组合 */
    if (targetLeft == 0) {
        CreateAns(comb, combCurSize);
        return;
    }
    if (candIdx >= candSize || targetLeft < cand[candIdx]) {
        return;
    }
    if (cand[candIdx] <= targetLeft) { /* 当前值可以放入组合 */
        comb[combCurSize] = cand[candIdx];
        /* 继续遍历当前值 */
        Dfs(cand, candSize, candIdx, comb, combCurSize + 1, targetLeft - cand[candIdx]);
    }
    /* 遍历下一个值 */
    Dfs(cand, candSize, candIdx + 1, comb, combCurSize, targetLeft);
}

int Compare(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** combinationSum(int* candidates, int candidatesSize, int target,
                     int* returnSize, int** returnColumnSizes)
{
    int comb[2001];
    g_count = 0; /* leetcode 全局变量需在代码中再次初始化 */
    g_combs = (int **)malloc(MAX_SIZE * sizeof(int *));
    *returnColumnSizes = (int *)malloc(MAX_SIZE * sizeof(int));
    g_colSize = *returnColumnSizes;

    /* 先按升序排序 */
    qsort(candidates, candidatesSize, sizeof(int), Compare);
    Dfs(candidates, candidatesSize, 0, comb, 0, target);
    *returnSize = g_count;
    return g_combs;
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
    printf("retSize = %d\n", retSize);
    PrintArray(retColSizes, retSize);
    for (i = 0; i < retSize; i++) {
        PrintArray(combs[i], retColSizes[i]);
    }

    int cands2[] = { 2, 7, 6, 3, 5, 1 };
    cSize = sizeof(cands2) / sizeof(cands2[0]);
    target = 9;
    combs = combinationSum(cands2, cSize, target, &retSize, &retColSizes);
    printf("\nretSize = %d\n", retSize);
    PrintArray(retColSizes, retSize);
    for (i = 0; i < retSize; i++) {
        PrintArray(combs[i], retColSizes[i]);
    }

    return 0;
}
