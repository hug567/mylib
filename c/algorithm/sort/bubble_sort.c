/*
 * 冒泡排序：未排序序列，相邻两元素两两比较，不符合预期顺序时，二者交换
 * 时间复杂度：O(n^2)
 * 2021-6-8
 */
#include "../common.h"

void BubbleSortAscend(int *arr, int size)
{
    int i, j, tmp;

    for (i = size - 1; i > 0; i--) {
        for (j = 0; j < i; j++) {
            if (arr[j] > arr[j + 1]) {
                tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
        }
    }
}

void BubbleSortDescend(int *arr, int size)
{
    int i, j, tmp;

    for (i = size - 1; i > 0; i--) {
        for (j = 0; j < i; j++) {
            if (arr[j] < arr[j + 1]) {
                tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
        }
    }
}

int main(void)
{
    int arr[] = {5, 9, 3, 6, 2, 8, 1, 0, 4, 7};
    int size = sizeof(arr) / sizeof(arr[0]);

    PrintArray(arr, size);
    BubbleSortAscend(arr, size);
    PrintArray(arr, size);
    BubbleSortDescend(arr, size);
    PrintArray(arr, size);

    return 0;
}
