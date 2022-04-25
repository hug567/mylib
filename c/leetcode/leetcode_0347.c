/*
 * leetcode 347: 前k个高频元素
 * 思路：计算每个元素出现次数，插入最大堆，删除k次，堆顶组成的数组即是出现频率前k高的元素
 * 2022-04-24
 */
#include "common.h"

/***** 提交代码 ******************************************************************/
struct NumFreq {
    int num;
    int freq;
};

struct Heap {
    struct NumFreq *nf;
    unsigned int size;
    unsigned int maxsize;
};

struct Heap *CreateHeap(unsigned int maxsize)
{
    struct Heap *h = NULL;

    if (maxsize == 0) {
        return NULL;
    }
    h = malloc(sizeof(struct Heap));
    if (h == NULL) {
        return NULL;
    }
    h->nf = malloc(maxsize * sizeof(struct NumFreq));
    if (h->nf == NULL) {
        free(h);
        return NULL;
    }
    memset(h->nf, 0, maxsize * sizeof(maxsize));
    h->size = 0;
    h->maxsize = maxsize;
    return h;
}

void DestroyHeap(struct Heap *h)
{
    if (h == NULL) {
        return;
    }
    if (h->nf != NULL) {
        free(h->nf);
    }
    free(h);
}

void SwapInt(int *a, int *b)
{
    int tmp;

    if (a == NULL || b == NULL) {
        return;
    }
    tmp = *a;
    *a = *b;
    *b = tmp;
}

void HeapInsert(struct Heap *h, int num, int freq)
{
    int cur, parent;

    if (h == NULL || h->nf == NULL || h->size >= h->maxsize) {
        return;
    }
    h->nf[h->size].num = num;
    h->nf[h->size].freq = freq;
    cur = h->size;
    h->size++;
    while (cur > 0) {
        parent = (cur - 1) / 2;
        if (h->nf[cur].freq <= h->nf[parent].freq) {
            break;
        }
        SwapInt(&h->nf[cur].num, &h->nf[parent].num);
        SwapInt(&h->nf[cur].freq, &h->nf[parent].freq);
        cur = parent;
    }
}

int HeapDelete(struct Heap *h)
{
    int num, cur, child;

    if (h == NULL || h->nf == NULL || h->size == 0) {
        return -1;
    }
    num = h->nf[0].num;
    h->size--;
    h->nf[0].num = h->nf[h->size].num;
    h->nf[0].freq = h->nf[h->size].freq;
    cur = 0;
    while (cur < h->size) {
        if (2 * cur + 1 >= h->size) {
            break;
        }
        child = 2 * cur + 1;
        if ((2 * cur + 2 < h->size) &&
            (h->nf[child].freq < h->nf[2 * cur + 2].freq)) {
            child =  2 * cur + 2;
        }
        if (h->nf[cur].freq >= h->nf[child].freq) {
            break;
        }
        SwapInt(&h->nf[cur].num, &h->nf[child].num);
        SwapInt(&h->nf[cur].freq, &h->nf[child].freq);
        cur = child;
    }

    return num;
}

int* topKFrequent(int* nums, int numsSize, int k, int* returnSize)
{
    int i, j, count = 0, exist;
    int *ret = NULL;
    int *arr = NULL;
    int *freq = NULL;
    struct Heap *h = NULL;

    ret = malloc(k * sizeof(int));
    memset(ret, 0, k * sizeof(int));
    arr = malloc(numsSize * sizeof(int));
    memset(arr, 0, numsSize * sizeof(int));
    freq = malloc(numsSize * sizeof(int));
    memset(freq, 0, numsSize * sizeof(int));
    for (i = 0; i < numsSize; i++) {
        exist = 0;
        for (j = 0; j < count; j++) {
            if (arr[j] == nums[i]) {
                freq[j]++;
                exist = 1;
                break;
            }
        }
        if (!exist) {
            arr[count] = nums[i];
            freq[count] = 0;
            count++;
        }
    }
    h = CreateHeap(count);
    for (i = 0; i < count; i++) {
        HeapInsert(h, arr[i], freq[i]);
    }
    for (i = 0; i < k; i++) {
        ret[i] = HeapDelete(h);
    }

    DestroyHeap(h);
    free(arr);
    free(freq);
    *returnSize = k;
    return ret;
}

/***** 本地调试 ******************************************************************/
void TestCase1(void)
{
    int nums[] = {1,1,1,2,2,3};
    int size = ARRAY_SIZE(nums);
    int k = 2;
    int retSize;
    int *ret = topKFrequent(nums, size, k, &retSize);
    PrintArray(ret, retSize);
}

void TestCase2(void)
{
    int nums[] = {1};
    int size = ARRAY_SIZE(nums);
    int k = 1;
    int retSize;
    int *ret = topKFrequent(nums, size, k, &retSize);
    PrintArray(ret, retSize);
}

int main(void)
{
    TestCase1();
    TestCase2();
    return 0;
}