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
        {1000, "M"},
        {900, "CM"},
        {500, "D"},
        {400, "CD"},
        {100, "C"},
        {90, "XC"},
        {50, "L"},
        {40, "XL"},
        {10, "X"},
        {9, "IX"},
        {5, "V"},
        {4, "IV"},
        {1, "I"},
};

char * intToRoman(int num)
{
    int i;
    int len = sizeof(g_numList) / sizeof(g_numList[0]);
    char *str = malloc(100);

    memset(str, 0, 100);
    while (num > 0) {
        for (i = 0; i < len; i++) {
            if (num >= g_numList[i].num) {
                num -= g_numList[i].num;
                strcat(str, g_numList[i].str);
                break;
            }
        }
    }
    return str;
}

/***** 本地调试 ******************************************************************/
void TestCase1(void)
{
    Log("roman num: %s(III)\n", intToRoman(3));
    Log("roman num: %s(IV)\n", intToRoman(4));
    Log("roman num: %s(IX)\n", intToRoman(9));
    Log("roman num: %s(LVIII)\n", intToRoman(58));
}

int main(void)
{
    TestCase1();
    return 0;
}