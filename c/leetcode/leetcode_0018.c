/*
 * leetcode 18: 四数之和 [中等]
 * 思路：先排序数，前两个数用双重循环，后两个数用双指针，分别指向剩余数组首尾，向中间遍历，结合剪枝加速
 * 2022-03-10
 */
#include "common.h"

/***** 提交代码 ******************************************************************/
int Compare(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}

int** fourSum(int* nums, int numsSize, int target, int* returnSize, int** returnColumnSizes)
{
    int i, j;
    int **ret = NULL;
    int *p1, *p2, *p3, *p4;
    int max_size = 1001;

    *returnSize = 0;
    if (numsSize < 4) {
        return NULL;
    }
    ret = malloc(max_size * sizeof(int *));
    *returnColumnSizes = malloc(max_size * sizeof(int));
    memset(*returnColumnSizes, 0, max_size * sizeof(int));
    qsort(nums, numsSize, sizeof(int), Compare);
    for (i = 0; i < numsSize - 3; i++) {
        p1 = nums + i;
        if ((long)*p1 + *(p1 + 1) + *(p1 + 2) + *(p1 + 3) > target) {
            break;
        }
        if (i > 0 && *p1 == *(p1 - 1)) {
            continue;
        }
        for (j = i + 1; j < numsSize - 2; j++) {
            p2 = nums + j;
            if ((long)*p1 + *p2 + *(p2 + 1) + *(p2 + 2) > target) {
                break;
            }
            if (j > i + 1 && *p2 == *(p2 - 1)) {
                continue;
            }
            p3 = p2 + 1;
            p4 = nums + numsSize - 1;
            while (p3 < p4) {
                if ((long)*p1 + *p2 + *p3 + *p4 == target) {
                    ret[*returnSize] = malloc(4 * sizeof(int));
                    (*returnColumnSizes)[*returnSize] = 4;
                    ret[*returnSize][0] = *p1;
                    ret[*returnSize][1] = *p2;
                    ret[*returnSize][2] = *p3;
                    ret[*returnSize][3] = *p4;
                    (*returnSize)++;
                    while (p3 < p4 && *p3 == *(p3 + 1)) {
                        p3++;
                    }
                    p3++;
                    while (p3 < p4 && *p4 == *(p4 - 1)) {
                        p4--;
                    }
                    p4--;
                } else if ((long)*p1 + *p2 + *p3 + *p4 > target) {
                    p4--;
                } else {
                    p3++;
                }
            }
        }
    }
    return ret;
}

/***** 本地调试 ******************************************************************/
void DoPrintResult(const char *func, int line, int **arr, int retSize, int *retColSize)
{
    int i;
    int *a = NULL;

    for (i = 0; i < retSize; i++) {
        a = arr[i];
        printf("[%s:%d] [%d, %d, %d, %d]\n", func, line, a[0], a[1], a[2], a[3]);
    }
}
#define PrintResult(arr, retSize, retColSize) \
        DoPrintResult(__func__, __LINE__, (int **)(arr), retSize, (int *)(retColSize))

void TestCase1(void)
{
    int nums[] = { 1, 0, -1, 0, -2, 2 };
    int size = ARRAY_SIZE(nums);
    int target = 0;
    int retSize;
    int *retColSize = NULL;
    int **ret = fourSum(nums, size, target, &retSize, &retColSize);
    PrintResult(ret, retSize, retColSize);
}

void TestCase2(void)
{
    int nums[] = { 2, 2, 2, 2, 2 };
    int size = ARRAY_SIZE(nums);
    int target = 8;
    int retSize;
    int *retColSize = NULL;
    int **ret = fourSum(nums, size, target, &retSize, &retColSize);
    PrintResult(ret, retSize, retColSize);
}

void TestCase3(void)
{
    int nums[] = { 1,-2,-5,-4,-3,3,3,5 };
    int size = ARRAY_SIZE(nums);
    int target = -11;
    int retSize;
    int *retColSize = NULL;
    int **ret = fourSum(nums, size, target, &retSize, &retColSize);
    PrintResult(ret, retSize, retColSize);
}

void TestCase4(void)
{
    int nums[] = { -1,0,-5,-2,-2,-4,0,1,-2 };
    int size = ARRAY_SIZE(nums);
    int target = -9;
    int retSize;
    int *retColSize = NULL;
    int **ret = fourSum(nums, size, target, &retSize, &retColSize);
    PrintResult(ret, retSize, retColSize);
}

int main(void)
{
    TestCase1();
    TestCase2();
    TestCase3();
    TestCase4();
    return 0;
}
