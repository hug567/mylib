/*
 * leetcode 5: 最长回文子串 [中等]
 * 分治：查找起点固定字符串的最长回文子串，从最长忘最短子串反向逐个判断
 * 剪枝：最大长度比剩余子串长时，可结束比较
 * 2021-6-9
 */

#include "common.h"

/***** 提交代码 ****************************************************************/
int IsPalindrome(char *s, int len)
{
    int i;
    for (i = 0; i < len / 2; i++) {
        if (s[i] != s[len - i - 1]) {
            return 0;
        }
    }
    return 1;
}

int MaxPalindromeLength(char *s)
{
    int i;
    int len = strlen(s);
    if (s == NULL) {
        return 0;
    }

    for (i = len ; i > 1; i--) {
        if (IsPalindrome(s, i)) {
            return i;
        }
    }

    return 1;
}

char *longestPalindrome(char * s){
    int i, pal_len, str_len, max_len;
    char *max_start, *pal_str;

    if (s == NULL) {
        return NULL;
    }
    max_start = s;
    max_len = 1;
    str_len = strlen(s);
    for (i = 0; i < str_len; i++) {
        if (max_len > str_len - i) {
            break;
        }
        pal_len = MaxPalindromeLength(s + i);
        if (pal_len > max_len) {
            max_len = pal_len;
            max_start = s + i;
        }
    }
    pal_str = (char *)malloc(max_len + 1);
    memset(pal_str, 0, max_len + 1);
    memcpy(pal_str, max_start, max_len);
    return pal_str;
}

/***** 本地调试 ****************************************************************/
int main(void)
{
    DebugLog("longest palindrome: %s\n", longestPalindrome("babad"));
    DebugLog("longest palindrome: %s\n", longestPalindrome("cbbd"));
    DebugLog("longest palindrome: %s\n", longestPalindrome("a"));
    DebugLog("longest palindrome: %s\n", longestPalindrome("ac"));
    DebugLog("longest palindrome: %s\n", longestPalindrome(NULL));
    return 0;
}
