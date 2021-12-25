/*
 * C语言创建，复制，传递二维数组
 * 2021-12-23
 */
#include <stdio.h>
#include <stdlib.h>

#define Log(fmt, ...) printf("[%s:%d] " fmt, __func__, __LINE__, ##__VA_ARGS__)

/*
 * 传递二维数组首指针的二级指针:
 */
void PrintArray1(int **array, int row, int col)
{
    int i, j;
    int (*arr)[col] = (int(*)[col])array;

    Log("two dimensional array:\n");
    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
}

/*
 * 传递二维数组中首行首元素的一级指针:
 * 要求数组存储在连续地址空间中，把二维数组当做连续的一维数组
 */
void PrintArray2(int *arr, int row, int col)
{
    int i, j;

    Log("two dimensional array:\n");
    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            printf("%d ", *(arr + i * col + j));
        }
        printf("\n");
    }
}

/*
 * 传递二维数组中每行首元素的指针数组:
 * 只要求数组每行存储在连续地址空间中
 *   arr: (int *)指针数组，为每行首元素地址
 */
void PrintArray3(int **arr, int row, int col)
{
    int i, j;

    Log("two dimensional array:\n");
    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            printf("%d ", *(arr[i] + j));
        }
        printf("\n");
    }
}

void TestCase1(void)
{
    int i;
    int arr[][5] = {
        { 0, 1, 2, 3, 4 },
        { 1, 2, 3, 4, 5 },
        { 3, 4, 5, 6, 7 },
    };
    int row = 3;
    int col = 5;
    PrintArray1((int **)arr, row, col);
    PrintArray2((int *)arr, row, col);

    int *arrPoint[5] = {NULL};  /* 指针数组，存储每行首元素的地址 */
    for (i = 0; i < 5; i++) {
        arrPoint[i] = &arr[i][0];
    }
    PrintArray3(arrPoint, 3, 5);
    PrintArray3(arrPoint, 3, 4);
    PrintArray3(arrPoint, 3, 3);
    PrintArray3(arrPoint, 2, 5);
}

int main(void)
{
    TestCase1();
    return 0;
}
