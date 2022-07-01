/*
 * leetcode 20: 有效的括号 [简单]
 * 思路：栈，如果是左括号，则入栈；
 *      如果是右括号，判断与栈顶是否匹配，匹配则出栈，不匹配则括号无效；
 *      若最后栈为空，则括号有效
 */
#include "common.h"

/***** 提交代码 ******************************************************************/
char *g_stack = NULL;
int g_top = 0;

bool isLeft(char c)
{
    return (c == '(' || c == '[' || c == '{');
}

bool isMatch(char l, char r)
{
    if (l == '(' && r == ')') {
        return true;
    }
    if (l == '[' && r == ']') {
        return true;
    }
    if (l == '{' && r == '}') {
        return true;
    }
    return false;
}

bool isValid(char *s)
{
    int i;
    int len = strlen(s);

    if (len == 0 || (len % 2 == 1)) {
        return false;
    }
    g_stack = malloc(len);
    g_top = 0;
    g_stack[g_top] = s[0];
    g_top++;
    for (i = 1; i < len; i++) {
        if (g_top < 0) {
            return false;
        }
        if (isLeft(s[i])) {
            g_stack[g_top] = s[i];
            g_top++;
        } else {
            if (g_top > 0 && !isMatch(g_stack[g_top - 1], s[i])) {
                return false;
            } else {
                g_top--;
            }
        }
    }
    return g_top <= 0;
}

/***** 本地调试 ******************************************************************/
void TestCase1(void)
{
    Log("is valid: %d(1)\n", isValid("()"));
    Log("is valid: %d(1)\n", isValid("()[]{}"));
    Log("is valid: %d(0)\n", isValid("([)]"));
    Log("is valid: %d(1)\n", isValid("{()}"));
}

int main(void)
{
    TestCase1();
    return 0;
}