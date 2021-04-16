/*
 * 八数码问题：9宫格中有1-8个数字和一个空格子，空格子可与周围数字格子交换，
 *            求移动成12345678x的最短路径，无解输出"unsolvable"
 * 解法：BFS
 * 2021-04-14
 */
#include "common.h"

int main(void)
{
    int arr[3][3] = {
        { 1, 2, 3 },
        { 4, 5, 6 },
        { 7, 8, 9 },
    };
    PrintArray2((int **)arr, 3, 3);
    char
    return 0;
}

