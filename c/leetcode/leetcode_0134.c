/*
 * leetcode 134: 加油站 [中等]
 * 2022-02-14
 */
#include "common.h"

/***** 提交代码 ****************************************************************/
int canCicuit(int *gas, int *cost, int size, int start, int *next)
{
    int flag = 0;
    int left = 0;
    int i = start;

    while ((flag == 0) || ((i % size) != start)) {
        left = left + gas[i] - cost[i];
        if (left < 0) {
            *next = i + 1;
            *next %= size;  //若无法到达，返回第一个无法到达的加油站
            return 0;
        }
        flag = 1;
        i++;
        i %= size;
    }
    return 1;
}

int canCompleteCircuit(int* gas, int gasSize, int* cost, int costSize)
{
    int i, next;

    for (i = 0; i < gasSize;) {
        if (canCicuit(gas, cost, gasSize, i, &next)) {
            return i;
        }
        if (next <= i) { //已遍历超过一圈
            return -1;
        }
        i = next;
    }
    return -1;
}

/***** 提交代码 ****************************************************************/
void TestCase1(void)
{
    int gas[] = { 1, 2, 3, 4, 5 };
    int gasSize = ARRAY_SIZE(gas);
    int cost[] = { 3, 4, 5, 1, 2 };
    int costSize = ARRAY_SIZE(cost);
    Log("start pos: %d(3)\n", canCompleteCircuit(gas, gasSize, cost, costSize));
}

void TestCase2(void)
{
    int gas[] = { 2, 3, 4 };
    int gasSize = ARRAY_SIZE(gas);
    int cost[] = { 3, 4, 3 };
    int costSize = ARRAY_SIZE(cost);
    Log("start pos: %d(-1)\n", canCompleteCircuit(gas, gasSize, cost, costSize));
}

void TestCase3(void)
{
    int gas[] = { 3, 1, 1 };
    int gasSize = ARRAY_SIZE(gas);
    int cost[] = { 1, 2, 2 };
    int costSize = ARRAY_SIZE(cost);
    Log("start pos: %d(0)\n", canCompleteCircuit(gas, gasSize, cost, costSize));
}

void TestCase4(void)
{
    int gas[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    int gasSize = ARRAY_SIZE(gas);
    int cost[] = { 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 };
    int costSize = ARRAY_SIZE(cost);
    Log("start pos: %d(-1)\n", canCompleteCircuit(gas, gasSize, cost, costSize));
}

int main(void)
{
    TestCase1();
    TestCase2();
    TestCase3();
    TestCase4();
    return 0;
}