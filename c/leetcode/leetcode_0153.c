/* leetcode 153: (简单) */
#include <stdio.h>
#include <stdlib.h>

int candy(int *ratings, int ratingsSize)
{
	int i = 0;
	int count = 0;
	int *left = (int *)malloc(ratingsSize * sizeof(int));
	int *right = (int *)malloc(ratingsSize * sizeof(int));

	for (i = 0; i < ratingsSize; i++) {
		*(left + i) = 1;
		*(right + i) = 1;
	}
	/* 左遍历：分高递增，分低不变 */
	for (i = 1; i < ratingsSize; i++) {
		if (*(ratings + i - 1) < *(ratings + i)) {
			*(left + i) = *(left + i - 1) + 1;
		}
	}
	/* 右遍历：分高递增，分低不变 */
	for (i = ratingsSize - 1; i > 0; i--) {
		if (*(ratings + i - 1) > *(ratings + i)) {
			*(right + i - 1) = *(right + i) + 1;
		}
	}
	/* 最两次遍历各位置较大值 */
	for (i = 0; i < ratingsSize; i++) {
		if (*(left + i) > *(right + i)) {
			count += *(left + i);
		} else {
			count += *(right + i);
		}
	}
	/* 所需的最少糖果 */
	return count;
}

int main()  /* 贪心算法 */
{
	//int ratings[3] = {1, 0, 2};
	//int ratingsSize = 3;
	int ratings[] = {5, 7, 8, 3, 4, 2, 1};
	int ratingsSize = 7;

	int num = candy(ratings, ratingsSize);
	printf("min candy: %d\n", num);
	return 0;
}
