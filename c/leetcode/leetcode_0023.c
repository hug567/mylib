/* leetcode 23: 合并K个排序链表(困难) */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct ListNode {
	int val;
	struct ListNode *next;
};

struct ListNode* mergeKLists(struct ListNode** lists, int listsSize)
{
	struct ListNode *head = NULL;
	return head;
}

int main()
{
	int i;
	int val1[] = {1, 2, 4};
	int val2[] = {1, 3, 4};
	struct ListNode *l1 = NULL, *l2 = NULL;
	struct ListNode *next = NULL, *tmp = NULL;
	int listsSize = 3;
	struct ListNode *lists[3];

	/* 构造链表 */
	for (i = 0; i < sizeof(val1) / sizeof(int); i++) {
		next = (struct ListNode *)malloc(sizeof(struct ListNode));
		next->val = val1[i];
		next->next = NULL;
		if (i == 0) {
			l1 = next;
			tmp = next;
		} else {
			tmp->next = next;
			tmp = next;
		}
	}
	for (i = 0; i < sizeof(val2) / sizeof(int); i++) {
		next = (struct ListNode *)malloc(sizeof(struct ListNode));
		next->val = val2[i];
		next->next = NULL;
		if (i == 0) {
			l2 = next;
			tmp = next;
		} else {
			tmp->next = next;
			tmp = next;
		}
	}

	tmp = l1;
	printf("list1 : ");
	while (tmp != NULL) {
		printf("%d ", tmp->val);
		tmp = tmp->next;
	}
	printf("\n");
	tmp = l2;
	printf("list2 : ");
	while (tmp != NULL) {
		printf("%d ", tmp->val);
		tmp = tmp->next;
	}
	printf("\n");

	tmp = mergeKLists(lists, listsSize);
	printf("merge list : ");
	while (tmp != NULL) {
		printf("%d ", tmp->val);
		tmp = tmp->next;
	}
	printf("\n");

	return 0;
}
