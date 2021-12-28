/*
 * leetcode二叉树相关题目头文件
 * 2021-12-26
 */
#ifndef __TREE_H__
#define __TREE_H__

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

/*
 * 根据树的前序遍历数组创建二叉树
 */
int __g_index = 0;
struct TreeNode *CreateTreeByPreArray(int *arr, int size)
{
    struct TreeNode *t = NULL;
    if (__g_index >= size) {
        return NULL;
    } else if (arr[__g_index] == -1) {
        __g_index++;
        return NULL;
    } else {
        t = malloc(sizeof(struct TreeNode));
        t->val = arr[__g_index];
        __g_index++;
        t->left = CreateTreeByPreArray(arr, size);
        t->right = CreateTreeByPreArray(arr, size);
        return t;
    }
}

/*
 * 根据二叉树的层次遍历数组创建二叉树
 * 父节点：i
 * 左子节点：2*i+1
 * 右子节点：2*i+2
 */
void CreateTreeByLevelArray(struct TreeNode **t, int *arr, int size, int i)
{
    if (i >= size || arr[i] == -1) {
        *t = NULL;
        return;
    }
    *t = malloc(sizeof(struct TreeNode));
    (*t)->val = arr[i];
    CreateTreeByLevelArray(&((*t)->left), arr, size, 2 * i + 1);
    CreateTreeByLevelArray(&((*t)->right), arr, size, 2 * i + 2);
}

/*
 * 二叉树的深度
 */
int __TreeDepth(struct TreeNode *t)
{
    if (t == NULL) {
        return 0;
    }
    int l = __TreeDepth(t->left);
    int r = __TreeDepth(t->right);
    return (l > r ? l : r) + 1;
}

/*
 * 二叉树的前序遍历
 */
void __PreOrder(struct TreeNode *t)
{
    if (t == NULL) {
        return;
    }
    printf("%d ", t->val);
    __PreOrder(t->left);
    __PreOrder(t->right);
}


/*
 * 二叉树的中序遍历
 */
void __InOrder(struct TreeNode *t)
{
    if (t == NULL) {
        return;
    }
    __InOrder(t->left);
    printf("%d ", t->val);
    __InOrder(t->right);
}

/*
 * 二叉树的后序遍历
 */
void __PostOrder(struct TreeNode *t)
{
    if (t == NULL) {
        return;
    }
    __PostOrder(t->left);
    __PostOrder(t->right);
    printf("%d ", t->val);
}
/*
 * 二叉树的层次遍历
 */
#define MAX_QUEUE_SIZE 1000
void __LevelOrder(struct TreeNode *root)
{
    int head = 0, tail = 0;
    struct TreeNode *t = NULL;
    struct TreeNode *queue[MAX_QUEUE_SIZE] = {NULL}; /* 节点队列 */

    Log("level order: ");
    if (root == NULL) {
        printf("\n");
        return;
    }
    queue[tail] = root;
    tail++;
    while (head != tail) {
        /* 出队 */
        t = queue[head];
        head++;
        head %= MAX_QUEUE_SIZE;
        printf("%d ", t->val);
        if (t->left != NULL) {
            /* 入队 */
            queue[tail] = t->left;
            tail++;
            tail %= MAX_QUEUE_SIZE;
        }
        if (t->right != NULL) {
            /* 入队 */
            queue[tail] = t->right;
            tail++;
            tail %= MAX_QUEUE_SIZE;
        }
    }
    printf("\n");
}

/*
 * 打印二叉树信息
 */
void PrintTreeInfo(struct TreeNode *t)
{
    Log("----- tree info -----\n");
    Log("tree depth: %d\n", __TreeDepth(t));
    Log("pre order: ");
    __PreOrder(t);
    printf("\n");
    Log("in order: ");
    __InOrder(t);
    printf("\n");
    Log("post order: ");
    __PostOrder(t);
    printf("\n");
    __LevelOrder(t);
}

#endif