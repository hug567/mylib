/*
 * leetcode 208: 实现Trie (前缀树) [中等]
 * 2022-05-04
 */
#include "common.h"

/***** 提交代码 ******************************************************************/
struct TrieNode {
    struct TrieNode *child[26];
    int isEnd;
};

typedef struct Trie {
    struct Trie *child[26];
    int isEnd;
} Trie;


Trie* trieCreate() {
    Trie *t = malloc(sizeof(Trie));
    memset(t, 0, sizeof(Trie));
    t->isEnd = 0;
    return t;
}

void trieInsert(Trie* obj, char * word) {
    int idx;

    while (*word != '\0') {
        idx = *word - 'a';
        if (obj->child[idx] != NULL) {
            obj = obj->child[idx];
        } else {
            obj->child[idx] = malloc(sizeof(Trie));
            memset(obj->child[idx], 0, sizeof(Trie));
            obj = obj->child[idx];
            obj->isEnd = 0;
        }
        if (*(word + 1) == '\0') {
            obj->isEnd = 1;
            break;
        }
        word++;
    }
}

bool trieSearch(Trie* obj, char * word) {
    int idx;

    while (*word != '\0') {
        idx = *word - 'a';
        if (obj->child[idx] == NULL) {
            return false;
        }
        obj = obj->child[idx];
        if (*(word + 1) == '\0' && obj->isEnd == 1) {
            return true;
        }
        word++;
    }
    return false;
}

bool trieStartsWith(Trie* obj, char * prefix) {
    int idx;

    while (*prefix != '\0') {
        idx = *prefix - 'a';
        if (obj->child[idx] == NULL) {
            return false;
        }
        obj = obj->child[idx];
        if (*(prefix + 1) == '\0') {
            return true;
        }
        prefix++;
    }
    return false;
}

void trieFree(Trie* obj) {
    int i;

    if (obj == NULL) {
        return;
    }
    for (i = 0; i < 26; i++) {
        trieFree(obj->child[i]);
    }
    free(obj);
}

/***** 本地调试 ******************************************************************/
void TestCase1(void)
{
    Trie *t = trieCreate();
    trieInsert(t, "apple");
    Log("trie search: %d(1)\n", trieSearch(t, "apple"));
    Log("trie search: %d(0)\n", trieSearch(t, "app"));
    Log("trie search: %d(1)\n", trieStartsWith(t, "app"));
    trieInsert(t, "app");
    Log("trie search: %d(1)\n", trieSearch(t, "app"));
}

int main(void)
{
    TestCase1();
    return 0;
}