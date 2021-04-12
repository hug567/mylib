/*
 * leetcode 40: 组合总和II [中等]
 * 方法：DFS + 回溯 + 剪枝
 * 2021-03-29
 */
#include "common.h"

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

void Dfs(int *cand, int candSize, int candIdx, int *comb, int combCurIdx, int targetLeft)
{
    int i;
    /* 目标剩余值为0，找到一个有效组合 */
    if (targetLeft == 0) {
        CreateAns(comb, combCurIdx);
        return;
    }
    if (candIdx >= candSize || targetLeft < 0) {// || targetLeft < cand[candIdx]) {
        return;
    }

    for (i = candIdx; i < candSize; i++) {
        comb[combCurIdx] = cand[i];
        Dfs(cand, candSize, i, comb, combCurIdx + 1, targetLeft - cand[i]);
    }

#if 0
    //Dfs(cand, candSize, candIdx + 1, comb, combCurIdx, targetLeft);
//PrintArray(comb, combCurIdx);
    if (cand[candIdx] <= targetLeft) { /* 当前值可以放入组合 */
        comb[combCurIdx] = cand[candIdx];
        /* 遍历下一个 */
        Dfs(cand, candSize, candIdx + 1, comb, combCurIdx + 1, targetLeft - cand[candIdx]);
    } else {
    /* 当前值不能放入组合，回溯一个已放入组合的值，继续遍历当前值 */
    //if (combCurIdx > 0) {
        //combCurIdx--;
        Dfs(cand, candSize, candIdx, comb, combCurIdx - 1, targetLeft + comb[combCurIdx - 1]);
        //Dfs(cand, candSize, candIdx, comb, combCurIdx, targetLeft);
    }
#endif
}

int Compare(const void *a, const void *b)
{
    return *(int *)a - *(int *)b; //升序
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** combinationSum2(int* candidates, int candidatesSize, int target,
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

    int cands[] = { 10, 1, 2, 7, 6, 1, 5 };
    int cSize = sizeof(cands) / sizeof(cands[0]);
    int target = 8;
    int retSize;
    int *retColSizes = NULL;
    int **combs = NULL;

    combs = combinationSum2(cands, cSize, target, &retSize, &retColSizes);
    printf("retSize = %d(4)\n", retSize);
    //PrintArray(retColSizes, retSize);
    for (i = 0; i < retSize; i++) {
        PrintArray(combs[i], retColSizes[i]);
    }

    int cands2[] = { 2, 5, 2, 1, 2 };
    cSize = sizeof(cands2) / sizeof(cands2[0]);
    target = 5;
    combs = combinationSum2(cands2, cSize, target, &retSize, &retColSizes);
    printf("\nretSize = %d(2)\n", retSize);
    //PrintArray(retColSizes, retSize);
    for (i = 0; i < retSize; i++) {
        PrintArray(combs[i], retColSizes[i]);
    }

    return 0;
}
