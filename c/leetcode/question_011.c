/*
 * 题目：11、Olympic Game
 * 难度：中等
 * 技巧：
 * 时间：200-03-11
 */
/*
5
China 32 28 34
England 12 34 22
France 23 33 2
Japan 12 34 25
Rusia 23 43 0
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "securec.h"

#define MAX_CTY 20
#define NAME_LEN 20

struct Country {
	char name[NAME_LEN + 1];
	char gold;
	char silver;
	char bronze;
};

void DebugPrint(struct Country *cty, int n)
{
	int i;
	printf("----- cty info, n = %d -----\n", n);
	for (i = 0; i < n; i++) {
		printf("%s %d %d %d\n", cty[i].name, cty[i].gold, cty[i].silver, cty[i].bronze);
	}
}

int main()
{
	int i;
	int n;

	if (scanf_s("%d", &n) != 1) {
		return -1;
	}
	/* malloc struct array */
	struct Country *cty = (struct Country *)malloc(n * sizeof(struct Country));
	for (i = 0; i < n; i++) {
		(void)memset_s(&cty[i], sizeof(struct Country), 0, sizeof(struct Country));
		if (scanf_s("%s %d %d %d", cty[i].name, &cty[i].gold, &cty[i].silver,
			    &cty[i].bronze, sizeof(struct Country)) != 4) {
			return -1;
		}
	}
	DebugPrint(cty, n);

	return 0;
}
