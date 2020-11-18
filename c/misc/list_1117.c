/*
 * 练习：链表节点删除
 * 2020-11-17
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

struct List {
    struct ListNode *node;
    int num;
};

void InitList(struct List *l)
{
    l->node = NULL;
    l->num = 0;
}

void InsertNodeTail(struct List *l, int val)
{
    struct ListNode *tail = NULL;
    struct ListNode *node = NULL;

    node = (struct ListNode *)malloc(sizeof(struct ListNode));
    node->val = val;
    node->next = NULL;
    if (l->node == NULL) {
        l->node = node;
    } else {
        tail = l->node;
        while (tail->next != NULL) {
            tail = tail->next;
        }
        tail->next = node;
    }
    l->num++;
}

struct ListNode *DeleteListNode(struct ListNode *cur, int val)
{
    struct ListNode *pre = NULL;
    struct ListNode *tmp = NULL;
    struct ListNode *head = (struct ListNode *)malloc(sizeof(struct ListNode));

    if (cur == NULL) {
        return NULL;
    }
    /* 添加头结点 */
    head->next = cur;
    pre = head;
    while (cur != NULL) {
        if (cur->val == val) {
            pre->next = cur->next;
            tmp = cur;
            cur = cur->next;
            free(tmp);
        } else {
            cur = cur->next;
            pre = pre->next;
        }
    }
    tmp = pre->next;
    free(head);
    return tmp;
}

void PrintList(struct List *l)
{
    struct ListNode *node = l->node;

    printf("list: ");
    while (node != NULL) {
        printf("%d ", node->val);
        node = node->next;
    }
    printf("\n");
}

int main(void)
{
    int i;
    struct List list;

    InitList(&list);
    for (i = 0; i < 10; i++) {
        InsertNodeTail(&list, i);
    }
    PrintList(&list);
    list.node = DeleteListNode(&list.node, 5);
    PrintList(&list);

    return 0;
}
