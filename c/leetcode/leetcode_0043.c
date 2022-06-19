/*
 * leetcode 43: 字符串相乘 [中等]
 * 2022-06.19
 */
#include "common.h"

/***** 提交代码 ******************************************************************/
#define MAX_STR_LEN 402

void MultiplyOneChar(char *str, char ch, char *ret)
{
    int i, tmp;
    int carry = 0;
    int len = strlen(str);
    char *cur = ret;

    for (i = len - 1; i >= 0; i--) {
        tmp = (str[i] - '0') * (ch - '0') + carry;
        *cur = (tmp % 10) + '0';
        carry = tmp / 10;
        cur++;
    }
    if (carry > 0) {
        *cur = carry + '0';
    }
}

void AddToSum(char *sum, char *num)
{
    int i, tmp;
    int len = strlen(num);
    int carry = 0;

    for (i = 0; i < len; i++) {
        tmp = (sum[i] - '0') + (num[i] - '0') + carry;
        sum[i] = (tmp % 10) + '0';
        carry = tmp / 10;
    }
    if (carry > 0) {
        sum[i] = sum[i] + carry;
    }
}

char *CopySum(char *sum)
{
    char ch;
    int i, len = 0;
    char *copy = NULL;

    for (i = MAX_STR_LEN - 1; i >= 0; i--) {
        if (sum[i] == '0') {
            sum[i] = 0;
        } else {
            len = i + 1;
            break;
        }
    }
    copy = malloc(len + 1);
    memcpy(copy, sum, len);
    copy[len] = 0;
    for (i = 0; i < len / 2; i++) {
        ch = copy[i];
        copy[i] = copy[len - i - 1];
        copy[len - i - 1] = ch;
    }
    return copy;
}

char * multiply(char * num1, char * num2)
{
    int i, j;
    int len1 = strlen(num1);
    int len2 = strlen(num2);
    char sum[MAX_STR_LEN];
    char ret[MAX_STR_LEN];

    if (len1 == 0 || len2 == 0) {
        return NULL;
    }
    if (*num1 == '0' || *num2 == '0') {
        return "0";
    }
    memset(sum, '0', MAX_STR_LEN);
    j = 0;
    for (i = len2 - 1; i >= 0; i--) {
        memset(ret, 0, MAX_STR_LEN);
        memset(ret, '0', j);
        MultiplyOneChar(num1, num2[i], ret + j);
        AddToSum(sum, ret);
        j++;
    }
    return CopySum(sum);
}

/***** 本地调试 ******************************************************************/
void TestCase1(void)
{
    Log("str multiply: %s(6)\n", multiply("2", "3"));
    Log("str multiply: %s(56088)\n", multiply("123", "456"));
    Log("str multiply: %s(0)\n", multiply("0", "0"));
}

int main(void)
{
    TestCase1();
    return 0;
}