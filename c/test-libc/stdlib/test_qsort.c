/*
 * 练习：C语言快速排序库函数
 * 原型：void qsort(void *base, size_t nmemb, size_t size, int(*compar)(const void *, const void *));
 *       base：数据首地址
 *       nmemb：元素个数
 *       size：每个元素占用的地址空间
 *       compar：比较函数
 *       int (*compar)(const void *a, const void *b)
 *           a > b 返回 >0 的值，为升序
 *           a > b 返回 <0 的值，为降序
 * 时间：2020-03-30
 */
#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

int Compare(const void *a, const void *b)
{
	//return *(int *)a - *(int *)b; /* 升序 */
	return *(int *)b - *(int *)a; /* 降序 */
}

void PrintArray(int *data, int size)
{
	int i;
	printf("array[%d]: ", size);
	for (i = 0; i < size; i++) {
		printf("%d ", data[i]);
	}
	printf("\n");
}

int main()
{
	int i;
	int nums[SIZE] = {0};

	for (i = 0; i < SIZE; i++) {
		nums[i] = rand() % 20;
	}
	PrintArray(nums, SIZE);
	qsort(nums, SIZE, sizeof(int), Compare);
	PrintArray(nums, SIZE);
	return 0;
}
