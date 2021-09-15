/*
 * leetcode 8: 字符串转换整数 (atoi) [中等]
 * 2021.09.15
 */
#include "common.h"

/***** 提交代码 ****************************************************************/
#define INT_MAX (int)(~0U >> 1)
#define INT_MIN (int)(1U << 31)

char *DeleteHeadSpace(char *s)
{
    while (*s != '\0' && *s == ' ') {
        s++;
    }
    return s;
}

char *NumSign(char *s, int *sign)
{
    if (*s == '-') {
        *sign = -1;
        s++;
    } else if (*s == '+') {
        *sign = 1;
        s++;
    } else if (*s >= 0 && *s <= '9') {
        *sign = 1;
    }else {
        *sign = 0;
    }
    return s;
}

char *DeleteHeadZero(char *s)
{
    while (*s != '\0' && *s == '0') {
        s++;
    }
    return s;
}

int NumCharCount(char *s)
{
    int count = 0;
    while (*s != '\0' && *s >= '0' && *s <= '9') {
        count++;
        if (count > 10) {
            break;
        }
        s++;
    }
    return count;
}

int NumIsTooLarge(char *s, int count, int sign)
{
    int i;
    char max[] = "2147483647";

    if (count > 10) {
        return 1;
    } else if (count < 10) {
        return 0;
    }
    if (sign < 0) {
        max[9] = '8';
    }
    for (i = 0; i < 10; i++) {
        if (s[i] > max[i]) {
            return 1;
        } else if (s[i] < max[i]) {
            return 0;
        }
    }
    return 0;
}

int myAtoi(char * s)
{
    int i;
    int sign; /* 符号 */
    int count; /* 开头非零数字字符数 */
    int num = 0;

    s = DeleteHeadSpace(s);
    s = NumSign(s, &sign);
    if (sign == 0) { /* 没有符号位且不是数字开头 */
        return 0;
    }
    s = DeleteHeadZero(s);
    count = NumCharCount(s);
    if (NumIsTooLarge(s, count, sign)) {
        return sign > 0 ? INT_MAX : INT_MIN;
    }
    if (count == 10 && sign < 0 &&
        strcmp(s, "2147483648") == 0) {
        return INT_MIN;
    }
    for (i = 0; i < count; i++) {
        num = s[i] - '0' + num * 10;  /* 未避免溢出，先减'0' */
    }
    return sign * num;
}

/***** 本地调试 ****************************************************************/
int main(void)
{
    DebugLog("INT_MAX = %d\n", INT_MAX);
    DebugLog("INT_MIN = %d\n", INT_MIN);
    DebugLog("atoi(\"42\") = %d\n", myAtoi("42"));
    DebugLog("atoi(\"-42\") = %d\n", myAtoi("-42"));
    DebugLog("atoi(\"4193 with words\") = %d\n", myAtoi("4193 with words"));
    DebugLog("atoi(\"words and 98\") = %d\n", myAtoi("words and 98"));
    DebugLog("atoi(\"-91283472332\") = %d\n", myAtoi("-91283472332"));
    DebugLog("atoi(\"2147483646\") = %d\n", myAtoi("2147483646"));
    DebugLog("atoi(\"2147483647\") = %d\n", myAtoi("2147483647"));
    DebugLog("atoi(\"-2147483648\") = %d\n", myAtoi("-2147483648"));

    return 0;
}
