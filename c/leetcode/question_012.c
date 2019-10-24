#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
	int x;
	int y;
} point;

int get_next(char **maze, int n, int m, point *cur, point *next, char ch)
{
	int i;
	int cx, cy;
	int dir[5] = {0, 1, 0, -1, 0};

	for (i = 0; i < 4; i++) {
		cx = cur->x + dir[i];
		cy = cur->y + dir[i+1];
		if (cx >= 0 && cx < n && cy >= 0 && cy < m
		    && maze[cx][cy] == ch) {
			next->x = cx;
			next->y = cy;
			return 1;
		}
	}
	return 0;
}

int match(char **maze, int n, int m, char *word, int x, int y)
{
	int i = 0, j = 0, top = 0;
	int index = 0;
	int visit[20][20];
	point p[100];

	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++) {
			visit[i][j] = 0;
		}
	}

	/* push */
	p[top].x = x;
	p[top].y = y;
	top++;
	index++;
	visit[x][y] = 1;

	point cur = {.x = x, .y = y};
	point next;

	do {
		if (get_next(maze, n, m, &cur, &next, word[index])) {
			p[top].x = x;
			p[top].y = y;
			index++;
			visis[cur.x][cur.y] = 1;
		}

	} while(0);


	return 0;
}

int main()
{
	int n = 5, m = 5;
	char *word = "SOLO";
	char maze[20][20] = {"CPUCY", "EKLQH", "CRSOL", "EKLQO", "PGRBC"};
	int i, j, ret;

	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++) {
			printf("%c", maze[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++) {
			if (maze[i][j] == word[0]) {
				ret = match((char **)maze, n, m, word, i, j);
				printf("i = %d, j = %d, ret = %d\n", i, j, ret);
			}
		}
	}

	printf("siezof(maze) = %ld\n", sizeof(maze));

	return 0;
}
