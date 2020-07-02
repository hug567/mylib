/* 二叉树 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tree.h>

/*
 * example: AB##C##
 */
void CreateTree(struct BTNode **tree)
{
	char ch;
	scanf("%c", &ch);
	if (ch == '#') {
		*tree = NULL;
		return;
	} else {
		*tree = (struct BTNode *)malloc(sizeof(struct BTNode));
		(*tree)->data = ch;
		CreateTree(&((*tree)->left));
		CreateTree(&((*tree)->right));
	}
}

/*
 * 根据数组创建树
 * 对于节点i：(从1开始)
 *     父节点：i / 2
 *     左孩子：2 * i
 *     右孩子：2 * i + 1
 * 结束字符：#
 * 例：abc####
 *  a
 * / \
 * b c
 */
struct BTNode *CreateTreeByArray(char *buf, int index)
{
	struct BTNode *tree = NULL;
	if (buf[index] == '#') {
		tree = NULL;
	} else {
		tree = (struct BTNode *)malloc(sizeof(struct BTNode));
		tree->data = buf[index];
		tree->left = CreateTreeByArray(buf, index + 1);
		tree->right = CreateTreeByArray(buf, index + 2);
	}

	return tree;
}

void PreOrder(struct BTNode *tree)
{
	if (tree == NULL) {
		return;
	}
	printf("%c", tree->data);
	PreOrder(tree->left);
	PreOrder(tree->right);
}

void InOrder(struct BTNode *tree)
{
	if (tree == NULL) {
		return;
	}
	InOrder(tree->left);
	printf("%c", tree->data);
	InOrder(tree->right);
}

void PostOrder(struct BTNode *tree)
{
	if (tree == NULL) {
		return;
	}
	PostOrder(tree->left);
	PostOrder(tree->right);
	printf("%c", tree->data);
}
