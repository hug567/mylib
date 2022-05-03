/*
 * leetcode 146: LRU缓存 [中等]
 * 思路：双向链表
 * 结果：超时，需使用哈希表优化
 * 2022-05-02
 */
#include "common.h"

/***** 提交代码 ******************************************************************/
struct MyListNode {
    struct MyListNode *next;
    struct MyListNode *pre;
};

void ListNodeInit(struct MyListNode *node)
{
    if (node == NULL) {
        return;
    }
    node->next = node;
    node->pre = node;
}

void ListNodeDelete(struct MyListNode *node)
{
    struct MyListNode *pre = NULL, *next = NULL;

    if (node == NULL) {
        return;
    }
    pre = node->pre;
    next = node->next;
    pre->next = next;
    next->pre = pre;
}

void ListAdd(struct MyListNode *pre, struct MyListNode *new)
{
    struct MyListNode *next = NULL;

    if (pre == NULL || new == NULL) {
        Log("pre or new is NULL\n");
        return;
    }
    next = pre->next;
    pre->next = new;
    new->pre = pre;
    new->next = next;
    next->pre = new;
}

void ListAddHead(struct MyListNode *head, struct MyListNode *new)
{
    if (head == NULL || new == NULL) {
        Log("head or new is NULL\n");
        return;
    }
    ListAdd(head, new);
}

#define container_of(ptr, type, member) (type *)((uintptr_t)(ptr) - (uintptr_t)(&((type *)0)->member))
#define ListEntry(ptr, type, member) container_of(ptr, type, member)
#define ListFirstEntry(head, type, member) ListEntry((head)->next, type, member)
#define ListNextEntry(pos, type, member) ListEntry((pos)->member.next, type, member)
#define ListForEachEntry(pos, head, type, member) \
        for (pos = ListFirstEntry(head, type, member); \
             &(pos)->member != head; \
             pos = ListNextEntry(pos, type, member))
#define ListForEachEntrySafe(pos, next, head, type, member) \
        for (pos = ListFirstEntry(head, type, member); \
             &(pos)->member != head && (next = ListNextEntry(pos, type, member), true); \
             pos = next)

typedef struct {
    int key;
    int value;
    struct MyListNode node;
} Cache;

typedef struct {
    int count;
    int capacity;
    struct MyListNode cache_head;
} LRUCache;


LRUCache* lRUCacheCreate(int capacity) {
    LRUCache *l = malloc(sizeof(LRUCache));
    l->count = 0;
    l->capacity = capacity;
    ListNodeInit(&l->cache_head);
    return l;
}

int lRUCacheGet(LRUCache* obj, int key) {
    Cache *c = NULL;

    ListForEachEntry(c, &obj->cache_head, Cache, node) {
        if (c->key == key) {
            ListNodeDelete(&c->node);
            ListAddHead(&obj->cache_head, &c->node);
            return c->value;
        }
    }
    return -1;
}

Cache *CreateCache(int key, int value)
{
    Cache *c = malloc(sizeof(Cache));
    c->key = key;
    c->value = value;
    return c;
}

void lRUCachePut(LRUCache* obj, int key, int value) {
    Cache *c = NULL, *old = NULL, *tmp = NULL;

    ListForEachEntry(tmp, &obj->cache_head, Cache, node) {
        if (tmp->key == key) {
            c = tmp;
            ListNodeDelete(&c->node);
            break;
        }
    }
    if (c != NULL) {
        c->value = value;
        ListNodeDelete(&c->node);
    } else {
        c = CreateCache(key, value);
        if (obj->count >= obj->capacity) {
            old = ListEntry(obj->cache_head.pre, Cache, node);
            ListNodeDelete(&old->node);
            free(old);
        } else {
            obj->count++;
        }
    }
    ListAddHead(&obj->cache_head, &c->node);
}

void lRUCacheFree(LRUCache* obj) {
    Cache *pos = NULL, *next = NULL;

    ListForEachEntrySafe(pos, next, &obj->cache_head, Cache, node) {
        ListNodeDelete(&pos->node);
        free(pos);
    }
    free(obj);
}

/***** 本地调试 ******************************************************************/
void PrintAllCache(LRUCache *l)
{
    Cache *c = NULL;

    ListForEachEntry(c, &l->cache_head, Cache, node) {
        Log("key: %d, value: %d\n", c->key, c->value);
    }
}

void TestCase1(void)
{
    int capacity = 2;
    LRUCache *l = lRUCacheCreate(capacity);
    lRUCachePut(l, 1, 1);
    lRUCachePut(l, 2, 2);
    PrintAllCache(l);
    Log("value: %d(1)\n", lRUCacheGet(l, 1));
    lRUCachePut(l, 3, 3);
    Log("value: %d(-1)\n", lRUCacheGet(l, 2));
    lRUCachePut(l, 4, 4);
    Log("value: %d(-1)\n", lRUCacheGet(l, 1));
    Log("value: %d(3)\n", lRUCacheGet(l, 3));
    Log("value: %d(4)\n", lRUCacheGet(l, 4));
    lRUCacheFree(l);
}

int main(void)
{
    TestCase1();
    return 0;
}