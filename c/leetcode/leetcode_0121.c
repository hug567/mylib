/*
 * leetcode 121: 买卖股票的最佳时机 [简单]
 * 思路：第i天的最大利润是，在前i-1天的最低点买进，第i天卖出的利润
 * 2021-1-9
 */
#include "common.h"
/***** 提交代码 ****************************************************************/
int maxProfit(int* prices, int pricesSize)
{
    int i;
    int profit = 0;
    int min = prices[0];

    for (i = 1; i < pricesSize; i++) {
        if (min > prices[i]) {
            min = prices[i];
        } else if (prices[i] - min > profit) {
            profit = prices[i] - min;
        }
    }
    return profit;
}

/***** 本地调试 ****************************************************************/
void TestCase1(void)
{
    int prices[] = { 7, 1, 5, 3, 6, 4 };
    int size = ARRAY_SIZE(prices);
    Log("max profit: %d(5)\n", maxProfit(prices, size));
}

void TestCase2(void)
{
    int prices[] = { 7, 6, 4, 3, 1 };
    int size = ARRAY_SIZE(prices);
    Log("max profit: %d(0)\n", maxProfit(prices, size));
}

void TestCase3(void)
{
    int prices[] = { 2, 4, 1 };
    int size = ARRAY_SIZE(prices);
    Log("max profit: %d(2)\n", maxProfit(prices, size));
}

int main(void)
{
    TestCase1();
    TestCase2();
    TestCase3();
    return 0;
}