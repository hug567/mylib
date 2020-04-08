/* 二叉树 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

/*
 * example: AB##C##
 */
void CreateTree(BTNode **tree)
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

void pre_order(btnode *tree)
{
	if (tree == NULL) {
		return;
	}
	printf("%c", tree->data);
	pre_order(tree->lchild);
	pre_order(tree->rchild);
}

void in_order(btnode *tree)
{
	if (tree == NULL) {
		return;
	}
	pre_order(tree->lchild);
	printf("%c", tree->data);
	pre_order(tree->rchild);
}

void post_order(btnode *tree)
{
	if (tree == NULL) {
		return;
	}
	pre_order(tree->lchild);
	pre_order(tree->rchild);
	printf("%c", tree->data);
}

int main()
{
/* 测试用例：
AB##C##
ABD##E##C##
 */
	btnode *tree = (btnode *)malloc(sizeof(btnode));

	printf("input tree: ");
	create_tree(&tree);
	printf("pre order: ");
	pre_order(tree);
	printf("\nin order: ");
	in_order(tree);
	printf("\npost order: ");
	post_order(tree);
	printf("\n");

	return 0;
}
