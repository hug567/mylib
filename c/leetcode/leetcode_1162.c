#include <stdio.h>

#define MAX_SIZE (10000)

struct point {
	int x;
	int y;
};

int maxDistance(int** grid, int gridSize, int* gridColSize)
{
	int i = 0, j = 0, len = 0;
	int x = 0, y = 0;
	int d[5]  ={0, 1, 0, -1, 0};
	int front = -1, rear = -1, size = 0;
	struct point p[MAX_SIZE];

	/* 在LeetCode中获取二维数组 */
	int g[gridSize][gridSize];
	for (i = 0; i < gridSize; i++) {
		for (j = 0; j < gridSize; j++) {
			g[i][j] = *(*(grid+i)+j);
		}
	}
	/* 在本地编译获取二维数组 */
	/* int (*g)[gridSize] = (int(*)[gridSize])grid; */

	for (i = 0; i < gridSize; i++) {
		for (j = 0; j < gridSize; j++) {
			if (g[i][j] == 1 && size < MAX_SIZE) {
				rear++;
				rear %= MAX_SIZE;
				p[rear].x = i;
				p[rear].y = j;
				size++;
			}
		}
	}

	int num = gridSize * gridSize;
	if (size == num) {
		return -1;
	}

	while (size) {
		front++;
		front %= MAX_SIZE;
		size--;
		len = g[p[front].x][p[front].y];
		for (i = 0; i < 4; i++) {
			x = p[front].x + d[i];
			y = p[front].y + d[i + 1];
			if (x >= 0 && x < gridSize && y >= 0 && y < gridSize && g[x][y] == 0) {
				g[x][y] = len + 1;
				rear++;
				rear %= MAX_SIZE;
				size++;
				p[rear].x = x;
				p[rear].y = y;
			}
		}

	}

	return len - 1;
}

int main()
{
	return 0;
}

