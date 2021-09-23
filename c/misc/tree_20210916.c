/*
 * 练习：二叉树
 * 2021-09-16
 */
#include "common.h"

#define INT_MAX ((int)((~0U) >> 1))
#define INT_MIN ((int)(1U << 31))

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

void __PreOrder(const struct TreeNode *t)
{
    if (t == NULL) {
        return;
    }
    printf("%d ", t->val);
    __PreOrder(t->left);
    __PreOrder(t->right);
}

void PreOrder(const struct TreeNode *t)
{
    DebugLog("pre order: ");
    __PreOrder(t);
    printf("\n");
}

void __InOrder(const struct TreeNode *t)
{
    if (t == NULL) {
        return;
    }
    __InOrder(t->left);
    printf("%d ", t->val);
    __InOrder(t->right);
}

void InOrder(const struct TreeNode *t)
{
    DebugLog("in order: ");
    __InOrder(t);
    printf("\n");
}

void __PostOrder(const struct TreeNode *t)
{
    if (t == NULL) {
        return;
    }
    __PostOrder(t->left);
    __PostOrder(t->right);
    printf("%d ", t->val);
}

void PostOrder(const struct TreeNode *t)
{
    DebugLog("post order: ");
    __PostOrder(t);
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
        return NULL;
    } else {
        t = (struct TreeNode *)malloc(sizeof(struct TreeNode));
        t->val = arr[g_idx];
        g_idx++;
        t->left = CreateTreeByArray(arr, size);
        t->right = CreateTreeByArray(arr, size);
        return t;
    }
}

void PrintTreePath(int *path, int len)
{
    int i;
    DebugLog("path: ");
    for (i = 0; i < len; i++) {
        printf("%d ", path[i]);
    }
    printf("\n");
}

int g_num[10];
void Dfs(struct TreeNode *t, int depth)
{
    if (t == NULL) {
        return;
    }
    g_num[depth] = t->val;
    if (t->left == NULL && t->right == NULL) {
        PrintTreePath(g_num, depth + 1);
    } else {
        Dfs(t->left, depth + 1);
        Dfs(t->right, depth + 1);
    }
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

#define MAX_NODE 100
struct TreeNode *g_queue[MAX_NODE] = {NULL};
int g_head = 0;
int g_tail = 0;

int QueueEmpty(void)
{
    return (g_head == g_tail);
}

int QueueFull(void)
{
    return ((g_tail + 1) % MAX_NODE == g_head);
}

void EnQueue(struct TreeNode *t)
{
    if (t == NULL || QueueFull()) {
        return;
    }
    g_queue[g_tail] = t;
    g_tail = (g_tail + 1) % MAX_NODE;
}

struct TreeNode *DeQueue(void)
{
    struct TreeNode *head = NULL;
    if (QueueEmpty()) {
        return NULL;
    }
    head = g_queue[g_head];
    g_head = (g_head + 1) % MAX_NODE;
    return head;
}

void Bfs(struct TreeNode *t)
{
    struct TreeNode *tmp = NULL;
    if (t == NULL) {
        return;
    }
    EnQueue(t);
    DebugLog("bfs: ");
    while (!QueueEmpty()) {
        tmp = DeQueue();
        printf("%d ",  tmp->val);
        if (tmp->left != NULL) {
            EnQueue(tmp->left);
        }
        if (tmp->right != NULL) {
            EnQueue(tmp->right);
        }
    }
    printf("\n");
}

int main(void)
{
    int arr[] = {5, 4, 11, 7, -1, -1, 2, -1, -1, -1, 8,
                 13, -1, -1, 4, 5, -1, -1, 1, -1, -1};
    int size = sizeof(arr) / sizeof(arr[0]);
    struct TreeNode *t = CreateTreeByArray(arr, size);

    DebugLog("INT_MAX = %d\n", INT_MAX);
    DebugLog("INT_MIN = %d\n", INT_MIN);

    DebugLog("tree depth: %d\n", TreeDepth(t));
    PreOrder(t);
    InOrder(t);
    PostOrder(t);

    Dfs(t, 0);

    Bfs(t);

    return 0;
}
