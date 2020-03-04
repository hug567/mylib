/*
 * 题目：leetcode 14: 最长公共前缀
 * 难度：简单
 * 时间：2020-03-04
 * */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHAR_NUM 26

struct _node {
	char ch;
	int count;
	struct _node *next[CHAR_NUM];
};

void insert_word(struct _node *root, char *str)
{
	int i;

	if (root == NULL || str == NULL) {
		return;
	}

	struct _node *node = root;
	struct _node *tmp = NULL;
	while (*str != '\0') {
		if (node->next[*str - 'a'] == NULL) {
			tmp = (struct _node *)malloc(sizeof(struct _node));
			tmp->ch = *str;
			tmp->count = 1;
			for (i = 0; i < CHAR_NUM; i++) {
				tmp->next[i] = NULL;
			}
			node->next[*str - 'a'] = tmp;
			node = tmp;
		} else {
			node = node->next[*str - 'a'];
			node->count++;
		}
		str++;
	}
}

int next_count(struct _node *node, int *pos)
{
	int i;
	int flag = 0;
	int count = 0;

	*pos = -1;
	if (node == NULL) {
		return 0;
	}
	for (i = 0; i < CHAR_NUM; i++) {
		if (node->next[i] != NULL) {
			count++;
			if (flag == 0) {
				*pos = i;
				flag++;
			}
		}
	}
	return count;
}

char *get_common(struct _node *root, char *str)
{
	int idx = 0;
	int pos;
	char *com_str = (char *)malloc(strlen(str) + 1);

	memset(com_str, '\0', strlen(str) + 1);
	if (next_count(root, &pos) != 1) {
		return "";
	}

	struct _node *node = root;
	while (*str != '\0') {
		if (next_count(node, &pos) != 1) {
			break;
		}
		node = node->next[pos];
		if (node->count <= 1) {
			break;
		}
		com_str[idx] = node->ch;
		idx++;
		str++;
	}
	return com_str;
}

char * longestCommonPrefix(char ** strs, int strsSize){
	int i;
	struct _node *root = (struct _node *)malloc(sizeof(struct _node));

	if (strsSize < 1) {
		return "";
	} else if (strsSize == 1) {
		return strs[0];
	}
	/* 根节点初始化 */
	root->ch = 0;
	root->count = 0;
	for (i = 0; i < CHAR_NUM; i++) {
		root->next[i] = NULL;
	}

	int idx = 0;
	int len = strlen(strs[0]);
	for (i = 0; i < strsSize; i++) {
		if (strs[i][0] == '\0') {
			return "";
		}
		if (len > strlen(strs[i])) {
			len = strlen(strs[i]);
			idx = i;
		}
		insert_word(root, strs[i]);
	}

	return get_common(root, strs[idx]);
}

int main()
{
	int strsSize = 3;
	char *strs[] = {"flower", "flow", "flight"};

	printf("common prefix: %s\n", longestCommonPrefix(strs, strsSize));
	return 0;
}
