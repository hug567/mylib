/*
 * leetcode 17: 电话号码的字母组合
 * 思路：DFS
 * 2022-06-29
 */
#include "common.h"

/***** 提交代码 ******************************************************************/
#define MAX_COMB_LEN 8

char g_numChar[][4] = {
        {},
        {},
        {"abc"},
        {"def"},
        {"ghi"},
        {"jkl"},
        {"mno"},
        {"pqrs"},
        {"tuv"},
        {"wxyz"},
};
int g_numCharLen[] = {0, 0, 3, 3, 3, 3, 3, 4, 3, 4};
char g_combStr[MAX_COMB_LEN];
int g_count = 0;
int g_strLen = 0;

void Dfs(int idx, int len, char *digits, char **ret)
{
    int i, j;
    if (idx >= g_strLen) {
        memcpy(ret[g_count], g_combStr, len);
        g_count++;
        return;
    }
    j = digits[idx] - '0';
    for (i = 0; i < g_numCharLen[j]; i++) {
        g_combStr[idx] = g_numChar[j][i];
        Dfs(idx + 1, len, digits, ret);
    }
}

char **letterCombinations(char *digits, int *returnSize)
{
    int i;
    char **ret = NULL;
    int len = strlen(digits);

    if (len == 0) {
        *returnSize = 0;
        return NULL;
    }
    *returnSize = 1;
    for (i = 0; i < len; i++) {
        *returnSize = (*returnSize) * (g_numCharLen[digits[i] - '0']);
    }
    ret = (char **)malloc((*returnSize) * sizeof(char *));
    for (i = 0; i < *returnSize; i++) {
        ret[i] = (char *)malloc(len + 1);
        memset(ret[i], 0, len + 1);
    }
    g_count = 0;
    g_strLen = len;
    Dfs(0, len, digits, ret);

    return ret;
}

/***** 本地调试 ******************************************************************/
void TestCase1(void)
{
    int i;
    int retSize;
    int **ret = letterCombinations("23", &retSize);
    for (i = 0; i < retSize; i++) {
        Log("str: [%s]\n", ret[i]);
    }
}

void TestCase2(void)
{
    int i;
    int retSize;
    int **ret = letterCombinations("2", &retSize);
    for (i = 0; i < retSize; i++) {
        Log("str: [%s]\n", ret[i]);
    }
}

void TestCase3(void)
{
    int i;
    int retSize;
    int **ret = letterCombinations("", &retSize);
    for (i = 0; i < retSize; i++) {
        Log("str: [%s]\n", ret[i]);
    }
}

int main(void)
{
    TestCase1();
    TestCase2();
    TestCase3();
    return 0;
}