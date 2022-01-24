/*
 * 练习：带头节点的有序循环双链表的基本操作
 * 2022-01-23
 */
#include "common.h"

struct Node {
    struct Node *pre;
    struct Node *next;
};

struct IntNode {
    int val;
    struct Node node;
};

#define continer_of(ptr, type, member) \
        ((void *)(ptr) - (size_t)&((type *)0->member))

#define ListEntry(ptr, type, member) \
        continer_of(ptr, type, member)

#define ListEmpty(head) \
        (head->next == head)

#define ListFirstEntry(head, type, member) \
        ListEntry((head)->next, type, member)

#define ListNextEntry(entry, member) \
        ListEntry(entry->member.next, typeof(*(entry)), member)

#define ListForEachEntry(entry, head, member) \
        for (entry = ListFirstEntry(head, typeof(*(entry)), member); \
             &entry->member != head;
             entry = ListNextEntry(entry, member))

void list_node_init(struct Node *n)
{
    n->pre = n;
    n->next = n;
}

void list_insert_next(struct Node *cur, struct Node *new)
{
    new->next = cur->next;
    new->pre = cur;
    cur->next = new;
    new->next->pre = new;
}

void list_insert_head(struct Node *head, struct Node *new)
{
    list_insert_next(head, new);
}

void list_insert_tail(struct Node *head, struct Node *new)
{
    list_insert_next(head->pre, new);
}

struct IntNode *alloc_int_node(int val)
{
    struct IntNode *n = malloc(sizeof(struct IntNode));
    n->val = val;
    list_node_init(&n->node);
    return n;
}


/***** 测试用例 ****************************************************************/
void test_print_list(struct Node *head)
{
    struct Node *n = NULL;
    Log("list: ");
    ListForEachEntry(n, head, node) {
        printf("%d ", n->val);
    }
    printf("\n");
}

int main(void)
{
    int i;
    int arr[] = { 4, 5, 3, 6, 1, 2, 0, 9, 7, 8 };
    int size = ARRAY_SIZR(arr);
    struct Node head;
    struct IntNode *n = NULL, *entry = NULL;

    list_node_init(&head);
    for (i = 0; i < size; i++) {
        n = alloc_int_node(arr[i]);
        ListForEachEntry(entry, head, node) {
            if (entry->val < n->val) {
                list_insert_next(&entry->node->pre, &n->node);
                break;
            }
        }
    }

    return 0;
}