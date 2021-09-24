/*
 * leetcode 94: 二叉树的中序遍历 [简单]
 * 2021-09-24
 */
#include "common.h"

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

/***** 提交代码 ****************************************************************/
#define MAX_SIZE 100

int g_pre_idx = 0;
void PreOrder(struct TreeNode *t, int *arr)
{
    if (t == NULL) {
        return;
    }
    PreOrder(t->left, arr);
    arr[g_pre_idx] = t->val;
    g_pre_idx++;
    PreOrder(t->right, arr);
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* inorderTraversal(struct TreeNode* root, int* returnSize){
    int *pre = NULL;

    pre = (int *)malloc(MAX_SIZE * sizeof(int));
    g_pre_idx = 0;
    PreOrder(root, pre);
    *returnSize = g_pre_idx;
    return pre;
}

/***** 本地调试 ****************************************************************/
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
    struct TreeNode *t = NULL;
    int arr[] = {5, 4, 11, 7, -1, -1, 2, -1, -1, -1, 8,
                 13, -1, -1, 4, 5, -1, -1, 1, -1, -1};
    int size = sizeof(arr) / sizeof(arr[0]);
    int *pre = NULL;
    int returnSize;

    t = CreateTreeByArray(arr, size);
    pre = inorderTraversal(t, &returnSize);
    PrintArray(pre, returnSize);

    return 0;
}
