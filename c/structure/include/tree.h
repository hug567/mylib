/*
 * 练习：树头文件
 * 创建：2020-04-09
 */

#ifndef __TREE_H__
#define __TREE_H__

/* 二叉树节点 */
struct BTNode {
	char data;
	struct BTNode *left;
	struct BTNode *right;
};

void CreateTree(struct BTNode **tree);
struct BTNode *CreateTreeByArray(char *buf);
void PreOrder(struct BTNode *tree);
void InOrder(struct BTNode *tree);
void PostOrder(struct BTNode *tree);

#endif /* __TREE_H__ */
