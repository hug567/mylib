/*
 * leetcode 122: 买卖股票的最佳时机 II
 * 2022-02-11
 */
#include "common.h"

/***** 提交代码 ****************************************************************/
int maxProfit(int* prices, int pricesSize)
{
    int i;
    int p = 0;

    for (i = 0; i < pricesSize - 1; i++) {
        if (prices[i] < prices[i + 1]) {
            p = p + prices[i + 1] - prices[i];
        }
    }
    return p;
}

/***** 本地调试 ****************************************************************/
void TestCase1(void)
{
    int arr[] = { 7, 1, 5, 3, 6, 4 };
    int size = ARRAY_SIZE(arr);
    Log("max profit = %d(7)\n", maxProfit(arr, size));
}

void TestCase2(void)
{
    int arr[] = { 1, 2, 3, 4, 5 };
    int size = ARRAY_SIZE(arr);
    Log("max profit = %d(4)\n", maxProfit(arr, size));
}

void TestCase3(void)
{
    int arr[] = { 7, 6, 4, 3, 1 };
    int size = ARRAY_SIZE(arr);
    Log("max profit = %d(0)\n", maxProfit(arr, size));
}

int main(void)
{
    TestCase1();
    TestCase2();
    TestCase3();
    return 0;
}