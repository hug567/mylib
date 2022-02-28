/*
 * leetcode 125: 验证回文串 [简单]
 * 思路：双指针
 *      1）、向用双指针格式化字符串，两个指针先均指向head；
 *      2）、再用双指针判断是否是回文字符串，两个指针分别指向首尾；
 * 2022-02-28
 */
#include "common.h"

/***** 提交代码 ******************************************************************/
bool isPalindrome(char * s)
{
    int len = strlen(s);
    char *p1 = NULL;
    char *p2 = NULL;

    if (len == 0) {
        return true;
    }
    p1 = s;
    p2 = s;
    while (*p2 != '\0') {
        if ((*p2 >= 'a' && *p2 <= 'z') || (*p2 >= '0' && *p2 <= '9')) {
            *p1 = *p2;
            p1++;
        } else if (*p2 >= 'A' && *p2 <= 'Z') {
            *p1 = *p2 - 'A' + 'a';
            p1++;
        }
        p2++;
    }
    p2 = p1 - 1;
    p1 = s;
    while (p1 < p2) {
        if (*p1 != *p2) {
            return false;
        }
        p1++;
        p2--;
    }
    return true;
}

/***** 本地调试 ******************************************************************/
void TestCase1(void)
{
    char s[] = "A man, a plan, a canal: Panama";
    Log("is palindrome: %d(1)\n", isPalindrome(s));
}

void TestCase2(void)
{
    char s[] = "race a car";
    Log("is palindrome: %d(0)\n", isPalindrome(s));
}

int main(void)
{
    TestCase1();
    TestCase2();
    return 0;
}
