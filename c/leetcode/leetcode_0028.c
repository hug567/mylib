/*
 * leetcode 28: 实现strStr() [简单]
 * 思路：
 * 2022-02-27
 */
#include "common.h"

/***** 提交代码 ******************************************************************/
int strCmp(char *str1, char *str2)
{
    int i, len1, len2;

    len1 = strlen(str1);
    len2 = strlen(str2);
    if (len1 < len2) {
        return -1;
    }
    for (i = 0; i < len2; i++) {
        if (str1[i] != str2[i]) {
            return str1[i] - str2[i];
        }
    }
    return 0;
}

int strStr(char * haystack, char * needle)
{
    int i, len1, len2;

    len1 = strlen(haystack);
    len2 = strlen(needle);
    if (len2 == 0) {
        return 0;
    }else if (len1 < len2) {
        return -1;
    }
    for (i = 0; i <= len1 - len2; i++) {
        if (haystack[i] != needle[0]) {
            continue;
        }
        if (strCmp(haystack + i, needle) == 0) {
            return i;
        }
    }
    return -1;

}

/***** 本地调试 ******************************************************************/
void TestCase1(void)
{
    char *haystack = "hello";
    char *needle = "ll";
    Log("index: %d(2)\n", strStr(haystack, needle));
}
void TestCase2(void)
{
    char *haystack = "aaaaa";
    char *needle = "bba";
    Log("index: %d(-1)\n", strStr(haystack, needle));
}

void TestCase3(void)
{
    char *haystack = "";
    char *needle = "";
    Log("index: %d(0)\n", strStr(haystack, needle));
}

void TestCase4(void)
{
    char *haystack = "a";
    char *needle = "a";
    Log("index: %d(0)\n", strStr(haystack, needle));
}

void TestCase5(void)
{
    char *haystack = "mississippi";
    char *needle = "issip";
    Log("index: %d(4)\n", strStr(haystack, needle));
}
int main(void)
{
    TestCase1();
    TestCase2();
    TestCase3();
    TestCase4();
    TestCase5();
    return 0;
}
