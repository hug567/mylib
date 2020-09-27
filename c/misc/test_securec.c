/*
 * 测试常用安全函数打桩
 * 2020-09-26
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "securec.h"

#define BUF_SIZE 100

static void TestSprintfs(void)
{
    char buf[BUF_SIZE];

    (void)memset_s(buf, BUF_SIZE, 0, BUF_SIZE);
    (void)sprintf_s(buf, BUF_SIZE, "test sprintf_s in func: %s, line: %d\n",
                    __func__, __LINE__);
    (void)printf("%s", buf);
}

#define MAX_SRC_IP_NUM 100
#define BIN_IP_SIZE 33
#define BYTE_SIZE 8
#define MAX_STR_IP_LEN 18

static void OneStrIpToBinary(const char *str, char *bin)
{
    int i;
    unsigned int num = atoi(str);
    for (i = BYTE_SIZE - 1; i >= 0; i--) {
        bin[i] = num & 0x1;
        num >>= 1;
    }
}

static void PrintBinartIp(const char *ip, const char *bin)
{
    int i;
    (void)printf("ip: %s\n", ip);
    (void)printf("binary ip: ");
    for (i = 0; i < BIN_IP_SIZE; i++) {
        (void)printf("%d", bin[i]);
        if (i == BIN_IP_SIZE - 2) {
            (void)printf("/");
        }
    }
    (void)printf("\n");
}

void HandleStrIp(char *new, const char *old)
{
    int i;

    int len = strlen(old);

    (void)memcpy_s(new, MAX_STR_IP_LEN, old, len);
    for (i = 0; i < len; i++) {
        if (old[i] == '/') {
            return;
        }
    }
    new[len] = '/';
    new[len + 1] = '0';
}

static void IpToBinary(const char *_str, char *bin)
{
#define TEMP_SIZE 4
    int i, j = 0, k = 0;
    int ip;
    //char bin[BIN_IP_SIZE] = {0};
    char temp[TEMP_SIZE] = {0};
    char str[MAX_STR_IP_LEN + 1] = {0};

    HandleStrIp(str, _str);
    for (i = 0; i < strlen(str); i++) {
        if (str[i] == '.' || str[i] == '/') {
            OneStrIpToBinary(temp, bin + k * BYTE_SIZE);
            (void)memset_s(temp, TEMP_SIZE, 0, TEMP_SIZE);
            j = 0;
            k++;
        } else {
            temp[j] = str[i];
            j++;
        }
    }
    bin[BIN_IP_SIZE - 1] = atoi(temp);
    PrintBinartIp(str, bin);
}

/*
 * -1: 不匹配
 * 正整数：匹配的长度
 */
int MatchLength(char *str1, char *str2)
{
    int i;

    for (i = 0; i < str2[BIN_IP_SIZE - 1]; i++) {
        if (str1[i] != str2[i]) {
            return -1;
        }
    }
    return str2[BIN_IP_SIZE - 1];
}

int main(void)
{
    int i;
    char *dstStrIp = "192.168.0.1";
    char *srcStrIp[] = {
        "192.168.0.2/23", "192.168.8.13/20", "10.156.21.38/24",
        "0.0.0.0/0",
    };
    int srcStrIpNum = 4;

    char dstBinaryIp[BIN_IP_SIZE] = {0};
    char srcBinaryIp[MAX_STR_IP_LEN][BIN_IP_SIZE] = {0};

    TestSprintfs();

    IpToBinary(dstStrIp, dstBinaryIp);
    for (i = 0; i < srcStrIpNum; i++) {
        IpToBinary(srcStrIp[i], srcBinaryIp[i]);
        printf("match len: %d\n", MatchLength(dstBinaryIp, srcBinaryIp[i]));
    }
    return 0;
}