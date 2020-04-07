/*
 * 练习：C语言快速排序库函数，排序结构体
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

struct Node {
	int x;
	int y;
};

int Compare(const void *a, const void *b)
{
	//return *(int *)a - *(int *)b; /* 升序 */
	//return *(int *)b - *(int *)a; /* 降序 */
	struct Node *n1 = (struct Node *)a;
	struct Node *n2 = (struct Node *)b;

	return n1->y - n2->y;
}

void PrintArray(struct Node *points, int size)
{
	int i;
	printf(">>> print points: <<<\n");
	for (i = 0; i < size; i++) {
		printf("point[%d]: %d %d\n", i, points[i].x, points[i].y);
	}
}

int main()
{
	int i;
	struct Node points[SIZE] = {0};

	for (i = 0; i < SIZE; i++) {
		points[i].x = rand() % 20;
		points[i].y = rand() % 20;
	}
	PrintArray(points, SIZE);
	qsort(points, SIZE, sizeof(struct Node), Compare);
	PrintArray(points, SIZE);
	return 0;
}
