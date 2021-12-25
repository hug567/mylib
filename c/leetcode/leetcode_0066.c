/*
 * leetcode 66: 加一 [简单]
 * 注意：最高位有可能进位，结果数组比输入数组长度大1
 * 2021-12-24
 */
#include "common.h"

/***** 提交代码 ****************************************************************/
int* plusOne(int* digits, int digitsSize, int* returnSize)
{
    int i;
    int carry = 1;
    int *ret = (int *)malloc((digitsSize + 1) * sizeof(int));

    for (i = digitsSize - 1; i >= 0; i--) {
        ret[i + 1] = digits[i] + carry;
        carry = ret[i + 1] / 10;
        ret[i + 1] %= 10;
    }
    ret[0] = carry;
    if (ret[0] == 0) {
        *returnSize = digitsSize;
        return ret + 1;
    } else {
        *returnSize = digitsSize + 1;
        return ret;
    }
}

/***** 本地调试 ****************************************************************/

void TestCase1(void)
{
    int arr[] = {1, 2, 3};
    int size = sizeof(arr) / sizeof(arr[0]);
    int retSize;
    PrintArray(arr, size);
    int *ret = plusOne(arr, size, &retSize);
    PrintArray(ret, retSize);
}

void TestCase2(void)
{
    int arr[] = {4, 3, 2, 1};
    int size = sizeof(arr) / sizeof(arr[0]);
    int retSize;
    PrintArray(arr, size);
    int *ret = plusOne(arr, size, &retSize);
    PrintArray(ret, retSize);
}

void TestCase3(void)
{
    int arr[] = {1};
    int size = sizeof(arr) / sizeof(arr[0]);
    int retSize;
    PrintArray(arr, size);
    int *ret = plusOne(arr, size, &retSize);
    PrintArray(ret, retSize);
}

void TestCase4(void)
{
    int arr[] = {9};
    int size = sizeof(arr) / sizeof(arr[0]);
    int retSize;
    PrintArray(arr, size);
    int *ret = plusOne(arr, size, &retSize);
    PrintArray(ret, retSize);
}

int main(void)
{
    TestCase1();
    TestCase2();
    TestCase3();
    TestCase4();
    return 0;
}
