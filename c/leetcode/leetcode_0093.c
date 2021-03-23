/*
 * Leetcode 93：复原IP地址
 * 方法：DFS，搜索3个点可放置的位置，基于递归实现，原理通八皇后问题和全排列
 * 2021-03-07
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>

/***** 调试代码 ****************************************************************/
#define debug_log(fmt, ...) if (1) {printf("[%s:%d] " fmt, __func__, __LINE__, ##__VA_ARGS__);}

void PrintArray(int *arr, int size)
{
    int i;
    printf("array: ");
    for (i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

/***** 提交代码 ****************************************************************/
#define MAX_NUM 20 /* 实测最多20个可能组合 */

char **g_ipStr = NULL; /* 所有合格的ip地址数组 */
int g_count = 0; /* 合格的ip地址数量 */
int g_pointPos[3] = {0}; /* 记录3个点的位置，值i表示在第(i-1)个数字后放置点 */

/* 根据给的原始字符串和3个点的坐标，生成ip */
char *CreateIpStr(char *s, int *pointPos, int pointNum)
{
    int i, j, k;
    int len = strlen(s);
    char *str = (char *)malloc(len + 4);

    memset(str, 0, len + 4);
    j = 0; /* ip字符串当前放置字符位置 */
    k = 0; /* 点位置当前遍历到的下标 */
    for (i = 0; i < len; i++) {
        str[j] = s[i];
        j++;
        if (k < 3 && i == (pointPos[k] - 1)) {
            str[j] = '.';
            j++;
            k++;
        }
    }
    return str;
}

/* 判断给定的字符串是否是合格的iP地址(0~255) */
int IsIpNum(char *start, int len)
{
    int i;
    int num = 0;
    int isIpNum = 0;

    if (len == 1) {/* 单个数字一定是合格的ip地址 */
        return 1;
    } else if (len < 1 || len > 3) { /* 长度为0或大于3的一定是不合格的ip地址 */
        return 0;
    }
    /* 长度为2或3 */
    for (i = 0; i < len; i++) {
        num = num * 10 + start[i] - '0';
    }
    /* 值小于等于255且首字符不为0，是合格ip */
    if (num <= 255 && start[0] != '0') {
        isIpNum = 1;
    }
    return isIpNum;
}

void Dfs(char *s, int cur, int *pointPos, int pointNum)
{
    int i;
    int len = strlen(s);

    if (pointNum > 0 && pointNum < 3 && pointPos[pointNum - 1] >= len) {
        return;
    }
    if (pointNum == 3) {
        if (pointPos[pointNum - 1] >= len) {
            return;
        }
        if (IsIpNum(s + cur, len - cur)) {
            g_ipStr[g_count] = CreateIpStr(s, pointPos, pointNum);
            g_count++;
        }
        return;
    }
    if (cur >= len - 1) {
        return;
    }
    /* 从当前点开始搜索，最多搜索3个数字 */
    for (i = cur; i < cur + 3 && i < len; i++) {
        if (IsIpNum(s + cur, i - cur + 1)) {
            pointPos[pointNum] = i + 1;
            /* 起点当当前点的数字是合格的ip地址，开始搜索下一个点的位置 */
            Dfs(s, i + 1, pointPos, pointNum + 1);
        }
    }
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char ** restoreIpAddresses(char * s, int* returnSize){
    g_ipStr = (char **)malloc(MAX_NUM * sizeof(char *));
    g_count = 0; /* leetcode全局变量需在运行时初始化 */
    Dfs(s, 0, g_pointPos, 0); /* 从第0个字符开始搜索 */
    *returnSize = g_count;
    return g_ipStr;
}

/***** 本地调试代码 ************************************************************/
void PrintAllIpStr(const char **ipStr, int size)
{
    int i;
    printf("All ip str:\n");
    for (i = 0; i < size; i++) {
        printf("ip: %s\n", ipStr[i]);
    }
}

int main(void)
{
    char *s = NULL;
    int returnSize;
    char **ipStr = NULL;

    s = "012111";
    g_count = 0;
    printf("s = %s\n", s);
    ipStr = restoreIpAddresses(s, &returnSize);
    PrintAllIpStr((const char **)ipStr, returnSize);

    s = "0000";
    g_count = 0;
    printf("\ns = %s\n", s);
    ipStr = restoreIpAddresses(s, &returnSize);
    PrintAllIpStr((const char **)ipStr, returnSize);

    s = "25525511135";
    g_count = 0;
    printf("s = %s\n", s);
    ipStr = restoreIpAddresses(s, &returnSize);
    PrintAllIpStr((const char **)ipStr, returnSize);

    s = "1111";
    g_count = 0;
    printf("\ns = %s\n", s);
    ipStr = restoreIpAddresses(s, &returnSize);
    PrintAllIpStr((const char **)ipStr, returnSize);

    s = "010010";
    g_count = 0;
    printf("\ns = %s\n", s);
    ipStr = restoreIpAddresses(s, &returnSize);
    PrintAllIpStr((const char **)ipStr, returnSize);

    s = "101023";
    g_count = 0;
    printf("\ns = %s\n", s);
    ipStr = restoreIpAddresses(s, &returnSize);
    PrintAllIpStr((const char **)ipStr, returnSize);

    return 0;
}
