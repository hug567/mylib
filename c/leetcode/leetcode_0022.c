/*
 * leetcode 22: 括号生成 [中等]
 * 思路：动态规划, DFS
 * 2021.1.10
 */
#include "common.h"

/***** 提交代码 ****************************************************************/

/*
 * n对括号可组成的种类数:
 *   对于n对括号组成的组合，可表示为：f(n)=(a)b
 *   其中，a和b表示由n-1对括号组成的组合，可以为NULL
 *   若a=f(i)，则有b=f(n-i-1)，其中：i=0,1,2,...,n-1
 *   则：f(n) = f(0)f(n-1) + ... + f(n-1)f(0)
 *   初始条件为：f(0)=f(1)=1
 */
int ParenthesisNumber(int n)
{
    int i, num = 0;

    if (n == 0 || n == 1) {
        return 1;
    }
    for (i = 0; i <= n - 1; i++) {
        num += ParenthesisNumber(i) * ParenthesisNumber(n - i - 1);
    }
    return num;
}

void Dfs(char **res, char *tmp, int idx, int n, int l, int r, int *returnSize)
{
    if (l > n || r > n || r > l) {
        return;
    } else if (l == r && l == n) {
        tmp[idx] = '\0';
        res[*returnSize] = malloc(2 * n + 1);
        memcpy(res[*returnSize], tmp, 2 * n + 1);
        (*returnSize)++;
        return;
    }
    tmp[idx] = '(';
    Dfs(res, tmp, idx + 1, n, l + 1, r, returnSize);
    tmp[idx] = ')';
    Dfs(res, tmp, idx + 1, n, l, r + 1, returnSize);
}

char ** generateParenthesis(int n, int* returnSize)
{
    int retSize = ParenthesisNumber(n);
    char **res = malloc(retSize * sizeof(char *));
    char tmp[2 * n + 1];

    *returnSize = 0;
    Dfs(res, tmp, 0, n, 0, 0, returnSize);
    return res;
}

/***** 本地调试 ****************************************************************/
void TestCase1(void)
{
    int i;
    int n = 3;
    int returnSize;
    char **str = generateParenthesis(n, &returnSize);
    Log("---------- %s ----------\n", __func__);
    for (i = 0; i < returnSize; i++) {
        Log("str[%d] = %s\n", i, str[i]);
    }
}

void TestCase2(void)
{
    int i;
    int n = 1;
    int returnSize;
    char **str = generateParenthesis(n, &returnSize);
    Log("---------- %s ----------\n", __func__);
    for (i = 0; i < returnSize; i++) {
        Log("str[%d] = %s\n", i, str[i]);
    }
}

void test(void)
{
    int i;
    for (i = 0; i <= 8; i++) {
        Log("ParenthesisNumber(%d) = %d\n", i, ParenthesisNumber(i));
    }
}

int main(void)
{
    test();
    TestCase1();
    TestCase2();
    return 0;
}