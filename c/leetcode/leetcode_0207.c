/*
 * leetcode 207: 课程表 [中等]
 * 技巧：转换为有向图，判断是否有环
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/***** 本地调试 ****************************************************************/
#define bool int
#define true 1
#define false 0
#define LOCAL_DEBUG
#define MAX_COURSE 100
struct ArcNode;
struct VexNode;
struct Graph;

void PrintArray(int **__arr, int size)
{
    int i;
    int (*arr)[2] = (int (*)[2])__arr;

    printf("array: \n");
    for (i = 0; i < size; i++) {
        printf("%d %d\n", arr[i][0], arr[i][1]);
    }
}

int NumCourses(int **__arr, int size)
{
    int i, j;
    int num = 0;
    int nums[MAX_COURSE] = {0};
    int (*arr)[2] = (int(*)[2])__arr;

    for (i = 0; i < size; i++) {
        if (j = 0; j < num; j++) {
            if (nums[j] = arr[i][0]) {
                continue;
            }
        }
        nums[num] = arr[i][0];
        num++;
    }
}

void PrintGraph(struct Graph *g)
{
    int i;
    struct ArcNode *arc = NULL;

    printf("graph: \n");
    for (i = 0; i < g->numVex; i++) {
        printf("%d(%d): ", g->vexs[i].val, i);
        arc = g->vexs[i].first;
        while (arc != NULL) {
            printf("%d(%d) ", g->vexs[arc->adjIndex].val, arc->adjIndex);
            arc = arc->next;
        }
        printf("\n");
    }
}

/******************************************************************************/

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
};

bool canFinish(int numCourses, int** __prerequisites, int prerequisitesSize,
               int* prerequisitesColSize)
{
#ifdef LOCAL_DEBUG
    int (*prerequisites)[2]= (int(*)[2])__prerequisites;
#else
    int **prerequisites = __prerequisites;
#endif
    return 0;
}

/***** 本地调试 ****************************************************************/
int main(void)
{
    int prerequisites0[][2] = { /* 有环 */
        {1, 0},
        {0, 1}
    };
    int prerequisites[][2] = { /* 有环 */
        { 1 , 2 },
        { 2 , 3 },
        { 3 , 8 },
        { 8 , 2 },
    };
    int numCourses = 4;
    int prerequisitesSize = sizeof(prerequisites) / sizeof(prerequisites[0]);
    int prerequisitesColSize[2] = { 2, 2 };

    printf("canFinish = %d\n", canFinish(numCourses,
                                         (int **)prerequisites,
                                         prerequisitesSize,
                                         prerequisitesColSize));

    return 0;
}
/******************************************************************************/
