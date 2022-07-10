/*
 * leetcode 31: 下一个排列 [中等]
 * 思路： 1、从后往前遍历一个值降序的点，则从值降低的点往后的数，能组成一个更大的数；
 *       2、把下一个比首位数大的值与首位交换，后面的升序排列，就是下一个更大的数；
 * 2022-07-03
 */
#include "common.h"

/***** 提交代码 ******************************************************************/
int compare(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}

void UpdateToNextBiggerNum(int *num, int size)
{
    int i, tmp;
    int idx = 1; /* 第2个数为最大值 */

    /* 找打下一个比num[0]大的数的索引 */
    for (i = 1; i < size; i++) {
        if (num[i] > num[0] && num[i] < num[idx]) {
            idx = i;
        }
    }
    /* 下一个比num[0]大的值与num[0]交换 */
    tmp = num[0];
    num[0] = num[idx];
    num[idx] = tmp;
    /* 后面的升序排列 */
    qsort(num + 1, size - 1, sizeof(int), compare);
}

void nextPermutation(int* nums, int numsSize)
{
    int i, tmp, flag = 0;
    int *cur = NULL;
    int curSize;

    /* 从后往前遍历到一个值降序的点，则从该降序点往后可组成一个更大的数值 */
    for (i = numsSize - 1; i > 0; i--) {
        if (nums[i] > nums[i - 1]) {
            cur = nums + i - 1;
            curSize = numsSize - i + 1;
            flag = 1;
            break;
        }
    }

    if (flag == 1) {
        UpdateToNextBiggerNum(cur, curSize);
    } else { /* 全降序，已经是最大的数 */
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