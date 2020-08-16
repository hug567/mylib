/*
 * leetcode 199: 二叉树右视图 [中等]
 * 技巧：二叉树的前序遍历，每一层的最后一个数最后访问到，覆盖前面同层的数
 * 2020-08-16
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

/* 提交代码：----------------------------------------------------------------- */
/* 二叉树深度 */
int TreeDepth(struct TreeNode *t)
{
    if (t == NULL) {
        return 0;
    }
    int ld = TreeDepth(t->left);
    int rd = TreeDepth(t->right);
    return (ld > rd ? ld : rd) + 1;
}

/* 二叉树前序遍历 */
void PreTraverse(struct TreeNode *t, int high, int *arr)
{
    if (t == NULL) {
        return;
    }
    arr[high] = t->val;
    PreTraverse(t->left, high + 1, arr);
    PreTraverse(t->right, high + 1, arr);
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* rightSideView(struct TreeNode* root, int* returnSize){
    int *arr = NULL;
    if (root == NULL) {
        *returnSize = 0;
        return NULL;
    }
    *returnSize = TreeDepth(root);
    arr = (int *)malloc(*returnSize * sizeof(int));
    PreTraverse(root, 0, arr);
    return arr;
}

/* 本地调试：----------------------------------------------------------------- */
static int g_idx = 0;
struct TreeNode *CreateTreeByArray(int *arr, int size)
{
    struct TreeNode *tn = NULL;
    if (g_idx >= size) {
        return NULL;
    } else if (arr[g_idx] < 0) {
        g_idx++;
    } else {
        tn = (struct TreeNode *)malloc(sizeof(struct TreeNode));
        tn->val = arr[g_idx];
        g_idx++;
        tn->left = CreateTreeByArray(arr, size);
        tn->right = CreateTreeByArray(arr, size);
    }
    return tn;
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

int main(void)
{
    int i;
    int returnSize;
    int *right_arr = NULL;
    int arr[] = {1, 2, -1, 5, -1, -1, 3, -1, 4, -1, -1};
    struct TreeNode *t = CreateTreeByArray(arr, sizeof(arr) / sizeof(arr[0]));

    printf("tree pre order: ");
    PreOrder(t);
    printf("\n");
    printf("tree depth = %d\n", TreeDepth(t));

    right_arr = rightSideView(t, &returnSize);
    printf("tree right view: ");
    for (i = 0; i < returnSize; i++) {
        printf("%d ", right_arr[i]);
    }
    printf("\n");

    return 0;
}
