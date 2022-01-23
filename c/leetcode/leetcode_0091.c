/*
 * leetcode 91: 解码方法 [中等]
 * 动态规划：
 *     f(i)表示前i个字符可组成的解码方法数
 *       1）、若s[i] != '0'，则单独一个s[i]可被解码，有：f(i) += f(i-1)
 *       2）、若s[i-1] != '0', 且s[i-1]s[i] <= "26"，则第i个字符可以和第i-1字符组合
 *           可被解码，有：f(i) += f(i-2)
 *       3）、边界条件：s[i] != '0'时，f(0)=1
 * 2022-01-23
 */
#include "common.h"

/***** 提交代码 ****************************************************************/
int StrToNum(const char *s, int len)
{
    int i;
    int num = 0;
    for (i = 0; i < len; i++) {
        num = 10 * num + s[i] - '0';
    }
    return num;
}

int HeadTwoCharEncondingNum(const char *s)
{
    int n = StrToNum(s, 2);

    if (s[1] == '0') {
        if (s[0] > '2') {  //eg: "30"
            return 0;
        } else {
            return 1;  //eg: "20"
        }
    } else if (n > 26) {
        return 1; //eg: "35"
    } else {
        return 2; //eg: "18"
    }
}

int numDecodings(char *s)
{
    int len = strlen(s);
    int cur = 0, pre = 0, ppre = 0;
    int i;

    if (s[0] == '0') {
        return 0;
    } else {
        ppre = 1;
    }
    if (len < 2) {
        return 1;
    } else if ((pre = HeadTwoCharEncondingNum(s)) == 0) {
        return 0;
    }
    cur = pre;

    for (i = 2; i < len; i++) {
        cur = 0;
        if (s[i] != '0') {
            cur += pre;
        }
        if (s[i - 1] != '0' && StrToNum(s + i - 1, 2) <= 26) {
            cur += ppre;
        }
        ppre = pre;
        pre = cur;
    }
    return cur;
}

/***** 本地调试 ****************************************************************/
void TestCase1(void)
{
    Log("num: %d(2)\n", numDecodings("12"));
    Log("num: %d(3)\n", numDecodings("226"));
    Log("num: %d(0)\n", numDecodings("0"));
    Log("num: %d(0)\n", numDecodings("06"));
    Log("num: %d(0)\n", numDecodings("301"));
}

int main(void)
{
    TestCase1();
    return 0;
}