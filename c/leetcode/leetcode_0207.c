/*
 * leetcode 207: 课程表 [中等]
 * 技巧：转换为有向图，判断是否有环
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define bool int
#define COL_SIZE 2
#define PRE_REQ_SIZE 2
#define LOCAL_DEBUG
#define MAX_VEX 100 /* 图中存储的最大顶点数 */

struct ArcNode {
    int adjIndex; /* 弧的邻接点在顶点数组中的下标 */
    struct ArcNode *next;
};

struct VexNode {
    int val;
    struct ArcNode *first;
};

struct Graph {
    struct VexNode vexs[MAX_VEX];
    int numVex;
    int numArc;
};

bool canFinish(int numCourses, int** __prerequisites, int prerequisitesSize,
               int* prerequisitesColSize)
{
#ifdef LOCAL_DEBUG
    int (*prerequisites)[COL_SIZE]= (int(*)[COL_SIZE])__prerequisites;
#else
    int **prerequisites = __prerequisites;
#endif
    return 0;
}

int main(void)
{
    int numCourses = 2;
    int prerequisitesSize = PRE_REQ_SIZE;
    int prerequisitesColSize[PRE_REQ_SIZE] = { 2, 2 };
    int prerequisites[PRE_REQ_SIZE][COL_SIZE] = {
        {1, 0},
        {0, 1}
    };

    printf("canFinish = %d\n", canFinish(numCourses,
                                         (int **)prerequisites,
                                         prerequisitesSize,
                                         prerequisitesColSize));

    return 0;
}
