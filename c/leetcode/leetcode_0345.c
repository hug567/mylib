/*
 * leetcode 345: 反转字符串中的元音字母 [简单]
 * 思路：双指针 (注：对调左边第n个元音字符和右边第n个元音字母)
 * 2022-03-02
 */
#include "common.h"

/***** 提交代码 ******************************************************************/
bool IsVowel(char ch)
{
    char *str = "aeiouAEIOU";

    while (*str != '\0') {
        if (*str == ch) {
            return true;
        }
        str++;
    }
    return false;
}

char *NextVowel(char *cur)
{
    while (*cur != '\0') {
        if (IsVowel(*cur)) {
            return cur;
        }
        cur++;
    }
    return NULL;
}

char *PreVowel(char *start, char *cur)
{
    while (cur >= start) {
        if (IsVowel(*cur)) {
            return cur;
        }
        cur--;
    }
    return NULL;
}

char *reverseVowels(char *s)
{
    char tmp;
    char *left = NULL;
    char *right = NULL;

    left = NextVowel(s);
    right = PreVowel(s, s + strlen(s) - 1);
    while (left != NULL && right != NULL && left < right) {
        tmp = *left;
        *left = *right;
        *right = tmp;
        left = NextVowel(left + 1);
        right = PreVowel(s, right - 1);
    }
    return s;
}

/***** 本地调试 ******************************************************************/
void TestCase1(void)
{
    char s[] = "hello";
    Log("s: %s\n", s);
    char *retS = reverseVowels(s);
    Log("s: %s\n", retS);
}

void TestCase2(void)
{
    char s[] = "leetcode";
    Log("s: %s\n", s);
    char *retS = reverseVowels(s);
    Log("s: %s\n", retS);
}

int main(void)
{
    TestCase1();
    TestCase2();
    return 0;
}
