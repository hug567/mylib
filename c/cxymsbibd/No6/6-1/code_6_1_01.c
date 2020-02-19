/*
 * 《程序员面试宝典》第2版
 * 第6章 数据结构与算法
 * 6.1 数组
 * 6.1.1 如何使用递归实现数组求和
 */
#include <stdio.h>

static int sum(int *arr, int n)
{
	if (n == 0) {
		return arr[0];
	} else {
		return arr[n] + sum(arr, n - 1);
	}
}

int main()
{
	int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	int len = sizeof(arr) / sizeof(arr[0]);
	printf("sum = %d\n", sum(arr, len - 1));
	return 0;
}
