/*
 * leetcode 344: 反转字符串 [简单]
 * 思路：数组前后对调(size / 2)，或双指针
 * 不借助第三个变量交换两个变量的值：
 *   异或：
 *       a = a ^ b;
 *       b = a ^ b;
 *       a = a ^ b;
 *   加减：
 *       a = a + b;
 *       b = a - b;
 *       a = a - b;
 * 2022-03-02
 */
#include "common.h"

/***** 提交代码 ******************************************************************/
void reverseString(char* s, int sSize){
    int i;

    for (i = 0; i < sSize / 2; i++) {
        s[i] = s[i] ^ s[sSize - i -1];
        s[sSize - i - 1] = s[i] ^ s[sSize - i -1];
        s[i] = s[i] ^ s[sSize - i -1];
    }
}

/***** 本地调试 ******************************************************************/
void TestCase1(void)
{
    char s[] = "hello"; //需修改字符串值的，不能用字符串常量，必须要字符串数组
    int size = strlen(s);
    Log("str: %s\n", s);
    reverseString(s, size);
    Log("str: %s\n", s);
}

void TestCase2(void)
{
    char s[] = "Hannah"; //需修改字符串值的，不能用字符串常量，必须要字符串数组
    int size = strlen(s);
    Log("str: %s\n", s);
    reverseString(s, size);
    Log("str: %s\n", s);
}

int main(void)
{
    TestCase1();
    TestCase2();
    return 0;
}
