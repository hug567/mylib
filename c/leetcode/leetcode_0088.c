/*
 * leetcode 88: 合并两个有序数组 [简单]
 * 思路：双指针
 *     1）、结果指针指向数组1的尾部，从大到小合并，避免覆盖；
 *     2）、指针1指向数组1尾部，指针2指向数组2尾部；
 *     3）、比较指针1与指针2的大小，较大的赋值给结果指针，赋值指针减1，同时结果指针减1
 *     4）、若某一数组遍历完，直接拷贝另一数组到结果数组中；
 * 2022-02-28
 */
#include "common.h"

/***** 提交代码 ******************************************************************/
void merge(int* nums1, int nums1Size, int m, int* nums2, int nums2Size, int n)
{
    int i;
    int *tail = nums1 + nums1Size - 1;
    int *tail1 = nums1 + m - 1;
    int *tail2 = nums2 + n - 1;

    if (n == 0) {
        return;
    } else if (m == 0) {
        memcpy(nums1, nums2, n * sizeof(int));
        return;
    }
    for (i = 0; i < m + n; i++) {
        if (tail1 < nums1) {
            //num1中元素已全部拷贝到后方，可把nums2中剩余元素直接拷贝到nums1头部
            memcpy(nums1, nums2, (tail2 - nums2 + 1) * sizeof(int));
            return;
        } else if (tail2 < nums2) {
            return;  //nums2中元素已全部拷贝到nums1中，直接返回
        } else if (*tail1 < *tail2) {
            *tail = *tail2;
            tail2--;
        } else {
            *tail = *tail1;
            tail1--;
        }
        tail--;
    }
}

/***** 本地调试 ******************************************************************/
void TestCase1(void)
{
    int nums1[] = { 1, 2, 3, 0, 0, 0 };
    int nums1Size = ARRAY_SIZE(nums1);
    int m = 3;
    int nums2[] = { 2, 5, 6 };
    int nums2Size = ARRAY_SIZE(nums2);
    int n = 3;
    merge(nums1, nums1Size, m, nums2, nums2Size, n);
    PrintArray(nums1, m + n);
}

void TestCase2(void)
{
    int nums1[] = { 1 };
    int nums1Size = ARRAY_SIZE(nums1);
    int m = 1;
    int nums2[] = { 0 };
    int nums2Size = ARRAY_SIZE(nums2);
    int n = 0;
    merge(nums1, nums1Size, m, nums2, nums2Size, n);
    PrintArray(nums1, m + n);
}

void TestCase3(void)
{
    int nums1[] = { 0 };
    int nums1Size = ARRAY_SIZE(nums1);
    int m = 0;
    int nums2[] = { 1 };
    int nums2Size = ARRAY_SIZE(nums2);
    int n = 1;
    merge(nums1, nums1Size, m, nums2, nums2Size, n);
    PrintArray(nums1, m + n);
}

int main(void)
{
    TestCase1();
    TestCase2();
    TestCase3();
    return 0;
}
