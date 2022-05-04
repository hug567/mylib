/*
 * 带头结点的循环双链表
 * 2022-05-04
 */
#include "common.h"

/***** 代码实现 ******************************************************************/
struct list_node {
    struct list_node *pre;
    struct list_node *next;
};

void list_init(struct list_node *node)
{
    if (node == NULL) {
        return;
    }
    node->next = node;
    node->pre = node;
}

void list_add_tail(struct list_node *head, struct list_node *new)
{
    struct list_node *pre = NULL, *next = NULL;

    if (head == NULL || new == NULL) {
        return;
    }
    pre = head->pre;
    next = head;
    pre->next = new;
    new->pre = pre;
    new->next = next;
    next->pre = new;
}

void list_add_head(struct list_node *head, struct list_node *new)
{
    struct list_node *pre = NULL, *next = NULL;

    if (head == NULL || new == NULL) {
        return;
    }
    pre = head;
    next = head->next;
    pre->next = new;
    new->pre = pre;
    new->next = next;
    next->pre = new;
}

void list_delete(struct list_node *node)
{
    struct list_node *pre = NULL, *next = NULL;

    if (node == NULL) {
        return;
    }
    pre = node->pre;
    next = node->next;
    pre->next = next;
    next->pre = pre;
}

#define container_of(ptr, type, member) (type *)((uintptr_t)(ptr) - (uintptr_t)(&((type *)0)->member))
#define list_entry(ptr, type, member) container_of(ptr, type, member)
#define list_first_entry(head, type, member) list_entry((head)->next, type, member)
#define list_next_entry(pos, type, member) list_entry((pos)->member.next, type, member)
#define list_for_each_entry(pos, head, type, member) \
        for ((pos) = list_first_entry(head, type, member); \
             &(pos)->member != head; \
             pos = list_next_entry(pos, type, member))
#define list_for_each_entry_safe(pos, n, head, type, member) \
        for ((pos) = list_first_entry(head, type, member); \
             &(pos)->member != head && (n = list_next_entry(pos, type, member), true); \
             pos = n)

/***** 功能测试 ******************************************************************/

struct Position {
    int x;
    struct list_node node;
};

void TestCase1(void)
{
    int i;
    struct list_node pos_head;
    struct Position *pos = NULL, *n = NULL;

    list_init(&pos_head);
    for (i = 0; i < 10; i++) {
        pos = malloc(sizeof(struct Position));
        pos->x = i;
        list_init(&pos->node);
        list_add_tail(&pos_head, &pos->node);
    }
    list_for_each_entry(pos, &pos_head, struct Position, node) {
        Log("pos: %p, x: %d\n", pos, pos->x);
    }
    list_for_each_entry_safe(pos, n, &pos_head, struct Position, node) {
        list_delete(&pos->node);
        free(pos);
    }
}

int main(void)
{
    TestCase1();
    return 0;
}