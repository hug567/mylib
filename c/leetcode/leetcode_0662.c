/*
 * 题目：leetcode 662: 二叉树最大宽度
 * 难度：中等
 * 技巧：bfs
 * 时间：2020-03-09
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

void create_tree(struct TreeNode **tree, int *nums, int len, int idx)
{
	if (idx >= len || nums[idx] == -1) {
		return;
	}

	*tree = (struct TreeNode *)malloc(sizeof(struct TreeNode));
	(*tree)->val = nums[idx];
	(*tree)->left = NULL;
	(*tree)->right = NULL;
	create_tree(&((*tree)->left), nums, len, 2 * idx + 1);
	create_tree(&((*tree)->right), nums, len, 2 * idx + 2);
}

void pre_order(struct TreeNode *tree)
{
	if (tree == NULL) {
		return;
	}

	printf("%d ", tree->val);
	pre_order(tree->left);
	pre_order(tree->right);
}

/* LeetCode提交函数 */
int widthOfBinaryTree(struct TreeNode* root){
	if (root == NULL) {
		return 0;
	}
	return 0;
}

int main()
{
	int i;
	int nums[] = {1, 2, 3, -1, 5};
	int len = sizeof(nums) / sizeof(int);
	struct TreeNode *tree = NULL;

	create_tree(&tree, nums, len, 0);
	printf("pre order: ");
	pre_order(tree);
	printf("\n");

	printf("max width = %d\n", widthOfBinaryTree(tree));

	return 0;
}
