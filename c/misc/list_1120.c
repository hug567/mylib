/*
 * 练习：带头结点的单链表
 * 功能：初始化，插入，删除，销毁
 * 2020-11-20
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

void PrintList(struct ListNode *head)
{
    struct ListNode *cur = NULL;

    if (head == NULL) {
        return;
    }
    printf("list: ");
    cur = head->next;
    while (cur != NULL) {
        printf("%d ", cur->val);
        cur = cur->next;
    }
    printf("\n");
}

void InitList(struct ListNode *head)
{
    if (head == NULL) {
        return;
    }
    head->next = NULL;
}

void InsertNodeTail(struct ListNode *head, int val)
{
    struct ListNode *tmp = NULL;
    struct ListNode *node = NULL;

    if (head == NULL) {
        return;
    }
    node = (struct ListNode *)malloc(sizeof(struct ListNode));
    node->val = val;
    node->next = NULL;
    tmp = head;
    while (tmp->next != NULL) {
        tmp = tmp->next;
    }
    tmp->next = node;
}

void InsertNodeHead(struct ListNode *head, int val)
{
    struct ListNode *node = NULL;

    if (head == NULL) {
        return;
    }
    node = (struct ListNode *)malloc(sizeof(struct ListNode));
    node->val = val;
    node->next = head->next;
    head->next = node;
}

void DeleteNode(struct ListNode *head, int val)
{
    struct ListNode *pre = NULL;
    struct ListNode *cur = NULL;
    struct ListNode *tmp = NULL;

    if (head == NULL) {
        return;
    }
    pre = head;
    cur = pre->next;
    while (cur != NULL) {
        if (cur->val == val) {
            tmp = cur;
            cur = cur->next;
            pre->next = cur;
            free(tmp);
            if (pre == head) {
                head->next = cur;
            }
        } else {
            pre = cur;
            cur = cur->next;
        }
    }
}

void DestroyList(struct ListNode *head)
{
    struct ListNode *cur = NULL;
    struct ListNode *tmp = NULL;

    if (head == NULL) {
        return;
    }
    cur = head->next;
    while (cur != NULL) {
        tmp = cur;
        cur = cur->next;
        free(tmp);
    }
    head->next = NULL;
}

int main(void)
{
    int i;
    struct ListNode real_lsit;
    struct ListNode *head = &real_lsit;

    InitList(head);
    for (i = 0; i < 10; i++) {
        InsertNodeTail(head, i);
    }
    PrintList(head);

    /* 删除尾节点 */
    DeleteNode(head, 9);
    PrintList(head);

    /* 删除头节点 */
    DeleteNode(head, 0);
    PrintList(head);

    /* 删除中间节点 */
    DeleteNode(head, 5);
    PrintList(head);

    InsertNodeTail(head, 8);
    InsertNodeTail(head, 10);
    InsertNodeTail(head, 11);
    PrintList(head);
    /* 删除中间多个节点 */
    DeleteNode(head, 8);
    PrintList(head);

    InsertNodeTail(head, 11);
    PrintList(head);
    /* 删除尾部多个节点 */
    DeleteNode(head, 11);
    PrintList(head);

    InsertNodeHead(head, 1);
    PrintList(head);
    /* 删除头部多个节点 */
    DeleteNode(head, 1);
    PrintList(head);

    return 0;
}
