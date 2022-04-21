/*
 * leetcode 215: 数组中的第K个最大元素 [中等]
 * 思路：创建最大堆，做K-1次删除堆顶元素，则此时堆顶为第K大的值
 *      堆：开始索引：0
 *         当前节点：n
 *           左子节点：2*n+1
 *           右子节点：2*n+2
 *           父节点：(n-1)/2
 * 2022-04-19
 */
#include "common.h"

/***** 提交代码 ******************************************************************/
struct MyHeap {
    int *data;
    int size;
    int maxSize;
};

struct MyHeap *HeapAlloc(int size)
{
    struct MyHeap *h = NULL;

    if (size <= 0) {
        return NULL;
    }
    h = malloc(sizeof(struct MyHeap));
    h->data = malloc(size * sizeof(int));
    h->size = 0;
    h->maxSize = size;
    return h;
}

void HeapFree(struct MyHeap *h)
{
    if (h == NULL) {
        return;
    }
    if (h->data != NULL) {
        free(h->data);
    }
    free(h);
}

void HeapInsert(struct MyHeap *h, int val)
{
    int idx, tmp;

    if (h == NULL || h->size == h->maxSize) {
        return;
    }
    idx = h->size;
    h->data[idx] = val;
    h->size++;
    while (idx > 0) {
        if (h->data[idx] > h->data[(idx - 1) / 2]) {
            tmp = h->data[idx];
            h->data[idx] = h->data[(idx - 1) / 2];
            h->data[(idx - 1) / 2] = tmp;
            idx = (idx - 1) / 2;
        } else {
            break;
        }
    }
}

int HeapDeleteRoot(struct MyHeap *h)
{
    int root, idx, tmp, child;

    if (h == NULL || h->size <= 0) {
        return -1;
    }
    root = h->data[0];
    h->size--;
    h->data[0] = h->data[h->size];
    idx = 0;
    /* 删除最大堆堆顶元素，将堆尾元素拿至堆顶，然后调整为最大堆 */
    while (idx < h->size) {
        if (2 * idx + 1 >= h->size) {
            break;
        }
        child = 2 * idx + 1;
        if (2 * idx + 2 < h->size && h->data[child] < h->data[2 * idx + 2]) {
            child = 2 * idx + 2;
        }
        if (h->data[idx] >= h->data[child]) {
            break;
        }
        tmp = h->data[idx];
        h->data[idx] = h->data[child];
        h->data[child] = tmp;
        idx = child;
    }

    return root;
}

int findKthLargest(int* nums, int numsSize, int k)
{
    int i, kth;
    struct MyHeap *h = HeapAlloc(numsSize);

    for (i = 0; i < numsSize; i++) {
        HeapInsert(h, nums[i]);
    }
    for (i = 0; i < k - 1; i++) {
        HeapDeleteRoot(h);
    }
    kth = h->data[0];
    HeapFree(h);
    return kth;
}

/***** 本地调试 ******************************************************************/
void TestCase1(void)
{
    int nums[] = { 3,2,1,5,6,4 };
    int size = ARRAY_SIZE(nums);
    int k = 2;
    Log("Kth largest: %d(5)\n", findKthLargest(nums, size, k));
}

void TestCase2(void)
{
    int nums[] = { 3,2,3,1,2,4,5,5,6 };
    int size = ARRAY_SIZE(nums);
    int k = 4;
    Log("Kth largest: %d(4)\n", findKthLargest(nums, size, k));
}

void TestCase3(void)
{
    int nums[] = { 7, 6, 5, 4, 3, 2, 1 };
    int size = ARRAY_SIZE(nums);
    int k = 5;
    Log("Kth largest: %d(3)\n", findKthLargest(nums, size, k));
}

int main(void)
{
    TestCase1();
    TestCase2();
    TestCase3();
    return 0;
}