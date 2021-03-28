/*
 * leetcode 3: 无重复的最长子串 [中等]
 * 思路；双指针，首指针不动，尾指针后移，当尾指针指向的字符在前面有重复时，
 *       首指针移动到前面重复字符的下一个字符，每次更新移动更新一下子串最大长度
 * 2021-03-28
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/***** 本地调试 ****************************************************************/

/***** 提交代码 ****************************************************************/
char *UpdateHead(char *head, const char *tail)
{
    char *cur = NULL;
    /* 若head-tail中有与tail相同的字符，则head指向相同字符的下一个字符 */
    for (cur = head; cur < tail; cur++) {
        if (*cur == *tail) {
            head = cur + 1;
        }
    }
    return head;
}

int lengthOfLongestSubstring(char * s){
    int len, maxLen = 0;
    char *head = s;
    char *tail = s;
    if (s == NULL || *s == '\0') {
        return 0;
    }
    maxLen = tail - head + 1;
    tail++;
    while (*tail != '\0') {
        head = UpdateHead(head, tail);
        len = tail - head + 1;
        maxLen = maxLen > len ? maxLen : len; //更新最大长度
        tail++;
    }
    return maxLen;
}

/***** 本地调试 ****************************************************************/
int main(void)
{
    printf("max sub str len: %d(3)\n", lengthOfLongestSubstring("abcabcbb"));
    printf("max sub str len: %d(1)\n", lengthOfLongestSubstring("bbbbb"));
    printf("max sub str len: %d(3)\n", lengthOfLongestSubstring("pwwkew"));
    printf("max sub str len: %d(0)\n", lengthOfLongestSubstring(""));
    return 0;
}
