/*
 * 题目：leetcode 452: 用最少数量的箭引爆气球
 * 难度：中等
 * 技巧：贪心思想，使用qsort对区间按结束坐标升序排列，区间结束坐标能射穿的
 *       最多气球即为一支箭能射穿的最多气球
 * 时间：2020-04-06
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define LOCAL_DEBUG

struct Node {
	int start;
	int end;
};

/* 为快排库函数qsort提供的比较函数 */
int compare(const void *a, const void *b)
{
	return ((struct Node *)a)->end - ((struct Node *)b)->end;
}

int CanShot(struct Node pt, int x)
{
	if (x >= pt.start && x <= pt.end) {
		return 1;
	} else {
		return 0;
	}
}

int findMinArrowShots(int** points, int pointsSize, int* pointsColSize){
	int i;
	int end;
	int min = 0;
#ifdef LOCAL_DEBUG
	/* 本地编译获取二维数组 */
	int (*pt)[2] = (int(*)[2])points;
#else
	/* leetcode获取二维数组 */
	int **pt = points;
#endif
	struct Node *pts = (struct Node *)malloc(pointsSize * sizeof(struct Node));

    if (pointsSize == 0) {
        return 0;
    }
	for (i = 0; i < pointsSize; i++) {
		pts[i].start = pt[i][0];
		pts[i].end = pt[i][1];
	}
	/* C语言快排库函数排序结构体数组 */
	qsort(pts, pointsSize, sizeof(struct Node), compare);

    i = 0;
    end = pts[0].end;
    while (i < pointsSize) {
        while (i < pointsSize && CanShot(pts[i], end)) {
            i++;
        }
        min++;
        end = pts[i].end;
    }

	*pointsColSize = 2;
	return min;
}

int main(int argc, char *argv[])
{
	int points[][2] = {{10, 16}, {2, 8}, {1, 6}, {7, 12}};
	//int points[][2] = {{1, 2}, {3, 4}, {5, 6}, {7, 8}};
	int pointsSize = 4;

	int pointsColSize;
	printf("min arror = %d\n", findMinArrowShots((int **)points, pointsSize, &pointsColSize));
	return 0;
}
