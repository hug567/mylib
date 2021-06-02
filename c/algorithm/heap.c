/*
 * 堆：使用数组表示的二叉树
 * 下标：i, 从1开始，heap[0]可记录堆节点个数；
 * 左子节点：2 * i
 * 右子节点：2 * i + 1
 * 父节点：i / 2
 * 最大堆：父节点均比左右子节点大；
 * 最小堆：父节点均比左右子节点小；
 * 增加节点：先将节点放在堆尾部，再依次循环与父节点比较换位，直到放在合适位置；
 *          堆是完全二叉树，因此数组存储堆无缝隙，最后一个元素总是堆尾部；
 * 删除节点：删除指定元素，将尾部元素拿到指定点，依次循环与父节点或子节点比较换位，直到放到合适位置；
 *          删除顶点时，将尾部元素拿到顶点，依次循环与子节点比较换位；
 * 打印堆：按二叉树的先、中、后序及层次遍历打印堆节点；
 * 堆常见应用：优先队列、堆排序、求最值；
 * 2021-06-02
 */
#include "common.h"

#define MAX_SIZE 100

/* 最大堆插入元素 */
void MaxHeapInsertNode(int *heap, int val)
{
    int i, tmp;
    if (heap[0] >= MAX_SIZE) {
        return;
    }
    heap[0]++;
    heap[heap[0]] = val;
    i = heap[0];
    while (i > 1 && heap[i] > heap[i / 2]) {
        tmp = heap[i];
        heap[i] = heap[i / 2];
        heap[i / 2] = tmp;
        i /= 2;
    }
}

/* 最大堆删除顶点元素 */
void MaxHeapDeleteTopNode(int *heap)
{}

/* 按二叉树的前序遍历打印堆 */
void __PrintHeapPreOrder(const int *heap, int idx)
{
    if (idx > heap[0]) {
        return;
    }
    printf("%d ", heap[idx]);
    __PrintHeapPreOrder(heap, 2 * idx);
    __PrintHeapPreOrder(heap, 2 * idx + 1);
}

void PrintHeapPreOrder(const int *heap)
{
    DebugLog("pre: ");
    __PrintHeapPreOrder(heap, 1);
    printf("\n");
}

int main(void)
{
    int i;
    int heap[MAX_SIZE] = {0};

    for (i = 0; i < 10; i++) {
        MaxHeapInsertNode(heap, i);
    }
    PrintHeapPreOrder(heap);
    return 0;
}
