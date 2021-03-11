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
#define MAX_NUM 100

int g_pos[3] = {0}; /* 3个分割点可放置的位置 */
char **g_ipStr = NULL;
int g_count = 0;
char g_tmpStr[3] = {0};
int g_tmpStrIndx = 0;
int g_pointPos[3] = {0};
int g_pointNum;

/* 根据给的原始字符串和3个点的坐标，生成ip */
char *CreateIpStr(char *s, int *pointPos, int pointNum)
{
    int i, j, k;
    int len = strlen(s);
    char *str = (char *)malloc(len + 4);

//PrintArray(pointPos, pointNum);
    memset(str, 0, len + 4);
    j = 0; /* ip字符串当前放置字符位置 */
    k = 0; /* 点位置当前遍历到的下标 */
    for (i = 0; i < len; i++) {
//debug_log("i = %d, str = %s\n", i, str);
        str[j] = s[i];
        j++;
        if (i == (pointPos[k] - 1) && k < 3) {
            str[j] = '.';
            j++;
            k++;
        }
    }
debug_log("ip str: %s\n", str);
    return str;
}

/* 判断给定的字符串是否是合格的iP地址(0~255) */
int IsIpNum(char *start, int len)
{
    int num;
    int isIpNum = 0;
    char *str = NULL;

//debug_log("len = %d\n", len);
    if (len == 1) {/* 单个数字一定是合格的ip地址 */
debug_log("str = %c\n", *start);
        return 1;
    } else if (len < 1 || len > 3) { /* 长度为0或大于3的一定是不合格的ip地址 */
        return 0;
    }
    /* 长度为2或3 */
    str = (char *)malloc(len + 1);
    memset(str, 0, len + 1);
    memcpy(str, start, len);
    num = atoi(str);
    /* 值小于等于255且首字符不为0，是合格ip */
    if (num <= 255 && start[0] != '0') {
debug_log("str = %s\n", str);
        isIpNum = 1;
    }
    free(str);
    return isIpNum;
}

void Dfs(char *s, int cur, int *pointPos, int pointNum)
{
    int i;
    //char *start = NULL;
    //int len;

//debug_log("cur = %d, pointNum = %d\n", cur, pointNum);
PrintArray(pointPos, pointNum);
    if (pointNum > 0 && pointPos[pointNum - 1] >= strlen(s)) {
        return;
    }
    if (pointNum == 3) {
        if (pointPos[pointNum - 1] >= strlen(s)) {
            return;
        }
        if (IsIpNum(s + cur, strlen(s) - cur)) {
            g_ipStr[g_count] = CreateIpStr(s, pointPos, pointNum);
            //return;
            g_count++;
        }
        return;
    }
    if (cur >= strlen(s) - 1) {
        return;
    }
    for (i = cur; i < cur + 3; i++) {
        if (IsIpNum(s + cur, i - cur + 1)) {
            pointPos[pointNum] = i + 1;
            pointNum++;
            Dfs(s, i + 1, pointPos, pointNum);
        }
    }
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char ** restoreIpAddresses(char * s, int* returnSize){
//debug_log("s = %s\n", s);
    char **ipStr = (char **)malloc(MAX_NUM * sizeof(char *));
    g_ipStr = ipStr;
    Dfs(s, 0, g_pointPos, 0); /* 从第0个字符开始搜索 */
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

    //s = "25525511135";
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

    return 0;
}
