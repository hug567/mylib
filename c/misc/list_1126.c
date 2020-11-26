/*
 * 练习：无头结点的单链表
 * 2020-11-16
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

void PrintList(const struct ListNode *first)
{
    printf("list: ");
    while (first != NULL) {
        printf("%d ", first->val);
        first = first->next;
    }
    printf("\n");
}

int ListLength(const struct ListNode *first)
{
    int len = 0;
    while (first != NULL) {
        len++;
        first = first->next;
    }
    return len;
}

struct ListNode *InsertHead(struct ListNode *first, int val)
{
    struct ListNode *node = NULL;

    node = (struct ListNode *)malloc(sizeof(struct ListNode));
    node->val = val;
    node->next = NULL;
    if (first != NULL) {
        node->next = first;
    }
    return node;
}

struct ListNode *InsertTail(struct ListNode *first, int val)
{
    struct ListNode *node = NULL;
    struct ListNode *tail = NULL;

    node = (struct ListNode *)malloc(sizeof(struct ListNode));
    node->val = val;
    node->next = NULL;
    if (first == NULL) {
        first = node;
    } else {
        tail = first;
        while (tail->next != NULL) {
            tail = tail->next;
        }
        tail->next = node;
    }
    return first;
}

struct ListNode *DeleteNode(struct ListNode *first, int val)
{
    struct ListNode *head = NULL;
    struct ListNode *pre = NULL;
    struct ListNode *cur = NULL;
    struct ListNode *tmp = NULL;

    head = (struct ListNode *)malloc(sizeof(struct ListNode));
    head->next = first;
    pre = head;
    cur = pre->next;
    while (cur != NULL) {
        if (cur->val == val) {
            tmp = cur;
            cur = cur->next;
            pre->next = cur;
            free(tmp);
            if (head == pre) {
                head->next = cur;
            }
        } else {
            pre = cur;
            cur = cur->next;
        }
    }
    first = head->next;
    free(head);
    return first;
}

void DestroyList(struct ListNode *first)
{
    struct ListNode *tmp = NULL;

    while (first != NULL) {
        tmp = first;
        first = first->next;
        free(tmp);
    }
}

int main(void)
{
    int i;
    struct ListNode *list = NULL;

    /* 从尾部插入 */
    for (i = 0; i < 10; i++) {
        list = InsertTail(list, i);
    }
    PrintList(list);

    /* 从头部插入 */
    for (i = 10; i < 20; i++) {
        list = InsertHead(list, i);
    }
    PrintList(list);

    /* 删除头部节点 */
    list = DeleteNode(list, 19);
    PrintList(list);

    /* 删除尾部节点 */
    list = DeleteNode(list, 9);
    PrintList(list);

    /* 删除中间节点 */
    list = DeleteNode(list, 0);
    PrintList(list);

    list = InsertTail(list, 8);
    list = InsertTail(list, 9);
    list = InsertTail(list, 10);
    PrintList(list);
    /* 删除中间多个节点 */
    list = DeleteNode(list, 8);
    PrintList(list);

    /* 链表长度 */
    printf("list len: %d\n", ListLength(list));

    /* 销毁链表 */
    DestroyList(list);
    list = NULL;

    return 0;
}
