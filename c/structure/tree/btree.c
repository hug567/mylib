/*
 * 练习：二叉树
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

/* 测试用例：
AB##C##
ABD##E##C##
*/
int main()
{
	struct BTNode *tree = (struct BTNode *)malloc(sizeof(struct BTNode));

	printf("input tree: ");
	CreateTree(&tree);
	printf("pre order: ");
	PreOrder(tree);
	printf("\nin order: ");
	InOrder(tree);
	printf("\npost order: ");
	PostOrder(tree);
	printf("\n");

	return 0;
}
