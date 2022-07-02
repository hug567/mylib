/*
 * leetcode 24: 两两交换链表中的节点 [中等]
 * 思路：使用两个队列，相邻节点分别入队列1、2，在按队列2、1的顺序出队，组成新的链表
 *      原始链表拆分成2个链表，再按相关顺序组装成一个新的链表
 * 2022-07-02
 */
#include "common.h"

struct ListNode {
    int val;
    struct ListNode *next;
};

void PrintList(struct ListNode *head)
{
    Log("list: ");
    while (head != NULL) {
        printf("%d ", head->val);
        head = head->next;
    }
    printf("\n");
}

/***** 提交代码 ******************************************************************/
struct ListNode* swapPairs(struct ListNode* head)
{
    int count = 0;
    struct ListNode *cur = NULL;
    struct ListNode *h1 = NULL, *h2 = NULL, *t1 = NULL, *t2 = NULL;

    while (head != NULL) {
        if (count % 2 == 0) {
            if (h1 == NULL) {
                h1 = head;
                t1 = h1;
            } else {
                t1->next = head;
                t1 = head;
            }
        } else {
            if (h2 == NULL) {
                h2 = head;
                t2 = h2;
            } else {
                t2->next = head;
                t2 = head;
            }
        }
        head = head->next;
        count++;
    }
    if (t1 != NULL) {t1->next = NULL;}
    if (t2 != NULL) {t2->next = NULL;}
    head = NULL;
    while (h1 != NULL || h2 != NULL) {
        if (h2 != NULL) {
            if (head == NULL) {
                head = h2;
                cur = head;
            } else {
                cur->next = h2;
                cur = h2;
            }
            h2 = h2->next;
        }
        if (h1 != NULL) {
            if (head == NULL) {
                head = h1;
                cur = head;
            } else {
                cur->next = h1;
                cur = h1;
            }
            h1 = h1->next;
        }
    }

    return head;
}

/***** 本地调试 ******************************************************************/
void TestCase1(void)
{
    int i;
    int arr[] = {1, 2, 3, 4};
    int size = ARRAY_SIZE(arr);
    struct ListNode *head = NULL, *tail = NULL;

    for (i = 0; i < size; i++) {
        if (head == NULL) {
            head = malloc(sizeof(struct ListNode));
            head->val = arr[i];
            head->next = NULL;
            tail = head;
        } else {
            tail->next = malloc(sizeof(struct ListNode));
            tail = tail->next;
            tail->val = arr[i];
            tail->next = NULL;
        }
    }
    PrintList(head);
    head = swapPairs(head);
    PrintList(head);
}

int main(void)
{
    TestCase1();
    return 0;
}