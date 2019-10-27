/* leetcode 160: 相交链表(简单) */
#include <stdio.h>
#include <stdlib.h>

struct ListNode {
	int val;
	struct ListNode *next;
};

struct ListNode *getIntersectionNode(struct ListNode *headA, struct ListNode *headB)
{
	if (headA == NULL || headB == NULL) {
		return NULL;
	}
	int i, lenA = 0, lenB = 0, lenMin = 0;
	struct ListNode *cur = NULL;

	cur = headA;
	do {
		lenA++;
		cur = cur->next;
	} while(cur != NULL);
	cur = headB;
	do {
		lenB++;
		cur = cur->next;
	} while(cur != NULL);

	if (lenA > lenB) {
		lenMin = lenB;
		for (i = 0; i < lenA - lenB; i++) {
			headA = headA->next;
		}
	} else {
		lenMin = lenA;
		for (i = 0; i < lenB - lenA; i++) {
			headB = headB->next;
		}
	}

	for (i = 0; i < lenMin; i++) {
		if (headA == headB) {
			return headA;
		}
		headA = headA->next;
		headB = headB->next;
	}

	return NULL;
}

int main()
{
	int i;//, m, n;
	int valA[] = {4, 1, 8, 4, 5};
	int valB[] = {5, 0, 1};
	struct ListNode *headA = (struct ListNode *)malloc(sizeof(struct ListNode));
	struct ListNode *headB = (struct ListNode *)malloc(sizeof(struct ListNode));
	struct ListNode *next = NULL, *tmp = NULL;
	headA->val = valA[0];
	headA->next = NULL;
	headB->val = valB[0];
	headB->next = NULL;

	tmp = headA;
	for (i = 1; i < 5; i++) {
		next = (struct ListNode *)malloc(sizeof(struct ListNode));
		next->val = valA[i];
		next->next = NULL;
		tmp->next = next;
		tmp = next;
	}
	tmp = headB;
	for (i = 1; i < 3; i++) {
		next = (struct ListNode *)malloc(sizeof(struct ListNode));
		next->val = valB[i];
		next->next = NULL;
		tmp->next = next;
		tmp = next;
	}
	tmp->next = headA->next->next;

	tmp = headA;
	printf("listA : ");
	while (tmp != NULL) {
		printf("%d ", tmp->val);
		tmp = tmp->next;
	}
	printf("\n");
	tmp = headB;
	printf("listB : ");
	while (tmp != NULL) {
		printf("%d ", tmp->val);
		tmp = tmp->next;
	}
	printf("\n");

	tmp = getIntersectionNode(headA, headB);
	printf("Intersection : ");
	if (tmp != NULL) {
		printf("%d\n", tmp->val);
	} else {
		printf("NULL\n");
	}

	return 0;
}
