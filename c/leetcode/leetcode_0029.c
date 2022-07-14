/*
 * leetcode 29: 两数相除
 * 2022-07-10
 */
#include "common.h"

/****** 提交代码 *****************************************************************/
/*
 * 使用位移实现乘法：
 *   20 * 14 = 20 * 1110(2)
 *           = 20 * 2^3 + 20 * 2^2 + 20 * 2^1
 *           = 20 << 3 + 20 << 2 + 20 << 1
 *           = 160 + 80 + 40
 *           = 280
 */
long long multiplication(long long a, long long b)
{
    long long ret = 0, idx = 0;

    while (b > 0) {
        if (b & 0x1) {
            ret += a << idx;
        }
        idx++;
        b >>= 1;
    }
    return ret;
}

/* a / b */
long long getDiv(long long a, long long b)
{
    long long x, left = 1, right = a, middle;

    while (left <= right) {
        middle = (left + right) >> 1;
        x = multiplication(middle, b);  //需要考虑溢出
        if (x <= a && (x + b) > a) {
            return middle;
        } else if (x < a) {
            left = middle + 1;
        } else {
            right = middle - 1;
        }
    }
    return middle;
}

int divide(int dividend, int divisor)
{
    int ret = 0;
    int sign = 1;
    long long a = dividend, b = divisor;
    if (a == INT_MIN) {
        if (b == 1) {
            return INT_MIN;
        } else if (b == -1) {
            return INT_MAX;
        }
    }
    if (a < 0) {
        sign = -sign;
        a = -a;
    }
    if (b < 0) {
        sign = -sign;
        b = -b;
    }
    if (a < b) {
        return 0;
    }
    ret = getDiv(a, b);
    if (sign < 0) {
        ret = -ret;
    }
    return ret;
}

/****** 本地调试 *****************************************************************/
void TestCase1(void)
{
    Log("10 / 3 = %d(3)\n", divide(10, 3));
    Log("7 / -3 = %d(-2)\n", divide(7, -3));
    Log("%d / -1 = %d(%d)\n", INT_MIN, divide(INT_MIN, -1), INT_MAX);
    Log("%d / 1 = %d(%d)\n", INT_MIN, divide(INT_MIN, 1), INT_MIN);
    Log("%d / 2 = %d(%d)\n", INT_MIN, divide(INT_MIN, 2), INT_MIN / 2);
    Log("%d / 3 = %d(%d)\n", INT_MAX, divide(INT_MAX, 3), INT_MAX / 3);
    Log("1 / 2 = %d(0)\n", divide(1, 2), 0);
}

int main(void)
{
    Log("INT_MIN = %d, INT_MAX = %d\n", INT_MIN, INT_MAX);
    Log("20 * 14 = %lld(280)\n", multiplication(20, 14));
    Log("14 * 20 = %lld(280)\n", multiplication(14, 20));
    Log("3 * 123 = %lld(369)\n", multiplication(3, 123));
    Log("123 * 3 = %lld(369)\n", multiplication(123, 3));
    long long a = INT_MAX;
    long long b = INT_MAX;
    long long c = a * b;
    Log("c = %lld\n", c);
    Log("sizeof(long) = %llu\n", sizeof(long));
    Log("sizeof(long long) = %llu\n", sizeof(long long));
    TestCase1();
    return 0;
}