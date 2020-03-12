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

struct Country *InsertCountry(struct Country *head, struct Country *tmp)
{
	struct Country *tail = head;
	if (head == NULL) {
		if (tmp == NULL) {
			return NULL;
		} else {
			return tmp;
		}
	}
	while (tail->next != NULL) {
		tail = tail->next;
	}
	tail->next = tmp;
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
