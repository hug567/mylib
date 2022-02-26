/*
 * leetcode 26: 删除有序数组中的重复项 [简单]
 * 思路：双指针
 *      初始时，p, q指向数组起始位置，比较p、q指向位置的值；
 *      若相等，q后移，p不变，跳过重复值；
 *      若不等，p后移一个位置，q指向的值存储到当前p的位置，然后q后移；
 *      直到q遍历到数组末尾；
 *      返回数组长度为p指向位置为末尾的数组的长度。
 * 2022-02-27
 */
#include "common.h"

/***** 提交代码 ******************************************************************/
int removeDuplicates(int* nums, int numsSize)
{
    int *p = nums, *q = nums;
    while (q < nums + numsSize) {
        if (*p != *q) {
            p++;
            *p = *q;
        }
        q++;
    }
    return p - nums + 1;
}

/***** 本地调试 ******************************************************************/
void TestCase1(void)
{
    int arr[] = { 1, 1, 2 };
    int size = ARRAY_SIZE(arr);
    int len = removeDuplicates(arr, size);
    PrintArray(arr, len);
}

void TestCase2(void)
{
    int arr[] = { 0, 0, 1, 1, 1, 2, 2, 3, 3, 4 };
    int size = ARRAY_SIZE(arr);
    int len = removeDuplicates(arr, size);
    PrintArray(arr, len);
}

int main(void)
{
    TestCase1();
    TestCase2();
    return 0;
}