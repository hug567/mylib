/*
 * leetcode 31: 下一个排列 [中等]
 * 思路：
 * 2022-07-03
 */
#include "common.h"

/***** 提交代码 ******************************************************************/
int *g_num = NULL;

int compare(const void *a, const void *b)
{
    return g_num[*(int *)a] - g_num[*(int *)b];
}

int minNumIdx(int *arr, int size)
{
    int i, minIdx;
    int *tmp = NULL;

    g_num = arr;
    tmp = malloc(size * sizeof(int));
    for (i = 0; i < size; i++) {
        tmp[i] = i;
    }
    qsort(tmp, size, sizeof(int), compare);
    minIdx = tmp[0];
    free(tmp);

    return minIdx;
}

void nextPermutation(int* nums, int numsSize)
{
    int i, tmp, minIdx, flag = 0;

    for (i = numsSize - 1; i > 0; i--) {
        minIdx = minNumIdx(nums, i);
        if (nums[minIdx] < nums[i]) {
            tmp = nums[minIdx];
            nums[minIdx] = nums[i];
            nums[i] = tmp;
            flag = 1;
            break;
        }
    }
    if (flag == 0) {
        for (i = 0; i < numsSize / 2; i++) {
            tmp = nums[i];
            nums[i] = nums[numsSize - i - 1];
            nums[numsSize - i - 1] = tmp;
        }
    }
}

/***** 本地调试 ******************************************************************/
void TestCase1(void)
{
    int arr[] = {1, 3, 2};
    int size = ARRAY_SIZE(arr);
    nextPermutation(arr, size);
    PrintArray(arr, size);
}

int main(void)
{
    TestCase1();
    return 0;
}