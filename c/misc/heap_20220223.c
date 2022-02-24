/*
 * 练习：堆
 * 2022-02-23
 */
#include "common.h"

#define MAX_LEN 100

struct Heap {
    int len;
    int val[MAX_LEN];
};

void HeapInit(struct Heap *p)
{
    p->len = 0;
}

void MaxHeapInsert(struct Heap *p, int val)
{
    int idx, tmp;

    if (p->len >= MAX_LEN) {
        return;
    }
    p->val[p->len] = val;
    idx = p->len;
    while (idx >= 0) {
        if (p->val[idx] <= p->val[idx / 2]) {
            break;
        }
        tmp = p->val[idx];
        p->val[idx] = p->val[idx / 2];
        p->val[idx / 2] = tmp;
        idx /= 2;
    }
    p->len++;
}

int MaxHeapDelete(struct Heap *p)
{
    int val, idx, tmp;

    if (p->len <= 0) {
        return -1;
    }
    val = p->val[0];
    p->len--;
    p->val[0] = p->val[p->len];
    idx = 0;
    while (idx < p->len) {
        if (2 * idx + 1 < p->len && p->val[idx] < p->val[2 * idx + 1]) {
            tmp = p->val[idx];
            p->val[idx] = p->val[2 * idx + 1];
            p->val[2 * idx + 1] = tmp;
            idx = 2 * idx + 1;
        } else if (2 * idx + 2 < p->len && p->val[idx] < p->val[2 * idx + 2]) {
            tmp = p->val[idx];
            p->val[idx] = p->val[2 * idx + 2];
            p->val[2 * idx + 2] = tmp;
            idx = 2 * idx + 2;
        } else {
            break;
        }
    }
    return val;
}

void MinHeapInsert(struct Heap *p, int val)
{
    int idx, tmp;

    if (p->len >= MAX_LEN) {
        return;
    }
    idx = p->len;
    p->val[idx] = val;
    p->len++;
    while (idx > 0) {
        if (p->val[idx] < p->val[idx / 2]) {
            tmp = p->val[idx];
            p->val[idx] = p->val[idx / 2];
            p->val[idx / 2] = tmp;
        } else {
            break; //当前节点不小于父节点，调整可结束
        }
        idx /= 2;
    }
}

int MinHeapDelete(struct Heap *p)
{
    int val, tmp, idx;

    if (p->len <= 0) {
        return -1;
    }
    p->len--;
    val = p->val[0];
    p->val[0] = p->val[p->len];
    idx = 0;
    while (idx < p->len) {
        if (2 * idx + 1 < p->len && p->val[idx] > p->val[2 * idx + 1]) {
            tmp = p->val[idx];
            p->val[idx] = p->val[2 * idx + 1];
            p->val[2 * idx + 1] = tmp;
            idx = 2 * idx + 1;
        } else if (2 * idx + 2 < p->len && p->val[idx] > p->val[2 * idx + 2]) {
            tmp = p->val[idx];
            p->val[idx] = p->val[2 * idx + 2];
            p->val[2 * idx + 2] = tmp;
            idx = 2 * idx + 2;
        } else {
            break; //当前节点均不大于左右子节点，调整可结束
        }
    }
    return val;
}

void HeapPrint(struct Heap *p)
{
    PrintArray(p->val, p->len);
}

void TestCase1(void)
{
    int i;
    struct Heap p;

    HeapInit(&p);
    for (i = 0; i < 10; i++) {
        MaxHeapInsert(&p, i);
    }
    HeapPrint(&p);
    MaxHeapDelete(&p);
    HeapPrint(&p);
}

void TestCase2(void)
{
    int i;
    struct Heap p;

    HeapInit(&p);
    for (i = 0; i < 10; i++) {
        MinHeapInsert(&p, i);
    }
    HeapPrint(&p);
    MinHeapDelete(&p);
    HeapPrint(&p);
}

int main(void)
{
    TestCase1();
    TestCase2();
    return 0;
}