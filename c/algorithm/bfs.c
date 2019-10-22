#include <stdio.h>

#define MAX_SIZE 100

struct {
	int x;
	int y;
} g_points[MAX_SIZE];

int g_front = -1;
int g_rear = -1;
int g_size = 0;

int bfs(int start)
{
	return 0;
}

int main()
{
	int maze[5][5] = {
		{ 0, 1, 1, 0, 0 },
		{ 0, 0, 1, 0, 1 },
		{ 0, 0, 1, 0, 0 },
		{ 1, 1, 0, 0, 1 },
		{ 0, 0, 1, 0, 0 }};
	printf("hello bfs\n");
	return 0;
}
