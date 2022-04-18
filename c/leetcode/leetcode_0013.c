/*
 * leetcode: 整数转罗马数组 [中等]
 * 思路：从大到小将数字分解为罗马数组，注意加上6个特例
 * 2022-04-18
 */
#include "common.h"

/***** 提交代码 ******************************************************************/
struct NumList {
    int num;
    char *str;
} g_numList[] = {
        {900, "CM"},
        {400, "CD"},
        {90, "XC"},
        {40, "XL"},
        {9, "IX"},
        {4, "IV"},
        {1000, "M"},
        {500, "D"},
        {100, "C"},
        {50, "L"},
        {10, "X"},
        {5, "V"},
        {1, "I"},
};

int OneRomanNum(char *str, int *oneLen)
{
    int i;
    int len = sizeof(g_numList) / sizeof(g_numList[0]);

    if (str == NULL || *str == '\0') {
        *oneLen = 0;
        return 0;
    }
    for (i = 0; i < len; i++) {
        if (strlen(str) > 1 && strlen(g_numList[i].str) == 2 &&
            str[0] == g_numList[i].str[0] && str[1] == g_numList[i].str[1]) {
            *oneLen = 2;
            return g_numList[i].num;
        } else if (strlen(g_numList[i].str) == 1 && str[0] == g_numList[i].str[0]) {
            *oneLen = 1;
            return g_numList[i].num;
        }
    }
    return 0;
}

int romanToInt(char * s)
{
    int num = 0;
    int oneLen;

    while (*s != '\0') {
        num += OneRomanNum(s, &oneLen);
        if (oneLen <= 0) {
            break;
        }
        s += oneLen;
    }
    return num;
}

/***** 本地调试 ******************************************************************/
void TestCase1(void)
{
    Log("int num: %d(3)\n", romanToInt("III"));
    Log("int num: %d(4)\n", romanToInt("IV"));
    Log("int num: %d(9)\n", romanToInt("IX"));
    Log("int num: %d(58)\n", romanToInt("LVIII"));
    Log("int num: %d(1994)\n", romanToInt("MCMXCIV"));
}

int main(void)
{
    TestCase1();
    return 0;
}