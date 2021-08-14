/*
 * 二叉树练习
 * 创建
 * 遍历：前序、中序、后序、层次
 * 深度
 * DFS：路径
 * BFS
 * 2021-08-01
 */
#include "common.h"

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

int g_idx = 0;
struct TreeNode *CreateTreeByArray(const int *arr, int size)
{
    struct TreeNode *tree = NULL;

    if (g_idx >= size) {
        return NULL;
    } else if (arr[g_idx] == -1) {
        g_idx++;
        return NULL;
    } else {
        tree = (struct TreeNode *)malloc(sizeof(struct TreeNode));
        tree->val = arr[g_idx];
        g_idx++;
        tree->left = CreateTreeByArray(arr, size);
        tree->right = CreateTreeByArray(arr, size);
    }
    return tree;
}

void __PreOrder(const struct TreeNode *tree)
{
    if (tree == NULL) {
        return;
    }
    printf("%d ", tree->val);
    __PreOrder(tree->left);
    __PreOrder(tree->right);
}

void PreOrder(const struct TreeNode *tree)
{
    DebugLog("pre order: ");
    __PreOrder(tree);
    printf("\n");
}

void __InOrder(const struct TreeNode *tree)
{
    if (tree == NULL) {
        return;
    }
    __InOrder(tree->left);
    printf("%d ", tree->val);
    __InOrder(tree->right);
}

void InOrder(const struct TreeNode *tree)
{
    DebugLog("in order: ");
    __InOrder(tree);
    printf("\n");
}

void __PostOrder(const struct TreeNode *tree)
{
    if (tree == NULL) {
        return;
    }
    __PostOrder(tree->left);
    __PostOrder(tree->right);
    printf("%d ", tree->val);
}

void PostOrder(const struct TreeNode *tree)
{
    DebugLog("post order: ");
    __PostOrder(tree);
    printf("\n");
}

int TreeDepth(const struct TreeNode *tree)
{
    if (tree == NULL) {
        return 0;
    }
    int ld = TreeDepth(tree->left);
    int rd = TreeDepth(tree->right);
    return (ld > rd ? ld : rd) + 1;
}

int main(void)
{
    struct TreeNode *tree = NULL;
    /*
     * tree:
     *         5
     *        /  \
     *       4    8
     *      /    /  \
     *     11   13   4
     *    /  \      / \
     *   7    2    5   1
     *
     * pre:  5 4 11 7 2 8 13 4 5 1
     * in:   7 11 2 4 5 13 8 5 4 1
     * post: 7 2 11 4 13 5 1 4 8 5
     * depth: 4
     */
    int arr[] = {5, 4, 11, 7, -1, -1, 2, -1, -1, -1, 8,
                 13, -1, -1, 4, 5, -1, -1, 1, -1, -1};
    int size = ARRAY_SIZE(arr);

    tree = CreateTreeByArray(arr, size);
    PreOrder(tree);
    InOrder(tree);
    PostOrder(tree);
    DebugLog("tree depth: %d\n", TreeDepth(tree));

    return 0;
}
