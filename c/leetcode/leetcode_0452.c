/*
 * 题目：leetcode 452: 用最少数量的箭引爆气球
 * 难度：中等
 * 技巧：
 * 时间：2020-04-06
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

int findMinArrowShots(int** points, int pointsSize, int* pointsColSize){
	return 0;
}

int main(int argc, char *argv[])
{
	int points[][2] = {{10, 16}, {2, 8}, {1, 6}, {7, 12}};
	int pointsSize = 4;

	int pointsColSize;
	printf("min arror = %d\n", findMinArrowShots((int **)points, pointsSize, &pointsColSize));
	return 0;
}
