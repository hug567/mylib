/*
 * leetcode 99: 恢复二叉搜索树 [中等]
 * 二叉搜索树：中序遍历为递增序列
 * 1、中序遍历二叉树，将节点值存储在数组中，则交换数组中两个元素的值，可使其恢复递增序列；
 * 2、对于非递增的点，有a(i) > a(i+1), 遍历整个数组，找到不符合递增序列的点；
 * 3、不满足递增序列的点一个有以下几种情况:
 *    1）、无不符合递增的点，则不需要更新二叉树；
 *    2）、只有一个不符合递增的点，则需要交换a(i)与a(i+1)两个值；
 *    3）、有两个不符合递增的点i和j，则需要交换a(i)和a(j+1)两个值；
 * 4、再遍历一遍二叉树，交换两个需要交换的节点；
 * 2021-12-25
 */
#include "common.h"
#include "tree.h"

/***** 本地调试 ****************************************************************/
#define MAX_NODE 1000

int g_index = 0;
void InOrder(struct TreeNode *t, int *arr)
{
    if (t == NULL) {
        return;
    }
    InOrder(t->left, arr);
    arr[g_index] = t->val;
    g_index++;
    InOrder(t->right, arr);
}

void UpdateTree(struct TreeNode *t, int x, int y)
{
    if (t == NULL) {
        return;
    }
    if (t->val == x) {
        t->val = y;
    } else if (t->val == y) {
        t->val = x;
    }
    UpdateTree(t->left, x, y);
    UpdateTree(t->right, x, y);
}

void recoverTree(struct TreeNode* root)
{
    int i, x, y, size;
    int num = 0;
    int arr[MAX_NODE] = {0};

    g_index = 0;
    InOrder(root, arr);
    size = g_index;
    for (i = 0; i < size - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            if (num == 0) { /* 只有一个不满足递增的点 */
                num++;
                x = arr[i];
                y = arr[i + 1];
            } else if (num == 1) { /* 有2个不满足递增的点 */
                num++;
                y = arr[i + 1];
                break;
            }
        }
    }
    if (num > 0) { /* 有不满足递增的点，需更新二叉树 */
        UpdateTree(root, x, y);
    }
}

/***** 本地调试 ****************************************************************/

void TestCase1(void)
{
    int arr[] = {1, 3, -1, -1, 2};
    int size = ARRAY_SIZE(arr);
    struct TreeNode *t = NULL;
    CreateTreeByLevelArray(&t, arr, size, 0);
    Log("======= %s =======\n", __func__);
    PrintTreeInfo(t);
    recoverTree(t);
    PrintTreeInfo(t);
}

void TestCase2(void)
{
    int arr[] = {3, 1, 4, -1, -1, 2};
    int size = ARRAY_SIZE(arr);
    struct TreeNode *t = NULL;
    CreateTreeByLevelArray(&t, arr, size, 0);
    Log("======= %s =======\n", __func__);
    PrintTreeInfo(t);
    recoverTree(t);
    PrintTreeInfo(t);
}

int main(void)
{
    TestCase1();
    TestCase2();
    return 0;
}
