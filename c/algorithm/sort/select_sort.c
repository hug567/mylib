/*
 * 选择排序：从未排序的序列中选择最小(大)的元素，放在已排序序列尾部
 * 时间复杂度：O(n^2)
 * 空间复杂度：O(1)
 * 2020-09-01
 */
#include "../common.h"

void SelectSort(int *arr, int size)
{
    int i, j;
    int temp;
    int index;

    for (i = 0; i < size - 1; i++) {
        index = i; /* 未排序序列中最值索引 */
        for (j = i + 1; j < size; j++) {
            if (arr[j] < arr[index]) { /* <: 为升序， >: 为降序 */
                index = j;
            }
        }
        /* 最值放在已排序数组尾部 */
        if (index != i) {
            temp = arr[i];
            arr[i] = arr[index];
            arr[index] = temp;
        }
    }
}

int main(void)
{
    int i;
    int arr[] = {5, 9, 3, 6, 2, 8, 1, 0, 4, 7};
    int size = sizeof(arr) / sizeof(arr[0]);

    PrintArray((int *)arr, size);
    SelectSort(arr, size);
    PrintArray(arr, size);
    printf("\n");

    return 0;
}
