/*
 * 字符串数组
 * 2023-09-02
 */
#include <stdio.h>

int main(void)
{
    int i, size;
    char *str_arr[] = {
        "Hello",
        "I'm Tom",
        "How are you",
        "I'm fine, thank you",
        "And you",
        "I'm fine too",
    };

    size = sizeof(str_arr) / sizeof(str_arr[0]);
    printf("size = %d\n", size);
    for (i = 0; i < size; i++) {
        printf("str_arr[%d]: [%s]\n", i, str_arr[i]);
    }

    return 0;
}
