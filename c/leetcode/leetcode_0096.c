/*
 * leetcode 96: 不同的二叉搜索树 [中等]
 * 思想：动态规划，当前问题最优解划分为子问题最优解，递归计算子问题直至边界值，
 *      再构造当前问题最优解
 * 1、对于序列1-n，遍历每一个数组i，将i作为根节点，1-(i-1)构建左子树，(i+1)-n构建右子树，
 *    其和即为可构成的二叉搜索树的总数；
 * 2、当根为i时，若左子树种类为m，右子树种类为n，则以i为根能构成的二叉搜索树种类为m * n;
 *    则有：f(n) = f(0)*f(n) + f(1)*f(n-1) + ... + f(n)*f(0)
 * 3、显然：有f(0) = f(1) = 1
 * 2021-10-16
 */
#include "common.h"

/***** 提交代码 ****************************************************************/
int numTrees(int n){
    int i, j;
    int num[20];

    if (n == 0) {
        return 0;
    }
    memset(num, 0, 20 * sizeof(int));
    num[0] = 1;
    num[1] = 1;
    for (i = 2; i <= n; i++) {
        for (j = 1; j <= i; j++) {
            num[i] += num[j - 1] * num[i - j];  //Sigma求和
        }
    }
    return num[n];
}

/***** 本地调试 ****************************************************************/
int main(void)
{
    DebugLog("numTrees(0) = %d(0)\n", numTrees(0));
    DebugLog("numTrees(1) = %d(1)\n", numTrees(1));
    DebugLog("numTrees(2) = %d(2)\n", numTrees(2));
    DebugLog("numTrees(3) = %d(5)\n", numTrees(3));
    DebugLog("numTrees(8) = %d(1430)\n", numTrees(8));
    return 0;
}
