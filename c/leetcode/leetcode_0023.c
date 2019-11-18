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
	int i = 0, j = 0, swap = 0;
	struct ListNode *head = NULL, *tail = NULL, *tmp = NULL;

	int sum = 0;
	for (i = 0; i < listsSize; i++) {
		tmp = lists[i];
		while(tmp != NULL) {
			sum++;
			tmp = tmp->next;
		}
	}

	int *nums = (int *)malloc(sum * sizeof(int));
	j = 0; head = NULL;
	for (i = 0; i < listsSize; i++) {
		tmp = lists[i];
		while(tmp != NULL) {
			if (head == NULL) {
				head = tmp;
				tail = head;
			} else {
				tail->next = tmp;
				tail = tail->next;
			}
			nums[j] = tmp->val;
			j++;
			tmp = tmp->next;
		}
	}

	for (i = 0; i < sum - 1; i++) {
		for (j = i + 1; j < sum; j++) {
			if (nums[i] > nums[j]) {
				swap = nums[i];
				nums[i] = nums[j];
				nums[j] = swap;
			}
		}
	}

	tmp = head;
	for (i = 0; i < sum; i++) {
		tmp->val = nums[i];
		tmp = tmp->next;
	}

	return head;
}

int main()
{
	int i;
	int val1[] = {1, 4, 5};
	int val2[] = {1, 3, 4};
	int val3[] = {2, 6};
	struct ListNode *l1 = NULL, *l2 = NULL, *l3 = NULL;
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
	tmp->next = NULL;
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
	tmp->next = NULL;
	for (i = 0; i < sizeof(val3) / sizeof(int); i++) {
		next = (struct ListNode *)malloc(sizeof(struct ListNode));
		next->val = val3[i];
		next->next = NULL;
		if (i == 0) {
			l3 = next;
			tmp = next;
		} else {
			tmp->next = next;
			tmp = next;
		}
	}
	tmp->next = NULL;

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
	tmp = l3;
	printf("list3 : ");
	while (tmp != NULL) {
		printf("%d ", tmp->val);
		tmp = tmp->next;
	}
	printf("\n");

	lists[0] = l1;
	lists[1] = l2;
	lists[2] = l3;
	tmp = mergeKLists(lists, listsSize);
	printf("merge list : ");
	while (tmp != NULL) {
		printf("%d ", tmp->val);
		tmp = tmp->next;
	}
	printf("\n");

	return 0;
}
