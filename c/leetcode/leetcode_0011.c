/*
 * leetcode 11: 盛最多水的容器 [中等]
 * 思路：贪心
 *      双指针，初始两个指针分别指向数组收尾，计算当前两个指针指向的值组成的容器容量，
 *      然后移动值较小的指针，再次计算容量，直至二者重合，保存最大值
 * 2022-02-08
 */
#include "common.h"

/***** 提交代码 ****************************************************************/
int maxVal(int a, int b)
{
    return a > b ? a : b;
}

int minVal(int a, int b)
{
    return a < b ? a : b;
}

int maxArea(int* height, int heightSize)
{
    int max = 0, area;
    int head = 0, tail = heightSize - 1;

    while (head != tail) {
        area = minVal(height[head], height[tail]) * (tail -  head);
        max = maxVal(max, area);
        if (height[head] < height[tail]) {
            head++;
        } else {
            tail--;
        }
    }
    return max;
}

/***** 本地调试 ****************************************************************/
void TestCase1(void)
{
    int arr[] = { 1, 8, 6, 2, 5, 4, 8, 3, 7 };
    int size = ARRAY_SIZE(arr);
    Log("max area: %d(49)\n", maxArea(arr, size));
}

void TestCase2(void)
{
    int arr[] = { 1, 1 };
    int size = ARRAY_SIZE(arr);
    Log("max area: %d(1)\n", maxArea(arr, size));
}

void TestCase3(void)
{
    int arr[] = { 4, 3, 2, 1, 4 };
    int size = ARRAY_SIZE(arr);
    Log("max area: %d(16)\n", maxArea(arr, size));
}

void TestCase4(void)
{
    int arr[] = { 1, 2, 1 };
    int size = ARRAY_SIZE(arr);
    Log("max area: %d(2)\n", maxArea(arr, size));
}

int main(void)
{
    TestCase1();
    TestCase2();
    TestCase3();
    TestCase4();
    return 0;
}