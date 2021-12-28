/*
 * leetcode 110: 平衡二叉树 [简单]
 * 平衡二叉树：任意节点的左右子树的高度相差不超过1
 * 2021-12-28
 */
#include "common.h"
#include "tree.h"

/***** 提交代码 ****************************************************************/
int Abs(int a, int b)
{
    if (a > b) {
        return a - b;
    } else {
        return b - a;
    }
}

int TreeDepth(struct TreeNode *t)
{
    if (t == NULL) {
        return 0;
    }
    int l = TreeDepth(t->left);
    int r = TreeDepth(t->right);
    return (l > r ? l : r) + 1;
}

bool isBalanced(struct TreeNode* root)
{
    if (root == NULL) {
        return true;
    }
    if (Abs(TreeDepth(root->left), TreeDepth(root->right)) > 1) {
        return false;
    }
    if (!isBalanced(root->left) || !isBalanced(root->right)) {
        return false;
    }
    return true;
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
    Log("======= %s =======\n", __func__);
    PrintTreeInfo(t);
    Log("is symmetric: %d(1)\n", isBalanced(t));
}

void TestCase2(void)
{
    /*
     *       1
     *      / \
     *     2   2
     *    / \
     *   3   3
     *  / \
     * 4   4
     */
    int arr[] = {1, 2, 2, 3, 3, -1, -1, 4, 4};
    int size = ARRAY_SIZE(arr);
    struct TreeNode *t = NULL;
    CreateTreeByLevelArray(&t, arr, size, 0);
    Log("======= %s =======\n", __func__);
    PrintTreeInfo(t);
    Log("is symmetric: %d(0)\n", isBalanced(t));
}


void TestCase3(void)
{
    struct TreeNode *t = NULL;
    CreateTreeByLevelArray(&t, NULL, 0, 0);
    Log("======= %s =======\n", __func__);
    PrintTreeInfo(t);
    Log("is symmetric: %d(1)\n", isBalanced(t));
}

int main(void)
{
    TestCase1();
    TestCase2();
    TestCase3();
    return 0;
}
