/*
 * leetcode 15: 三数之和 [简单]
 * 思路：排序后三指针，第一个指针从低到高一次遍历，固定第一个指针后，第二、三个指针分别指向剩余
 *      数组的头部和尾部，分别向中间移动，当3数和为0时存储；为避免重复，第二、三个指针移动时，
 *      需跳过相同的值。
 * 2022-03-04
 */
#include "common.h"

/***** 提交代码 ******************************************************************/
int Compare(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}

int** threeSum(int* nums, int numsSize, int* returnSize, int** returnColumnSizes)
{
    int i, max_size;
    int **ret = NULL;
    int *p1, *p2, *p3;

    if (numsSize < 3) {
        *returnSize = 0;
        returnColumnSizes = NULL;
        return NULL;
    }
    max_size = numsSize * 6;
    ret = malloc(max_size * sizeof(int *));
    *returnColumnSizes = malloc(max_size * sizeof(int));
    for (i = 0; i < max_size; i++) {
        (*returnColumnSizes)[i] = 3;
    }
    qsort(nums, numsSize, sizeof(int), Compare);
    *returnSize = 0;
    for (i = 0; i < numsSize - 2; i++) {
        p1 = nums + i;
        if (*p1 > 0) {
            break;
        } else if (i > 0 && *p1 == *(p1 - 1)) {
            continue;
        }
            p2 = p1 + 1;
            p3 = nums + numsSize - 1;
            while (p2 < p3) {
                if (*p1 + *p2 > 0) {
                    break;
                } else if (p2 > p1 + 1 && *p2 == *(p2 - 1)) {
                    p2++;
                    continue;
                }
                if (*p1 + *p2 + *p3 == 0) {
                    ret[*returnSize] = malloc(3 * sizeof(int));
                    ret[*returnSize][0] = *p1;
                    ret[*returnSize][1] = *p2;
                    ret[*returnSize][2] = -(*p1 + *p2);
                    (*returnSize)++;
                    p2++;
                    p3--;
                } else if (*p1 + *p2 + *p3 > 0) {
                    p3--;
                    while (p3 > p2 && *p3 == *(p3 + 1)) {
                        p3--;
                    }
                } else {
                    p2++;
                }
            }
    }
    return ret;
}

/***** 本地调试 ******************************************************************/
void PrintResult(int **ret, int retSize, const int *retColSize)
{
    int i, j;
    int *arr;

    Log("ret:\n");
    for (i = 0; i < retSize; i++) {
        arr = ret[i];
        printf("ret[%2d]: [", i);
        for (j = 0; j < retColSize[i]; j++) {
            printf("%d ", arr[j]);
        }
        printf("]\n");
    }
}

void TestCase1(void)
{
    int nums[] = { -1, 0, 1, 2, -1, -4 };
    int size = ARRAY_SIZE(nums);
    int retSize;
    int *retColSize = NULL;
    int **ret = threeSum(nums, size, &retSize, &retColSize);
    PrintResult(ret, retSize, retColSize);
}

void TestCase2(void)
{
    int nums[] = { 0, 0, 0 };
    int size = ARRAY_SIZE(nums);
    int retSize;
    int *retColSize = NULL;
    int **ret = threeSum(nums, size, &retSize, &retColSize);
    PrintResult(ret, retSize, retColSize);
}

void TestCase3(void)
{
    clock_t start_t = clock();
    int nums[] = { -7,-4,-6,6,4,-6,-9,-10,-7,5,3,-1,-5,8,-1,-2,-8,-1,5,-3,-5,4,2,-5,-4,4,7 };
    int size = ARRAY_SIZE(nums);
    int retSize;
    int *retColSize = NULL;
    int **ret = threeSum(nums, size, &retSize, &retColSize);
    PrintResult(ret, retSize, retColSize);  //retSize = 28
    clock_t end_t = clock();
    Log("time diff: %ld\n", end_t - start_t);
}

void TestCase4(void)
{
    int nums[] = { 3, -2, 1, 0 };
    int size = ARRAY_SIZE(nums);
    int retSize;
    int *retColSize = NULL;
    int **ret = threeSum(nums, size, &retSize, &retColSize);
    PrintResult(ret, retSize, retColSize);  //retSize =
}

int main(void)
{
    TestCase1();
    TestCase2();
    TestCase3();
    TestCase4();
    return 0;
}
