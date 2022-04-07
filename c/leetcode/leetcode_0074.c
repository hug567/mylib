/*
 * leetcode 74: 搜索二维矩阵
 * 思路：先遍历所在行，在二分查找是否存在
 * 2022-04-07
 */
#include "common.h"

/***** 提交代码 ****************************************************************/
int BinarySearch(int *arr, int size, int target)
{
    int left = 0;
    int right = size - 1;
    int mid;

    while (left <= right) {
        mid = (left + right) / 2;
        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] > target) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return -1;
}

bool searchMatrix(int** matrix, int matrixSize, int* matrixColSize, int target)
{
    int i;
    int *row = NULL;
    int m = matrixSize;
    int n = matrixColSize[0];

#ifdef LOCAL_DEBUG
    int (*mat)[n] = (int(*)[n])matrix;
#else
    int **mat = matrix;
#endif

    if (target < mat[0][0] || target > mat[m - 1][n - 1]) {
        return false;
    }
    row = mat[m - 1];
    for (i = 0; i < m - 1; i++) {
        if (target >= mat[i][0] && target < mat[i + 1][0]) {
            row = mat[i];
            break;
        }
    }
    return BinarySearch(row, n, target) >= 0;
}

/***** 本地调试 ****************************************************************/
void TestCase1(void)
{
    int matrix[][4] = {
            { 1, 3, 5, 7 },
            { 10, 11, 16, 20 },
            { 23, 30, 34, 60 }
    };
    int matrixSize = 3;
    int matrixColSize[] = { 4, 4, 4 };
    int target = 3;
    Log("target exist: %d(1)\n", searchMatrix(matrix, matrixSize, matrixColSize, target));
}

void TestCase2(void)
{
    int matrix[][4] = {
            { 1, 3, 5, 7 },
            { 10, 11, 16, 20 },
            { 23, 30, 34, 60 }
    };
    int matrixSize = 3;
    int matrixColSize[] = { 4, 4, 4 };
    int target = 13;
    Log("target exist: %d(0)\n", searchMatrix(matrix, matrixSize, matrixColSize, target));
}

int main(void)
{
    TestCase1();
    TestCase2();
    return 0;
}