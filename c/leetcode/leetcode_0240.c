/*
 * leetcode 240: 搜索二维矩阵 II
 * 思路：1)、暴力
 *      2）、对每一行，先判断在不在行范围内，再做二分查找
 *      3）、以右上角为起点，向左下角开始搜索，比较当前点左、下两个点的值，绝对下一个位置；
 * 2022-04-17
 */
#include "common.h"

/***** 提交代码 ******************************************************************/
#if 0
/* 方案一：暴力 */
bool searchMatrix(int** matrix, int matrixSize, int* matrixColSize, int target){
    int i, j;
    for (i = 0; i < matrixSize; i++) {
        for (j = 0; j < matrixColSize{0]; j++) {
            if (matrix[i][j] == target) {
                return true;
            }
        }
    }
    return false;
}
#endif

#if 0
/* 方案二：遍历每一行，先判断在不在当前行范围，再二分查找 */
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
    int m = matrixSize;
    int n = matrixColSize[0];
#ifdef LOCAL_DEBUG
    int (*arr)[n] = (int(*)[n])matrix;
#else
    int **arr = matrix;
#endif

    if (target < arr[0][0] || target > arr[m - 1][n - 1]) {
        return false;
    }
    for (i = 0; i < m; i++) {
        if (target < arr[i][0] || target > arr[i][n -1 ]) {
            continue;
        }
        if (BinarySearch(arr[i], n, target) >= 0) {
            return true;
        }
    }
    return false;
}
#endif

/*
 * 方案三：从右上角往左下角遍历，每次比较当前点的左、下点，若target<=左点，则下一个遍历左点，
 *        否则下一个遍历下点，若超出数组范围仍为找到目标值，则返回false
 */
bool searchMatrix(int** matrix, int matrixSize, int* matrixColSize, int target)
{
    int m = matrixSize;
    int n = matrixColSize[0];
#ifdef LOCAL_DEBUG
    int (*arr)[n] = (int(*)[n])matrix;
#else
    int **arr = matrix;
#endif
    int x = 0, y = n - 1;

    while (x >= 0 && x < m && y >= 0 && y < n) {
        if (arr[x][y] == target) {
            return true;
        } else if (y > 0 && target <= arr[x][y - 1]) {
            y--;
        } else if (x < m - 1) {
            x++;
        } else {
            return false;
        }
    }

    return false;
}

/***** 本地调试 ******************************************************************/
void TestCase1(void)
{
    int arr[][5] = {
            {  1,  4,  7, 11, 15 },
            {  2,  5,  8, 12, 19 },
            {  3,  6,  9, 16, 22 },
            { 10, 13, 14, 17, 24 },
            { 18, 21, 23, 26, 30 }
    };
    int size = 5;
    int colSize[] = { 5, 5, 5, 5, 5 };
    int target = 5;
    Log("target exist: %d(1)\n", searchMatrix((int **)arr, size, colSize, target));
}

int main(void)
{
    TestCase1();
    return 0;
}