/*
 * 题目：11、Olympic Game
 * 难度：中等
 * 技巧：
 * 时间：2020-03-11
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
	struct Country *next;
};

int CompareCountry(struct Country *cty1, struct Country *cty2)
{
	int cmp;

	if (cty1 == NULL || cty2 == NULL) {
		return 0;
	}

	if (cty1->gold > cty2->gold) {
		return 1;
	} else if (cty1->gold < cty2->gold) {
		return -1;
	}

	if (cty1->silver > cty2->silver) {
		return 1;
	} else if (cty1->silver < cty2->silver) {
		return -1;
	}

	if (cty1->bronze > cty2->bronze) {
		return 1;
	} else if (cty1->bronze < cty2->bronze) {
		return -1;
	}

	return strcmp(cty2->name, cty1->name);
}

struct Country *InsertCountry(struct Country *head, struct Country *tmp)
{
	struct Country *cur = head;

	if (tmp == NULL) {
		return head;
	} else if (head == NULL) {
		return tmp;
	}
	if (CompareCountry(head, tmp) < 0) {
		tmp->next = head;
		return tmp;
	}
	while (cur->next != NULL && CompareCountry(cur->next, tmp) > 0) {
		cur = cur->next;
	}
	if (cur->next == NULL) {
		cur->next = tmp;
	} else {
		tmp->next = cur->next;
		cur->next = tmp;
	}
	return head;
}

void PrintSorted(struct Country *head)
{
	if (head == NULL) {
		return;
	}
	while (head != NULL) {
		(void)printf("%s\n", head->name);
		head = head->next;
	}
}

int main()
{
	int i;
	int n;

	if (scanf_s("%d", &n) != 1) {
		return -1;
	}
	struct Country *head = NULL ;
	struct Country *tmp = NULL ;
	for (i = 0; i < n; i++) {
		tmp = (struct Country *)malloc(sizeof(struct Country));
		if (scanf_s("%s %d %d %d", tmp->name, &tmp->gold, &tmp->silver,
			    &tmp->bronze, sizeof(struct Country)) != 4) {
			return -1;
		}
		tmp->next = NULL;
		head = InsertCountry(head, tmp);
	}
	PrintSorted(head);

	return 0;
}
