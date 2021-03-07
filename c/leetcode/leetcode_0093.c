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

/***** 提交代码 ****************************************************************/
#define MAX_NUM 100

int g_pos[3] = {0}; /* 3个分割点可放置的位置 */
char **g_ipStr = NULL;
int g_count = 0;
char g_tmpStr[3] = {0};
int g_tmpStrIndx = 0;

char *CreateIpStr(char *s, int *pos)
{
    int i, j, k;
    int len = strlen(s);
    char *str = (char *)malloc(len + 4);

    memset(s, 0, len + 4);
    j = 0; /* ip字符串当前放置字符位置 */
    k = 0; /* 点位置当前遍历到的下标 */
    for (i = 0; i < len; i++) {
        str[j] = s[i];
        j++;
        if (i == pos[k]) {
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
    int num;
    int isIpNum = 0;
    char *str = NULL;

    if (len < 1 || len > 3) {
        return 0;
    }
    str = (char *)malloc(len + 1);
    memset(str, 0, len + 1);
    memcpy(str, start, len);
    num = atoi(str);
    if (num >= 0 && num <= 255) {
        isIpNum = 1;
    }
    free(str);
    return isIpNum;
}

void Dfs(char *s, int start, int idx)
{
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char ** restoreIpAddresses(char * s, int* returnSize){
    char **ipStr = (char **)malloc(MAX_NUM * sizeof(char *));
    g_ipStr = ipStr;
    //Dfs(0, 0, s, strlen(s)); /* 从第0个字符开始搜索，前一个点的位置初始化为0 */
    *returnSize = g_count;
    return ipStr;
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

    s = "25525511135";
    ipStr = restoreIpAddresses(s, &returnSize);
    PrintAllIpStr((const char **)ipStr, returnSize);

    return 0;
}
