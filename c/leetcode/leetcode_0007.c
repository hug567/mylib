/*
 * leetcode 7: 整数反转 [简单]
 * 整数范围：2^-31 ~ 2^31 -1
 * 2021.09.14
 */
#include "common.h"

void PrintNum(char *num, int count)
{
    int i;
    DebugLog("num: ");
    for (i = count - 1; i >= 0; i--) {
        printf("%d", num[i]);
    }
    printf("\n");
}

void PrintNum2(char *num, int count)
{
    int i;
    DebugLog("num2: ");
    for (i = 0; i < count; i++) {
        printf("%d", num[i]);
    }
    printf("\n");
}

/***** 提交代码 ****************************************************************/
#define INT_MAX (int)(~0U >> 1)
#define INT_MIN (int)(1U << 31)

int IsTooLarge(char *num, int count)
{
    int i;
    char max[] = "2147483647";

    if (count < 10) {
        return 0;
    }
    for (i = 0; i < 10; i++) {
        if (num[i] < max[i] - '0') {
            return 0;
        } else if (num[i] > max[i] - '0') {
            return 1;
        }
    }
    return 0;
}

int reverse(int x)
{
    int i;
    int sign = 1;
    char num[11] = {0};
    int count = 0;

    if (x == INT_MIN) {
        return 0;
    }
    if (x < 0) {
        sign = -1;
        x = -x;
    }

    while (x > 0) {
        num[count] = x % 10;
        x /= 10;
        count++;
    }

    if (IsTooLarge(num, count)) {
        return 0;
    }
    x = 0;
    for (i = 0; i < count; i++) {
        x *= 10;
        x += num[i];
    }
    x *= sign;

    return x;
}

/***** 本地调试 ****************************************************************/
int main(void)
{
    DebugLog("INT_MAX = %d\n", INT_MAX);
    DebugLog("INT_MIN = %d\n", INT_MIN);
    DebugLog("reverse(123) = %d\n", reverse(123));
    DebugLog("reverse(-123) = %d\n", reverse(-123));
    DebugLog("reverse(0) = %d\n", reverse(0));
    DebugLog("reverse(2111111111) = %d\n", reverse(2111111111));
    DebugLog("reverse(2111111113) = %d\n", reverse(2111111113));
    DebugLog("reverse(-2111111111) = %d\n", reverse(-2111111111));
    DebugLog("reverse(-2111111113) = %d\n", reverse(-2111111113));
    DebugLog("reverse(2147483647) = %d\n", reverse(2147483647));
    DebugLog("reverse(-2147483648) = %d\n", reverse(-2147483648));
    return 0;
}
