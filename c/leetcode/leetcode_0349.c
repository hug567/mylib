/*
 * leetcode 349: 两个数组的交集 [简单]
 * 思路：排序后双指针
 * 2022-03-03
 */
#include "common.h"

/***** 提交代码 ******************************************************************/
int Compare(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}

int *NextDiffVal(int *start, int size, int *cur)
{
    int *next = cur + 1;

    while (next < start + size) {
        if (*next != *cur) {
            return next;
        }
        next++;
    }
    return NULL;
}

int* intersection(int* nums1, int nums1Size, int* nums2, int nums2Size, int* returnSize)
{
    int *n1 = nums1;
    int *n2 = nums2;
    int size = nums1Size > nums2Size ? nums1Size : nums2Size;
    int *ret = malloc(size * sizeof(int));

    *returnSize = 0;
    qsort(nums1, nums1Size, sizeof(int), Compare);
    qsort(nums2, nums2Size, sizeof(int), Compare);
    while (n1 != NULL && n2 != NULL && n1 < nums1 + nums1Size && n2 < nums2 + nums2Size) {
        if (*n1 == *n2) {
            ret[*returnSize] = *n1;
            (*returnSize)++;
            n1 = NextDiffVal(nums1, nums1Size, n1);
            n2 = NextDiffVal(nums2, nums2Size, n2);
        } else if (*n1 < *n2) {
            n1 = NextDiffVal(nums1, nums1Size, n1);
        } else {
            n2 = NextDiffVal(nums2, nums2Size, n2);
        }
    }

    return ret;
}

/***** 本地调试 ******************************************************************/
void TestCase1(void)
{
    int nums1[] = { 1, 2, 2, 1 };
    int size1 = ARRAY_SIZE(nums1);
    int nums2[] = { 2, 2 };
    int size2 = ARRAY_SIZE(nums2);
    int retSize;
    int *ret = intersection(nums1, size1, nums2, size2, &retSize);
    PrintArray(ret, retSize);
    free(ret);
}

void TestCase2(void)
{
    int nums1[] = { 4, 9, 5 };
    int size1 = ARRAY_SIZE(nums1);
    int nums2[] = { 9, 4, 9, 8, 4 };
    int size2 = ARRAY_SIZE(nums2);
    int retSize;
    int *ret = intersection(nums1, size1, nums2, size2, &retSize);
    PrintArray(ret, retSize);
    free(ret);
}

int main(void)
{
    TestCase1();
    TestCase2();
    return 0;
}
