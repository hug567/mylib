/*
 * 练习：二叉树
 * 2020-09-17
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXINT (int)(~0U >> 1)
#define MININT (int)(1U << (8 * sizeof(int) - 1))

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct StackNode {
    int val;
    struct StackNode *next;
};

struct Stack {
    struct StackNode *top;
    int len;
};

struct QueueNode {
    struct TreeNode *val;
    struct QueueNode *next;
};

struct Queue {
    struct QueueNode *head;
    struct QueueNode *tail;
    int len;
};

void InitStack(struct Stack *s)
{
    s->top = NULL;
    s->len = 0;
}

void Push(struct Stack *s, int val)
{
    struct StackNode *sn = NULL;

    sn = (struct StackNode *)malloc(sizeof(struct StackNode));
    sn->val = val;
    sn->next = NULL;
    if (s->len == 0) {
        s->top = sn;
    } else {
        sn->next = s->top;
        s->top = sn;
    }
    s->len++;
}

int Pop(struct Stack *s)
{
    int val;
    struct StackNode *sn = NULL;

    if (s->len <= 0) {
        return MININT;
    }
    sn = s->top;
    val = sn->val;
    s->top = s->top->next;
    s->len--;
    free(sn);
    return val;
}

void InitQueue(struct Queue *q)
{
    q->head = NULL;
    q->tail = NULL;
    q->len = 0;
}

void EnQueue(struct Queue *q, struct TreeNode *val)
{
    struct QueueNode *qn = NULL;

    qn = (struct QueueNode *)malloc(sizeof(struct QueueNode));
    qn->val = val;
    qn->next = NULL;
    if (q->len <= 0) {
        q->head = qn;
        q->tail = qn;
    } else {
        q->tail->next = qn;
        q->tail = qn;
    }
    q->len++;
}

struct TreeNode *DeQueue(struct Queue *q)
{
    struct TreeNode *val = NULL;
    struct QueueNode *qn = NULL;

    if (q->len <= 0) {
        return NULL;
    }
    qn = q->head;
    val = qn->val;
    q->head = q->head->next;
    q->len--;
    free(qn);
    return val;
}

static int g_index = 0;
struct TreeNode *CreateTreeByArray(const int *arr, int size)
{
    struct TreeNode *tn = NULL;

    if (g_index >= size) {
        return NULL;
    } else if (arr[g_index] == -1) {
        g_index++;
    } else {
        tn = (struct TreeNode *)malloc(sizeof(struct TreeNode));
        tn->val = arr[g_index];
        g_index++;
        tn->left = CreateTreeByArray(arr, size);
        tn->right = CreateTreeByArray(arr, size);
    }
    return tn;
}

void PreOrder(const struct TreeNode *t)
{
    if (t == NULL) {
        return;
    }
    printf("%d ", t->val);
    PreOrder(t->left);
    PreOrder(t->right);
}

void InOrder(const struct TreeNode *t)
{
    if (t == NULL) {
        return;
    }
    InOrder(t->left);
    printf("%d ", t->val);
    InOrder(t->right);
}

void PostOrder(const struct TreeNode *t)
{
    if (t == NULL) {
        return;
    }
    PostOrder(t->left);
    PostOrder(t->right);
    printf("%d ", t->val);
}

void PrintOnePath(struct Stack *s)
{
    struct StackNode *sn = NULL;
    struct Stack temp;

    InitStack(&temp);
    sn = s->top;
    while (sn != NULL) {
        Push(&temp, sn->val);
        sn = sn->next;
    }
    printf("Path: ");
    while (temp.len > 0) {
        printf("%d ", Pop(&temp));
    }
    printf("\n");
}

static struct Stack g_s;
void PrintAllPath(struct TreeNode *t)
{
    if (t == NULL) {
        return;
    }
    Push(&g_s, t->val);
    if (t->left == NULL && t->right == NULL) {
        PrintOnePath(&g_s);
        Pop(&g_s);
    } else {
        PrintAllPath(t->left);
        PrintAllPath(t->right);
        Pop(&g_s);
    }
}

/* 二叉树的层次遍历 */
void LevelOrder(struct TreeNode *t)
{
    struct Queue q;
    struct TreeNode *tn = NULL;

    InitQueue(&q);
    EnQueue(&q, t);
    printf("level order: ");
    while (q.len > 0) {
        tn = DeQueue(&q);
        printf("%d ", tn->val);
        if (tn->left != NULL) {
            EnQueue(&q, tn->left);
        }
        if (tn->right != NULL) {
            EnQueue(&q, tn->right);
        }
    }
    printf("\n");
}

int main(void)
{
    int arr[] = {5, 4, 11, 7, -1, -1, 2, -1, -1, -1, 8, 13, -1, -1, 4, 5, -1,
                 -1, 1, -1, -1};
    int size = sizeof(arr) / sizeof(arr[0]);
    struct TreeNode *t = NULL;

    t = CreateTreeByArray((int *)arr, size);
    printf("pre order: ");
    PreOrder(t);
    printf("\n");
    printf("in order: ");
    InOrder(t);
    printf("\n");
    printf("post order: ");
    PostOrder(t);
    printf("\n");

    printf("int max = %d\n", (int)((~0U) >> 1));
    printf("int max = %d\n", MAXINT);
    printf("int min = %d\n", (int)(1U << (8 * sizeof(int) - 1)));
    printf("int min = %d\n", MININT);
    printf("long max = %ld\n", (long)((~0UL) >> 1));
    printf("long min = %ld\n", (long)(1UL << (8 * sizeof(long) - 1)));

    InitStack(&g_s);
    PrintAllPath(t);

    LevelOrder(t);

    return 0;
}