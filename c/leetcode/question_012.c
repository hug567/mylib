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

int match(char **maze, point *size, point *cur, char *word)
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
	p[top].x = cur->x;
	p[top].y = cur->y;
	top++;
	index++;
	visit[cur->x][cur->y] = 1;

	point now = {cur->x, cur->y};
	point next = {0, 0};

	do {
		if (get_next(maze, n, m, &now, &next, word[index])) {
			p[top].x = x;
			p[top].y = y;
			index++;
			visis[cur.x][cur.y] = 1;
		} else if (top < strlen(word) - 1) {
			return 0;
		} else {
			/* pop */
			top--;
			index--;
		}
	} while(top >= 0 && top < strlen(word) - 1);


	return top;
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

	point size = {n, m};
	point cur = {0, 0};
	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++) {
			if (maze[i][j] != word[0]) {
				continue;
			}
			cur.x = i;
			cur.y = y;
			ret = match(maze, &size, &cur, word);
			if (ret >= strlen(word) - 1) {
				printf("YES\n");
				goto test2;
			}
		}
	}
	printf("NO\n");
test2:
	return 0;
}
