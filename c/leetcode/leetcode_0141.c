/* leetcode 141: 环形链表(简单) */
#include <stdio.h>
#include <stdlib.h>

struct ListNode {
	int val;
	struct ListNode *next;
};

bool hasCycle(struct ListNode *head)
{
	return 0;
}

int main()
{
	int i;
	int val[] = {3, 2, 0, 4};
	struct ListNode *head = (struct ListNode *)malloc(sizeof(struct ListNode));
	struct ListNode *next = NULL, *tmp = NULL;
	head->val = val[0];
	head->next = NULL;

	tmp = head;
	for (i = 1; i < 4; i++) {
		next = (struct ListNode *)malloc(sizeof(struct ListNode));
		next->val = val[i];
		next->next = NULL;
		tmp->next = next;
		tmp = next;
	}
	tmp->next = head->next;

	tmp = head;
	printf("listA : ");
	while (tmp != NULL) {
		printf("%d ", tmp->val);
		tmp = tmp->next;
	}
	printf("\n");

	if (hasCycle(head)) {
		printf("true\n");
	} else {
		printf("false\n");
	}

	return 0;
}
