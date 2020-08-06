/*
 * 练习：
 * 1、链队
 * 2、根据数组创建二叉树
 * 3、获取二叉树深度
 * 4、二叉树层次遍历
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct QueueNode {
    struct TreeNode *t;
    struct QueueNode *next;
};

struct Queue {
    struct QueueNode *head;
    struct QueueNode *tail;
    int size;
};

void InitQueue(struct Queue *q)
{
    if (q == NULL) {
        return;
    }
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
}

void EnQueue(struct Queue *q, struct TreeNode *t)
{
    if (q == NULL) {
        printf("queue is NULL\n");
        return;
    }
    if (q->size == 0) {
        q->head = t;
        q->tail = t;
    } else {
        q->tail->next = t;
        q->tail = t;
    }
    q->size++;
}

struct TreeNode *DeQueue(struct Queue *q)
{
    struct TreeNode *t = NULL;
    if (q == NULL || q->size == 0) {
        printf("queue is empty\n");
        return NULL;
    }
    t = q->head;
    q->head = q->head->next;
    q->size--;
    return t;
}

int Empty(struct Queue *q)
{
    if (q == NULL) {
        printf("q is NULL\n");
        return 1;
    }
    if (q->head == NULL) {
        return 1;
    } else {
        return 0;
    }
}

void PrintQueue(struct Queue *q)
{
    if (q == NULL) {
        printf("q is NULL\n");
        return;
    }
    struct QueueNode *node = q->head;
    printf("Queue: ");
    while (node != NULL) {
        printf("%d ", node->val);
        node = node->next;
    }
    printf("\n");
}

int g_idx = 0;
struct TreeNode *CreateTreeByArray(int *arr, int size)
{
    struct TreeNode *t = NULL;
    if (g_idx >= size) {
        return NULL;
    } else if (arr[g_idx] == -1) {
        g_idx++;
    } else {
        t = (struct TreeNode *)malloc(sizeof(struct TreeNode));
        t->val = arr[g_idx];
        g_idx++;
        t->left = CreateTreeByArray(arr, size);
        t->right = CreateTreeByArray(arr, size);
    }
    return t;
}

void PreOrder(struct TreeNode *t)
{
    if (t == NULL) {
        return;
    }
    printf("%d ", t->val);
    PreOrder(t->left);
    PreOrder(t->right);
}

/* 二叉树的层次遍历 */
void LevelOrder(struct TreeNode *t)
{

}

int main(void)
{
    int i;
    struct Queue *q = NULL;
    struct TreeNode *t = NULL;
    int arr[] = {5, 4, 11, 7, -1, -1, 2, -1, -1, -1, 8, 13, -1, -1, 4, 5, -1, -1, 1, -1, -1};

    q = CreateQueue();
    for (i = 0; i < 10; i++) {
        Push(q, i);
    }
    PrintQueue(q);

    i = Pop(q);
    printf("i = %d\n", i);
    PrintQueue(q);

    t = CreateTreeByArray(arr, sizeof(arr) / sizeof(arr[0]));
    printf("tree pre order: ");
    PreOrder(t);
    printf("\n");

    return 0;
}
