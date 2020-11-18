/*
 * 练习：无头结点的单链表
 * 2020-11-18
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode *InsertTail(struct ListNode *l, int val)
{
    struct ListNode *node = NULL;
    struct ListNode *tmp = NULL;

    node = (struct ListNode *)malloc(sizeof(struct ListNode));
    node->val = val;
    node->next = NULL;
    if (l == NULL) {
        l = node;
    } else {
        tmp = l;
        while (tmp->next != NULL) {
            tmp = tmp->next;
        }
        tmp->next = node;
    }
    return l;
}

struct ListNode *DeleteNode(struct ListNode *l, int val)
{
    struct ListNode *head = NULL;
    struct ListNode *pre = NULL;
    struct ListNode *cur = NULL;
    struct ListNode *tmp = NULL;

    /* 添加头结点 */
    head = (struct ListNode *)malloc(sizeof(struct ListNode));
    head->next = l;
    /* 循环删除节点 */
    pre = head;
    cur = pre->next;
    while (cur != NULL) {
        if (cur->val == val) { /* 当前节点需删除 */
            tmp = cur;
            cur = cur->next;
            pre->next = cur;
            free(tmp);
            if (pre == head) { /* 删除的是头结点 */
                head->next = cur;
            }
        } else { /* 当前节点不需删除 */
            pre = cur;
            cur = cur->next;
        }
    }
    l = head->next;
    free(head);
    return l;
}

void DestroyList(struct ListNode *l)
{
    struct ListNode *tmp = NULL;

    while (l != NULL) {
        tmp = l;
        l = l->next;
        free(tmp);
    }
}

void PrintList(struct ListNode *l)
{
    printf("list: ");
    while (l != NULL) {
        printf("%d ", l->val);
        l = l->next;
    }
    printf("\n");
}

int main(void)
{
    int i;
    struct ListNode *l = NULL;

    for (i = 0; i < 10; i++) {
        l = InsertTail(l, i);
    }
    PrintList(l);

    /* 删除头结点 */
    l = DeleteNode(l, 0);
    PrintList(l);

    /* 删除尾结点 */
    l = DeleteNode(l, 9);
    PrintList(l);

    /* 删除中间结点 */
    l = DeleteNode(l, 4);
    PrintList(l);

    /* 删除不存在的结点 */
    l = DeleteNode(l, 10);
    PrintList(l);

    l = InsertTail(l, 8);
    l = InsertTail(l, 9);
    PrintList(l);
    /* 删除值相同的多个节点 */
    l = DeleteNode(l, 8);
    PrintList(l);

    /* 销毁链表 */
    DestroyList(l);
    l = NULL;
    PrintList(l);

    /* 删除空链表 */
    l = DeleteNode(l, 8);
    PrintList(l);

    return 0;
}
