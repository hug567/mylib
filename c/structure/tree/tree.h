/*
 *
 * 练习：树头文件
 * 创建：2020-04-09
 */

#ifndef __TREE_H__
#define __TREE_H__

struct BTNode {
	char data;
	struct BTNode *left;
	struct BTNode *right;
};

#endif /* __TREE_H__ */
