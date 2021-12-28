/*
 * leetcode 101: 对称二叉树 [简单]
 * 思路：将一棵树看成根节点相同的两颗树a、b，同时遍历两颗树时，先比较根节点，若相同，
 *       再依次递归比较a->left、b->right与a->left、b->right
 * 2021-12-27
 */
#include "common.h"
#include "tree.h"

/***** 提交代码 ****************************************************************/
bool isSame(struct TreeNode *a, struct TreeNode *b)
{
    if (a == NULL && b == NULL) {
        return true;
    } else if (a == NULL || b == NULL || a->val != b->val) {
        return false;
    } else if (!isSame(a->left, b->right) || !isSame(a->right, b->left)) {
        return false;
    } else {
        return true;
    }
}

bool isSymmetric(struct TreeNode* root)
{
    return isSame(root, root);
}

/***** 本地调试 ****************************************************************/
void TestCase1(void)
{
    /*
     *      1
     *    /   \
     *   2     2
     *  / \   / \
     * 3   4 4   3
     */
    int arr[] = {1, 2, 2, 3, 4, 4, 3};
    int size = ARRAY_SIZE(arr);
    struct TreeNode *t = NULL;
    CreateTreeByLevelArray(&t, arr, size, 0);
    Log("======= %s =======\n", __func__);
    PrintTreeInfo(t);
    Log("is symmetric: %d(1)\n", isSymmetric(t));
}

void TestCase2(void)
{
    /*
     *      1
     *    /   \
     *   2     2
     *    \     \
     *     3     3
     */
    int arr[] = {1, 2, 2, -1, 3, -1, 3};
    int size = ARRAY_SIZE(arr);
    struct TreeNode *t = NULL;
    CreateTreeByLevelArray(&t, arr, size, 0);
    Log("======= %s =======\n", __func__);
    PrintTreeInfo(t);
    Log("is symmetric: %d(0)\n", isSymmetric(t));
}

int main(void)
{
    TestCase1();
    TestCase2();
    return 0;
}