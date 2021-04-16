/*
 * 多字符串比较去重
 * 2021-04-15
 */
#include "common.h"

#define SUB_LEN 5
#define STR_NUM 30
#define BUF_LEN (SUB_LEN * STR_NUM)

void PrintStrByLen(const char *str, int len)
{
    int i;
    for (i = 0; i < len; i++) {
        printf("%c", str[i]);
    }
    printf("\n");
}

void PrintStrArr(char **subStrs, int size)
{
    int i;
    for (i = 0; i < size; i++) {
        PrintStrByLen(subStrs[i], SUB_LEN);
    }
}

void InitStr(char *str, int len)
{
    int i;

    srand(time(NULL));
    for (i = 0; i < len; i++) {
        str[i] = rand() % 16 + 'a';
    }
}

void InitSubStrArr(char **subStrArr, char *str)
{
    int i;
    for (i = 0; i < STR_NUM; i++) {
        subStrArr[i] = str + i * SUB_LEN;
    }
}

int main(void)
{
    char str[BUF_LEN];
    char *subStrArr[STR_NUM] = {NULL};

    InitStr(str, BUF_LEN);
    InitSubStrArr(subStrArr, str);
    PrintStrArr(subStrArr, STR_NUM);

    return 0;
}
