/*
 * 练习：sizeof
 * 时间：2020-04-06
 */
#include <stdio.h>
#include "../test.h"

int __test_sizeof_str_arr(void)
{
    const char *strs[] = {
        "12345",
        "1234567890",
        "a",
        "bbbbb",
        "ccc",
    };

    /* ans = 20, 指针长度(4) x 数组长度(5) */
    printf("sizeof string array = %ld\n", sizeof(strs));
    /* size = 5 */
    printf("array size = %ld\n", sizeof(strs) / sizeof(char *));
    return 0;
}

int test_sizeof()
{
    int ret;

    int oneDimArray[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    int oneDimArraySize = sizeof(oneDimArray) / sizeof(int);
    /* oneDimArraySize = 10 */
    printf("one dimensional array size = %d\n", oneDimArraySize);

    RUN_TEST(__test_sizeof_str_arr);

    return 0;
}
