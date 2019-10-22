#include <stdio.h>

int match(char maze[20][20], int n, int m, char *word, int x, int y)
{
	return 0;
}

int main()
{
	int n = 5, m = 5;
	char *word = "SOLO";
	char maze[20][20] = {"12345", "xixi"};

	int i,j;
	fot (i = 0; i < n; i++) {
		for (j = 0; j < m; j++) {
			printf("%c", maze[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	return 0;
}
