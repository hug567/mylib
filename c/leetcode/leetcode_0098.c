/*
 * leetcode 98：验证二叉搜索树 [中等]
 * 方法：二叉搜索树的中序遍历为升序或降序
 * 2021-12-08
 */
#include "common.h"

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

/***** 提交代码 ****************************************************************/
#define INT_MIN (int)(1U<<31)
#define MAX_SIZE 1000
static struct TreeNode *g_queue[MAX_SIZE] = {NULL};
static int g_head = 0;
static int g_end = 0;

int QueueIsEmpty(void)
{
    return g_head == g_end;
}

void EnQueue(struct TreeNode *t)
{
    if (t == NULL) {
        return;
    }
    g_queue[g_end] = t;
    g_end++;
    g_end %= MAX_SIZE;
}

struct TreeNode *DeQueue(void)
{
    struct TreeNode *t = NULL;
    if (QueueIsEmpty()) {
        return NULL;
    }
    t = g_queue[g_head];
    g_head++;
    g_head %= MAX_SIZE;
    return t;
}

int g_pre = INT_MIN;
int g_count = 0;
bool inOrder(struct TreeNode* t)
{
    if (t == NULL) {
        return true;
    }
    if (!inOrder(t->left)) {
        return false;
    }
    g_count++;
    if (t->val <= g_pre && g_count > 1) {
        return false;
    }
    g_pre = t->val;
    if (!inOrder(t->right)) {
        return false;
    }
    return true;
}

bool isValidBST(struct TreeNode* root)
{
    g_pre = INT_MIN;
    g_count = 0;
    return inOrder(root);
}

/***** 本地调试 ****************************************************************/

static int g_index = 0;
struct TreeNode *CreateTreeByArray(int *arr, int size)
{
    struct TreeNode *t = NULL;
    if (g_index >= size) {
        return NULL;
    } else if (arr[g_index] == -1) {
        g_index++;
        return NULL;
    } else {
        t = malloc(sizeof(struct TreeNode));
        t->val = arr[g_index];
        g_index++;
        t->left = CreateTreeByArray(arr, size);
        t->right = CreateTreeByArray(arr, size);
        return t;
    }
}

/* 层次遍历 */
void LevelOrder(struct TreeNode *t)
{
    struct TreeNode *node = NULL;
    if (t == NULL) {
        return;
    }
    g_head = 0;
    g_end = 0;
    EnQueue(t);
    DebugLog("level order: ");
    while (!QueueIsEmpty()) {
        node = DeQueue();
        printf("%d ", node->val);
        if (node->left != NULL) {
            EnQueue(node->left);
        }
        if (node->right != NULL) {
            EnQueue(node->right);
        }
    }
    printf("\n");
}

/* 中序遍历 */
void InOrderRecursion(struct TreeNode *t)
{
    if (t == NULL) {
        return;
    }
    InOrderRecursion(t->left);
    printf("%d ", t->val);
    InOrderRecursion(t->right);
}

void InOrder(struct TreeNode *t)
{
    DebugLog("in order: ");
    InOrderRecursion(t);
    printf("\n");
}

int main(void)
{
    DebugLog("int min = %d\n", (int)(1U<<31));
    DebugLog("int max = %d\n", (int)(~0U>>1));

    int arr[] = {2, 1, -1, -1, 3, -1, -1};
    int size = sizeof(arr) / sizeof(arr[0]);
    g_index = 0;
    struct TreeNode *t = CreateTreeByArray(arr, size);
    LevelOrder(t);
    InOrder(t);
    DebugLog("isValidBST: %d(1)\n", isValidBST(t));

    int arr2[] = {5, 4, -1, -1, 6, 3, -1, -1, 7, -1, -1};
    int size2 = sizeof(arr2) / sizeof(arr2[0]);
    g_index = 0;
    struct TreeNode *t2 = CreateTreeByArray(arr2, size2);
    LevelOrder(t2);
    InOrder(t2);
    DebugLog("isValidBST: %d(0)\n", isValidBST(t2));

    int arr3[] = {-2147483648, -1, -1};
    int size3 = sizeof(arr3) / sizeof(arr3[0]);
    g_index = 0;
    struct TreeNode *t3 = CreateTreeByArray(arr3, size3);
    LevelOrder(t3);
    InOrder(t3);
    DebugLog("isValidBST: %d(1)\n", isValidBST(t3));

    int arr4[] = {2147483647, -2147483648, -1, -1, -1};
    int size4 = sizeof(arr4) / sizeof(arr4[0]);
    g_index = 0;
    struct TreeNode *t4 = CreateTreeByArray(arr4, size4);
    LevelOrder(t4);
    InOrder(t4);
    DebugLog("isValidBST: %d(1)\n", isValidBST(t4));

    return 0;
}
