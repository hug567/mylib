/*
 * 练习：二叉树
 * 2021-09-16
 */
#include "common.h"

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

int main(void)
{
    int arr[] = {5, 4, 11, 7, -1, -1, 2, -1, -1, -1, 8,
                 13, -1, -1, 4, 5, -1, -1, 1, -1, -1};
    int size = sizeof(arr) / sizeof(arr[0]);
    struct TreeNode *t = CreateTreeByArray(arr, size);

    PreOrder(t);
    InOrder(t);
    PostOrder(t);

    return 0;
}
