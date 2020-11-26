/*
 * 练习：有向图，十字链表
 * 2020-11-25
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VEX 100

struct ArcNode {
    int adjIndex;
    struct ArcNode *next;
};

struct VexNode {
    int val;
    struct ArcNode *firstin;
    struct ArcNode *firstot;
};

struct Graph {
    struct VexNode vexs[MAX_VEX];
    int vexNum;
};

int main(void)
{
    return 0;
}