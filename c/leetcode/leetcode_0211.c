/*
 * leetcode 211: 添加与搜索单词 - 数据结构设计
 * 2022-05-13
 */
#include "common.h"
#if 0
/***** 提交代码 ******************************************************************/
struct TrieNode {
    struct TrieNode *child[26];
    bool isEnd;
};

typedef struct {
    struct TrieNode *root;
} WordDictionary;


WordDictionary* wordDictionaryCreate() {
    WordDictionary  *wd = malloc(sizeof(WordDictionary));
    memset(wd, 0, sizeof(WordDictionary));
    return wd;
}

void wordDictionaryAddWord(WordDictionary* obj, char * word) {
    struct TrieNode *new = NULL;
    struct TrieNode *parent = obj->root;

    while (*word != '\0') {
        new = malloc(sizeof(WordDictionary));
        memset(new, 0, sizeof(WordDictionary));
        if (*(word + 1) == '\0') {
            new->isEnd = true;
        } else {
            new->isEnd = false;
        }
        parent->child[*word - 'a'] = tmp;
        parent = new;
        word++;
    }
}

bool wordDictionarySearch(WordDictionary* obj, char *word)
{
    struct TrieNode *node = obj->root;

    while (*word != '\0') {
        if (*word == '.') {

        } else {
            if (node->child[*word - 'a'] == NULL) {
                return false;
            }
            node = node->child[*word - 'a'];
            word++;
        }
    }
    if (node != NULL && node->isEnd) {
        return true;
    }
    return false;
}

void trieFree(struct TrieNode *root)
{
    int i;

    if (root == NULL) {
        return;
    }
    for (i = 0; i < 26; i++) {
        trieFree(root->child[i]);
    }
    free(root);
}

void wordDictionaryFree(WordDictionary* obj) {
    trieFree(obj->root);
    free(obj);
}

/***** 本地调试 ******************************************************************/
void TestCase1(void)
{
}

int main(void)
{
    TestCase1();
    return 0;
}
#endif

int main(void)
{
    printf("Enter %s\n", __func__);
    return 0;
}