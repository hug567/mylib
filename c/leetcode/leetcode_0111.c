/*
 * leetcode 111: 二叉树的最小深度 [简单]
 * Dfs: 深度优先搜索遍历二叉树，当遍历到叶子节点时，计算当前叶子节点深度，与上一个叶子
 *      节点深度比较，记录较小的深度值
 * 2021-01-04
 */
#include "common.h"
#include "tree.h"

/***** 提交代码 ****************************************************************/
#define INT_MAX ((int)((~0U) >> 1))

int g_min = INT_MAX;
void Dfs(struct TreeNode *t, int depth)
{
    if (t == NULL) {
        return;
    } else if (t->left == NULL && t->right == NULL) {
        g_min = g_min < depth + 1 ? g_min : depth + 1;
    } else {
        Dfs(t->left, depth + 1);
        Dfs(t->right, depth + 1);
    }
}

int minDepth(struct TreeNode* root)
{
    if (root == NULL) {
        return 0;
    }
    g_min = INT_MAX;
    Dfs(root, 0);
    return g_min;
}

/***** 本地调试 ****************************************************************/
void TestCase1(void)
{
    /*
     *   3
     *  / \
     * 9  20
     *    / \
     *   15  7
     */
    int arr[] = {3, 9, 20, -1, -1, 15, 7};
    int size = ARRAY_SIZE(arr);
    struct TreeNode *t = NULL;
    CreateTreeByLevelArray(&t, arr, size, 0);
    PrintTreeInfo(t);
    Log("min depth: %d(2)\n", minDepth(t));
}

void TestCase2(void)
{
    /*
     * 2
     *  \
     *   3
     *    \
     *     4
     *      \
     *       5
     *        \
     *         6
     */
    int arr[] = {2, -1, 3, -1, -1, -1, 4, -1, -1, -1, -1, -1, -1, -1, 5,
                 -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 6};
    int size = ARRAY_SIZE(arr);
    struct TreeNode *t = NULL;
    CreateTreeByLevelArray(&t, arr, size, 0);
    PrintTreeInfo(t);
    Log("min depth: %d(5)\n", minDepth(t));
}

int main(void)
{
    TestCase1();
    TestCase2();
    return 0;
}
