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
    struct TreeNode *val;
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
    struct QueueNode *qn = NULL;
    if (q == NULL || t == NULL) {
        printf("queue or tree node is NULL\n");
        return;
    }
    qn = (struct QueueNode *)malloc(sizeof(struct QueueNode));
    qn->val = t;
    qn->next = NULL;
    if (q->size == 0) {
        q->head = qn;
        q->tail = qn;
    } else {
        q->tail->next = qn;
        q->tail = qn;
    }
    q->size++;
}

struct TreeNode *DeQueue(struct Queue *q)
{
    struct QueueNode *qn = NULL;
    struct TreeNode *tn = NULL;
    if (q == NULL || q->size <= 0) {
        printf("queue is empty\n");
        return NULL;
    }
    qn = q->head;
    q->head = q->head->next;
    q->size--;
    tn = qn->val;
    free(qn);
    return tn;
}

void PrintQueue(struct Queue *q)
{
    if (q == NULL) {
        printf("q is NULL\n");
        return;
    }
    struct QueueNode *qn = q->head;
    printf("Queue: ");
    while (qn != NULL) {
        printf("%d ", qn->val->val);
        qn = qn->next;
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
    struct Queue *q = NULL;
    struct TreeNode *tn = NULL;

    if (t == NULL) {
        return;
    }
    q = (struct Queue *)malloc(sizeof(struct Queue));
    InitQueue(q);
    EnQueue(q, t);
    while (q->size > 0) {
        tn = DeQueue(q);
        printf("%d ", tn->val);
        if (tn->left != NULL) {
            EnQueue(q, tn->left);
        }
        if (tn->right != NULL) {
            EnQueue(q, tn->right);
        }
    }

    free(q);
}

int TreeDepth(struct TreeNode *t)
{
    if (t == NULL) {
        return 0;
    }
    int ld = TreeDepth(t->left);
    int rd = TreeDepth(t->right);
    return (ld > rd ? ld : rd) + 1;
}

int main(void)
{
    int i;
    struct Queue q;
    struct TreeNode *t = NULL;
    int arr[] = {5, 4, 11, 7, -1, -1, 2, -1, -1, -1, 8, 13, -1, -1, 4, 5, -1, -1, 1, -1, -1};

    InitQueue(&q);
    for (i = 0; i < 10; i++) {
        t = (struct TreeNode *)malloc(sizeof(struct TreeNode));
        t->val = i;
        EnQueue(&q, t);
    }
    PrintQueue(&q);

    t = DeQueue(&q);
    printf("i = %d\n", t->val);
    free(t);
    PrintQueue(&q);

    t = CreateTreeByArray(arr, sizeof(arr) / sizeof(arr[0]));
    printf("tree pre order: ");
    PreOrder(t);
    printf("\n");

    printf("tree level order: ");
    LevelOrder(t);
    printf("\n");

    printf("tree depth is: %d\n", TreeDepth(t));

    return 0;
}
