/*
 * leetcode 202: 快乐数 [简单]
 * 思路：保存所有已计算的结果，若新计算出的结果原来出现过，会形成无限循环，不是快乐数
 * 2022-03-01
 */
#include "common.h"

/***** 提交代码 ******************************************************************/
#define MAX_ARRAY_SIZE 20

int EachSum(int n)
{
    int tmp;
    int sum = 0;

    while (n > 0) {
        tmp = n % 10;
        sum += (tmp * tmp);
        n /= 10;
    }
    return sum;
}

bool AlreadyAppeared(int *arr, int size, int num)
{
    int i;

    for (i = 0; i < size; i++) {
        if (arr[i] == num) {
            return true;
        }
    }
    return false;
}

bool isHappy(int n)
{
    int sum;
    int size = 0;
    int arr[MAX_ARRAY_SIZE] = {0};

    sum = EachSum(n);
    while (sum != 1) {
        if (AlreadyAppeared(arr, size, sum)) {
            return false;
        }
        arr[size] = sum;
        size++;
        sum = EachSum(sum);
    }
    return true;
}

/***** 本地调试 ******************************************************************/
void TestCase1(void)
{
    Log("19 is happy: %d(1)\n", isHappy(19));
    Log("2 is happy: %d(0)\n", isHappy(2));
}

int main(void)
{
    TestCase1();
    return 0;
}
